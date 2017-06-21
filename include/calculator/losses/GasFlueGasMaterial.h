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

#ifndef AMO_SUITE_GASFLUEGASMATERIAL_H
#define AMO_SUITE_GASFLUEGASMATERIAL_H

#include <unordered_map>
#include <functional>
#include <string>
#include <cmath>
#include <memory>

     /**
     * @class GasProperties GasFlueGasMaterial.h
     */
class GasProperties {
public:
	/**
     * Constructor
     * @param specificHeat specific heat in btu/hr
     * @param molecularWeight molecular weight in g/mol
     * @param specificWeight specific weight in lb/scf
     * @param compPercent composition percent as %
     * @param compByVol composition by volume as %
     * @param o2Generated O2 generated in g/mol
     * @param heatingValue heating value in btu/lb
     * @param h2oGenerated H2O generated in g/mol
     * @param co2Generated CO2 generated in g/mol
     * @return nothing
     */

	GasProperties( const std::function< double ( double t ) > specificHeat,
	               const double molecularWeight,
	               const double specificWeight,
	               const double compPercent,
	               const double compByVol,
	               const int o2Generated,
	               const int heatingValue,
	               const double h2oGenerated,
	               const double co2Generated
	) :
			specificHeat(specificHeat), molecularWeight(molecularWeight), specificWeight(specificWeight),
	        compByVol(compPercent), compAdjByVol(compByVol), h2oGenerated(h2oGenerated), co2Generated(co2Generated),
			o2Generated(o2Generated), heatingValue(heatingValue)
	{};

private:
	friend class GasCompositions;
	const std::function< double ( double t ) > specificHeat;
	// compByWeight == X double bar, compAdjByVol == X bar in document
	double compByWeight;
	const double molecularWeight, specificWeight, compByVol, compAdjByVol, h2oGenerated, co2Generated;

	// TODO so2Generated is always 0 according to the one table, are these all the gas types we deal with or not?
	const int so2Generated = 0, o2Generated, heatingValue;
};


// TODO should be a private class but unit tests need access to this


class GasCompositions {
public:
	/**
	 * Constructor for GasCompositions with which flue gas losses will be calculated. All molecule parameters are the
	 * percentage of that molecule present in the fuel
	 *
	 * @param substance name - string
	 * @param CH4 % - double
	 * @param C2H6 % - double
	 * @param N2 % - double
	 * @param H2 % - double
	 * @param C3H8 % - double
	 * @param C4H10_CnH2n % - double
	 * @param H2O % - double
	 * @param CO % - double
	 * @param CO2 % - double
	 * @param SO2 % - double
	 * @param O2 % - double
	 *
	 * */
	GasCompositions(const std::string & substance, const double CH4, const double C2H6, const double N2,
	                const double H2, const double C3H8, const double C4H10_CnH2n, const double H2O,
	                const double CO, const double CO2, const double SO2, const double O2) :
			substance(substance),
			totalPercent(CH4 + C2H6 + N2 + H2 + C3H8 + C4H10_CnH2n + H2O + CO + CO2 + SO2 + O2),
			CH4(std::make_shared<GasProperties>([] (double t) { return 4.23 + 0.01177 * t; }, 16.042, 0.042417, CH4,
			                  CH4 / totalPercent, 64, 23875, 36.032, 44.01)),
			C2H6(std::make_shared<GasProperties>([] (double t) { return 4.04 + 0.01636 * t; }, 30.068, 0.079503, C2H6,
			                   C2H6 / totalPercent, 112, 22323, 54.048, 88.02)),
			N2(std::make_shared<GasProperties>([] (double t) { return 9.47 - 3.47 * 1000 / t + 1.07 * 1000000 / (t * t); },
			                 28.016, 0.074077, N2, N2 / totalPercent, 0, 0, 0, 0)),
			H2(std::make_shared<GasProperties>([] (double t) { return 5.76 + 0.578 * t / 1000 + 20 / pow(t, 0.5); }, 2.016, 0.005331,
			                 H2, H2 / totalPercent, 16, 61095, 18.016, 0)),
			C3H8(std::make_shared<GasProperties>([] (double t) { (void)t; return 17.108; }, 44.094, 0.116589, C3H8,
			                   C3H8 / totalPercent, 160, 21669, 72.064, 132.03)),
			C4H10_CnH2n(std::make_shared<GasProperties>([] (double t) { (void)t; return 22.202; }, 58.12, 0.153675, C4H10_CnH2n,
			                          C4H10_CnH2n / totalPercent, 208, 21321, 90.08, 176.04)),
			H2O(std::make_shared<GasProperties>([] (double t) { return 19.86 - 597 / pow(t, 0.5) + 7500 / t; }, 18.016, 0.047636, H2O,
			                  H2O / totalPercent, 0, 0, 18.016, 0)),
			CO(std::make_shared<GasProperties>([] (double t) { return 9.46 - 3.29 * 1000 / t + 1.07 * 1000000 / (t * t); },
			                 28.01, 0.074061, CO, CO / totalPercent, 16, 4347, 0, 44.01)),
			CO2(std::make_shared<GasProperties>([] (double t) { return 16.2 - 6.53 * 1000 / t + 1.41 * 1000000 / (t * t); },
			                  44.01, 0.116367, CO2, CO2 / totalPercent, 0, 0, 0, 44.01)),
			SO2(std::make_shared<GasProperties>([] (double t) { (void)t; return 17.472; }, 64.06, 0.169381, SO2, SO2 * 100 / totalPercent,
			                  0, 0, 0, 0)),
			O2(std::make_shared<GasProperties>([] (double t) { return 11.515 - 172 / pow(t, 0.5) + 1530 / t; }, 32.00, 0.084611, O2,
			                 O2 / totalPercent, -32, 0, 0, 0))
	{
		gasses = {{"CH4", this->CH4}, {"C2H6", this->C2H6}, {"N2", this->N2}, {"H2", this->H2},
		          {"C3H8", this->C3H8}, {"C4H10_CnH2n", this->C4H10_CnH2n}, {"H2O", this->H2O}, {"CO", this->CO},
		          {"CO2", this->CO2}, {"SO2", this->SO2}, {"O2", this->O2}};
	}

