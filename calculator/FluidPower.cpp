/**
 * @brief Contains the definition of functions of CurveFitVal class.
 *      calculate(): Calculates the curve fit value
 *
 * Given a set of x and y coordinates and degree of polynomial curve to fit, it calculates the curve fit value
 * for a particular x coordinate value (read load factor here).
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

double FluidPower::calculate() {
    fluidPower_ = 0.746 * flowRate_ * head_ * specificGravity_ / 3961.38;
    return fluidPower_;
}