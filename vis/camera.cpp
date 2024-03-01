#include <cstring>
#include <errno.h> // errno for ioctl: https://en.wikipedia.org/wiki/Errno.h#GLIBC_macros
#include <fcntl.h> // O_RDWR (oflag)
#include <iostream> // perror
#include <sys/ioctl.h>
#include <sys/mman.h> // PROT_READ, PROT_WRITE, MAP_SHARED
#include <unistd.h> // close

#include "../global.hpp"
#include "camera.hpp"

using namespace std;

Camera::Camera(int *exit) {
    // open first camera device and check its capabilities
    if ((dev = open("/dev/video0", O_RDWR)) == -1) {
        perror("Failed to open camera");
        *exit = 1;
        return;
    }
    v4l2_capability capability{};
    if (ioctl(dev, VIDIOC_QUERYCAP, &capability) == -1) {
        perror("This camera cannot capture frames");
        *exit = 2;
        return;
    }

    // set `v4l2_format` on camera
    imageFormat.fmt.pix.width = W;
    imageFormat.fmt.pix.height = H;
    imageFormat.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    imageFormat.fmt.pix.field = V4L2_FIELD_NONE;
    if (ioctl(dev, VIDIOC_S_FMT, &imageFormat) == -1) {
        print("Camera could not set format: %d", errno);
        *exit = 3;
        return;
    }

    // allocate a buffer
    v4l2_requestbuffers reqBuf{1u, buf_info.type, buf_info.memory};
    if (ioctl(dev, VIDIOC_REQBUFS, &reqBuf) == -1) {
        print("Couldn't request buffer from camera: %d", errno);
        *exit = 4;
        return;
    }

    // the device supports video capture.
    //print("Query: %u", (reqBuf.capabilities & V4L2_BUF_CAP_SUPPORTS_MMAP) >> 0); // => 1
    //print("%u", reqBuf.count); => 1

    // retrieve data on the allocated buffer (must necessarily be separate from `buf_info`)
    v4l2_buffer queryBuf{.index=buf_info.index, .type=buf_info.type, .field=buf_info.field, .memory=buf_info.memory};
    //ioctl(dev, VIDIOC_QUERYBUF, &queryBuf);
    if (ioctl(dev, VIDIOC_QUERYBUF, &queryBuf) == -1) {
        print("Camera didn't return the buffer information: %d", errno);
        *exit = 5;
        return;
    }

    // map and clean the buffer
    buf = (unsigned char *) mmap(
            nullptr, queryBuf.length, PROT_READ | PROT_WRITE, MAP_SHARED,
            dev, queryBuf.m.offset);
    memset(buf, 0, queryBuf.length);

    // start streaming using `buf_info`
    if (ioctl(dev, VIDIOC_STREAMON, &buf_info.type) == -1) {
        print("Camera couldn't start streaming: %d", errno);
        *exit = 6;
        return;
    }

    // prepare for analysis and start recording
    segmentation = new Segmentation(&buf);
    recFuture = recPromise.get_future();
    record = std::thread(&Camera::Record, this);
    record.detach();
}

void Camera::Record() {
    while (on) {
        ioctl(dev, VIDIOC_QBUF, &buf_info);
        ioctl(dev, VIDIOC_DQBUF, &buf_info);

        segmentation->bufLength = buf_info.bytesused;
        segmentation->Process();
    }
#if VISUAL_STM
    // if recording is over, save state of VisualSTM
    segmentation->stm->SaveState();
#endif
    recPromise.set_value();
}

Camera::~Camera() {
    recFuture.wait();
    delete segmentation;
    ioctl(dev, VIDIOC_STREAMOFF, &buf_info.bytesused);
    close(dev);
}
