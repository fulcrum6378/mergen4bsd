#ifndef AUD_SPEAKER_H
#define AUD_SPEAKER_H

#include <sys/soundcard.h> // Open Sound System

#define AUD_OUT_FORMAT AFMT_S16_NE
#define AUD_OUT_CHANNELS 1
#define AUD_OUT_SAMPLE_RATE 44100

class Speaker {
public:
    Speaker(int *exit, int *aud);

    ~Speaker();

private:
    int *aud_;
};


#endif //AUD_SPEAKER_H
