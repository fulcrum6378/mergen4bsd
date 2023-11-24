#ifndef AUD_SPEAKER_H
#define AUD_SPEAKER_H

#define AUD_OUT_FORMAT AFMT_S16_NE
#define AUD_OUT_CHANNELS 1
#define AUD_OUT_SAMPLE_RATE 44100

class Speaker {
public:
    explicit Speaker(int *exit);

    ~Speaker();

private:
    int dev;
};


#endif //AUD_SPEAKER_H
