/**
 * @file
 * @brief Contains the implementation of the atmosphere total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/Atmosphere.h"

double Atmosphere::getTotalHeat() {
    // return the total net heat for the example case
    this->totalHeat_ = this->flowRate_ * this->specificHeat_ * (this->outletTemperature_ - this->inletTemperature_) * this->correctionFactor_;
    return this->totalHeat_;
}
