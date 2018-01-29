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

    const double tempDiff = this->dischargeTemperature - this->initialTemperature;
    const double hgas = (1.0 - this->percentVapor) * this->feedRate * this->specificHeatGas * tempDiff;
    const double hvapor = this->percentVapor * this->feedRate * this->specificHeatVapor * tempDiff;

    // heatReact ignored when exothermic
    double heatReact = 0.0;
    if (this->thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heatReact =this->feedRate * this->percentReacted * this->reactionHeat;
    }

    this->totalHeat =  hgas + hvapor + heatReact + this->additionalHeat;
    return this->totalHeat;
}
