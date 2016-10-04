//
// Created by Mishra, Subhankar on 10/3/16.
//

#ifndef UNTITLED_POLECALCULATE_H
#define UNTITLED_POLECALCULATE_H

#include "../Motor.h"

class Poles {
public:
    Poles(int motorRpm, Motor::LineFrequency lineFreq): motorRpm_(motorRpm), lineFreq_(lineFreq){};
    int calculate();
private:
    int motorRpm_;
    Motor::LineFrequency lineFreq_;
    int poles_;
};


#endif //UNTITLED_POLECALCULATE_H
