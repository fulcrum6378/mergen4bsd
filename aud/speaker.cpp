#include <fcntl.h> // O_WRONLY (oflag)
#include <iostream> // perror
#include <sys/ioctl.h>
#include <sys/soundcard.h> // Open Sound System
#include <unistd.h> // close

#include "speaker.hpp"

Speaker::Speaker(int *exit) {
    // open device
    if ((dev = open("/dev/dsp0.0", O_WRONLY)) == -1) {
        perror("Failed to open device");
        *exit = 1;
        return;
    }

    // set audio format
    int tmp = AUD_OUT_FORMAT;
    if (ioctl(dev, SNDCTL_DSP_SETFMT, &tmp) == -1) {
        perror("Couldn't set audio format");
        *exit = 2;
    }
    if (tmp != AUD_OUT_FORMAT) {
        perror("This device doesn't support this audio format");
        *exit = 3;
    }

    // set audio channels
    tmp = AUD_OUT_CHANNELS;
    if (ioctl(dev, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
        perror("Couldn't set audio channels");
        *exit = 4;
    }
    if (tmp != AUD_OUT_CHANNELS) {
        perror("This device doesn't support this number of channels");
        *exit = 5;
    }

    // set sample rate
    tmp = AUD_OUT_SAMPLE_RATE;
    if (ioctl(dev, SNDCTL_DSP_SPEED, &tmp) == -1) {
        perror("Couldn't set sample rate (speed)");
        *exit = 6;
    }
    if (tmp != AUD_OUT_SAMPLE_RATE) {
        perror("This device doesn't support this sample rate");
        *exit = 7;
    }
}

Speaker::~Speaker() {
    close(dev);
}
