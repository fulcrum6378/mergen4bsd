#ifndef AUD_SPEAKER_H
#define AUD_SPEAKER_H

#include "sound_card.hpp"

class Speaker {
public:
    Speaker(int *exit, SoundCard *aud);

    ~Speaker();

private:
    SoundCard *aud_;
};


#endif //AUD_SPEAKER_H
