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

#ifndef AMO_TOOLS_SUITE_WATERHEATINGUSINGSTEAM_H
#define AMO_TOOLS_SUITE_WATERHEATINGUSINGSTEAM_H

class WaterHeatingUsingSteam {
public:
    struct Output
    {
        Output(double tempWaterOut, double bpTempWaterOut, bool bpTempWarningFlag, double flowByPassSteam,
               double enthalpySteamIn, double enthalpySteamOut, double enthalpyMakeUpWater) :
                tempWaterOut(tempWaterOut), bpTempWaterOut(bpTempWaterOut), bpTempWarningFlag(bpTempWarningFlag), flowByPassSteam(flowByPassSteam),
                enthalpySteamIn(enthalpySteamIn), enthalpySteamOut(enthalpySteamOut), enthalpyMakeUpWater(enthalpyMakeUpWater){}

        Output() = default;
        bool bpTempWarningFlag = false;
        double tempWaterOut = 0, bpTempWaterOut = 0, flowByPassSteam = 0,
                enthalpySteamIn = 0, enthalpySteamOut = 0, enthalpyMakeUpWater = 0;
    };

    /**
     * @param no arguments
     */
    WaterHeatingUsingSteam(){}

    /**
     *
     * @param pressureSteamIn double, units MPaa
     * @param flowSteamRate double, units kg/hr
     * @param temperatureWaterIn double, units K
     * @param pressureWaterOut double, units MPaa
     * @param flowWaterRate double, units cubic meter per hr
     * @param tempMakeupWater double, units K
     * @param presMakeupWater double, units MPaa
     *
     * @return Output
     * @param tempWaterOut double, units K
     * @param bpTempWaterOut double, units MPaa
     * @param bpTempWarningFlag bool
     * @param flowByPassSteam double, units cubic meter per hr
     * @param enthalpySteamIn double, units kJ/kg
     * @param enthalpySteamOut double, units kJ/kg
     * @param enthalpyMakeUpWater double, units kJ/kg
     *
     */
    Output calculate(const double pressureSteamIn, const double flowSteamRate,
                     const double temperatureWaterIn, const double pressureWaterOut, const double flowWaterRate,
                     const double tempMakeupWater, const double presMakeupWater);
};

#endif //AMO_TOOLS_SUITE_WATERHEATINGUSINGSTEAM_H
