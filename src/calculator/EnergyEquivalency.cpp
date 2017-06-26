/**
 * @file
 * @brief Contains the implementation of the energy equivalency calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/EnergyEquivalency.h"

double ElectricalEnergyEquivalency::getElectricalHeatInput() {
    this->electricalHeatInput_ = ((this->fuelFiredHeatInput_)*(this->fuelFiredEfficiency_))/(this->electricallyHeatedEfficiency_) * (1000000/3412);
    return this->electricalHeatInput_;
}

double FuelFiredEnergyEquivalency::getFuelFiredHeatInput() {
    this->fuelFiredHeatInput_ = ((this->electricalHeatInput_)*(this->electricallyHeatedEfficiency_))/(this->fuelFiredEfficiency_) * (0.003412);
    return this->fuelFiredHeatInput_;
}