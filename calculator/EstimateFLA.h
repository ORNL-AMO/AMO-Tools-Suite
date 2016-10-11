//
// Created by Mishra, Subhankar on 10/4/16.
//

#ifndef UNTITLED_ESTIMATEFLA_H
#define UNTITLED_ESTIMATEFLA_H

#include "../Motor.h"
#include "MotorEfficiency.h"
#include<iostream>
class EstimateFLA {
public:
    EstimateFLA(double motorRatedPower, int motorRPM, Motor::LineFrequency lineFrequency, Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double ratedVoltage) :
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM), lineFrequency_(lineFrequency), efficiencyClass_(efficiencyClass), specifiedEfficiency_(specifiedEfficiency),
            ratedVoltage_(ratedVoltage) {};

    // Returns the 25% interval arrays.
    double *calculate();

    // Returns the estimated 25% interval values
    double getEstimatedFLA() {
        return estimatedFLA_;
    }

private:
    double estimatedFLA_;
    double plValues[6] = {};
    double motorRatedPower_ = 0.0;
    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_ =0.0;
    double ratedVoltage_ =0.0;
};


#endif //UNTITLED_ESTIMATEFLA_H
