#include <cmath>
#include "calculator/util/ElectricityReduction.h"

ElectricityReduction::ElectricityReduction(std::vector<ElectricityReductionInput> & electricityReductionInputVec)
    : electricityReductionInputVec(std::move(electricityReductionInputVec))
{
    calculate();
}

void ElectricityReduction::calculate() {
    double energyUse = 0, energyCost = 0, annualEnergySavings = 0, costSavings = 0;

    // loop through all supplied inputs
    for (auto & electricityReductionInput: electricityReductionInputVec) {
        double tmpTotalPower, tmpEnergyUse, tmpEnergyCost, tmpAnnualEnergySavings, tmpCostSavings;
        
        //multimeter data
        if (electricityReductionInput.getMeasurementMethod() == 0) {
            MultimeterData multimeterData = electricityReductionInput.getMultimeterData();
            if (multimeterData.getNumberOfPhases() == 1) {
                tmpTotalPower = multimeterData.getSupplyVoltage() * multimeterData.getAverageCurrent() * (1 / 1000);
            } else {
                tmpTotalPower = multimeterData.getSupplyVoltage() * multimeterData.getAverageCurrent() * (sqrt(3) / 1000);
            }
            tmpEnergyUse = tmpTotalPower * electricityReductionInput.getHoursPerDay() * electricityReductionInput.getDaysPerMonth() * electricityReductionInput.getMonthsPerYear();
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;


        } else if (electricityReductionInput.getMeasurementMethod() == 1) {
            NameplateData nameplateData = electricityReductionInput.getNameplateData();
            tmpTotalPower = nameplateData.getRatedMotorPower() * nameplateData.getLoadFactor() * pow((nameplateData.getOperationalFrequency() / nameplateData.getLineFrequency()), 2.5) * (1 / nameplateData.getMotorAndDriveEfficiency());
            tmpEnergyUse = tmpTotalPower * electricityReductionInput.getHoursPerDay() * electricityReductionInput.getDaysPerMonth() * electricityReductionInput.getMonthsPerYear();
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;
        } else if (electricityReductionInput.getMeasurementMethod() == 2) {

        } else {

        }
    }
}


void ElectricityReduction::setElectricityReductionInputVec(std::vector<ElectricityReductionInput> & electricityReductionInput) {
    this->electricityReductionInputVec = std::move(electricityReductionInputVec);
}