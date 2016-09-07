//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORSHAFTPOWER_H
#define AMO_LIBRARY_MOTORSHAFTPOWER_H

#include <cmath>
#include<iostream>
#include "../motor.h"

class MotorShaftPower {
public:

    MotorShaftPower(//double motorEfficiency,
            double motorRatedPower, double motorMeasuredPower, int motorRPM, Motor::EfficiencyClass efficiencyClass)
            : //motorEfficiency_(motorEfficiency),
            motorMeasuredPower_(motorMeasuredPower),
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM), efficiencyClass_(efficiencyClass) {};

    double calculate();

    /*
    double getMotorEfficiency() const {
        return motorEfficiency_;
    }

    void setMotorEfficiency(double motorEfficiency) {
        motorEfficiency_ = motorEfficiency;
    }

    double getMotorPower() const {
        return motorRatedPower_;
    }

    void setMotorPower(double motorPower) {
        motorRatedPower_ = motorPower;
    }
    */
private:
    //double motorEfficiency_;
    double motorRatedPower_;
    double motorMeasuredPower_;
    int motorRPM_;
    Motor::EfficiencyClass efficiencyClass_;
    double motorShaftPower_;
};


#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
