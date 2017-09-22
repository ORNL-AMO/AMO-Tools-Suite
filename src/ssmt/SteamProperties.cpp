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
            auto rv = SteamSystemModelerTool::region1(t, p);
			rv["quality"] = 0;
			return rv;
		}
		case 2: {
			auto rv = SteamSystemModelerTool::region2(t, p);
			rv["quality"] = 1;
			return rv;
		}
		case 3: {
			auto rv = SteamSystemModelerTool::region3(t, p);
			rv["quality"] = 0;
			return rv;
		}
		default:
            break;
	}
	return {{}};
};

// TODO combine this with waterPropertiesPressureEntropy?
std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEnthalpy(const double pressure, const double enthalpy) {
	double specificEnthalpyLimit = 0;
    std::unordered_map <std::string, double> pressureSatProps;
    double temperature;

	if ( pressure < SteamSystemModelerTool::PRESSURE_CRIT) {
        const double temp = SaturatedTemperature(pressure).calculate();
		pressureSatProps = SaturatedProperties(pressure, temp).calculate();
		specificEnthalpyLimit = pressureSatProps["liquidSpecificEnthalpy"];
	}
	if ( pressure > SteamSystemModelerTool::PRESSURE_Tp) {
		const double boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
		std::unordered_map<std::string, double> boundaryProps = SteamSystemModelerTool::region2(boundaryTemperature, pressure);
		specificEnthalpyLimit = boundaryProps["specificEnthalpy"];
	}

	if ( enthalpy < specificEnthalpyLimit ) {
		std::unordered_map<std::string, double> region13boundary;

		if (pressure > SteamSystemModelerTool::PRESSURE_Tp) {
			region13boundary = waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);
		}

		if ((pressure <= SteamSystemModelerTool::PRESSURE_Tp) || (enthalpy < region13boundary["specificEnthalpy"]) ) {
			temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion1Exact(pressure, enthalpy);
			return SteamSystemModelerTool::region1(temperature, pressure);
		}

		temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion3(pressure, enthalpy);
		auto rv = SteamSystemModelerTool::region3(temperature, pressure);
		rv["quality"] = -1; // TODO what should this do?
		return rv;
	}

    if ( (pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (enthalpy >= pressureSatProps["liquidSpecificEnthalpy"]) && (enthalpy <= pressureSatProps["gasSpecificEnthalpy"])) {
        const double quality = (enthalpy - pressureSatProps["liquidSpecificEnthalpy"]) / (pressureSatProps["gasSpecificEnthalpy"] - pressureSatProps["liquidSpecificEnthalpy"]);
        return {
                {"temperature", pressureSatProps["temperature"]}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
			    {"quality", quality},
                {"specificVolume", (pressureSatProps["gasSpecificVolume"] - pressureSatProps["liquidSpecificVolume"]) * quality + pressureSatProps["liquidSpecificVolume"]}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", enthalpy}, // enthalpy in kJ/kg
                {"specificEntropy", (pressureSatProps["gasSpecificEntropy"] - pressureSatProps["liquidSpecificEntropy"]) * quality + pressureSatProps["liquidSpecificEntropy"]} // entropy in kJ/kg/K
        };
    }

    if (pressure <= 4) {
//        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2A(pressure, enthalpy);
	    temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2AExact(pressure, enthalpy);
    } else {
        double constants[] = {0.90584278514723E+3, -0.67955786399241, 0.12809002730136E-3};

        double pressureLine = constants[0] + constants[1] * enthalpy + constants[2] * std::pow(enthalpy, 2);
        if (pressureLine > pressure) {
	        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2BExact(pressure, enthalpy);
        } else {
	        temperature = SteamSystemModelerTool::backwardPressureEnthalpyRegion2CExact(pressure, enthalpy);
        }
    }

    return SteamSystemModelerTool::region2(temperature, pressure);
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureEntropy(const double pressure, const double entropy) {
    std::unordered_map <std::string, double> pressureSatProps;
    double specificEntropyLimit = 0;
    std::unordered_map <std::string, double> boundaryProps;
    std::unordered_map <std::string, double> region13boundary;

    if (pressure < SteamSystemModelerTool::PRESSURE_CRIT) {
        double const satTemperature = SaturatedTemperature(pressure).calculate();
        SaturatedProperties sp = SaturatedProperties(pressure, satTemperature);
        pressureSatProps = sp.calculate();
        specificEntropyLimit = pressureSatProps["liquidSpecificEntropy"];
    }

	// this does stuff that determines what the boundary between 2 and 3 is
    if (pressure > SteamSystemModelerTool::PRESSURE_Tp) {
        const double boundaryTemperature = SteamSystemModelerTool::boundaryByPressureRegion3to2(pressure);
        boundaryProps = SteamSystemModelerTool::region2(boundaryTemperature, pressure);
        specificEntropyLimit = boundaryProps["specificEntropy"];
    }

	// this if statement decides if you're in region one or three when you're near the boundary
    if ( entropy < specificEntropyLimit ) {
        if (pressure > SteamSystemModelerTool::PRESSURE_Tp) {
            region13boundary = SteamProperties::waterPropertiesPressureTemperature(pressure, SteamSystemModelerTool::TEMPERATURE_Tp);
        }

        if (pressure <= SteamSystemModelerTool::PRESSURE_Tp || entropy < region13boundary.at("specificEntropy")) {
            const double temperature = SteamSystemModelerTool::backwardPressureEntropyRegion1Exact(pressure, entropy);
            return SteamSystemModelerTool::region1(temperature, pressure);
        }
	    const double temperature = SteamSystemModelerTool::backwardPressureEntropyRegion3(pressure, entropy);
	    auto rv = SteamSystemModelerTool::region3(temperature, pressure);
	    rv["quality"] = -1; // TODO what should this do?
	    return rv;
    }

    if ((pressure < SteamSystemModelerTool::PRESSURE_CRIT) && (entropy >= pressureSatProps["liquidSpecificEntropy"])
        && (entropy <= pressureSatProps["gasSpecificEntropy"])) {
        const double quality = (entropy - pressureSatProps["liquidSpecificEntropy"])
                               / (pressureSatProps["gasSpecificEntropy"] - pressureSatProps["liquidSpecificEntropy"]);

        return {
                {"temperature", pressureSatProps["temperature"]}, //temperature in Kelvin
                {"pressure", pressure}, //pressure in MPa
//			    {"phase", "Liquid"},
                {"quality", quality},
                {"specificVolume", (pressureSatProps["gasSpecificVolume"] - pressureSatProps["liquidSpecificVolume"]) * quality + pressureSatProps["liquidSpecificVolume"]}, //volume in m³/kg
                //{"density", 1 / (reducedPressure * gibbsPi * t * r / p / 1000.0)}, //density in kg/m³
                {"specificEnthalpy", (pressureSatProps["gasSpecificEnthalpy"] - pressureSatProps["liquidSpecificEnthalpy"]) * quality + pressureSatProps["liquidSpecificEnthalpy"]}, // enthalpy in kJ/kg
                {"specificEntropy", entropy} // entropy in kJ/kg/K
        };
    }

	double temperature = 0;
    if (pressure <= 4) {
        temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2AExact(pressure, entropy);
    } else {
        if (entropy >= 5.85) {
	        temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2BExact(pressure, entropy);
        } else {
	        temperature = SteamSystemModelerTool::backwardPressureEntropyRegion2CExact(pressure, entropy);
        }
    }

    return SteamSystemModelerTool::region2(temperature, pressure);
};

std::unordered_map <std::string, double> SteamProperties::waterPropertiesPressureQuality(const double pressure, const double quality) {
    auto satProps = SaturatedProperties(pressure, SaturatedTemperature(pressure).calculate()).calculate();

	const double specificVolume = satProps["gasSpecificVolume"] * quality + satProps["liquidSpecificVolume"] * (1 - quality);

	return {
			{"temperature", satProps["temperature"]},
			{"pressure", satProps["pressure"]},
			{"specificEnthalpy", satProps["gasSpecificEnthalpy"] * quality + satProps["liquidSpecificEnthalpy"] * (1 - quality)},
			{"specificEntropy", satProps["gasSpecificEntropy"] * quality + satProps["liquidSpecificEntropy"] * (1 - quality)},
			{"specificVolume", specificVolume},
			{"density", 1 / specificVolume},
			{"quality", quality}
	};
};
