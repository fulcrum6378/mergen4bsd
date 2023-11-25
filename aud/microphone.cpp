#include <ios>
#include <iostream> // perror
#include <unistd.h> // read

#include "../global.hpp"
#include "microphone.hpp"

Microphone::Microphone(int */*exit*/, SoundCard *aud) : aud_(aud) {
    // save PCM data in a test file
    testPcm = new std::ofstream("aud/test.pcm", std::ios::binary);

    // start recording
    recFuture = recPromise.get_future();
    record = std::thread(&Microphone::Record, this);
    record.detach();
}

void Microphone::Record() {
    while (on) {
        short buffer[1024];
        int bytes;
        if ((bytes = read(aud_->dev, buffer, sizeof(buffer))) == -1) {
            perror("Couldn't read the next audio buffer");
            break;
        }
        testPcm->write(reinterpret_cast<char *>(buffer), bytes);
    }
    recPromise.set_value();
}

// TODO USE ELSEWHERE: if (v < 0) v = -v;/* abs */

Microphone::~Microphone() {
    recFuture.wait();
    testPcm->close();
    delete testPcm;
}
