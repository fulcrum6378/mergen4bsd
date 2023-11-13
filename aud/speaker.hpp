#ifndef AUD_SPEAKER_H
#define AUD_SPEAKER_H

class Speaker {
public:
    explicit Speaker(int *exit);

    ~Speaker();

private:
    int dev;
};


#endif //AUD_SPEAKER_H
