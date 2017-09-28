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

	Solve getSolveFor() const { return solveFor; }
	double getInletPressure() const { return inletPressure; }
	double getIsentropicEfficiency() const { return isentropicEfficiency * 100; }
	double getGeneratorEfficiency() const { return generatorEfficiency * 100; }
	double getMassFlowOrPowerOut() const { return massFlowOrPowerOut; }
	double getOutletSteamPressure() const { return outletSteamPressure; }
	SteamProperties::ThermodynamicQuantity getInletQuantity() const { return inletQuantity; }
	SteamProperties::ThermodynamicQuantity getOutletQuantity() const { return outletQuantity; }
	double getInletQuantityValue() const { return inletQuantityValue; }
	double getOutletQuantityValue() const { return outletQuantityValue; }
	TurbineProperty getTurbineProperty() const { return turbineProperty; }
	std::unordered_map<std::string, double> const & getInletProperties() const { return inletProperties; }
	std::unordered_map<std::string, double> const & getOutletProperties() const { return outletProperties; }
	double getInletEnergyFlow() const { return inletEnergyFlow; }
	double getOutletEnergyFlow() const { return outletEnergyFlow; }
	double getPowerOut() const { return powerOut; }
	double getEnergyOut() const { return energyOut; }
	double getMassFlow() const { return massFlow; }

	void setSolveFor(Solve solveFor);
	void setInletPressure(double inletPressure);
	void setIsentropicEfficiency(double isentropicEfficiency);
	void setGeneratorEfficiency(double generatorEfficiency);
	void setMassFlowOrPowerOut(double massFlowOrPowerOut);
	void setOutletSteamPressure(double outletSteamPressure);
	void setInletQuantity(SteamProperties::ThermodynamicQuantity inletQuantity);
	void setOutletQuantity(SteamProperties::ThermodynamicQuantity outletQuantity);
	void setInletQuantityValue(double inletQuantityValue);
	void setOutletQuantityValue(double outletQuantityValue);
	void setTurbineProperty(TurbineProperty turbineProperty);

private:
	void calculateOutletProperties();
	void calculateIsentropicEfficiency();
	void calculateTurbineProperties(double inletSpecificEnthalpy, double outletSpecificEnthalpy);

	Solve solveFor;
	double inletPressure, isentropicEfficiency, generatorEfficiency, massFlowOrPowerOut, outletSteamPressure;
	SteamProperties::ThermodynamicQuantity inletQuantity, outletQuantity;
	double inletQuantityValue, outletQuantityValue = 0;
	TurbineProperty turbineProperty;

	std::unordered_map<std::string, double> inletProperties, outletProperties;

	double inletEnergyFlow, outletEnergyFlow = 0, energyOut, powerOut, massFlow;
};

#endif //AMO_TOOLS_SUITE_TURBINE_H
