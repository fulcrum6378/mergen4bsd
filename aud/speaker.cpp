#include <unistd.h> // write

#include "speaker.hpp"

Speaker::Speaker(int */*exit*/, SoundCard *aud) : aud_(aud) {
    short sineBuf[48] = {
            0, 4276, 8480, 12539, 16383, 19947, 23169, 25995,
            28377, 30272, 31650, 32486, 32767, 32486, 31650, 30272,
            28377, 25995, 23169, 19947, 16383, 12539, 8480, 4276,
            0, -4276, -8480, -12539, -16383, -19947, -23169, -25995,
            -28377, -30272, -31650, -32486, -32767, -32486, -31650, -30272,
            -28377, -25995, -23169, -19947, -16383, -12539, -8480, -4276
    };
    int phase = 0, freq = 500000, time = 100;
    while (time > 0) { // executes in and blocks the main thread!
        short buf[4096], *p = buf;
        int c, i, v, x;
        for (i = 0; i < aud_->blk_size; i++) {
            x = (phase + 1000000 / 2) / 1000000;
            if (x < 0) x = 0;
            v = sineBuf[x % 48] / 4;
            phase = phase + freq * 480 / AUD_SAMPLE_RATE;
            if (freq > 1000)freq -= 3 * 480 / AUD_SAMPLE_RATE;
            else freq -= 1;
            for (c = 0; c < AUD_CHANNELS; c++)*p++ = v;
            if (freq <= 0)break;
        }
        write(aud_->dev, buf, i * 2 * AUD_CHANNELS);
        time--;
    }
}

Speaker::~Speaker() {
}
