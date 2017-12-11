#include "calculator/losses/SlagOtherMaterialLosses.h"

double SlagOtherMaterialLosses::getHeatLoss() {
    this->totalHeat = weight * specificHeat * (outletTemperature - inletTemperature);
    this->totalHeat *= correctionFactor;
    return this->totalHeat;
}