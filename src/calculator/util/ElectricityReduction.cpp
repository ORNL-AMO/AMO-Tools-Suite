#include <iostream>
#include <cmath>
#include "calculator/util/ElectricityReduction.h"

ElectricityReduction::Output ElectricityReduction::calculate() {
    double energyUse = 0, energyCost = 0, annualEnergySavings = 0, costSavings = 0, power = 0;

    // loop through all supplied inputs
    for (auto & electricityReductionInput: electricityReductionInputVec) {
        double tmpTotalPower, tmpEnergyUse, tmpEnergyCost, tmpAnnualEnergySavings, tmpCostSavings;

        //multimeter data
        if (electricityReductionInput.getMeasurementMethod() == 0) {
            MultimeterData multimeterData = electricityReductionInput.getMultimeterData();
            if (multimeterData.getNumberOfPhases() == 1) {
                tmpTotalPower = multimeterData.getSupplyVoltage() * multimeterData.getAverageCurrent() * multimeterData.getPowerFactor() * 0.001 * electricityReductionInput.getUnits();
            } else {
                tmpTotalPower = multimeterData.getSupplyVoltage() * multimeterData.getAverageCurrent() * multimeterData.getPowerFactor() * (sqrt(3) / 1000) * electricityReductionInput.getUnits();
            }
            tmpEnergyUse = tmpTotalPower * electricityReductionInput.getOperatingHours();
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;

        // nameplate data
        } else if (electricityReductionInput.getMeasurementMethod() == 1) {
            NameplateData nameplateData = electricityReductionInput.getNameplateData();
            tmpTotalPower = nameplateData.getRatedMotorPower() * nameplateData.getLoadFactor() * pow((nameplateData.getOperationalFrequency() / nameplateData.getLineFrequency()), 2.5) * (1 / nameplateData.getMotorAndDriveEfficiency());
            tmpEnergyUse = tmpTotalPower * electricityReductionInput.getOperatingHours();
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;

        // power meter data
        } else if (electricityReductionInput.getMeasurementMethod() == 2) {
            PowerMeterData powerMeterData = electricityReductionInput.getPowerMeterData();
            tmpTotalPower = powerMeterData.getPower() * electricityReductionInput.getUnits();
            tmpEnergyUse = tmpTotalPower * electricityReductionInput.getOperatingHours();
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;

        // other method data
        } else {
            OtherMethodData otherMethodData = electricityReductionInput.getOtherMethodData();
            tmpTotalPower = otherMethodData.getEnergy();
            tmpEnergyUse = tmpTotalPower;
            tmpEnergyCost = tmpEnergyUse * electricityReductionInput.getElectricityCost();
            energyUse = energyUse + tmpEnergyUse;
            energyCost = energyCost + tmpEnergyCost;
        }
        power = power + tmpTotalPower;
    }

    // output = Output(energyUse, energyCost, annualEnergySavings, costSavings);
    return ElectricityReduction::Output(energyUse, energyCost, annualEnergySavings, costSavings, power);
}

void ElectricityReduction::setElectricityReductionInputVec(std::vector<ElectricityReductionInput> & electricityReductionInput) {
    this->electricityReductionInputVec = std::move(electricityReductionInputVec);
}


// MultimeterData object setters
void MultimeterData::setNumberOfPhases(const int numberOfPhases) {
    this->numberOfPhases = numberOfPhases;
}

void MultimeterData::setSupplyVoltage(const double supplyVoltage) {
    this->supplyVoltage = supplyVoltage;
}

void MultimeterData::setAverageCurrent(const double averageCurrent) {
    this->averageCurrent = averageCurrent;
}

void MultimeterData::setPowerFactor(const double powerFactor) {
    this->powerFactor = powerFactor;
}


// NameplateData object setters
void NameplateData::setRatedMotorPower(const double ratedMotorPower) {
    this->ratedMotorPower = ratedMotorPower;
}

void NameplateData::setVariableSpeedMotor(const bool variableSpeedMotor) {
    this->variableSpeedMotor = variableSpeedMotor;
}

void NameplateData::setOperationalFrequency(const double operationalFrequency) {
    this->operationalFrequency = operationalFrequency;
}

void NameplateData::setLineFrequency(const double lineFrequency) {
    this->lineFrequency = lineFrequency;
}

void NameplateData::setMotorAndDriveEfficiency(const double motorAndDriveEfficiency) {
    this->motorAndDriveEfficiency = motorAndDriveEfficiency;
}

void NameplateData::setLoadFactor(const double loadFactor) {
    this->loadFactor = loadFactor;
}


// PowerMeterData object setters
void PowerMeterData::setPower(const double power) {
    this->power = power;
}

// Other Method Data
void OtherMethodData::setEnergy(const double energy) {
    this->energy = energy;
}