#include <iostream>
#include <cmath>
#include "calculator/util/CompressedAirPressureReduction.h"

CompressedAirPressureReduction::Output CompressedAirPressureReduction::calculate()
{
    double totalEnergyUse = 0, totalEnergyCost = 0;

    for (auto &compressedAirPressureReductionInput : compressedAirPressureReductionInputVec)
    {
        double tmpEnergyUse = 0, tmpEnergyCost = 0;

        //modification calculation
        if (!compressedAirPressureReductionInput.getIsBaseline())
        {
            double pressure = compressedAirPressureReductionInput.getPressure();
            double atmosphericPressure = compressedAirPressureReductionInput.getAtmosphericPressure();
            double pressureRated = compressedAirPressureReductionInput.getPressureRated();
            double compressorPower = compressedAirPressureReductionInput.getCompressorPower();

            double r = (pressureRated + 14.7) / 14.7;
            double x = (pressure + atmosphericPressure) / atmosphericPressure;
            double c = .395 / 1.395;

            double energyUse = compressorPower * (pow(x, c) - 1) / (pow(r, c) - 1);
            tmpEnergyUse = compressedAirPressureReductionInput.getHoursPerYear() * energyUse;
            tmpEnergyCost = tmpEnergyUse * compressedAirPressureReductionInput.getElectricityCost();
        }
        //baseline calculation
        else
        {
            tmpEnergyUse = compressedAirPressureReductionInput.getHoursPerYear() * compressedAirPressureReductionInput.getCompressorPower();
            tmpEnergyCost = tmpEnergyUse * compressedAirPressureReductionInput.getElectricityCost();
        }
        totalEnergyUse = totalEnergyUse + tmpEnergyUse;
        totalEnergyCost = totalEnergyCost + tmpEnergyCost;
    }

    return CompressedAirPressureReduction::Output(totalEnergyUse, totalEnergyCost);
}

void CompressedAirPressureReduction::setCompressedAirPressureReductionInputVec(std::vector<CompressedAirPressureReductionInput> &compressedAirPressureReductionInputVec)
{
    this->compressedAirPressureReductionInputVec = std::move(compressedAirPressureReductionInputVec);
}