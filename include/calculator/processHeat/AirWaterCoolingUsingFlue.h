/**
 * @file
 * @brief Calculate Heat Recovery by using flue gas - condensing heat exchanger.
 *
 *
 *
 * @author Omer Aziz (omerb)
 *
 */

#ifndef AMO_TOOLS_SUITE_AIRWATERCOOLINGUSINGFLUE_H
#define AMO_TOOLS_SUITE_AIRWATERCOOLINGUSINGFLUE_H

#include "../losses/GasFlueGasMaterial.h"

class AirWaterCoolingUsingFlue {
public:
    struct Output
    {
        Output(double excessAir, double flowFlueGas, double specHeat, double fracCondensed,
               double effThermal, double effThermalLH, double effLH, double heatRecovery, double sensibleHeatRecovery) :
                excessAir(excessAir), flowFlueGas(flowFlueGas), specHeat(specHeat), fracCondensed(fracCondensed),
                effThermal(effThermal), effThermalLH(effThermalLH), effLH(effLH), heatRecovery(heatRecovery), sensibleHeatRecovery(sensibleHeatRecovery){}

        Output() = default;
        double excessAir = 0, flowFlueGas = 0, specHeat = 0, fracCondensed = 0,
        effThermal = 0, effThermalLH = 0, effLH = 0, heatRecovery = 0, sensibleHeatRecovery = 0;
    };

    AirWaterCoolingUsingFlue(){}

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
     * @param heatInput double, units MM BTU / hr
     * @param tempFlueGasInF double, units F
     * @param tempFlueGasOutF double, units F
     * @param tempCombAirF double, units F
     * @param fuelTempF double, units F
     * @param percO2, units percentage / fraction
     * @param ambientAirTempF double, units F, default 60 F
     * @param moistCombAir, units percentage / fraction, default 0
     *
     *
     * @return
     * @param excessAir double, units percentage / fraction
     * @param flowFlueGas double, units lbs / hr
     * @param specHeat double, units Btu / (lb.F)
     * @param fracCondensed double, units fraction
     * @param effThermal / availableHeat double, units percentage / fraction
     * @param effThermalLH double, units percentage / fraction
     * @param effLH / heatReclaimed double, units percentage / fraction
     * @param heatRecovery / latentHeatRecovery double, units MM Btu / hr
     * @param sensibleHeatRecovery double, units MM Btu / hr
     *
     */
    Output calculate(GasCompositions gasCompositions, const double heatInput, const double tempFlueGasInF, const double tempFlueGasOutF,
                     const double tempCombAirF, const double fuelTempF, const double percO2, const double ambientAirTempF = 60, const double moistCombAir = 0){

        const auto res = gasCompositions.getProcessHeatProperties(tempFlueGasInF, percO2, tempCombAirF,
                                                                  fuelTempF, ambientAirTempF, moistCombAir);
        const double fracCondensed = (1 - (0.0000009 * pow(tempFlueGasOutF,3.0136)) / (2.8082 - 0.1168 * percO2 * 100));
        const double effLH = (fracCondensed * 0.00935 * (1087 /*+ 0.467 * tempFlueGasOutF - tempCombAirF*/))/100;
        const double flowFlueGas = heatInput * (0.0763 * (0.6 + (res.stoichAir * (1 + res.excessAir)))) * 1000000 / res.heatValueFuel;
        const double sensibleHeatRecovery = res.specificHeat * (tempFlueGasInF - tempFlueGasOutF) * flowFlueGas / 1000000;

        return Output(res.excessAir, flowFlueGas, res.specificHeat, fracCondensed,
                      res.availableHeat, res.availableHeat + effLH, effLH, heatInput * effLH, sensibleHeatRecovery);
    }
};

#endif //AMO_TOOLS_SUITE_AIRWATERCOOLINGUSINGFLUE_H
