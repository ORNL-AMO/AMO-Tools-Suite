//
// Created by Preston Shires on 7/19/17.
//

#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/SaturatedProperties.h"

std::unordered_map <std::string, double> SteamProperties::calculate() {
	switch (thermodynamicQuantity_) {
		case ThermodynamicQuantity::TEMPERATURE:
			return waterPropertiesPressureTemperature(this->pressure_, this->quantityValue_);
		case ThermodynamicQuantity::ENTHALPY:
			return waterPropertiesPressureEnthalpy(this->pressure_, this->quantityValue_);
		case ThermodynamicQuantity::ENTROPY:
			return waterPropertiesPressureEntropy(this->pressure_, this->quantityValue_);
		case ThermodynamicQuantity::QUALITY:
			return waterPropertiesPressureQuality(this->pressure_, this->quantityValue_);
        default:
            return waterPropertiesPressureQuality(this->pressure_, this->quantityValue_);;
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
    std::unordered_map <std::string, double> pressureSatProps;
    std::unordered_map<std::string, double> testProps;
    double temperature = 0.0;

	if ( pressure < SteamSystemModelerTool::PRESSURE_CRIT)
	{
		SaturatedTemperature tempFromPressure = SaturatedTemperature(pressure);
        double temp = tempFromPressure.calculate();
        SaturatedProperties sp = SaturatedProperties(pressure, temp);
		pressureSatProps = sp.calculate();
		specificEnthalpyLimit = pressureSatProps["liquidSpecificEnthalpy"];
	}
	if ( pressure > SteamSystemModelerTool::PRESSURE_Tp)
	{
		double boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
		std::unordered_map<std::string, double> boundaryProps = SteamSystemModelerTool::region2(boundaryTemperature, pressure);
		specificEnthalpyLimit = boundaryProps["specificEnthalpy"];
	}

	if ( enthalpy < specificEnthalpyLimit )
	{
		std::unordered_map<std::string, double> region13boundary;

		if (pressure > SteamSystemModelerTool::PRESSURE_Tp)
			region13boundary = waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);

		if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) || (enthalpy < region13boundary["specificEnthalpy"]) )
		{
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion1Exact(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region1(temperature, pressure);
		}
		else
		{
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion3(pressure, enthalpy);
			testProps = SteamSystemModelerTool::region3(temperature, pressure);
		}

		return testProps;
	}

    if ( (pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (enthalpy >= pressureSatProps["liquidSpecificEnthalpy"]) && (enthalpy <= pressureSatProps["gasSpecificEnthalpy"])){
        double quality = (enthalpy - pressureSatProps["liquidSpecificEnthalpy"]) /(pressureSatProps["gasSpecificEnthalpy"] - pressureSatProps["liquidSpecificEnthalpy"]);
        testProps = {
                {"temperature", pressureSatProps["saturatedTemperature"]}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
			    {"quality", quality},
                {"specificVolume", (pressureSatProps["gasSpecificVolume"] - pressureSatProps["liquidSpecificVolume"]) * quality + pressureSatProps["liquidSpecificVolume"]}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", enthalpy}, // enthalpy in kJ/kg
                {"specificEntropy", (pressureSatProps["gasSpecificEntropy"] - pressureSatProps["liquidSpecificEntropy"]) * quality + pressureSatProps["liquidSpecificEntropy"]} // entropy in kJ/kg/K
        };

        return testProps;
    }

    if (pressure <= 4){
//        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2A(pressure, enthalpy);
	    temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2AExact(pressure, enthalpy);
    }
    else{
        double constants[] = {0.90584278514723E+3, -0.67955786399241, 0.12809002730136E-3};

        double pressureLine = constants[0] + constants[1] * enthalpy + constants[2] * pow(enthalpy, 2);
        if (pressureLine > pressure){
//            temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2B(pressure, enthalpy);
	        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2BExact(pressure, enthalpy);
        }else{
//            temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2C(pressure, enthalpy);
	        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2CExact(pressure, enthalpy);
        }
    }

    testProps = SteamSystemModelerTool::region2(temperature, pressure);

    return testProps;
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEntropy(const double pressure, const double entropy) {
    std::unordered_map <std::string, double> pressureSatProps;
    double specificEntropyLimit = 0;
    double boundaryTemperature = 0.0;
    std::unordered_map <std::string, double> boundaryProps;
    std::unordered_map <std::string, double> region13boundary;
    double temperature = 0.0;
    std::unordered_map <std::string, double> testProps;
    double quality = 0.0;

    if (pressure < SteamSystemModelerTool::PRESSURE_CRIT){
        SaturatedTemperature tempFromPressure(pressure);
        double satTemperature = tempFromPressure.calculate();
        SaturatedProperties sp = SaturatedProperties(pressure, satTemperature);
        pressureSatProps = sp.calculate();
        specificEntropyLimit = pressureSatProps["liquidSpecificEntropy"];
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
                (region13boundary.find("specificEntropy") != region13boundary.end() && (entropy < region13boundary["specificEntropy"])))
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

    if ((pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (entropy >= pressureSatProps["liquidSpecificEntropy"]) && (entropy <= pressureSatProps["gasSpecificEntropy"]))
    {
        quality = (entropy - pressureSatProps["liquidSpecificEntropy"]) /(pressureSatProps["gasSpecificEntropy"] - pressureSatProps["liquidSpecificEntropy"]);

        testProps = {
                {"temperature", pressureSatProps["saturatedTemperature"]}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
                {"quality", quality},
                {"specificVolume", (pressureSatProps["gasSpecificVolume"] - pressureSatProps["liquidSpecificVolume"]) * quality + pressureSatProps["liquidSpecificVolume"]}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", (pressureSatProps["gasSpecificEnthalpy"] - pressureSatProps["liquidSpecificEnthalpy"]) * quality + pressureSatProps["liquidSpecificEnthalpy"]}, // enthalpy in kJ/kg
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
    std::unordered_map <std::string, double> satProps = tmp.calculate();
    properties["temperature"] = tmp.getSaturatedTemperature() * 1;
    properties["pressure"] = tmp.getSaturatedPressure() * 1;
    properties["specificEnthalpy"] = satProps["gasSpecificEnthalpy"] * quality + satProps["liquidSpecificEnthalpy"] * (1 - quality);
    properties["specificEntropy"] = satProps["gasSpecificEntropy"] * quality + satProps["liquidSpecificEntropy"] * (1 - quality);
    properties["specificVolume"] = satProps["gasSpecificVolume"] * quality + satProps["liquidSpecificVolume"] * (1 - quality);
    properties["density"] = 1/properties["specificVolume"];
    properties["quality"] = quality;
    //properties['region'] = $tmp['region'];
    return properties;
};
