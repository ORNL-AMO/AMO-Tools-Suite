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
private:
	friend class gasCompositions;

	gasProperties( std::function< double ( double t ) > specificHeat,
	               const double molecularWeight,
	               const double specificWeight,
	               const double compPercent,
	               const double compByVol
	) :
			specificHeat(specificHeat), molecularWeight(molecularWeight), specificWeight(specificWeight),
	        compByVol(compPercent), compAdjByVol(compByVol)
	{};

	std::function< double ( double t ) > specificHeat;
	double compByWeight;
	const double molecularWeight, specificWeight, compByVol, compAdjByVol;
};


class gasCompositions {
public:
	/**
	 * Constructor for gasCompositions with which flue gas losses will be calculated
	 *
	 * @param all parameters are the percentage of that particular molecule present in the fuel
	 *
	 * */
	gasCompositions(const double CH4, const double C2H6, const double N2, const double H2,
	               const double C3H8, const double C4H10_CnH2n, const double H2O, const double CO,
	               const double CO2, const double SO2, const double O2) :
			totalPercent(CH4 + C2H6 + N2 + H2 + C3H8 + C4H10_CnH2n + H2O + CO + CO2 + SO2 + O2),
			CH4(gasProperties([] (double t) { return 4.23 + 0.01177 * t; }, 16.042, 0.042417, CH4,
			                  CH4 * 100 / totalPercent)),
			C2H6(gasProperties([] (double t) { return 4.04 + 0.01636 * t; }, 30.068, 0.079503, C2H6,
			                   C2H6 * 100 / totalPercent)),
			N2(gasProperties([] (double t) { return 9.47 - 3.47 * 1000 / t + 1.07 * 1000000 / (t * t); },
			                 28.016, 0.074077, N2, N2 * 100 / totalPercent)),
			H2(gasProperties([] (double t) { return 5.76 + 0.578 * t / 1000 + 20 / pow(t, 0.5); }, 2.016, 0.005331,
			                 H2, H2 * 100 / totalPercent)),
			C3H8(gasProperties([] (double t = 0) { return 17.108; }, 44.094, 0.116589, C3H8,
			                   C3H8 * 100 / totalPercent)),
			C4H10_CnH2n(gasProperties([] (double t = 0) { return 22.202; }, 58.12, 0.153675, C4H10_CnH2n,
			                          C4H10_CnH2n * 100 / totalPercent)),
			H2O(gasProperties([] (double t) { return 19.86 - 597 / pow(t, 0.5) + 7500 / t; }, 18.016, 0.047636, H2O,
			                  H2O * 100 / totalPercent)),
			CO(gasProperties([] (double t) { return 9.46 - 3.29 * 1000 / t + 1.07 * 1000000 / (t * t); },
			                 28.01, 0.074061, CO, CO * 100 / totalPercent)),
			CO2(gasProperties([] (double t) { return 16.2 - 6.53 * 1000 / t + 1.41 * 1000000 / (t * t); },
			                  44.01, 0.116367, CO2, CO2 * 100 / totalPercent)),
			SO2(gasProperties([] (double t = 0) { return 17.472; }, 64.06, 0.169381, SO2, SO2 * 100 / totalPercent)),
			O2(gasProperties([] (double t) { return 11.515 - 172 / pow(t, 0.5) + 1530 / t; }, 32.00, 0.084611, O2,
			                 O2 * 100 / totalPercent))
	{}

	gasCompositions( const gasCompositions & comps ) :
			CH4(comps.CH4), C2H6(comps.C2H6), N2(comps.N2), H2(comps.H2), C3H8(comps.C3H8),
			C4H10_CnH2n(comps.C4H10_CnH2n), H2O(comps.H2O), CO(comps.CO), CO2(comps.CO2), SO2(comps.SO2), O2(comps.O2),
	        totalPercent(comps.CH4.compByVol + comps.C2H6.compByVol + comps.N2.compByVol + comps.H2.compByVol
	                     + comps.C3H8.compByVol+ comps.C4H10_CnH2n.compByVol + comps.H2O.compByVol
	                     + comps.CO.compByVol + comps.CO2.compByVol + comps.SO2.compByVol + comps.O2.compByVol)
	{

	}

	const double totalPercent;
	const gasProperties CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2;
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
            const gasCompositions & compositions) :
            flueGasTemperature_(flueGasTemperature),
            oxygenPercentage_(oxygenPercentage),
            excessAirPercentage_(excessAirPercentage),
            combustionAirTemperature_(combustionAirTemperature),
            compositions_(compositions),
            heatLoss_(0.0)
    {}

    double getHeatLoss();

private:
    const double flueGasTemperature_, oxygenPercentage_, excessAirPercentage_, combustionAirTemperature_;
	const gasCompositions compositions_;
    double heatLoss_;
};
#endif //AMO_SUITE_FLUEGAS_H
