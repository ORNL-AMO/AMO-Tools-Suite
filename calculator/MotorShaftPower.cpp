//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"


double MotorShaftPower::calculate() {

    /*
     * Steps to calculate those properties are (Motor shaft power, current, efficiency and current):
     * 1. Initialize the following [Fixed values]
     * 1.1 Basic FLA coefficients
     * 1.2 EE FLA coefficients
     * 1.3 SE FLA coefficients
     *
     * 2. Initialize the following [Fixed values]
     * 2.1 Basic Part Load coefficients
     * 2.2 EE Part Load coefficients
     * 2.3 SE Part Load coefficients
     *
     * 3. Calculate the 25% load interval current values based on the motor HP
     * 3.1 The intervals are 0, 25, 50, 75, 100, 125
     *
     * 4.
     */

    /*
     *
     */

    double measuredPower_ = 80; // Hardcoded for now.
    double loadfraction_ = 0.5;//vlookup
    double motorPowerKWe_ = 79.085;//vlookup (loadfraction_)
    double loadfraction2_ = loadfraction_ + 0.01;
    double motorPowerKWe2_ = 80.626; //vlookup (loadfraction2_)
    double motorPowerdiff_ = motorPowerKWe2_ - motorPowerKWe_;
    double measuredMotorPowerdiff_ = measuredPower_ - motorPowerKWe_;
    double fractionalIndex_ = loadfraction_ + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    /*
     * Calculate rest of the interpolated values as well as the motorShaftPower
     */
    motorShaftPower_;
    return 101.19;
}