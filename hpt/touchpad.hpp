#ifndef HPT_TOUCHPAD_H
#define HPT_TOUCHPAD_H

class Touchpad {
public:
    explicit Touchpad(int *exit);

    ~Touchpad();

private:
    int dev;
};

#endif //HPT_TOUCHPAD_H
