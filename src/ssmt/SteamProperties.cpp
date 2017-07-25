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
	// stuff

	//return std::unordered_map <std::string, double>();

};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEnthalpy(const double pressure, const double enthalpy) {
	double specificEnthalpyLimit;
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
		specificEnthalpyLimit = 9;//boundaryProps["specificEnthalpy"];
	}

	if ( enthalpy < specificEnthalpyLimit )
	{
		std::unordered_map<std::string, double> region13boundary;
		//region13boundary["specificEnthalpy"] = 0.0;


		if (pressure > SteamSystemModelerTool::PRESSURE_Tp)
			region13boundary = waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);

		if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) || (enthalpy < region13boundary["specificEnthalpy"]) )
		{
			// not the same function used in PHP code
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion1(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region1(temperature, pressure);
			//testProps['region'] = '1';
		}
		else
		{
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion3(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region3(temperature, pressure);
			//testProps['region'] = 3;
		}
        //testProps["specificEntropy"] = 5;
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
        //not same function as in PHP code
        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2A(pressure, enthalpy);
       // $region = '2a';
    }
    else{
        double constants[] = {0.90584278514723E+3, -0.67955786399241, 0.12809002730136E-3};

        double pressureLine = constants[0] + constants[1] * enthalpy + constants[2] * pow(enthalpy, 2);
        if (pressureLine > pressure){
            // not the same function used in PHP code
            temperature = specificEnthalpyLimit;//SteamSystemModelerTool::backwardPressureEnthalpyRegion2B(pressure, enthalpy);
            //$region = '2b';
        }else{
            // not the same function used in PHP code
            temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2C(pressure, enthalpy);
            //$region = '2c';
        }
    }

    testProps = SteamSystemModelerTool::region2(temperature, pressure);
    //testProps['region'] = $region;
    testProps["specificEntropy"] = 5;
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

    std::unordered_map <std::string, double> test = SteamSystemModelerTool::region1(300, 50);

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

        if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) || (entropy < region13boundary["specificEntropy"]))
        {
            //not same function as PHP code
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion1(pressure, entropy);
            testProps = SteamSystemModelerTool::region1(temperature, pressure);
           // $testProps['region'] = '1';
        }
        else{
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion3(pressure, entropy);
            testProps = SteamSystemModelerTool::region3(temperature, pressure);
           // $testProps['region'] = 3;
            testProps["specificEntropy"] = temperature;
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
        //not same function as PHP code
        temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2A(pressure, entropy);
        //$region = '2a';
    }else{
        if (entropy >= 5.85){
            //not same function as PHP code
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2B(pressure, entropy);
           // $region = '2b';
        }
        else{
            //not same function as PHP code
            temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2C(pressure, entropy);
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