    /**
     * Gets the gas by
     *
     * @param gasName const string, name of gas
     *
     * @return double, compostion by volume as %
     */
	double getGasByVol(const std::string & gasName) const {
		auto const gas = gasses.find(gasName);
		if (gas == gasses.end()) {
			throw std::runtime_error("Cannot find " + gasName + " in gasses");
		}
		return gas->second->compByVol;
	}

    /**
     * Gets the name of substance
     *
     * @return string, name of substance
     */
	std::string getSubstance() const;

    /**
     * Gets the ID of gas
     *
     * @return int, ID of gas
     */
	int getID() const {
		return this->id;
	}

    /**
     * Sets the ID of gas
     *
     * @param id const int, ID number for gas
     *
     * @return nothing
     */
	void setID(const int id) {
		this->id = id;
	}

private:
	friend class GasFlueGasMaterial;
	friend class SQLite;

	void calculateCompByWeight();
	double calculateSensibleHeat(const double combustionAirTemp);
	double calculateHeatCombustionAir(const double combustionAirTemp, const double excessAir);
	double calculateHeatingValueFuel();
	void calculateMassFlueGasComponents(const double excessAir);
	void calculateEnthalpy();
	double calculateTotalHeatContentFlueGas(const double flueGasTemperature);

	// the hash map holds a reference to the GasProperties below for easier iterable summations
	std::unordered_map <std::string, std::shared_ptr<GasProperties>> gasses;
	int id;
	const std::string substance;
	const double totalPercent;
	double hH2Osat, tH2Osat;
	double mH2O = 0, mCO2 = 0, mO2 = 0, mN2 = 0, mSO2 = 0;
	std::shared_ptr<GasProperties> CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2, O2;
};


class GasFlueGasMaterial {
public:
    /**
     * Constructor for the flue gas losses with all inputs specified
     *
     * @param flueGasTemperature - Furnace Flue Gas Temperature in °F
     * @param excessAirPercentage - Percent Excess Air, expressed in normal percentage (i.e. 9% as 9 instead of 0.09)
     * @param combustionAirTemperature - Combustion Air Temperature
     * @param compositions - User defined gas compositions
     * @return nothing
     *
     * */
    GasFlueGasMaterial(const double flueGasTemperature,
            const double excessAirPercentage,
            const double combustionAirTemperature,
            GasCompositions & compositions) :
            flueGasTemperature_(flueGasTemperature),
            excessAirPercentage_(excessAirPercentage / 100.0),
            combustionAirTemperature_(combustionAirTemperature),
            compositions_(compositions)
    {}

	/**
     * Gets the heat loss
     *
     * @return double, heat loss in btu/hr
     */
    double getHeatLoss();

private:
    const double flueGasTemperature_, excessAirPercentage_, combustionAirTemperature_;
	GasCompositions compositions_;
};
#endif //AMO_SUITE_GASFLUEGASMATERIAL_H
