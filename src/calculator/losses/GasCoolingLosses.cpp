/**
 * @file
 * @brief Contains the implementation of the gas cooling losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/GasCoolingLosses.h"

double GasCoolingLosses::getHeatLoss() const {
    return flowRate_ * 60.0 * gasDensity_ * specificHeat_ * (finalTemperature_ - initialTemperature_) * correctionFactor_;
}