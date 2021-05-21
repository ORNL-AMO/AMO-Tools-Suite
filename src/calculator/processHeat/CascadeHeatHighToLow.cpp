/**
 * @file
 * @brief Calculate energy savings from using exhaust gas (waste) of high temperature to supply heat to low temperature equipment.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include <algorithm>
#include "calculator/processHeat/CascadeHeatHighToLow.h"

CascadeHeatHighToLow::Output CascadeHeatHighToLow::calculate()
{
    const double priFlueVolume = priFiringRate * stoichAirVolume / 32 * (1 + priExcessAir) * 1000000 / priFuelHV + priFiringRate * 1000000 / priFuelHV;
    const double hxEnergyRate = priFlueVolume * priFlueSpecHeat * (priExhaustTemperature - secExhaustTemperature) / 1000000;
    const double eqEnergySupply = hxEnergyRate / secAvailableHeat;
    const double effOpHours = std::min(priOpHours , secOpHours);
    const double hourlySavings = std::min(eqEnergySupply, secFiringRate);
    const double energySavings = hourlySavings * effOpHours;
    const double costSavings = energySavings * secFuelCost;

    return Output(priFlueVolume, hxEnergyRate, eqEnergySupply, effOpHours, energySavings, costSavings, hourlySavings);
}