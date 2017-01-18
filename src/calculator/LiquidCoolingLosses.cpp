/**
 * @file
 * @brief Contains the implementation of the liquid (not water) cooling losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/LiquidCoolingLosses.h"

double LiquidCoolingLosses::getHeatLoss() {
    heatLoss_ = (this->flowRate_ * 60.0 * this->density_) * this->specificHeat_ * (this->outletTemperature_ - this->initialTemperature_) * this->correctionFactor_;
    return heatLoss_;
}