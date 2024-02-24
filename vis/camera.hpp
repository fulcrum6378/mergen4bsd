#ifndef VIS_CAMERA_H
#define VIS_CAMERA_H

#include <future>
#include <thread>

#include "segmentation.hpp"
#include "videodev2.hpp"

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
     *
     * My laptop (Dell XPS L502X) and my old laptop ():
     *     'YUYV' (4:2:2), 640/480
     */
    v4l2_format imageFormat{};
    v4l2_buffer buffer_info{};
    unsigned char *buf;

    std::thread record;
    std::promise<void> recPromise;
    std::future<void> recFuture;
    Segmentation *segmentation;
};

#endif //VIS_CAMERA_H
