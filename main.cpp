#include <fcntl.h> // open, O_RDWR
#include <iostream> // std::cin
#include <unistd.h> // close

#include "global.hpp"
#include "aud/microphone.hpp"
#include "aud/speaker.hpp"
#include "hpt/touchpad.hpp"
#include "vis/camera.hpp"

int main() {
    int exit = 0;

    // open the required devices
    int dev_aud = open("/dev/dsp0.0", O_RDWR);
    if (exit != 0) return 1;

    // construct the low-level components (sensors/controls)
    auto *aud_in = new Microphone(&exit, &dev_aud);
    if (exit != 0) return 10 + exit;
    auto *aud_out = new Speaker(&exit, &dev_aud);
    if (exit != 0) return 20 + exit;
    auto *hpt = new Touchpad(&exit);
    if (exit != 0) return 30 + exit;
    auto vis = new Camera(&exit);
    if (exit != 0) return 40 + exit;

    // listen for a stop signal
    print("");
    std::cin.ignore();
    on = false;

    // destruct the low-level components
    delete aud_in;
    delete aud_out;
    delete hpt;
    delete vis;

    // close the required devices
    close(dev_aud);

    return 0;
}
