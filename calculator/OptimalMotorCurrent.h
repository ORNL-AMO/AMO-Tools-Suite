//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORCURRENT_H
#define AMO_LIBRARY_OPTIMALMOTORCURRENT_H

#include "../motor.h"
#include "CurveFitVal.h"
#include "EstimateFLA.h"

class OptimalMotorCurrent {
public:
    //OptimalMotorCurrent(double motorPower, double voltage) : motorPower_(motorPower), voltage_(voltage) {}
    OptimalMotorCurrent(double motorRatedPower, int motorRPM, Motor::LineFrequency lineFrequency,
                        Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double loadFactor , double ratedVoltage, double fieldVoltage, double fullLoadAmps) :
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM),
            lineFrequency_(lineFrequency),
            efficiencyClass_(efficiencyClass),
            specifiedEfficiency_(specifiedEfficiency),
            loadFactor_(loadFactor), ratedVoltage_(ratedVoltage),
            fieldVoltage_(fieldVoltage),
            fullLoadAmps_(fullLoadAmps){};
    double calculate();

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

private:
    double motorPower_;
    double voltage_;
    double motorRatedPower_ = 0.0;

    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_ =0.0;
    double loadFactor_ = 0.0;
    double motorCurrent_ = 0.0;
    double ratedVoltage_ =0.0;
    double estimatedFLA_ = 0.0;
    double fullLoadAmps_ = 0.0;
    double fieldVoltage_ =0.0;
};


#endif //AMO_LIBRARY_OPTIMALMOTORCURRENT_H
