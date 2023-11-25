/*#include <fcntl.h> // O_RDWR (oflag)
#include <iostream> // perror
#include <sys/ioctl.h>
#include <sys/mouse.h> // mouse and pointing device drivers
#include <unistd.h> // close

#include "../global.hpp"*/
#include "touchpad.hpp"

Touchpad::Touchpad(int */*exit*/) {
    /*aud_ = open("/dev/psm0", O_RDWR);
    if (aud_ < 0) {
        perror("Failed to open device");
        *exit = 1;
        return;
    }
    int ver;
    mousehw_t hwInfo;
    ioctl(aud_, MOUSE_GETHWINFO, &hwInfo);
    print("Number of buttons: %d", hwInfo.buttons);*/
}

Touchpad::~Touchpad() {
    //close(aud_);
}
