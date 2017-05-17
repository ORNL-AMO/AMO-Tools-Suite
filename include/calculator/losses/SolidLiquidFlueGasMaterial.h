#ifndef AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H
#define AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H

#include <unordered_map>

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
			const double nitrogen
	) :
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

private:
	const double flueGasTemperature, excessAirPercentage, combustionAirTemperature;
	const double fuelTemperature, moistureInAirCombustion, ashDischargeTemperature, unburnedCarbonInAsh;
	const double carbon, hydrogen, sulphur, inertAsh, o2, moisture, nitrogen;

//	class compound {
//	public:
//		compound(const std::function< double ( double t ) > specificHeat,
//		         const double molecularWeight) :
//				specificHeat(specificHeat),
//		        molecularWeight(molecularWeight)
//		{}
//
//		const std::function< double ( double t ) > specificHeat;
//		const double molecularWeight;
//	};

//	std::unordered_map< std::string, compound > compounds;

};



#endif //AMO_TOOLS_SUITE_SOLIDLIQUIDFLUEGASMATERIAL_H
