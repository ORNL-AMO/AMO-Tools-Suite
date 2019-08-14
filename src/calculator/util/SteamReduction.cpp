#include <iostream>
#include <cmath>
#include "calculator/util/SteamReduction.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SaturatedProperties.h"


SteamReduction::Output SteamReduction::calculate()
{
    double steamUse = 0, energyUse = 0, energyCost = 0;

    // loop through all supplied inputs
    for (auto &steamReductionInput : steamReductionInputVec)
    {
        double tmpSteamUse = 0, tmpEnergyUse = 0, tmpEnergyCost = 0;
        double specificEnthalpy = 0;

        //flow meter method
        if (steamReductionInput.getMeasurementMethod() == 0)
        {
            SteamFlowMeterMethodData flowMeterMethodData = steamReductionInput.getFlowMeterMethodData();
            tmpSteamUse = flowMeterMethodData.getFlowRate() * steamReductionInput.getHoursPerYear() * (steamReductionInput.getUnits() / steamReductionInput.getSystemEfficiency());

            // double saturatedTemperature = SaturatedTemperature(steamReductionInput.getPressure()).calculate();
            SaturatedTemperature saturatedTemperatureObject = SaturatedTemperature::SaturatedTemperature(steamReductionInput.getPressure());
            double saturatedTemperature = saturatedTemperatureObject.calculate();

            // SaturatedProperties saturatedProperties = SaturatedProperties::SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature);
            // auto saturatedPropertiesOutput = saturatedProperties.calculate();
            SteamSystemModelerTool::SaturatedPropertiesOutput saturatedPropertiesOutput = SaturatedProperties::SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature).calculate();

            double evaporationSpecificEnthalpy = saturatedPropertiesOutput.evaporationSpecificEnthalpy;
            specificEnthalpy = evaporationSpecificEnthalpy * (1.0 / 2.326);
            tmpEnergyUse = specificEnthalpy * tmpSteamUse / 1000000.0;
        }
        //air mass flow
        else if (steamReductionInput.getMeasurementMethod() == 1)
        {
            SteamMassFlowMethodData massFlowMethodData = steamReductionInput.getAirMassFlowMethodData();
            double airFlowRate;
            if (massFlowMethodData.getIsNameplate())
            {
                SteamMassFlowNameplateData massFlowNameplateData = massFlowMethodData.getMassFlowNameplateData();
                airFlowRate = massFlowNameplateData.getFlowRate();
            }
            else
            {
                SteamMassFlowMeasuredData massFlowMeasuredData = massFlowMethodData.getMassFlowMeasuredData();
                airFlowRate = massFlowMeasuredData.getAirVelocity() * massFlowMeasuredData.getAreaOfDuct();
            }
            double heatFlowRate = (1.08 * airFlowRate * (massFlowMethodData.getOutletTemperature() - massFlowMethodData.getInletTemperature())) / 1000000.0;
            tmpEnergyUse = (steamReductionInput.getUnits() * heatFlowRate * steamReductionInput.getHoursPerYear()) / steamReductionInput.getSystemEfficiency();

            // double saturatedTemperature = SaturatedTemperature(steamReductionInput.getPressure()).calculate();
            SaturatedTemperature saturatedTemperatureObject = SaturatedTemperature(steamReductionInput.getPressure());
            const double saturatedTemperature = saturatedTemperatureObject.calculate();

            // SaturatedProperties saturatedProperties = SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature);
            // auto saturatedPropertiesOutput = saturatedProperties.calculate();
            SteamSystemModelerTool::SaturatedPropertiesOutput saturatedPropertiesOutput = SaturatedProperties::SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature).calculate();

            double evaporationSpecificEnthalpy = saturatedPropertiesOutput.evaporationSpecificEnthalpy;
            specificEnthalpy = evaporationSpecificEnthalpy * (1.0 / 2.326);
            tmpSteamUse = tmpEnergyUse * (1000000.0 / specificEnthalpy);
        }
        //water mass flow
        else if (steamReductionInput.getMeasurementMethod() == 2)
        {
            SteamMassFlowMethodData massFlowMethodData = steamReductionInput.getWaterMassFlowMethodData();
            SteamMassFlowNameplateData massFlowNameplateData = massFlowMethodData.getMassFlowNameplateData();
            double waterFlowRate = massFlowNameplateData.getFlowRate();
            double heatFlowRate = (500.0 * waterFlowRate * (massFlowMethodData.getOutletTemperature() - massFlowMethodData.getInletTemperature())) / 1000000.0;
            tmpEnergyUse = (steamReductionInput.getUnits() * heatFlowRate * steamReductionInput.getHoursPerYear()) / steamReductionInput.getSystemEfficiency();

            // double saturatedTemperature = SaturatedTemperature(steamReductionInput.getPressure()).calculate();
            SaturatedTemperature saturatedTemperatureObject = SaturatedTemperature(steamReductionInput.getPressure());
            const double saturatedTemperature = saturatedTemperatureObject.calculate();

            // SaturatedProperties saturatedProperties = SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature);
            // auto saturatedPropertiesOutput = saturatedProperties.calculate();
            SteamSystemModelerTool::SaturatedPropertiesOutput saturatedPropertiesOutput = SaturatedProperties::SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature).calculate();

            double evaporationSpecificEnthalpy = saturatedPropertiesOutput.evaporationSpecificEnthalpy;
            specificEnthalpy = evaporationSpecificEnthalpy * (1.0 / 2.326);
            tmpSteamUse = tmpEnergyUse * (1000000.0 / specificEnthalpy);
        }
        //other/offsheet method
        else if (steamReductionInput.getMeasurementMethod() == 3)
        {
            SteamOtherMethodData otherMethodData = steamReductionInput.getOtherMethodData();
            tmpEnergyUse = otherMethodData.getConsumption();

            // double saturatedTemperature = SaturatedTemperature(steamReductionInput.getPressure()).calculate();
            SaturatedTemperature saturatedTemperatureObject = SaturatedTemperature(steamReductionInput.getPressure());
            const double saturatedTemperature = saturatedTemperatureObject.calculate();

            // SaturatedProperties saturatedProperties = SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature);
            // auto saturatedPropertiesOutput = saturatedProperties.calculate();
            SteamSystemModelerTool::SaturatedPropertiesOutput saturatedPropertiesOutput = SaturatedProperties::SaturatedProperties(steamReductionInput.getPressure(), saturatedTemperature).calculate();

            double evaporationSpecificEnthalpy = saturatedPropertiesOutput.evaporationSpecificEnthalpy;
            specificEnthalpy = evaporationSpecificEnthalpy * (1.0 / 2.326);
            tmpSteamUse = otherMethodData.getConsumption() * (1000000.0 / specificEnthalpy);
        }

        //steam
        if (steamReductionInput.getUtilityType() == 0)
        {
            double massResult = tmpEnergyUse * (1.0 / specificEnthalpy);
            tmpEnergyCost = massResult * steamReductionInput.getUtilityCost();
        }
        //natural gas || other
        else if (steamReductionInput.getUtilityType() == 1 || steamReductionInput.getUtilityType() == 2)
        {
            tmpEnergyCost = tmpEnergyUse * steamReductionInput.getUtilityCost();
        }

        steamUse += tmpSteamUse;
        energyUse += tmpEnergyUse;
        energyCost += tmpEnergyCost;
    }
    return SteamReduction::Output(steamUse, energyUse, energyCost);
}

void SteamReduction::setSteamReductionInputVec(std::vector<SteamReductionInput> &steamReductionInputVec)
{
    this->steamReductionInputVec = std::move(steamReductionInputVec);
}