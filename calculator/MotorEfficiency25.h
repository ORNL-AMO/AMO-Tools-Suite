//
// Created by Mishra, Subhankar on 10/6/16.
//

#ifndef UNTITLED_MOTOREFFICIENCY25_H
#define UNTITLED_MOTOREFFICIENCY25_H

#include "../Motor.h"

class MotorEfficiency25 {
public:
    MotorEfficiency25(Motor::EfficiencyClass efficiencyClass, double motorRatedPower):efficiencyClass_(efficiencyClass), motorRatedPower_(motorRatedPower){};
    double *calculate();
private:
    Motor::EfficiencyClass efficiencyClass_;
    double motorRatedPower_;
    double motorEfficiency_[5] = {};
};


#endif //UNTITLED_MOTOREFFICIENCY25_H
