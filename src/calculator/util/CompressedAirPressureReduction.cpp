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
            tmpEnergyUse = compressedAirPressureReductionInput.getHoursPerYear() * compressedAirPressureReductionInput.getCompressorPower() 
                           * (1 - (compressedAirPressureReductionInput.getPressure() - compressedAirPressureReductionInput.getProposedPressure()) * 0.005);
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