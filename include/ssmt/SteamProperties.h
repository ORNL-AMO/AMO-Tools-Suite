#include <unordered_map>
#include <string>

#ifndef AMO_TOOLS_SUITE_STEAMPROPERTIES_H
#define AMO_TOOLS_SUITE_STEAMPROPERTIES_H

class SteamProperties {
public:
	/**
	 * SteamProperties::Output contains the properties of steam
	 * @param temperature in Kelvin
	 * @param pressure in MPa
	 * @param quality - unitless
	 * @param specificVolume in m³/kg
	 * @param density in kg/m³
	 * @param specificEnthalpy in kJ/kg
	 * @param specificEntropy in kJ/kg/K
	 * @param internalEnergy - optional parameter - in MJ
	 */
	struct Output {
		Output(const double temperature, const double pressure, const double quality,
		       const double specificVolume, const double density, const double specificEnthalpy,
		       const double specificEntropy, const double internalEnergy = 0):
				temperature(temperature), pressure(pressure), quality(quality), specificVolume(specificVolume),
				density(density), specificEnthalpy(specificEnthalpy), specificEntropy(specificEntropy),
				internalEnergy(internalEnergy)
		{}

		Output():
				temperature(0), pressure(0), quality(0), specificVolume(0), density(0),
				specificEnthalpy(0), specificEntropy(0), internalEnergy(0)
		{}

		double temperature, pressure, quality, specificVolume, density, specificEnthalpy, specificEntropy, internalEnergy;
	};

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
     * @return SteamProperties::Output, steam properties
     */
	Output calculate();

private:
    /**
     * Calculates the steam properties using temperature
     * @param pressure double, pressure in MPa
     * @param temperature double, temperature in Kelvins
     * @return SteamProperties::Output, steam properties
     */
	SteamProperties::Output waterPropertiesPressureTemperature(double pressure, double temperature);

    /**
     * Calculates the steam properties using specific enthalpy
     * @param pressure double, pressure in MPa
     * @param enthalpy double, specific enthalpy in kJ/kg
     * @return SteamProperties::Output, steam properties
     */
	SteamProperties::Output waterPropertiesPressureEnthalpy(double pressure, double enthalpy);

    /**
     * Calculates the steam properties using specific entropy
     * @param pressure double, pressure in MPa
     * @param entropy double, specific entropy in kJ/kg/K
     * @return SteamProperties::Output, steam properties
     */
	SteamProperties::Output waterPropertiesPressureEntropy(double pressure, double entropy);

    /**
     * Calculates the steam properties using specific quality
     * @param pressure double, pressure in MPa
     * @param quality double, specific quality - unitless
     * @return SteamProperties::Output, steam properties
     */
	SteamProperties::Output waterPropertiesPressureQuality(double pressure, double quality);

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
