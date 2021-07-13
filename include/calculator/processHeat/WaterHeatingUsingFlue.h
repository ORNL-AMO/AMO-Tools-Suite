/**
 * @file
 * @brief Calculate energy and cost savings from using flue gas (waste) heat to heat boiler feed water using non-condensing heat exchanger.
 *
 *
 *
 * @author Omer Aziz (omerb)
 *
 */

#ifndef AMO_TOOLS_SUITE_WATERHEATINGUSINGFLUE_H
#define AMO_TOOLS_SUITE_WATERHEATINGUSINGFLUE_H

#include "../losses/GasFlueGasMaterial.h"

class WaterHeatingUsingFlue {
public:
    enum SteamCondition {
        Superheated,
        Saturated
    };

    struct Output
    {
        Output(double tempSteamSat, double flowFlueGas, double effBoiler,
               double enthalpySteam, double enthalpyFW, double flowSteam,
               double flowFW, double specheatFG, double heatCapacityFG, double specheatFW, double heatCapacityFW,
               double heatCapacityMin, double ratingHeatRecFW, double tempFlueGasOut, double tempFWOut,
               double energySavingsBoiler, double costSavingsBoiler) :
                tempSteamSat(tempSteamSat), flowFlueGas(flowFlueGas), effBoiler(effBoiler),
                enthalpySteam(enthalpySteam), enthalpyFW(enthalpyFW), flowSteam(flowSteam),
                flowFW(flowFW), specheatFG(specheatFG), heatCapacityFG(heatCapacityFG), specheatFW(specheatFW), heatCapacityFW(heatCapacityFW),
                heatCapacityMin(heatCapacityMin), ratingHeatRecFW(ratingHeatRecFW), tempFlueGasOut(tempFlueGasOut), tempFWOut(tempFWOut),
                energySavingsBoiler(energySavingsBoiler), costSavingsBoiler(costSavingsBoiler) {}

        Output() = default;
        double tempSteamSat = 0, flowFlueGas = 0, effBoiler = 0,
                enthalpySteam = 0, enthalpyFW = 0, flowSteam = 0,
                flowFW = 0, specheatFG = 0, heatCapacityFG = 0, specheatFW = 0, heatCapacityFW = 0,
                heatCapacityMin = 0, ratingHeatRecFW = 0, tempFlueGasOut = 0, tempFWOut = 0,
                energySavingsBoiler = 0, costSavingsBoiler = 0;
    };

    /**
     * @param no arguments
     */
    WaterHeatingUsingFlue(){}

    /**
     *
     * @param gasCompositions
     * Constructor for GasCompositions with which flue gas losses will be calculated. All molecule parameters are the
	 * percentage of that molecule present in the fuel
	 *
	 * @param          substance name - string
	 * @param          CH4 % - double
	 * @param          C2H6 % - double
	 * @param          N2 % - double
	 * @param          H2 % - double
	 * @param          C3H8 % - double
	 * @param          C4H10_CnH2n % - double
	 * @param          H2O % - double
	 * @param          CO % - double
	 * @param          CO2 % - double
	 * @param          SO2 % - double
	 * @param          O2 % - double
     *
     * @param tempFlueGas double, units K
     * @param percO2 double, units percentage / fraction
     * @param tempCombAir double, units K
     * @param moistCombAir double, units percentage / fraction
     * @param ratingBoiler double, units Gj/hr
     * @param prSteam double, units MPa
     * @param tempSteam double, units K
     * @param tempFW double, units K
     * @param percBlowDown double, units percentage / fraction
     * @param effHX double, units percentage / fraction
     * @param opHours double, units Hr
     * @param costFuel double, units $/Gj
     * @param hhvFuel double, units kJ/Nm3
     * @param condSteam enum
     *
     *
     * @return Output
     * @param tempSteamSat double, units K
     * @param flowFlueGas double, units kg/hr
     * @param effBoiler
     * @param enthalpySteam double, units KJ/kg
     * @param enthalpyFW double, units KJ/kg
     * @param flowSteam double, units kg/hr
     * @param flowFW double, units kg/hr
     * @param specheatFG double, units KJ/kg K
     * @param heatCapacityFG double, units KJ/hr K
     * @param specheatFW double, units KJ/kg K
     * @param heatCapacityFW double, units KJ/hr K
     * @param heatCapacityMin double, units KJ/hr K
     * @param ratingHeatRecFW double, units KJ/hr
     * @param tempFlueGasOut double, units K
     * @param tempFWOut double, units K
     * @param energySavingsBoiler double, units GJ/yr
     * @param costSavingsBoiler double, units $/yr
     *
     */
    Output calculate(GasCompositions gasCompositions, const double tempFlueGas, const double percO2, const double tempCombAir,
                     const double moistCombAir, const double ratingBoiler, const double prSteam, const double tempAmbientAir,
                     const double tempSteam, const double tempFW, const double percBlowDown, const double effHX,
                     const double opHours, const double costFuel, const double hhvFuel, const SteamCondition condSteam = Superheated);
};

#endif //AMO_TOOLS_SUITE_WATERHEATINGUSINGFLUE_H
