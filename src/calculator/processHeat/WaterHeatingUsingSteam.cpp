/**
 * @file
 * @brief Calculate energy savings from using vent steam to heat water using a steam to liquid heat exchanger.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include "calculator/processHeat/WaterHeatingUsingSteam.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/SaturatedProperties.h"

WaterHeatingUsingSteam::Output WaterHeatingUsingSteam::calculate(const double pressureSteamIn, const double flowSteamRate,
                                           const double temperatureWaterIn, const double pressureWaterOut, const double flowWaterRate,
                                           const double tempMakeupWater, const double presMakeupWater)
{
    auto res = SaturatedProperties(pressureSteamIn, SaturatedTemperature(pressureSteamIn).calculate()).calculate();
    const double enthalpySteamIn = res.gasSpecificEnthalpy;
    const double enthalpySteamOut = res.liquidSpecificEnthalpy;
    const double bpTempWaterOut = SaturatedTemperature(pressureWaterOut).calculate();
    const double enthalpyMakeUpWater = SteamProperties(presMakeupWater, SteamProperties::ThermodynamicQuantity::TEMPERATURE, tempMakeupWater).calculate().specificEnthalpy;

    double tempWaterOut = temperatureWaterIn + ((enthalpySteamIn - enthalpySteamOut) * flowSteamRate) / (4.1796 * 1000 * flowWaterRate);
    const double tempBpWaterOut = 0.96328 * bpTempWaterOut;

    bool bpTempWarningFlag = false;
    double flowByPassSteam = 0;
    if (tempWaterOut >= tempBpWaterOut)
    {
        bpTempWarningFlag = true;
        tempWaterOut = tempBpWaterOut;
        const double heatGainRateBypass = 1000 * 4.1796 * (tempWaterOut - temperatureWaterIn) * flowWaterRate;
        flowByPassSteam = flowSteamRate - (heatGainRateBypass / ( enthalpySteamIn-enthalpySteamOut));
    }

    return Output(tempWaterOut, bpTempWaterOut, bpTempWarningFlag, flowByPassSteam,
                  enthalpySteamIn, enthalpySteamOut, enthalpyMakeUpWater);
}
