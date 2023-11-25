#ifndef AUD_MICROPHONE_H
#define AUD_MICROPHONE_H

#include <fstream>
#include <future>
#include <thread>

#include "sound_card.hpp"

class Microphone {
public:
    Microphone(int *exit, SoundCard *aud);

    ~Microphone();

private:
    void Record();


    SoundCard *aud_;

    std::thread record;
    std::promise<void> recPromise;
    std::future<void> recFuture;
    std::ofstream *testPcm;
};

#endif //AUD_MICROPHONE_H
