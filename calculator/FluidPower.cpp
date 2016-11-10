/**
 * @brief Contains the definition of functions of FluidPower class.
 *      calculate(): Calculates the fluid power
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


//
// Created by Mishra, Subhankar on 10/13/16.
//

#include "FluidPower.h"

/**
 * Calculates the fluid power
 * @return Fluid power
 */
double FluidPower::calculate() {
    fluidPower_ = 0.746 * flowRate_ * head_ * specificGravity_ / 3961.38;
    return fluidPower_;
}