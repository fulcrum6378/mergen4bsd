#include <fcntl.h> // O_RDONLY (oflag)
#include <iostream> // perror
#include <sys/ioctl.h>
#include <unistd.h> // close

#include "../global.hpp"
#include "microphone.hpp"

Microphone::Microphone(int *exit) {
    // open device
    if ((dev = open("/dev/dsp0.0", O_RDONLY)) == -1) {
        perror("Failed to open device");
        *exit = 1;
        return;
    }

    // set audio format
    int tmp = AUD_IN_FORMAT;
    if (ioctl(dev, SNDCTL_DSP_SETFMT, &tmp) == -1) {
        perror("Couldn't set audio format");
        *exit = 2;
    }
    if (tmp != AUD_IN_FORMAT) {
        perror("This device doesn't support this audio format");
        *exit = 3;
    }

    // set audio channels
    tmp = AUD_IN_CHANNELS;
    if (ioctl(dev, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
        perror("Couldn't set audio channels");
        *exit = 4;
    }
    if (tmp != AUD_IN_CHANNELS) {
        perror("This device doesn't support this number of channels");
        *exit = 5;
    }

    // set sample rate
    tmp = AUD_IN_SAMPLE_RATE;
    if (ioctl(dev, SNDCTL_DSP_SPEED, &tmp) == -1) {
        perror("Couldn't set sample rate (speed)");
        *exit = 6;
    }
    if (tmp != AUD_IN_SAMPLE_RATE) {
        perror("This device doesn't support this sample rate");
        *exit = 7;
    }

    // start recording
    recFuture = recPromise.get_future();
    record = std::thread(&Microphone::Record, this);
    record.detach();
}

void Microphone::Record() {
    while (on) {
        short buffer[1024];
        int bytes;
        if ((bytes = read(dev, buffer, sizeof(buffer))) == -1) {
            perror("Couldn't read the next audio buffer");
            break;
        }
        print("%d bytes read.", bytes);
    }
    recPromise.set_value();
}

// TODO USE ELSEWHERE: if (v < 0) v = -v;/* abs */

Microphone::~Microphone() {
    recFuture.wait();
    close(dev);
}
