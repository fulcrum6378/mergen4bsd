//#include <iostream> // perror
//#include <sys/ioctl.h>
#include <unistd.h>

#include "../global.hpp"
#include "speaker.hpp"

static short sinebuf[48] = {
        0, 4276, 8480, 12539, 16383, 19947, 23169, 25995,
        28377, 30272, 31650, 32486, 32767, 32486, 31650, 30272,
        28377, 25995, 23169, 19947, 16383, 12539, 8480, 4276,
        0, -4276, -8480, -12539, -16383, -19947, -23169, -25995,
        -28377, -30272, -31650, -32486, -32767, -32486, -31650, -30272,
        -28377, -25995, -23169, -19947, -16383, -12539, -8480, -4276
};

int phase = 0, freq = 500000;

Speaker::Speaker(int *exit, int *aud) : aud_(aud) {
    // set audio format
    int tmp/* = AUD_OUT_FORMAT*/;
    /*if (ioctl(*aud_, SNDCTL_DSP_SETFMT, &tmp) == -1) {
        perror("Couldn't set audio format");
        *exit = 2;
        return;
    }
    if (tmp != AUD_OUT_FORMAT) {
        perror("This device doesn't support this audio format");
        *exit = 3;
        return;
    }

    // set audio channels
    tmp = AUD_OUT_CHANNELS;
    if (ioctl(*aud_, SNDCTL_DSP_CHANNELS, &tmp) == -1) {
        perror("Couldn't set audio channels");
        *exit = 4;
        return;
    }
    if (tmp != AUD_OUT_CHANNELS) {
        perror("This device doesn't support this number of channels");
        *exit = 5;
        return;
    }

    // set sample rate
    tmp = AUD_OUT_SAMPLE_RATE;
    if (ioctl(*aud_, SNDCTL_DSP_SPEED, &tmp) == -1) {
        perror("Couldn't set sample rate (speed)");
        *exit = 6;
        return;
    }
    if (tmp != AUD_OUT_SAMPLE_RATE) {
        perror("This device doesn't support this sample rate");
        *exit = 7;
        return;
    }*/
    ioctl (*aud_, SNDCTL_DSP_GETBLKSIZE, &tmp);

    while (on) {
        short buf[4096], *p = buf;
        int c, i, n, v, x;

        for (i = 0; i < tmp; i++) {
            x = (phase + 1000000 / 2) / 1000000;
            if (x < 0) x = 0;
            v = sinebuf[x % 48] / 4;

            phase = phase + freq * 480 / AUD_OUT_SAMPLE_RATE;

            if (freq > 1000)
                freq -= 3 * 480 / AUD_OUT_SAMPLE_RATE;
            else
                freq -= 1;

            for (c = 0; c < AUD_OUT_CHANNELS; c++)
                *p++ = v;

            if (freq <= 0)
                break;
        }

        write(*aud_, buf, i * 2 * AUD_OUT_CHANNELS);
    }
}

Speaker::~Speaker() {
}
