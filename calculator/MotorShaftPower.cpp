//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"


double MotorShaftPower::calculate() {







    /*
     * Given the load% calculate the Efficiency
     * Pick the 25,50,75,100,and 125% motor efficiency values and do a 4th order polynomial fit.
     * Use the fit coefficients to popluate, in 1% load intervals, from 26 to 125% load
     * Pick the 75, 100, and 125% motor efficiency values and do a 2nd order polynomial fit
     * Use the fit coefficients to populate, in 1% load intervals, the current range from 126 to 150% load
     */


    /*
     * ****************************************************************
     */
    double loadfraction_ = 0.5;//vlookup
    double motorPowerKWe_ = 79.085;//vlookup (loadfraction_)
    double loadfraction2_ = loadfraction_ + 0.01;
    double motorPowerKWe2_ = 80.626; //vlookup (loadfraction2_)
    double motorPowerdiff_ = motorPowerKWe2_ - motorPowerKWe_;
    double measuredMotorPowerdiff_ = motorMeasuredPower_ - motorPowerKWe_;
    double fractionalIndex_ = loadfraction_ + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    /*
     * Calculate rest of the interpolated values as well as the motorShaftPower
     */
    motorShaftPower_;
    return 101.19;
}