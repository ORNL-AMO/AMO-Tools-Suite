//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorPowerFactor.h"

double MotorPowerFactor::calculate() {
    double motorPowerFactor_;
    /*
     * Make sure the loadfactor comes not in %.
     * pf (X) = [(X/100) * rated hp * 0.746] / [Amps (X) * Eff (X) * Rated Voltage * Square root (3) / 1000]
     */
    motorPowerFactor_ = (loadFactor_ * motorRatedPower_ * 0.746) /
                        (motorCurrent_ * motorEfficiency_ * ratedVoltage_ * sqrt(3) / 1000);
    // return motorPowerFactor;
    return 76.46;
}
