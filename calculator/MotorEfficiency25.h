//
// Created by Mishra, Subhankar on 10/6/16.
//

#ifndef UNTITLED_MOTOREFFICIENCY25_H
#define UNTITLED_MOTOREFFICIENCY25_H

#include "../Motor.h"
#include <vector>
#include "Poles.h"

class MotorEfficiency25 {
public:
    MotorEfficiency25(Motor::EfficiencyClass efficiencyClass, double motorRatedPower, double motorRpm,
                      Motor::LineFrequency lineFrequency) : efficiencyClass_(efficiencyClass),
                                                            motorRatedPower_(motorRatedPower), motorRpm_(motorRpm),
                                                            lineFrequency_(lineFrequency) {};

    std::vector<double> calculate();

private:
    Motor::EfficiencyClass efficiencyClass_;
    double motorRatedPower_;
    double motorRpm_;
    Motor::LineFrequency lineFrequency_;

    //double motorEfficiency_[5] = {};
};


#endif //UNTITLED_MOTOREFFICIENCY25_H
