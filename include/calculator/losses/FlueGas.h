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

#include <unordered_map>
#include <functional>
#include <string>

class gasProperties {
public:
	gasProperties( std::function< double ( double t ) > specificHeat, const double molecularWeight, const double specificWeight) :
			specificHeat(specificHeat), molecularWeight(molecularWeight), specificWeight(specificWeight)
	{};

	std::function< double ( double t ) > specificHeat;
	// TODO rename userInput to something better (it's just user defined gas percentage), use xBar, x double bar etc
	double userInput, xBar, xBarBar, molecularWeight, specificWeight;
};

class gasComposition {
public:
	gasComposition(const double CH4, const double C2H6, const double N2, const double H2,
	               const double C3H8, const double C4H10_CnH2n, const double H2O, const double CO,
	               const double CO2, const double SO2, const double O2) :
			CH4(gasProperties([] (double t) { return 4.23 + 0.01177 * t; }, 16.042, 0.042417)),
			C2H6(gasProperties([] (double t) { return 4.04 + 0.01636 * t; }, 30.068, 0.079503)),
			N2(gasProperties([] (double t) { return 9.47 - 3.47 * 1000 / t + 1.07 * 1000000 / (t * t); }, 28.016, 0.074077)),
			H2(gasProperties([] (double t) { return 5.76 + 0.578 * t / 1000 + 20 / pow(t, 0.5); }, 2.016, 0.005331)),
			C3H8(gasProperties([] (double t = 0) { return 17.108; }, 44.094, 0.116589)),
			C4H10_CnH2n(gasProperties([] (double t = 0) { return 22.202; }, 58.12, 0.153675)),
			H2O(gasProperties([] (double t) { return 19.86 - 597 / pow(t, 0.5) + 7500 / t; }, 18.016, 0.047636)),
			CO(gasProperties([] (double t) { return 9.46 - 3.29 * 1000 / t + 1.07 * 1000000 / (t * t); }, 28.01, 0.074061)),
			CO2(gasProperties([] (double t) { return 16.2 - 6.53 * 1000 / t + 1.41 * 1000000 / (t * t); }, 44.01, 0.116367)),
			SO2(gasProperties([] (double t = 0) { return 17.472; }, 64.06, 0.169381)),
			O2(gasProperties([] (double t) { return 11.515 - 172 / pow(t, 0.5) + 1530 / t; }, 32.00, 0.084611))


//			CH4(CH4), C2H6(C2H6), N2(N2), H2(H2), C3H8(C3H8), C4H10_CnH2n(C4H10_CnH2n), H2O(H2O),
//			CO(CO), CO2(CO2), SO2(SO2), O2(O2),
//			totalPercent(CH4 + C2H6 + N2 + H2 + C3H8 + C4H10_CnH2n + H2O + CO + CO2 + SO2 + O2)
	{}

	gasComposition( const gasComposition & composition ) :
			CH4(composition.CH4), C2H6(composition.C2H6), N2(composition.N2), H2(composition.H2),
			C3H8(composition.C3H8), C4H10_CnH2n(composition.C4H10_CnH2n), H2O(composition.H2O),
			CO(composition.CO), CO2(composition.CO2), SO2(composition.SO2), O2(composition.O2)
//	        totalPercent(CH4 + C2H6 + N2 + H2 + C3H8 + C4H10_CnH2n + H2O + CO + CO2 + SO2 + O2)
	{}

	const gasProperties CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2;
//	const double totalPercent;

// this are the correct specific weights for each molecule according to the table
//	const std::unordered_map < std::string, const double > specificWeight = {
//			{"CH4", 0.042417},
//			{"C2H6", 0.079503},
//			{"N2", 0.074077},
//			{"H2", 0.005331},
//			{"C3H8", 0.116589},
//			{"C4H10_CnH2n", 0.153675},
//			{"H2O", 0.047636},
//			{"CO", 0.074061},
//			{"CO2", 0.116367},
//			{"SO2", 0.169381},
//			{"O2", 0.084611}
//	};
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
