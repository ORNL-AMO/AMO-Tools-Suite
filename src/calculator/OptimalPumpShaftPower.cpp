/**
 * @brief Contains the definition of functions of OptimalPumpShaftPower class.
 *      calculate(): Calculates the Optimal Pump ShaftPower
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "calculator/OptimalPumpShaftPower.h"

double OptimalPumpShaftPower::calculate() {
    FluidPower fluidPower(specificGravity_,flowRate_,head_);
    double fluidPower_ = fluidPower.calculate();
    double requiredShaftPowerkW = fluidPower_ / pumpEfficiency_;
    double requiredShaftPowerhP = requiredShaftPowerkW / 0.746;
    return requiredShaftPowerhP;
}
