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
    double tempLoadFraction_ = 0.01;
    double power = 0.0, powerE1 = 0.0, powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;
    MotorShaftPower(//double motorEfficiency,
            double motorRatedPower, double motorMeasuredPower, int motorRPM, Motor::EfficiencyClass efficiencyClass,
            double ratedVoltage, double fieldVoltage)
            : //motorEfficiency_(motorEfficiency),
            motorMeasuredPower_(motorMeasuredPower),
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM), efficiencyClass_(efficiencyClass),
            ratedVoltage_(ratedVoltage), fieldVoltage_(fieldVoltage) {};

    double calculate();

    double calculateCurrent();

    double calculateEfficiency();

    double calculatePowerFactor();

    double calculateElectricPower();

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
    double motorRatedPower_ = 0.0;
    double motorMeasuredPower_ = 0.0;
    int motorRPM_ = 0;
    double ratedVoltage_ = 0.0;
    double fieldVoltage_ = 0.0;
    Motor::EfficiencyClass efficiencyClass_;
    double motorShaftPower_ = 0.0;
};

#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
