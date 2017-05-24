#ifndef AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H
#define AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H

#include <string>

class SolidLiquidFlueGasMaterial {
public:
	/**
	 * Constructor for the SolidLiquidFlueGasMaterial losses with all inputs specified
	 *
	 * @param flueGasTemperature - Furnace Flue Gas Temperature in °F
	 * @param excessAirPercentage - Percent Excess Air, expressed in normal percentage (i.e. 9% as 9 instead of 0.09)
	 * @param combustionAirTemperature - Combustion Air Temperature
	 * @param fuelTemperature - fuel Temperature in °F
	 * @param moistureInAirCombustion - moisture in Air Combustion
	 * @param ashDischargeTemperature - ash discharge Temperature
	 * @param unburned carbon in ash - unburned carbon in ash expressed as a percentage
	 * @param carbon, hydrogen, sulphur, inertAsh, o2, moisture, and nitrogen content in fuel (as percentage)
	 * @return nothing
	 *
	 * */
	SolidLiquidFlueGasMaterial(
			const double flueGasTemperature,
			const double excessAirPercentage,
			const double combustionAirTemperature,
			const double fuelTemperature,
			const double moistureInAirCombustion,
			const double ashDischargeTemperature,
			const double unburnedCarbonInAsh,
			const double carbon,
			const double hydrogen,
			const double sulphur,
			const double inertAsh,
			const double o2,
			const double moisture,
			const double nitrogen) :
			flueGasTemperature(flueGasTemperature),
			excessAirPercentage(excessAirPercentage / 100.0),
			combustionAirTemperature(combustionAirTemperature),
			fuelTemperature(fuelTemperature),
			moistureInAirCombustion(moistureInAirCombustion),
			ashDischargeTemperature(ashDischargeTemperature),
			unburnedCarbonInAsh(unburnedCarbonInAsh / 100.0),
			carbon(carbon / 100),
			hydrogen(hydrogen / 100),
			sulphur(sulphur / 100),
			inertAsh(inertAsh / 100),
			o2(o2 / 100),
			moisture(moisture / 100),
			nitrogen(nitrogen / 100)
	{}

	double getHeatLoss();
	std::string getSubstance() const { return substance; }
	double getFlueGasTemperature() const { return flueGasTemperature; }
	double getExcessAirPercentage() const { return excessAirPercentage; }
	double getCombustionAirTemperature() const { return combustionAirTemperature; }
	double getFuelTemperature() const { return fuelTemperature; }
	double getMoistureInAirCombustion() const { return moistureInAirCombustion; }
	double getAshDischargeTemperature() const { return ashDischargeTemperature; }
	double getUnburnedCarbonInAsh() const { return unburnedCarbonInAsh; }
	double getCarbon() const { return carbon; }
	double getHydrogen() const { return hydrogen; }
	double getSulphur() const { return sulphur; }
	double getInertAsh() const { return inertAsh; }
	double getO2() const { return o2; }
	double getMoisture() const { return moisture; }
	double getNitrogen() const { return nitrogen; }

	void setSubstance( std::string const & substanceName ) { substance = substanceName; }
	void setFlueGasTemperature( const double temperature ) { flueGasTemperature = temperature; }
	void setExcessAirPercentage( const double excessAir ) { excessAirPercentage = excessAir; }
	void setCombustionAirTemperature( const double temperature ) { combustionAirTemperature = temperature; }
	void setFuelTemperature( const double temperature ) { fuelTemperature = temperature; }
	void setMoistureInAirCombustion( const double moisture ) { moistureInAirCombustion = moisture; }
	void setAshDischargeTemperature( const double temperature ) { ashDischargeTemperature = temperature; }
	void setUnburnedCarbonInAsh( const double unburnedCarbon ) { unburnedCarbonInAsh = unburnedCarbon; }

private:
	friend class SQLite;

	SolidLiquidFlueGasMaterial(
			const std::string & substance,
			const double carbon,
			const double hydrogen,
			const double sulphur,
			const double inertAsh,
			const double o2,
			const double moisture,
			const double nitrogen) :
			substance(substance),
			carbon(carbon / 100),
			hydrogen(hydrogen / 100),
			sulphur(sulphur / 100),
			inertAsh(inertAsh / 100),
			o2(o2 / 100),
			moisture(moisture / 100),
			nitrogen(nitrogen / 100)
	{}

	std::string substance = "UndefinedSubstance";
	double flueGasTemperature, excessAirPercentage, combustionAirTemperature;
	double fuelTemperature, moistureInAirCombustion, ashDischargeTemperature, unburnedCarbonInAsh;
	const double carbon, hydrogen, sulphur, inertAsh, o2, moisture, nitrogen;
};

#endif //AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H
