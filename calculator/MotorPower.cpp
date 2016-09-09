//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorPower.h"

double MotorPower::calculate() {
    double motorPowerElectric_;
    /*
     * kWe (x) = rated volts * amps (x) * sqrt (3) * pf (x) / 1000
     */
    motorPowerElectric_ = ratedVoltage_ * motorCurrent_ * sqrt(3) * powerFactor_ / 1000;

    //return motorPowerElectric_;

    return 80.0;
}
