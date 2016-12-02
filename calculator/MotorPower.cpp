/**
 * @brief Contains the definition of functions of MotorPower class.
 *      calculate(): Calculates the motor power given rated voltage, motor current and power factor.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorPower.h"
#include <cmath>

double MotorPower::calculate() {
    double motorPowerElectric_ = 0.0;
    /**
     * Formula to calculate the motor electric power
     * kWe (x) = rated volts * amps (x) * sqrt (3) * pf (x) / 1000
     */
    motorPowerElectric_ = ratedVoltage_ * motorCurrent_ * sqrt(3) * powerFactor_ / 1000;
    return motorPowerElectric_;
}
