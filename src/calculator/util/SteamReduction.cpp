/**
 * @file Implementation of Steam Reduction Calculations
 * @author Updated by Omer Aziz (omerb).
 */

#include "calculator/util/SteamReduction.h"

SteamReduction::Output SteamReduction::calculate()
{
    double steamUse = 0, energyUse = 0, energyCost = 0;

    // loop through all supplied inputs
    for (auto &steamReductionInput : steamReductionInputVec)
    {
        double tmpSteamUse = 0, tmpEnergyUse = 0, tmpEnergyCost = 0;
        double steamEnthalpy = SteamProperties(steamReductionInput.getPressure(), steamReductionInput.getSteamVariableOption(),
                                               steamReductionInput.getSteamVariable()).calculate().specificEnthalpy;
        double feedEnthalpy = SteamProperties(0.101325, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                                              steamReductionInput.getFeedWaterTemperature()).calculate().specificEnthalpy;
        double changeEnthalpy = steamEnthalpy - feedEnthalpy;

        //flow meter method
        if (steamReductionInput.getMeasurementMethod() == 0)
        {
            SteamFlowMeterMethodData flowMeterMethodData = steamReductionInput.getFlowMeterMethodData();
            tmpSteamUse = flowMeterMethodData.getFlowRate() * steamReductionInput.getHoursPerYear() * (steamReductionInput.getUnits() / steamReductionInput.getSystemEfficiency());
            tmpEnergyUse = changeEnthalpy * tmpSteamUse * 1 / steamReductionInput.getBoilerEfficiency();
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
            // 0.072381 is air Cp in kJ-min/(m3-hr-K) (from 1.08  btu-hr/(scf-hr-R))
            double heatFlowRate = (0.072381 * airFlowRate * (massFlowMethodData.getOutletTemperature() - massFlowMethodData.getInletTemperature()));
            tmpEnergyUse = (steamReductionInput.getUnits() * (heatFlowRate) * steamReductionInput.getHoursPerYear()) / (steamReductionInput.getSystemEfficiency() * steamReductionInput.getBoilerEfficiency());
            tmpSteamUse = (tmpEnergyUse / changeEnthalpy) * steamReductionInput.getBoilerEfficiency();
        }
        //water mass flow
        else if (steamReductionInput.getMeasurementMethod() == 2)
        {
            SteamMassFlowMethodData massFlowMethodData = steamReductionInput.getWaterMassFlowMethodData();
            SteamMassFlowNameplateData massFlowNameplateData = massFlowMethodData.getMassFlowNameplateData();
            double waterFlowRate = massFlowNameplateData.getFlowRate();
            // 251045 (kJ/m3K)*(min/hr) from (8.34 lb/gal * 1 btu/lbF * 60 min/hr)
            double heatFlowRate = (251045 * waterFlowRate * (massFlowMethodData.getOutletTemperature() - massFlowMethodData.getInletTemperature()));
            tmpEnergyUse = (steamReductionInput.getUnits() * heatFlowRate * steamReductionInput.getHoursPerYear()) / (steamReductionInput.getSystemEfficiency() * steamReductionInput.getBoilerEfficiency());
            tmpSteamUse = (tmpEnergyUse / changeEnthalpy) * steamReductionInput.getBoilerEfficiency();
        }
        //Offsheet method
        else if (steamReductionInput.getMeasurementMethod() == 3)
        {
            SteamOffsheetMethodData offsheetMethodData = steamReductionInput.getOffsheetMethodData();
            tmpEnergyUse = offsheetMethodData.getConsumption();
            tmpSteamUse = (tmpEnergyUse / changeEnthalpy) * steamReductionInput.getBoilerEfficiency();
        }

        //steam
        if (steamReductionInput.getUtilityType() == 0)
        {
            tmpEnergyCost = tmpSteamUse * steamReductionInput.getUtilityCost();
        }
        //natural gas || Offsheet Method
        else if (steamReductionInput.getUtilityType() == 1 || steamReductionInput.getUtilityType() == 2)
        {
            tmpEnergyCost = tmpEnergyUse * steamReductionInput.getUtilityCost();
        }

        steamUse += tmpSteamUse;
        energyUse += tmpEnergyUse;
        energyCost += tmpEnergyCost;
    }

    return {steamUse, energyUse, energyCost};
}
