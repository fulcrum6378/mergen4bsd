#define CL_HPP_TARGET_OPENCL_VERSION 300
#define CL_HPP_ENABLE_EXCEPTIONS

#include <iostream>
#include <CL/opencl.hpp> // pkg install opencl

#include "global.hpp"
/*#include "aud/microphone.hpp"
#include "aud/speaker.hpp"
#include "vis/camera.hpp"*/

int main() {
    int exit = 0;

    // construct the low-level components (sensors/controls)
    /*auto *aud = new SoundCard(&exit);
    if (exit != 0) return 10 + exit;
    auto *aud_in = new Microphone(&exit, aud);
    if (exit != 0) return 20 + exit;
    auto *aud_out = new Speaker(&exit, aud);
    if (exit != 0) return 30 + exit;
    auto vis = new Camera(&exit);
    if (exit != 0) return 40 + exit;

    // listen for a stop signal
    on = true;
    print("");
    std::cin.ignore();
    on = false;

    // destruct the low-level components
    delete aud_in;
    delete aud_out;
    delete aud;
    delete vis;*/

    std::vector<cl::Platform> allPlatforms;
    cl::Platform::get(&allPlatforms);
    print("Size: %zu", allPlatforms.size());

    return exit;
}
