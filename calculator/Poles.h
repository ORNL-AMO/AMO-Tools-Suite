//
// Created by Mishra, Subhankar on 10/3/16.
//

#ifndef AMO_LIBRARY_POLES_H
#define AMO_LIBRARY_POLES_H


class Poles {
public:
    Poles(int motorRpm, int lineFreq) : motorRpm_(motorRpm), lineFreq_(lineFreq) {};

    int calculate();

private:
    int motorRpm_;
    int lineFreq_;
    int poles_;
};


#endif //AMO_LIBRARY_POLES_H
