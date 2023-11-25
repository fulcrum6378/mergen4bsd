#ifndef AUD_SOUND_CARD_H
#define AUD_SOUND_CARD_H

#include <sys/soundcard.h> // Open Sound System

#define AUD_FORMAT AFMT_S16_NE
#define AUD_CHANNELS 1
#define AUD_SAMPLE_RATE 44100

class SoundCard {
public:
    explicit SoundCard(int *exit);

    ~SoundCard();


    int dev, blk_size;
};

#endif //AUD_SOUND_CARD_H
