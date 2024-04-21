#ifndef VIS_CAMERA_H
#define VIS_CAMERA_H

#include <future>
#include <linux/videodev2.h> // $ pkg install v4l_compat
#include <thread>

// image processing method: 1 => Segmentation, 2 => EdgeDetection.
#define VIS_METHOD 1

#if VIS_METHOD == 1

#include "segmentation.hpp"

#elif VIS_METHOD == 2

#include "edge_detection.hpp"

#endif

class Camera {
public:
    explicit Camera(int *exit);

    ~Camera();

private:
    void Record();


    int dev;
    /**
     * Install V4L utilities for gathering information about your system.
     * $ pkg install v4l-utils
	 * $ v4l2-ctl --all
     * ...
	 * Format Video Capture:
	 *     Width/Height      : 640/480
     *     Pixel Format      : 'YUYV' (YUYV 4:2:2)
     *     Field             : None
     *     Bytes per Line    : 1280
     *     Size Image        : 614400
     * ...
     */
    v4l2_format imageFormat{
            V4L2_BUF_TYPE_VIDEO_CAPTURE, {W, H, V4L2_PIX_FMT_YUYV, V4L2_FIELD_NONE}
    };
    v4l2_buffer buf_info{
            .index = 0u,
            .type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
            .field = V4L2_FIELD_NONE,
            .memory = V4L2_MEMORY_MMAP
    };
    unsigned char *buf;

    std::thread record;
    std::promise<void> recPromise;
    std::future<void> recFuture;
#if VIS_METHOD == 1
    Segmentation *segmentation;
#elif VIS_METHOD == 2
    EdgeDetection *edgeDetection;
#endif
};

#endif //VIS_CAMERA_H
