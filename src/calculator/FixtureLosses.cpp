/**
 * @file
 * @brief Contains the implementation of the fixture losses total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/FixtureLosses.h"

double FixtureLosses::getHeatLoss() {
    this->heatLoss_ = this->feedRate_ * this->specificHeat_ * (this->finalTemperature_ - this->initialTemperature_) * this->correctionFactor_;
    return this->heatLoss_;
}