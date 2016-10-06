//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORCURRENT_H
#define AMO_LIBRARY_MOTORCURRENT_H


#include <cmath>
#include<iostream>
#include "../motor.h"
#include "CurveFitVal.h"
#include "EstimateFLA.h"

class MotorCurrent {
public:
    //MotorCurrent(double motorAmps, double motorKw, double voltage) : motorAmps_(motorAmps), motorKw_(motorKw),voltage_(voltage) {}
    MotorCurrent(double motorRatedPower, int motorRPM,
                 Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double loadFactor , double ratedVoltage, double fullLoadAmps) :
                                                                              motorRatedPower_(motorRatedPower), motorRPM_(motorRPM),
                                                                              efficiencyClass_(efficiencyClass),
                                                                              specifiedEfficiency_(specifiedEfficiency),
                                                                              loadFactor_(loadFactor), ratedVoltage_(ratedVoltage),
                                                                              fullLoadAmps_(fullLoadAmps){};
    double calculate();

    double getEstimatedFLA(){
        return estimatedFLA_;
    }

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
    double motorRatedPower_ = 0.0;

    int motorRPM_ = 0;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_ =0.0;
    double loadFactor_ = 0.0;
    double motorCurrent_ = 0.0;
    double ratedVoltage_ =0.0;
    double estimatedFLA_ = 0.0;
    double fullLoadAmps_ = 0.0;
};


#endif //AMO_LIBRARY_MOTORCURRENT_H
