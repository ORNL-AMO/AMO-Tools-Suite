//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORCURRENT_H
#define AMO_LIBRARY_MOTORCURRENT_H


#include <cmath>
#include<iostream>
#include "../motor.h"

class MotorCurrent {
public:
    //MotorCurrent(double motorAmps, double motorKw, double voltage) : motorAmps_(motorAmps), motorKw_(motorKw),voltage_(voltage) {}
    MotorCurrent(double motorRatedPower, double motorMeasuredPower, int motorRPM,
                 Motor::EfficiencyClass efficiencyClass) : motorMeasuredPower_(motorMeasuredPower),
                                                           motorRatedPower_(motorRatedPower), motorRPM_(motorRPM),
                                                           efficiencyClass_(efficiencyClass) {};
    double calculate();

/*    double getMotorAmps() const {
        return motorAmps_;
    }

    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    double getMotorKw() const {
        return motorKw_;
    }

    void setMotorKw(double motorKw) {
        motorKw_ = motorKw;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }*/

private:
    /* Commented for now
    double motorAmps_;
    double motorKw_;
    double voltage_;
     */
    double motorRatedPower_;
    double motorMeasuredPower_;
    int motorRPM_;
    Motor::EfficiencyClass efficiencyClass_;
    double motorCurrent_;
};


#endif //AMO_LIBRARY_MOTORCURRENT_H
