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
    return flowRate * 60.0 * gasDensity * specificHeat * (finalTemperature - initialTemperature) * correctionFactor;
}