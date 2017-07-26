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

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureTemperature(const double p, const double t) {
	switch (SteamSystemModelerTool::regionSelect(p, t)) {
		case 1: {
            return SteamSystemModelerTool::region1(t, p);
		}
		case 2: {
			return SteamSystemModelerTool::region2(t, p);
		}
		case 3: {
			return SteamSystemModelerTool::region3(t, p);
		}
		default:
            break;
	}
	return std::unordered_map <std::string, double>();
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEnthalpy(const double pressure, const double enthalpy) {
	double specificEnthalpyLimit = 0;
    SaturatedProperties pressureSatProps(0.0, 0.0);
    std::unordered_map<std::string, double> testProps;
    double temperature = 0.0;

	if ( pressure < SteamSystemModelerTool::PRESSURE_CRIT)
	{
		SaturatedTemperature tempFromPressure = SaturatedTemperature(pressure);
		pressureSatProps = SaturatedProperties(pressure, tempFromPressure.calculate());
		specificEnthalpyLimit = pressureSatProps.getLiquidEnthalpy();
	}
	if ( pressure > SteamSystemModelerTool::PRESSURE_Tp)
	{
		double boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
		std::unordered_map<std::string, double> boundaryProps = SteamSystemModelerTool::region2(boundaryTemperature, pressure);
		specificEnthalpyLimit = boundaryProps["specificEnthalpy"];
//		specificEnthalpyLimit = boundaryTemperature;//boundaryProps["specificEnthalpy"];
	}

	if ( enthalpy < specificEnthalpyLimit )
	{
		std::unordered_map<std::string, double> region13boundary;

		if (pressure > SteamSystemModelerTool::PRESSURE_Tp)
			region13boundary = waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);

		if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) || (enthalpy < region13boundary["specificEnthalpy"]) )
		{
            // not same function as PHP
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion1(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region1(temperature, pressure);
		}
		else
		{
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion3(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region3(temperature, pressure);
		}

		return testProps;
	}

    if ( (pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (enthalpy >= pressureSatProps.getLiquidEnthalpy()) && (enthalpy <= pressureSatProps.getGasEnthalpy())){
        double quality = (enthalpy - pressureSatProps.getLiquidEnthalpy()) /(pressureSatProps.getGasEnthalpy() - pressureSatProps.getLiquidEnthalpy());
        testProps = {
                {"temperature", pressureSatProps.getSaturatedTemperature()}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
			    {"quality", quality},
                {"specificVolume", (pressureSatProps.getGasVolume() - pressureSatProps.getLiquidVolume()) * quality + pressureSatProps.getLiquidVolume()}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", enthalpy}, // enthalpy in kJ/kg
                {"specificEntropy", (pressureSatProps.getGasEntropy() - pressureSatProps.getLiquidEntropy()) * quality + pressureSatProps.getLiquidEntropy()} // entropy in kJ/kg/K
        };

        return testProps;
    }

    if (pressure <= 4){
        // not
        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2A(pressure, enthalpy);
    }
    else{
        double constants[] = {0.90584278514723E+3, -0.67955786399241, 0.12809002730136E-3};

        double pressureLine = constants[0] + constants[1] * enthalpy + constants[2] * pow(enthalpy, 2);
        if (pressureLine > pressure){
            // not same function as PHP
            temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2B(pressure, enthalpy);
        }else{
            // not same function as PHP
            temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2C(pressure, enthalpy);
        }
    }

    testProps = SteamSystemModelerTool::region2(temperature, pressure);

    return testProps;
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEntropy(const double pressure, const double entropy) {
    SaturatedProperties pressureSatProps(0.0, 0.0);
    double specificEntropyLimit;
    double boundaryTemperature = 0.0;
    std::unordered_map <std::string, double> boundaryProps;
    std::unordered_map <std::string, double> region13boundary;
    double temperature = 0.0;
    std::unordered_map <std::string, double> testProps;
    double quality = 0.0;

    if (pressure < SteamSystemModelerTool::PRESSURE_CRIT){
        SaturatedTemperature tempFromPressure(pressure);
        double satTemperature = tempFromPressure.calculate();
        pressureSatProps = SaturatedProperties(pressure, satTemperature);
        specificEntropyLimit = pressureSatProps.getLiquidEntropy();
    }

    if (pressure > SteamSystemModelerTool::PRESSURE_Tp){
        boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
        boundaryProps = SteamSystemModelerTool::region2(boundaryTemperature, pressure);
        specificEntropyLimit = boundaryProps["specificEntropy"];

    }
    if ( entropy < specificEntropyLimit ){
        if (pressure > SteamSystemModelerTool::PRESSURE_Tp) {
            region13boundary = SteamProperties::waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);

        }

        if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) ||
		        region13boundary.find("specificEntropy") != region13boundary.end() && (entropy < region13boundary["specificEntropy"]))
        {
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion1Exact(pressure, entropy);
            testProps = SteamSystemModelerTool::region1(temperature, pressure);
//	        auto density = region13boundary["density"];
//	        auto enthalpy = region13boundary["specificEnthalpy"];
//	        auto entropy = region13boundary["specificEntropy"];
//	        auto specVol = region13boundary["specificVolume"];
//	        auto pressure = region13boundary["pressure"];
//	        auto temp = region13boundary["temperature"];
//	        auto blah = 10;
           // $testProps['region'] = '1';
        }
        else{
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion3(pressure, entropy);
            testProps = SteamSystemModelerTool::region3(temperature, pressure);
           // $testProps['region'] = 3;
        }
        return testProps;
    }

    if ((pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (entropy >= pressureSatProps.getLiquidEntropy()) && (entropy <= pressureSatProps.getGasEntropy()))
    {
        quality = (entropy - pressureSatProps.getLiquidEntropy()) /(pressureSatProps.getGasEntropy() - pressureSatProps.getLiquidEntropy());

        testProps = {
                {"temperature", pressureSatProps.getSaturatedTemperature()}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
                {"quality", quality},
                {"specificVolume", (pressureSatProps.getGasVolume() - pressureSatProps.getLiquidVolume()) * quality + pressureSatProps.getLiquidVolume()}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", (pressureSatProps.getGasEnthalpy() - pressureSatProps.getLiquidEnthalpy()) * quality + pressureSatProps.getLiquidEnthalpy()}, // enthalpy in kJ/kg
                {"specificEntropy", entropy} // entropy in kJ/kg/K
        };

        return testProps;
    }

    if (pressure <= 4){
        temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2AExact(pressure, entropy);
        //$region = '2a';
    }else{
        if (entropy >= 5.85){
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2BExact(pressure, entropy);
           // $region = '2b';
        }
        else{
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2CExact(pressure, entropy);
            //$region = '2c';
        }
    }

    testProps = SteamSystemModelerTool::region2(temperature, pressure);
    //$testProps['region'] = $region;
    return testProps;
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureQuality(const double pressure, const double quality) {
    std::unordered_map <std::string, double> properties;

    SaturatedTemperature satTemp = SaturatedTemperature(pressure);
    SaturatedProperties tmp = SaturatedProperties(pressure, satTemp.calculate());
    properties["temperature"] = tmp.getSaturatedTemperature() * 1;
    properties["pressure"] = tmp.getSaturatedPressure() * 1;
    properties["specificEnthalpy"] = tmp.getGasEnthalpy() * quality + tmp.getLiquidEnthalpy() * (1 - quality);
    properties["specificEntropy"] = tmp.getGasEntropy() * quality + tmp.getLiquidEntropy() * (1 - quality);
    properties["specificVolume"] = tmp.getGasVolume() * quality + tmp.getLiquidVolume() * (1 - quality);
    properties["density"] = 1/properties["specificVolume"];
    properties["quality"] = quality;
    //properties['region'] = $tmp['region'];
    return properties;
};
