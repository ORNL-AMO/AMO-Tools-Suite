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
    const double coalHeatContent = (coalHeatingValue * coalCarbonInjection) / 1000000;
    const double electrodeHeatContent = (electrodeUse * electrodeHeatingValue) / 1000000;
    return (naturalGasHeatInput + coalHeatContent + electrodeHeatContent + otherFuels) * 1000000;
}
double EnergyInputEAF::getHeatDelivered() {
    const double coalHeatContent = (coalHeatingValue * coalCarbonInjection) / 1000000;
    const double electrodeHeatContent = (electrodeUse * electrodeHeatingValue) / 1000000;
    const double electricityHeat = (electricityInput * 3412) / 1000000;
    return (naturalGasHeatInput + coalHeatContent + electrodeHeatContent + otherFuels + electricityHeat) * 1000000;
}
