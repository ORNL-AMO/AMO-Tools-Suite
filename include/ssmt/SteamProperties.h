//
// Created by Preston Shires on 7/19/17.
//

#include <unordered_map>
#include <string>

#ifndef AMO_TOOLS_SUITE_STEAMPROPERTIES_H
#define AMO_TOOLS_SUITE_STEAMPROPERTIES_H

class SteamProperties {
public:
	enum class ThermodynamicQuantity {
		TEMPERATURE,
		ENTHALPY,
		ENTROPY,
		QUALITY
	};

	SteamProperties(ThermodynamicQuantity quantity) :
			thermodynamicQuantity_(quantity)
	{}

	std::unordered_map <std::string, double> calculate(const double pressure, const double quantityValue);

private:
	std::unordered_map <std::string, double> waterPropertiesPressureTemperature(const double pressure,
	                                                                       const double temperature);
	std::unordered_map <std::string, double> waterPropertiesPressureEnthalpy(const double pressure,
	                                                                         const double enthalpy);
	std::unordered_map <std::string, double> waterPropertiesPressureEntropy(const double pressure,
	                                                                        const double entropy);
	std::unordered_map <std::string, double> waterPropertiesPressureQuality(const double pressure,
	                                                                        const double quality);

//	enum class Region {
//		LIQUIDREGION1,
//		GASREGION2,
//		LIQUIDREGION3
//	};

//	Region regionSelect(const double pressure, const double temperature);

	ThermodynamicQuantity thermodynamicQuantity_;

};

#endif //AMO_TOOLS_SUITE_STEAMPROPERTIES_H
