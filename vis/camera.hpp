#ifndef VIS_CAMERA_H
#define VIS_CAMERA_H

#include <future>
#include <linux/videodev2.h> // $ pkg install v4l_compat
#include <thread>

#include "segmentation.hpp"

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
	 *
     * $ v4l2-ctl --list-formats
     *     [0]: 'YUYV' (YUYV 4:2:2)
     * 	   [1]: 'MJPG' (Motion-JPEG, compressed)
	 *
	 * $ v4l2-ctl --list-framesizes 0
	 *     Size: Discrete 640x480
	 *     ...
     */
    v4l2_format imageFormat{V4L2_BUF_TYPE_VIDEO_CAPTURE};
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
    Segmentation *segmentation;
};

#endif //VIS_CAMERA_H
