#ifndef AMO_TOOLS_SUITE_TURBINE_H
#define AMO_TOOLS_SUITE_TURBINE_H

#include "SteamProperties.h"

class Turbine {
public:
	enum class Solve {
		OutletProperties,
		IsentropicEfficiency
	};

	enum class TurbineProperty {
		MassFlow,
		PowerOut
	};

	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double isentropicEfficiency,
	        double generatorEfficiency, double massFlowOrPowerOut, double outletSteamPressure);

	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double generatorEfficiency,
	        double massFlowOrPowerOut, double outletSteamPressure,
	        SteamProperties::ThermodynamicQuantity outletQuantity, double outletQuantityValue);

private:
	void calculate();

	Solve solveFor;
	double inletPressure, isentropicEfficiency, generatorEfficiency, massFlowOrPowerOut, outletSteamPressure;
	SteamProperties::ThermodynamicQuantity inletQuantity, outletQuantity;
	double inletQuantityValue, outletQuantityValue = 0;
	TurbineProperty turbineProperty;

	std::unordered_map<std::string, double> inletProperties, outletProperties;

	double inletEnergyFlow, outletEnergyFlow, energyOut, powerOut;
};

#endif //AMO_TOOLS_SUITE_TURBINE_H
