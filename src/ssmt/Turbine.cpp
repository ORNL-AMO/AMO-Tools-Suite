#include "ssmt/Turbine.h"

Turbine::Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
                 double inletQuantityValue, TurbineProperty turbineProperty, double isentropicEfficiency,
                 double generatorEfficiency, double massFlowOrPowerOut, double outletSteamPressure)
		: solveFor(solveFor), inletPressure(inletPressure), isentropicEfficiency(isentropicEfficiency / 100),
		  generatorEfficiency(generatorEfficiency / 100), massFlowOrPowerOut(massFlowOrPowerOut),
		  outletSteamPressure(outletSteamPressure), inletQuantity(inletQuantity),
		  inletQuantityValue(inletQuantityValue), turbineProperty(turbineProperty)
{
	if (solveFor == Solve::IsentropicEfficiency) {
		throw std::runtime_error("Must use the other Turbine constructor to solve for Isentropic Efficiency");
	}
	calculateOutletProperties();
}

Turbine::Turbine(const Solve solveFor, const double inletPressure,
                 const SteamProperties::ThermodynamicQuantity inletQuantity, const double inletQuantityValue,
                 const TurbineProperty turbineProperty, const double generatorEfficiency,
                 const double massFlowOrPowerOut, const double outletSteamPressure,
                 const SteamProperties::ThermodynamicQuantity outletQuantity, const double outletQuantityValue)
		: solveFor(solveFor), inletPressure(inletPressure), generatorEfficiency(generatorEfficiency / 100),
		  massFlowOrPowerOut(massFlowOrPowerOut), outletSteamPressure(outletSteamPressure),
		  inletQuantity(inletQuantity), outletQuantity(outletQuantity), inletQuantityValue(inletQuantityValue),
		  outletQuantityValue(outletQuantityValue), turbineProperty(turbineProperty)
{
	if (solveFor == Solve::OutletProperties) {
		throw std::runtime_error("Must use the other Turbine constructor to solve for Outlet Properties");
	}
	calculateIsentropicEfficiency();
}

void Turbine::calculateOutletProperties() {
	inletProperties = SteamProperties(inletPressure, inletQuantity, inletQuantityValue).calculate();
	auto const inletSpecificEnthalpy = inletProperties.at("specificEnthalpy");

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTROPY,
	                                   inletProperties.at("specificEntropy")).calculate();
	auto const idealOutletSpecificEnthalpy = outletProperties.at("specificEnthalpy");

	auto const outletSpecificEnthalpy = inletSpecificEnthalpy
	                                    - isentropicEfficiency * (inletSpecificEnthalpy - idealOutletSpecificEnthalpy);

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
	                                   outletSpecificEnthalpy).calculate();

	calculateTurbineProperties(inletSpecificEnthalpy, outletSpecificEnthalpy);
}

void Turbine::calculateIsentropicEfficiency() {
	inletProperties = SteamProperties(inletPressure, inletQuantity, inletQuantityValue).calculate();
	auto const inletSpecificEnthalpy = inletProperties.at("specificEnthalpy");

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTROPY,
	                                   inletProperties.at("specificEntropy")).calculate();
	auto const idealOutletSpecificEnthalpy = outletProperties.at("specificEnthalpy");

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
	                                   outletQuantityValue).calculate();

	isentropicEfficiency = (inletSpecificEnthalpy - outletProperties.at("specificEnthalpy"))
	                       / (inletSpecificEnthalpy - idealOutletSpecificEnthalpy);

	calculateTurbineProperties(inletSpecificEnthalpy, outletProperties.at("specificEnthalpy"));
	// outletEnergyFlow ???? TODO
}

void Turbine::calculateTurbineProperties(const double inletSpecificEnthalpy, const double outletSpecificEnthalpy) {
	if (turbineProperty == TurbineProperty::PowerOut) {
		energyOut = massFlowOrPowerOut / generatorEfficiency;
		massFlow = energyOut / (inletSpecificEnthalpy - outletSpecificEnthalpy);
		powerOut = massFlowOrPowerOut;
	} else {
		massFlow = massFlowOrPowerOut;
		energyOut = (inletSpecificEnthalpy - outletSpecificEnthalpy) * massFlow;
		powerOut = energyOut * generatorEfficiency;
	}

	inletEnergyFlow = inletSpecificEnthalpy * massFlow;
}

void Turbine::setSolveFor(Turbine::Solve solveFor) {
	this->solveFor = solveFor;
}

void Turbine::setInletPressure(double inletPressure) {
	this->inletPressure = inletPressure;
}

void Turbine::setIsentropicEfficiency(double isentropicEfficiency) {
	this->isentropicEfficiency = isentropicEfficiency / 100;
}

void Turbine::setGeneratorEfficiency(double generatorEfficiency) {
	this->generatorEfficiency = generatorEfficiency / 100;
}

void Turbine::setMassFlowOrPowerOut(double massFlowOrPowerOut) {
	this->massFlowOrPowerOut = massFlowOrPowerOut;
}

void Turbine::setOutletSteamPressure(double outletSteamPressure) {
	this->outletSteamPressure = outletSteamPressure;
}

void Turbine::setInletQuantity(SteamProperties::ThermodynamicQuantity inletQuantity) {
	this->inletQuantity = inletQuantity;
}

void Turbine::setOutletQuantity(SteamProperties::ThermodynamicQuantity outletQuantity) {
	this->outletQuantity = outletQuantity;
}

void Turbine::setInletQuantityValue(double inletQuantityValue) {
	this->inletQuantityValue = inletQuantityValue;
}

void Turbine::setOutletQuantityValue(double outletQuantityValue) {
	this->outletQuantityValue = outletQuantityValue;
}

void Turbine::setTurbineProperty(Turbine::TurbineProperty turbineProperty) {
	this->turbineProperty = turbineProperty;
}
