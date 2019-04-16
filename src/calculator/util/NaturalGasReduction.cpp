#include <iostream>
#include <cmath>
#include "calculator/util/NaturalGasReduction.h"

NaturalGasReduction::Output NaturalGasReduction::calculate()
{
    double energyUse = 0, energyCost = 0, annualEnergySavings = 0, costSavings = 0, totalFlow = 0, heatFlowRate = 0;

    // loop through all supplied inputs
    for (auto &naturalGasReductionInput : naturalGasReductionInputVec)
    {
        double tmpEnergyUse = 0, tmpEnergyCost = 0, tmpAnnualEnergySavings = 0, tmpCostSavings = 0, tmpTotalFlow = 0, tmpHeatFlowRate = 0;

        //flow meter method
        if (naturalGasReductionInput.getMeasurementMethod() == 0)
        {
            FlowMeterMethodData flowMeterMethodData = naturalGasReductionInput.getFlowMeterMethodData();
            tmpTotalFlow = flowMeterMethodData.getFlowRate() * naturalGasReductionInput.getUnits();
            tmpEnergyUse = tmpTotalFlow * naturalGasReductionInput.getHoursPerDay() * naturalGasReductionInput.getDaysPerMonth() * naturalGasReductionInput.getMonthsPerYear() * 1.03;
            tmpEnergyCost = tmpEnergyUse * naturalGasReductionInput.getFuelCost();
        }
        //air mass flow method
        else if (naturalGasReductionInput.getMeasurementMethod() == 1)
        {
            AirMassFlowData airMassFlowData = naturalGasReductionInput.getAirMassFlowData();
            double tmpAirFlowRate, tmpHeatFlowRate;
            //nameplate
            if (airMassFlowData.getIsNameplate())
            {
                AirMassFlowNameplateData nameplateData = airMassFlowData.getAirMassFlowNameplateData();
                tmpAirFlowRate = nameplateData.getAirFlow();
            }
            //measured
            else
            {
                AirMassFlowMeasuredData measuredData = airMassFlowData.getAirMassFlowMeasuredData();
                tmpAirFlowRate = measuredData.getAreaOfDuct() * measuredData.getAirVelocity();
            }

            tmpHeatFlowRate = (1.08 * tmpAirFlowRate * (airMassFlowData.getOutletTemperature() - airMassFlowData.getInletTemperature())) / 1000000;
            heatFlowRate = heatFlowRate + tmpHeatFlowRate;

            tmpEnergyUse = (tmpHeatFlowRate * naturalGasReductionInput.getHoursPerDay() * naturalGasReductionInput.getDaysPerMonth() * naturalGasReductionInput.getMonthsPerYear() * naturalGasReductionInput.getUnits()) / airMassFlowData.getSystemEfficiency();
            tmpEnergyCost = tmpEnergyUse * naturalGasReductionInput.getFuelCost();
        }
        //water mass flow method
        else if (naturalGasReductionInput.getMeasurementMethod() == 2)
        {
            WaterMassFlowData waterMassFlowData = naturalGasReductionInput.getWaterMassFlowData();
            double tmpHeatFlowRate;
            tmpHeatFlowRate = (500 * waterMassFlowData.getWaterFlow() * (waterMassFlowData.getOutletTemperature() - waterMassFlowData.getInletTmperature())) / 1000000;
            tmpEnergyUse = (tmpHeatFlowRate * naturalGasReductionInput.getHoursPerDay() * naturalGasReductionInput.getDaysPerMonth() * naturalGasReductionInput.getMonthsPerYear() * naturalGasReductionInput.getUnits()) / waterMassFlowData.getSystemEfficiency();
            tmpEnergyCost = tmpEnergyUse * naturalGasReductionInput.getFuelCost();
        }
        else if (naturalGasReductionInput.getMeasurementMethod() == 3)
        {
            OtherMethodData otherMethodData = naturalGasReductionInput.getOtherMethodData();
            tmpEnergyUse = otherMethodData.getConsumption();
            tmpEnergyCost = tmpEnergyUse * naturalGasReductionInput.getFuelCost();
        }
        energyUse = energyUse + tmpEnergyUse;
        energyCost = energyCost + tmpEnergyCost;
        totalFlow = totalFlow + tmpTotalFlow;
    }
}

void FlowMeterMethodData::setFlowRate(const double flowRate)
{
    this->flowRate = flowRate;
}

void OtherMethodData::setConsumption(const double consumption)
{
    this->consumption = consumption;
}

void AirMassFlowMeasuredData::setAreaOfDuct(const double areaOfDuct)
{
    this->areaOfDuct = areaOfDuct;
}

void AirMassFlowMeasuredData::setAirVelocity(const double airVelocity)
{
    this->airVelocity = airVelocity;
}

void AirMassFlowNameplateData::setAirFlow(const double airFlow)
{
    this->airFlow = airFlow;
}

void AirMassFlowData::setIsNameplate(const bool isNameplate)
{
    this->isNameplate = isNameplate;
}

void AirMassFlowData::setAirMassFlowMeasuredData(const AirMassFlowMeasuredData airMassFlowMeasuredData)
{
    this->airMassFlowMeasuredData = airMassFlowMeasuredData;
}

void AirMassFlowData::setAirMassFlowNameplateData(const AirMassFlowNameplateData airMassFlowNameplateData)
{
    this->airMassFlowNameplateData = airMassFlowNameplateData;
}

void AirMassFlowData::setInletTemperature(const double inletTemperature)
{
    this->inletTemperature = inletTemperature;
}

void AirMassFlowData::setOutletTemperature(const double outletTemperature)
{
    this->outletTemperature = outletTemperature;
}

void AirMassFlowData::setSystemEfficiency(const double systemEfficiency)
{
    this->systemEfficiency = systemEfficiency;
}

void WaterMassFlowData::setWaterFlow(const double waterFlow)
{
    this->waterFlow = waterFlow;
}

void WaterMassFlowData::setInletTemperature(const double inletTemperature)
{
    this->inletTemperature = inletTemperature;
}

void WaterMassFlowData::setOutletTemperature(const double outletTemperature)
{
    this->outletTemperature = outletTemperature;
}

void WaterMassFlow::setSystemEfficiency(const double systemEfficiency)
{
    this->systemEfficiency = systemEfficiency;
}

void NaturalGasReduction::setNaturalGasReductionInputVec(std::vector<NaturalGasReductionInput> &naturalGasReductionInputVec)
{
    this->naturalGasReductionInputVec = std::move(naturalGasReductionInputVec);
}