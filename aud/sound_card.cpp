#include <fcntl.h> // open, O_RDWR
#include <iostream> // perror
#include <sys/ioctl.h>
#include <unistd.h> // close

#include "sound_card.hpp"

SoundCard::SoundCard(int *exit) {
    // open the device
    if ((dev = open("/dev/dsp0.0", O_RDWR)) == -1) {
        perror("Failed to open the sound device");
        *exit = 1;
        return;
    }

    // set audio format
    int tmp = AUD_FORMAT;
    if (ioctl(dev, SNDCTL_DSP_SETFMT, &tmp) == -1) {
        perror("Couldn't set audio format");
        *exit = 2;
        return;
    }
    if (tmp != AUD_FORMAT) {
        perror("This device doesn't support this audio format");
        *exit = 3;
        return;
    }

    // set audio channels
    tmp = AUD_CHANNELS;
    if (ioctl(dev, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
        perror("Couldn't set audio channels");
        *exit = 4;
        return;
    }
    if (tmp != AUD_CHANNELS) {
        perror("This device doesn't support this number of channels");
        *exit = 5;
        return;
    }

    // set sample rate
    tmp = AUD_SAMPLE_RATE;
    if (ioctl(dev, SNDCTL_DSP_SPEED, &tmp) == -1) {
        perror("Couldn't set sample rate (speed)");
        *exit = 6;
        return;
    }
    if (tmp != AUD_SAMPLE_RATE) {
        perror("This device doesn't support this sample rate");
        *exit = 7;
        return;
    }

    // get block size
    if (ioctl(dev, SNDCTL_DSP_GETBLKSIZE, &blk_size) == -1) {
        perror("Couldn't get the block size");
        *exit = 8;
        return;
    }
}

SoundCard::~SoundCard() {
    close(dev);
}
