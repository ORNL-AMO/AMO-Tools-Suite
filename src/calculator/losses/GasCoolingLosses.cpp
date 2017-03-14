/**
 * @file
 * @brief Contains the implementation of the gas cooling losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/GasCoolingLosses.h"

double GasCoolingLosses::getHeatLoss() {
// return the heat loss for the air test case
    this->heatLoss_ = (this->flowRate_ * 60.0) * this->specificHeat_ * (this->finalTemperature_ - this->initialTemperature_) * this->correctionFactor_;
    return this->heatLoss_;
}