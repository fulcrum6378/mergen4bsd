#ifndef AUD_MICROPHONE_H
#define AUD_MICROPHONE_H

#include <future>
#include <sys/soundcard.h> // Open Sound System
#include <thread>

#define AUD_IN_FORMAT AFMT_S16_NE
#define AUD_IN_CHANNELS 1
#define AUD_IN_SAMPLE_RATE 44100

class Microphone {
public:
    explicit Microphone(int *exit);

    ~Microphone();

private:
    void Record();


    int dev;

    std::thread record;
    std::promise<void> recPromise;
    std::future<void> recFuture;
};

#endif //AUD_MICROPHONE_H
