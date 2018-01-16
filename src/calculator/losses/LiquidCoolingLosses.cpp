/**
 * @file
 * @brief Contains the implementation of the liquid (not water) cooling losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/LiquidCoolingLosses.h"

double LiquidCoolingLosses::getHeatLoss() {
    heatLoss = (this->flowRate * 60.0 * this->density) * this->specificHeat * (this->outletTemperature - this->initialTemperature) * this->correctionFactor;
    return heatLoss;
}