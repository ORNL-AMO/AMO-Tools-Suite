/**
 * @file
 * @brief Contains the implementation of the gas load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/GasLoadChargeMaterial.h"

double GasLoadChargeMaterial::getTotalHeat() {
    // return the total net heat for the example case

    const double tempDiff = this->dischargeTemperature_ - this->initialTemperature_;
    const double hgas = (1.0 - this->percentVapor_) * this->feedRate_ * this->specificHeatGas_ * tempDiff;
    const double hvapor = this->percentVapor_ * this->feedRate_ * this->specificHeatVapor_ * tempDiff;

    // heatReact ignored when exothermic
    double heatReact = 0.0;
    if (this->thermicReactionType_ == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heatReact =this->feedRate_ * this->percentReacted_ * this->reactionHeat_;
    }

    this->totalHeat_ =  hgas + hvapor + heatReact + this->additionalHeat_;
    return this->totalHeat_;
}
