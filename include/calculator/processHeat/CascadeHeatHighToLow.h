/**
 * @file
 * @brief Calculate energy savings from using exhaust gas (waste) of high temperature to supply heat to low temperature equipment.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_CASCADEHEATHIGHTOLOW_H
#define AMO_TOOLS_SUITE_CASCADEHEATHIGHTOLOW_H

#include "../losses/GasFlueGasMaterial.h"
#include "../losses/SolidLiquidFlueGasMaterial.h"

class CascadeHeatHighToLow {
public:
    struct Output
    {
        Output(double priFlueVolume, double hxEnergyRate, double eqEnergySupply, double effOpHours, double energySavings, double costSavings) :
                priFlueVolume(priFlueVolume), hxEnergyRate(hxEnergyRate), eqEnergySupply(eqEnergySupply),
                effOpHours(effOpHours), energySavings(energySavings), costSavings(costSavings) {}

        Output() = default;
        double priFlueVolume = 0, hxEnergyRate = 0, eqEnergySupply = 0, effOpHours = 0, energySavings = 0, costSavings = 0;
    };

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
     *
     * @param priFiringRate double
     * @param priExhaustTemperature double
     * @param priExhaustO2 double
     * @param priCombAirTemperature double
     * @param priOpHours double
     * @param priFuelHV double
     *
     * @param secExhaustTemperature double
     * @param secCombAirTemperature double
     * @param secOpHours double
     * @param secFuelCost double
     */
    CascadeHeatHighToLow(GasCompositions gasCompositions, double priFiringRate, double priExhaustTemperature,
                         double priExhaustO2, double priCombAirTemperature, double priOpHours, double priFuelHV,
                         double secExhaustTemperature, double secCombAirTemperature, double secOpHours, double secFuelCost) :
            priFiringRate(priFiringRate), priExhaustTemperature(priExhaustTemperature),
            priExhaustO2(priExhaustO2), priCombAirTemperature(priCombAirTemperature), priOpHours(priOpHours), priFuelHV(priFuelHV),
            secExhaustTemperature(secExhaustTemperature), secCombAirTemperature(secCombAirTemperature), secOpHours(secOpHours), secFuelCost(secFuelCost)
    {
        stoichAirVolume = gasCompositions.getStoichometricAir();
        priExcessAir = gasCompositions.getExcessAir(priExhaustO2);
        secAvailableHeat = gasCompositions.getAvailableHeat(secExhaustTemperature, priExcessAir, secCombAirTemperature);
    }

    /**
     *
     * @return
     * @param priFlueVolume double
     * @param hxEnergyRate double
     * @param eqEnergySupply double
     * @param effOpHours double
     * @param energySavings double
     * @param costSavings double
     *
     */
    CascadeHeatHighToLow::Output calculate();

private:
    const double priFlueSpecHeat = 0.0215;
    double stoichAirVolume = 0, priExcessAir = 0, secAvailableHeat = 0;
    double priFiringRate = 0, priExhaustTemperature = 0, priExhaustO2 = 0, priCombAirTemperature = 0, priOpHours = 0, priFuelHV = 0;
    double secExhaustTemperature = 0, secCombAirTemperature = 0, secOpHours = 0, secFuelCost = 0;
};

#endif //AMO_TOOLS_SUITE_CASCADEHEATHIGHTOLOW_H
