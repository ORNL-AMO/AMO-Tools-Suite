//
// Created by Preston Shires on 7/19/17.
//

#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"

std::unordered_map <std::string, double> SteamProperties::calculate(const double pressure, const double quantityValue) {
	switch (thermodynamicQuantity_) {
		case ThermodynamicQuantity::TEMPERATURE:
			return waterPropertiesPressureTemperature(pressure, quantityValue);
		case ThermodynamicQuantity::ENTHALPY:
			return waterPropertiesPressureEnthalpy(pressure, quantityValue);
		case ThermodynamicQuantity::ENTROPY:
			return waterPropertiesPressureEntropy(pressure, quantityValue);
		case ThermodynamicQuantity::QUALITY:
			return waterPropertiesPressureQuality(pressure, quantityValue);
	};
}

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureTemperature(const double p,
                                                                                             const double t) {
	switch (SteamSystemModelerTool::regionSelect(p, t)) {
		case 1: {
			return SteamSystemModelerTool::region1(p, t);
		}
		case 2: {
			return SteamSystemModelerTool::region2(p, t);
		}
		case 3: {
			return SteamSystemModelerTool::region3(p, t);
		}
		default:
			break;
	}
	// stuff

	return std::unordered_map <std::string, double>();

};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEnthalpy(const double pressure,
                                                                                     const double enthalpy) {
	return std::unordered_map <std::string, double>();
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEntropy(const double pressure,
                                                                                    const double entropy) {
	return std::unordered_map <std::string, double>();
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureQuality(const double pressure,
                                                                                    const double quality) {
	return std::unordered_map <std::string, double>();
};
