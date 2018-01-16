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
     * @param pressure double, pressure in MPa
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
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> calculate();

private:
    /**
     * Calculates the steam properties using temperature
     * @param pressure double, pressure in MPa
     * @param temperature double, temperature in Kelvins
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureTemperature(double pressure, double temperature);

    /**
     * Calculates the steam properties using specific enthalpy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureEnthalpy(double pressure, double enthalpy);

    /**
     * Calculates the steam properties using specific entropy
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureEntropy(double pressure, double entropy);

    /**
     * Calculates the steam properties using specific quality
     * @param pressure double, pressure in MPa
     * @param quality double, specific quality - unitless
     * @return unordered_map <string, double>, steam properties
     */
	std::unordered_map <std::string, double> waterPropertiesPressureQuality(double pressure, double quality);

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
