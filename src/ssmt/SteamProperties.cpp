//
// Created by Preston Shires on 7/19/17.
//

#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/SaturatedProperties.h"

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
//	double specificEnthalpyLimit;
//	if ( pressure < SteamSystemModelerTool::PRESSURE_CRIT)
//	{
//		SaturatedTemperature tempFromPressure = SaturatedTemperature(pressure);
//		SaturatedProperties pressureSatProps = SaturatedProperties(pressure, tempFromPressure.calculate());
//		specificEnthalpyLimit = pressureSatProps.getLiquidEnthalpy();
//	}
//	if ( pressure > SteamSystemModelerTool::PRESSURE_Tp)
//	{
//		double boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
//		std::unordered_map<std::string, double> boundaryProps = SteamSystemModelerTool::region2(pressure, boundaryTemperature);
//		specificEnthalpyLimit = boundaryProps["specificEnthalpy"];
//	}
//
//	if ( enthalpy < specificEnthalpyLimit )
//	{
//		std::unordered_map<std::string, double> region13boundary;
//		region13boundary["specificEnthalpy"] = 0.0;
//
//		double temperature = 0.0;
//		std::unordered_map<std::string, double> testProps;
//
//		if (pressure > SteamSystemModelerTool::PRESSURE_Tp)
//			region13boundary = waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);
//
//		if (pressure <= SteamSystemModelerTool::PRESSURE_Tp or enthalpy < region13boundary["specificEnthalpy"] )
//		{
//			// not the same function used in PHP code
//			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion1(pressure, enthalpy);
//			testProps = SteamSystemModelerTool::region1(pressure, temperature);
//			//testProps['region'] = '1';
//		}
//		else
//		{
//			//not the same function used in PHP code
//			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion3(pressure, enthalpy);
//			testProps = SteamSystemModelerTool::region3(pressure, temperature);
//			//testProps['region'] = 3;
//		}
//		return testProps;
//	}

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
