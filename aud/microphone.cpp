#include <iostream> // perror
#include <sys/ioctl.h>
#include <unistd.h>

#include "../global.hpp"
#include "microphone.hpp"

Microphone::Microphone(int *exit, int *aud) : aud_(aud) {
    // set audio format
    int tmp = AUD_IN_FORMAT;
    if (ioctl(*aud_, SNDCTL_DSP_SETFMT, &tmp) == -1) {
        perror("Couldn't set audio format");
        *exit = 2;
        return;
    }
    if (tmp != AUD_IN_FORMAT) {
        perror("This device doesn't support this audio format");
        *exit = 3;
        return;
    }

    // set audio channels
    tmp = AUD_IN_CHANNELS;
    if (ioctl(*aud_, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
        perror("Couldn't set audio channels");
        *exit = 4;
        return;
    }
    if (tmp != AUD_IN_CHANNELS) {
        perror("This device doesn't support this number of channels");
        *exit = 5;
        return;
    }

    // set sample rate
    tmp = AUD_IN_SAMPLE_RATE;
    if (ioctl(*aud_, SNDCTL_DSP_SPEED, &tmp) == -1) {
        perror("Couldn't set sample rate (speed)");
        *exit = 6;
        return;
    }
    if (tmp != AUD_IN_SAMPLE_RATE) {
        perror("This device doesn't support this sample rate");
        *exit = 7;
        return;
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
        if ((bytes = read(*aud_, buffer, sizeof(buffer))) == -1) {
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
}
