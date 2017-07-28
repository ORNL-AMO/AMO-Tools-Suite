//
// Created by Preston Shires on 7/19/17.
//

#include <unordered_map>
#include <string>

#ifndef AMO_TOOLS_SUITE_STEAMPROPERTIES_H
#define AMO_TOOLS_SUITE_STEAMPROPERTIES_H

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
     * @param quantity ThermodynamicQuantity, the value type used to calculate steam propeties (TEMPERATURE, ENTHALPY, etc.)
     */
	SteamProperties(ThermodynamicQuantity quantity) :
			thermodynamicQuantity_(quantity)
	{}

    /**
     * Calculates the steam properties
     *
     * @param pressure double, pressure in MPa
     * @param quantityValue ThermodynamicQuantity, the type of value that will be used to calculate the steam properties (TEMPERATURE,ENTHALPY, etc.)
     *
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> calculate(const double pressure, const double quantityValue);

//private:
    /**
     * Calculates the steam properties using temperature
     * @param pressure double, pressure in MPa
     * @param temperature double, temperature in Kelvins
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureTemperature(const double pressure, const double temperature);

    /**
     * Calculates the steam properties using specific enthalpy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureEnthalpy(const double pressure, const double enthalpy);

    /**
     * Calculates the steam properties using specific entropy
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureEntropy(const double pressure, const double entropy);

    /**
     * Calculates the steam properties using specific quality
     * @param pressure double, pressure in MPa
     * @param quality double, specific quality - unitless
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureQuality(const double pressure, const double quality);

//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

//	Region regionSelect(const double pressure, const double temperature);

	ThermodynamicQuantity thermodynamicQuantity_;

};

#endif //AMO_TOOLS_SUITE_STEAMPROPERTIES_H
