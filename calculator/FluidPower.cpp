//
// Created by Mishra, Subhankar on 10/13/16.
//

#include "FluidPower.h"

double FluidPower::calculate() {
    fluidPower_ = 0.746 * flowRate_ * head_ * specificGravity_ / 3961.38;
    return fluidPower_;
}