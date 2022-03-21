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
        Output(double priFlueVolume, double hxEnergyRate, double eqEnergySupply, double effOpHours, double energySavings, double costSavings, double hourlySavings,
               double priExcessAir, double priAvailableHeat, double secExcessAir, double secAvailableHeat) :
                priFlueVolume(priFlueVolume), hxEnergyRate(hxEnergyRate), eqEnergySupply(eqEnergySupply),
                effOpHours(effOpHours), energySavings(energySavings), costSavings(costSavings), hourlySavings(hourlySavings),
                priExcessAir(priExcessAir), priAvailableHeat(priAvailableHeat), secExcessAir(secExcessAir), secAvailableHeat(secAvailableHeat) {}

        Output() = default;
        double priFlueVolume = 0, hxEnergyRate = 0, eqEnergySupply = 0, effOpHours = 0, energySavings = 0, costSavings = 0, hourlySavings = 0,
                priExcessAir = 0, priAvailableHeat = 0, secExcessAir = 0, secAvailableHeat = 0;
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
   * @param fuelHV double, units Btu/SCF
   * @param fuelCost double, units $/MMBtu

   * @param priFiringRate double, units MMBtu/hr
   * @param priExhaustTemperature double, units  F
   * @param priExhaustO2 double, percentage / fraction
   * @param priCombAirTemperature double, units F
   * @param priOpHours double, units hrs/yr
   *
   * @param secFiringRate double, units MMBtu/hr
   * @param secExhaustTemperature double, units F
   * @param secExhaustO2 double, percentage / fraction
   * @param secCombAirTemperature double, units F
   * @param secOpHours double, units hrs/yr
   */
    CascadeHeatHighToLow(GasCompositions gasCompositions, double fuelHV, double fuelCost,
                         double priFiringRate, double priExhaustTemperature, double priExhaustO2, double priCombAirTemperature, double priOpHours,
                         double secFiringRate, double secExhaustTemperature, double secExhaustO2, double secCombAirTemperature, double secOpHours,
                         const double fuelTempF = 60, const double ambientAirTempF = 60, const double combAirMoisturePerc = 0) :
            fuelHV(fuelHV), fuelCost(fuelCost),
            priFiringRate(priFiringRate), priExhaustTemperature(priExhaustTemperature), priExhaustO2(priExhaustO2), priCombAirTemperature(priCombAirTemperature), priOpHours(priOpHours),
            secFiringRate(secFiringRate), secExhaustTemperature(secExhaustTemperature), secExhaustO2(secExhaustO2), secCombAirTemperature(secCombAirTemperature), secOpHours(secOpHours)
    {
        const auto res = gasCompositions.getProcessHeatProperties(priExhaustTemperature, priExhaustO2, priCombAirTemperature,
                                                                  fuelTempF, ambientAirTempF, combAirMoisturePerc);
        stoichAirVolume = res.stoichAir;
        priExcessAir = res.excessAir;
        priAvailableHeat = res.availableHeat;
        priFlueSpecHeat = res.specificHeat;
        priFlueDensity = res.density / 16.018463;

        const auto resSec = gasCompositions.getProcessHeatProperties(secExhaustTemperature, secExhaustO2, secCombAirTemperature,
                                                                     fuelTempF, ambientAirTempF, combAirMoisturePerc);
        secExcessAir = resSec.excessAir;
        secAvailableHeat = resSec.availableHeat;
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
     * @param hourlySavings double
     * @param priExcessAir double, percentage / fraction
     * @param priAvailableHeat double, percentage / fraction
     * @param secExcessAir double, percentage / fraction
     * @param secAvailableHeat double, percentage / fraction
     *
     */
    CascadeHeatHighToLow::Output calculate();

private:
    double stoichAirVolume = 0, priExcessAir = 0, secExcessAir = 0, priAvailableHeat = 0, secAvailableHeat = 0, priFlueSpecHeat = 0, priFlueDensity = 0;
    double priFiringRate = 0, priExhaustTemperature = 0, priExhaustO2 = 0, priCombAirTemperature = 0, priOpHours = 0;
    double secFiringRate = 0, secExhaustTemperature = 0, secExhaustO2 = 0, secCombAirTemperature = 0, secOpHours = 0;
    double fuelHV = 0, fuelCost = 0;
};

#endif //AMO_TOOLS_SUITE_CASCADEHEATHIGHTOLOW_H
