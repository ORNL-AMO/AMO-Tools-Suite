/**
 * @file
 * @brief Calculator for flue gas heat losses
 *
 * This contains the inputs for calculating flue gas heat loss.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_FLUEGAS_H
#define AMO_SUITE_FLUEGAS_H

class gasComposition {
public:
	gasComposition(const double CH4, const double C2H6, const double N2, const double H2,
	               const double C3H8, const double C4H10_CnH2n, const double H2O, const double CO,
	               const double CO2, const double SO2, const double O2) :
			CH4(CH4), C2H6(C2H6), N2(N2), H2(H2), C3H8(C3H8), C4H10_CnH2n(C4H10_CnH2n), H2O(H2O),
			CO(CO), CO2(CO2), SO2(SO2), O2(O2)
	{}

	gasComposition( const gasComposition & composition ) :
			CH4(composition.CH4), C2H6(composition.C2H6), N2(composition.N2), H2(composition.H2),
			C3H8(composition.C3H8), C4H10_CnH2n(composition.C4H10_CnH2n), H2O(composition.H2O),
			CO(composition.CO), CO2(composition.CO2), SO2(composition.SO2), O2(composition.O2)
	{}

	const double CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2;
};

class FlueGas {
public:
    /**
     * Constructor for the flue gas losses with all inputs specified
     *
     * @param flueGasTemperature - Furnance Flue Gas Temperature in °F
     * @param oxygenPercentage - Percent Oxygen in Flue Gases
     * @param excessAirPercentage - Percent Excess Air
     * @param combustionAirTemperature - Combustion Air Temperature
     * @param composition - User defined gas compositions
     * @return nothing
     *
     * */
    FlueGas(const double flueGasTemperature,
            const double oxygenPercentage,
            const double excessAirPercentage,
            const double combustionAirTemperature,
            const gasComposition & composition) :
            flueGasTemperature_(flueGasTemperature),
            oxygenPercentage_(oxygenPercentage),
            excessAirPercentage_(excessAirPercentage),
            combustionAirTemperature_(combustionAirTemperature),
            composition_(composition),
            heatLoss_(0.0)
    {}

    double getHeatLoss();
private:
    const double flueGasTemperature_, oxygenPercentage_, excessAirPercentage_, combustionAirTemperature_;
	const gasComposition composition_;
    double heatLoss_;
};
#endif //AMO_SUITE_FLUEGAS_H
