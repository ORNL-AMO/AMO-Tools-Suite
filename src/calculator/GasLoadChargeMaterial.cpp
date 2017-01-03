/**
 * @file
 * @brief Contains the implementation of the gas load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/GasLoadChargeMaterial.h"

double GasLoadChargeMaterial::getTotalHeat() {
    // return the total net heat for the example case

    double tempDiff = this->dischargeTemperature_ - this->initialTemperature_;
    double hgas = (1.0 - this->percentVapor_) * this->feedRate_ * this->specificHeatGas_ * tempDiff;
    double hvapor = this->percentVapor_ * this->feedRate_ * this->specificHeatVapor_ * tempDiff;
    double hreact = this->feedRate_ * this->percentReacted_ * this->reactionHeat_;
    if (this->thermicReactionType_ == LoadChargeMaterial::ThermicReactionType::EXOTHERMIC) {
        hreact *= -1.0;
    }

    return hgas + hvapor + hreact + this->additionalHeat_;
}
