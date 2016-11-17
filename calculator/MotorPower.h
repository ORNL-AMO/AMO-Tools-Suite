//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORPOWER_H
#define AMO_LIBRARY_MOTORPOWER_H

#include <cmath>

class MotorPower {
public:
    MotorPower(double ratedVoltage, double motorCurrent, double powerFactor) :
            ratedVoltage_(ratedVoltage), motorCurrent_(motorCurrent), powerFactor_(powerFactor) {};

    double calculate();

private:
    double ratedVoltage_;
    double motorCurrent_;
    double powerFactor_;
};


#endif //AMO_LIBRARY_MOTORPOWER_H
