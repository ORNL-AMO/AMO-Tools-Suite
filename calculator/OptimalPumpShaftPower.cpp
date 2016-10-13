//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpShaftPower.h"

double OptimalPumpShaftPower::calculate() {
    FluidPower fluidPower(specificGravity_,flowRate_,head_);
    double fluidPower_ = fluidPower.calculate();
    double requiredShaftPowerkW = fluidPower_/pumpEfficiency_;
    double requiredShaftPowerhP = requiredShaftPowerkW/0.746;
    return requiredShaftPowerhP;
}
