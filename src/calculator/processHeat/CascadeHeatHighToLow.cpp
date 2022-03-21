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
    const double priFlueVolume = priFiringRate * stoichAirVolume * (1 + priExcessAir) * 1000000 / fuelHV + priFiringRate * 1000000 / fuelHV;
    const double hxEnergyRate = priFlueVolume * priFlueSpecHeat * priFlueDensity * (priExhaustTemperature - secExhaustTemperature) / 1000000;
    const double eqEnergySupply = hxEnergyRate / secAvailableHeat;
    const double effOpHours = std::min(priOpHours , secOpHours);
    const double hourlySavings = std::min(eqEnergySupply, secFiringRate);
    const double energySavings = hourlySavings * effOpHours;
    const double costSavings = energySavings * fuelCost;

    return Output(priFlueVolume, hxEnergyRate, eqEnergySupply, effOpHours, energySavings, costSavings, hourlySavings,
                  priExcessAir, priAvailableHeat, secExcessAir, secAvailableHeat);
}