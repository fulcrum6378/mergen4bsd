#include <fcntl.h> // O_RDWR (oflag)
#include <iostream> // perror
#include <sys/ioctl.h>
#include <sys/soundcard.h> // Open Sound System
#include <unistd.h> // close

#include "../global.hpp"
#include "speaker.hpp"

Speaker::Speaker(int *exit) {
    dev = open("/dev/dsp0.0", O_RDWR);
    if (dev < 0) {
        perror("Failed to open device");
        *exit = 1;
        return;
    }
    int ver;
    ioctl(dev, OSS_GETVERSION, &ver);
    print("OSS Version: %d", ver);
}

Speaker::~Speaker() {
    close(dev);
}
