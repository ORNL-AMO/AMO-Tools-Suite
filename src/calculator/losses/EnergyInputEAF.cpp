/**
 * @file
 * @brief Contains the implementation of the energy input EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/EnergyInputEAF.h"

double EnergyInputEAF::getTotalChemicalEnergyInput() {
    const double coalHeatContent = (coalHeatingValue_ * coalCarbonInjection_) / 1000000;
    const double electrodeHeatContent = (electrodeUse_ * electrodeHeatingValue_) / 1000000;
    return naturalGasHeatInput_ + coalHeatContent + electrodeHeatContent + otherFuels_;
}
double EnergyInputEAF::getHeatDelivered() {
    const double coalHeatContent = (coalHeatingValue_ * coalCarbonInjection_) / 1000000;
    const double electrodeHeatContent = electrodeUse_ * electrodeHeatingValue_ / 1000000;
    return naturalGasHeatInput_ + coalHeatContent + electrodeHeatContent + otherFuels_ + electricityInput_;
}
