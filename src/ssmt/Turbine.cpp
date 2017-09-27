#include "ssmt/Turbine.h"

Turbine::Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
                 double inletQuantityValue, TurbineProperty turbineProperty, double isentropicEfficiency,
                 double generatorEfficiency, double massFlowOrPowerOut, double outletSteamPressure)
		: solveFor(solveFor), inletPressure(inletPressure), isentropicEfficiency(isentropicEfficiency),
		  generatorEfficiency(generatorEfficiency), massFlowOrPowerOut(massFlowOrPowerOut),
		  outletSteamPressure(outletSteamPressure), inletQuantity(inletQuantity),
		  inletQuantityValue(inletQuantityValue), turbineProperty(turbineProperty)
{
	calculate();
}

Turbine::Turbine(const Solve solveFor, const double inletPressure,
                 const SteamProperties::ThermodynamicQuantity inletQuantity, const double inletQuantityValue,
                 const TurbineProperty turbineProperty, const double generatorEfficiency,
                 const double massFlowOrPowerOut, const double outletSteamPressure,
                 const SteamProperties::ThermodynamicQuantity outletQuantity, const double outletQuantityValue)
		: solveFor(solveFor), inletPressure(inletPressure), generatorEfficiency(generatorEfficiency),
		  massFlowOrPowerOut(massFlowOrPowerOut), outletSteamPressure(outletSteamPressure),
		  inletQuantity(inletQuantity), outletQuantity(outletQuantity), inletQuantityValue(inletQuantityValue),
		  outletQuantityValue(outletQuantityValue), turbineProperty(turbineProperty)
{
	calculate();
}

void Turbine::calculate() {
	// outlet properties and mass flow
	inletProperties = SteamProperties(inletPressure, inletQuantity, inletQuantityValue).calculate();
	inletEnergyFlow = inletProperties.at("specificEnthalpy") * massFlowOrPowerOut;
	// TODO massFlow ^ is always exists it seems, but in certain cases it's not input, can it be calculated?

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTROPY,
	                                   inletProperties.at("specificEntropy")).calculate();

	auto const outletSpecificEnthalpy = inletProperties.at("specificEnthalpy")
	                                    - isentropicEfficiency * (inletProperties.at("specificEnthalpy")
	                                                              - outletProperties.at("specificEnthalpy"));

	// TODO what is the difference between IDEAL outlet enthalpy and (non-ideal) enthalpy
//	isentropicEfficiency = (inletProperties.at("specificEnthalpy") - outletProperties.at("specificEnthalpy"))
//	                       / (inletProperties.at("specificEnthalpy") - outletProperties.at("specificEnthalpy"));

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
	                                   outletSpecificEnthalpy).calculate();

	energyOut = (inletProperties.at("specificEnthalpy") - outletSpecificEnthalpy) * massFlowOrPowerOut;
	powerOut = energyOut * generatorEfficiency;

}