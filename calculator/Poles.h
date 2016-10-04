//
// Created by Mishra, Subhankar on 10/3/16.
//

#ifndef UNTITLED_POLECALCULATE_H
#define UNTITLED_POLECALCULATE_H


class Poles {
public:
    Poles(int motorRpm, int lineFreq) : motorRpm_(motorRpm), lineFreq_(lineFreq) {};
    int calculate();
private:
    int motorRpm_;
    int lineFreq_;
    int poles_;
};


#endif //UNTITLED_POLECALCULATE_H
