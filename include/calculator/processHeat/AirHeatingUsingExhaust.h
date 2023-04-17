/**
 * @file
 * @brief Estimate maximum air flow that can be heated by using exhaust gas heat of flue gases from a furnace or oven or a boiler.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H
#define AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H

#include "../losses/GasFlueGasMaterial.h"
#include "../losses/SolidLiquidFlueGasMaterial.h"

class AirHeatingUsingExhaust {
public:
    struct Output
    {
        Output(double hxColdAir, double hxOutletExhaust, double energySavings, double heatCapacityFlue, double heatCapacityAir) :
        hxColdAir(hxColdAir), hxOutletExhaust(hxOutletExhaust), energySavings(energySavings), heatCapacityFlue(heatCapacityFlue), heatCapacityAir(heatCapacityAir) {}

        Output() = default;
        double hxColdAir = 0, hxOutletExhaust = 0, energySavings = 0, heatCapacityFlue = 0, heatCapacityAir = 0;
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
     */
    AirHeatingUsingExhaust(GasCompositions gasCompositions) {
        fuelHeatingValue = gasCompositions.getHeatingValueVolume();
        stoichAir = gasCompositions.getStoichometricAir();
    }

    /**
     *
     * @param solidLiquidFlueGasMaterial
     * Constructor for the SolidLiquidFlueGasMaterial losses with all inputs specified
	 *
	 * @param          flueGasTemperature - double, Furnace Flue Gas Temperature in °F
	 * @param          excessAir - double, Percent Excess Air, expressed in normal percentage (i.e. 9% as 9 instead of 0.09)
	 * @param          combustionAirTemperature - double, Combustion Air Temperature in °F
	 * @param          fuelTemperature - double, fuel Temperature in °F
	 * @param          moistureInAirCombustion - double, moisture in Air Combustion as %
	 * @param          ashDischargeTemperature - double, ash discharge Temperature in °F
	 * @param          unburnedCarbonInAsh - double, unburned carbon in ash expressed as %
	 * @param          carbon, hydrogen, sulphur, inertAsh, o2, moisture, nitrogen content in fuel (as percentage)
	 *
     */
    AirHeatingUsingExhaust(SolidLiquidFlueGasMaterial solidLiquidFlueGasMaterial, bool solids = true) {
        solids = solids;//keep or fix unused variable
        fuelHeatingValue = solidLiquidFlueGasMaterial.getHeatingValueFuel();
        stoichAir = solidLiquidFlueGasMaterial.getStoichAirFuel();
    }

    /**
     *
     * @param flueTemperature double, units F
     * @param excessAir double, units percentage / fraction
     * @param fireRate double, units MMBtu/hr
     * @param airflow double, units scfm
     * @param inletTemperature double, units F
     * @param heaterEfficiency double, units percentage / fraction
     * @param hxEfficiency double, units percentage / fraction
     * @param operatingHours double, units hr
     * @return Output
     * @param hxColdAir double, units Btu/hr
     * @param hxOutletExhaust double, units F
     * @param energySavings double, units MMBtu/yr
     * @param heatCapacityFlue double
     * @param heatCapacityAir double
     *
     */
    AirHeatingUsingExhaust::Output calculate(const double flueTemperature, const double excessAir, const double fireRate,
                                             const double airflow, const double inletTemperature,
                                             const double heaterEfficiency, const double hxEfficiency, const double operatingHours);

private:
    double fuelHeatingValue = 1;
    double stoichAir = 0;
};

#endif //AMO_TOOLS_SUITE_AIRHEATINGUSINGEXHAUST_H
