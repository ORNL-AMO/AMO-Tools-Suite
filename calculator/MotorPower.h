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

    /*MotorPower(double motorKw, double motorAmps, double motorPowerFactor, double voltage) : motorKw_(motorKw),
                                                                                            motorAmps_(motorAmps),
                                                                                            motorPowerFactor_(
                                                                                                    motorPowerFactor),
                                                                                            voltage_(voltage) {}*/
    double calculate();
/*
    double getMotorKw() const {
        return motorKw_;
    }

    void setMotorKw(double motorKw) {
        motorKw_ = motorKw;
    }

    double getMotorAmps() const {
        return motorAmps_;
    }

    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    double getMotorPowerFactor() const {
        return motorPowerFactor_;
    }

    void setMotorPowerFactor(double motorPowerFactor) {
        motorPowerFactor_ = motorPowerFactor;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }
*/
private:
    double motorKw_;
    double motorAmps_;
    double motorPowerFactor_;
    double voltage_;

    /*
     * New variables for the updated constructor
     */

    double ratedVoltage_;
    double motorCurrent_;
    double powerFactor_;

};


#endif //AMO_LIBRARY_MOTORPOWER_H
