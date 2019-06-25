#ifndef AMO_TOOLS_SUITE_STEAMPROPERTIES_H
#define AMO_TOOLS_SUITE_STEAMPROPERTIES_H

#include <string>
#include "SteamSystemModelerTool.h"

class SteamSystemModelerTool;

class SteamProperties {
public:

    ///enum class for ThermodynamicQuantity
	enum class ThermodynamicQuantity {
		TEMPERATURE,
		ENTHALPY,
		ENTROPY,
		QUALITY
	};

    /**
     * Constructor for SteamProperties class
     * @param pressure double, pressure in MPa
     * @param quantityValue, Thermodynamic Property used for calculation- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
     * @param quantity ThermodynamicQuantity, the value type used to calculate steam properties (TEMPERATURE, ENTHALPY, etc.)
     */
	SteamProperties(const double pressure, const ThermodynamicQuantity quantity, const double quantityValue)
			: pressure_(pressure),
			  quantityValue_(quantityValue),
			  thermodynamicQuantity_(quantity)
	{}

    /**
     * Calculates the steam properties
     *
     * @param pressure double, pressure in MPa
     * @param quantityValue ThermodynamicQuantity, the type of value that will be used to calculate the steam properties (TEMPERATURE,ENTHALPY, etc.)
     *
     * @return SteamSystemModelerTool::SteamPropertiesOutput, steam properties
     */
     SteamSystemModelerTool::SteamPropertiesOutput calculate();

private:
    /**
     * Calculates the steam properties using temperature
     * @param pressure double, pressure in MPa
     * @param temperature double, temperature in Kelvins
     * @return SteamSystemModelerTool::SteamPropertiesOutput, steam properties
     */
	SteamSystemModelerTool::SteamPropertiesOutput waterPropertiesPressureTemperature(double pressure, double temperature);

    /**
     * Calculates the steam properties using specific enthalpy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return SteamSystemModelerTool::SteamPropertiesOutput, steam properties
     */
	SteamSystemModelerTool::SteamPropertiesOutput waterPropertiesPressureEnthalpy(double pressure, double enthalpy);

    /**
     * Calculates the steam properties using specific entropy
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return SteamSystemModelerTool::SteamPropertiesOutput, steam properties
     */
	SteamSystemModelerTool::SteamPropertiesOutput waterPropertiesPressureEntropy(double pressure, double entropy);

    /**
     * Calculates the steam properties using specific quality
     * @param pressure double, pressure in MPa
     * @param quality double, specific quality - unitless
     * @return SteamSystemModelerTool::SteamPropertiesOutput, steam properties
     */
	SteamSystemModelerTool::SteamPropertiesOutput waterPropertiesPressureQuality(double pressure, double quality);

//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

//	Region regionSelect(const double pressure, const double temperature);
private:
	const double pressure_, quantityValue_;
	const ThermodynamicQuantity thermodynamicQuantity_;

};

#endif //AMO_TOOLS_SUITE_STEAMPROPERTIES_H
