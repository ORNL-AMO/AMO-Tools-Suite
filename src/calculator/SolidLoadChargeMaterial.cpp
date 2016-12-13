/**
 * @file
 * @brief Contains the implementation of the solid load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/SolidLoadChargeMaterial.h"

double SolidLoadChargeMaterial::getTotalHeat() {

    // Heat required for removal of moisture
    double hmv = 0.0;
    double hmr = 0.0;
    if (this->dischargeTemperature_ < 212.0) {
        hmv = this->chargeFeedRate_ * this->waterContentCharged_ * (this->waterVaporDischargeTemperature_ - this->initialTemperature_);
    } else {
        hmv = this->chargeFeedRate_ * (this->waterContentCharged_ - this->waterContentDischarged_) * (212.0 - this->initialTemperature_);
    }
    hmr = this->chargeFeedRate_ * this->waterContentDischarged_ * (this->waterVaporDischargeTemperature_ - this->initialTemperature_);

    // Heat required for solid
    double hs = 0.0;
    if (this->dischargeTemperature_ < this->meltingPoint_) {
        hs = this->chargeFeedRate_ * (1.0 - this->waterContentCharged_) * this->specificHeatSolid_ * (this->dischargeTemperature_ - this->initialTemperature_);
    } else {
        hs = this->chargeFeedRate_ * (1.0 - this->waterContentCharged_) * this->specificHeatSolid_ * (this->meltingPoint_ - this->initialTemperature_) + this->latentHeat_ + this->specificHeatLiquid_ * (this->dischargeTemperature_ - this->meltingPoint_);
    }

    // Return the total net heat for the example case
    return 3204056;

}

