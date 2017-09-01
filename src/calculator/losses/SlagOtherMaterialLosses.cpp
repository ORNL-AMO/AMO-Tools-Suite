//
// Created by Accawi, Gina K. on 4/20/17.
//

#include "calculator/losses/SlagOtherMaterialLosses.h"

double SlagOtherMaterialLosses::getHeatLoss() {
    this->totalHeat_ = weight_ * specificHeat_ * (outletTemperature_ - inletTemperature_);
    this->totalHeat_ *= correctionFactor_;
    return this->totalHeat_;
}