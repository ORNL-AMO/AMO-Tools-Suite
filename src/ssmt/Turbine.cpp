#include <stdexcept>
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
	calculate();
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
	calculate();
}

void Turbine::calculate() {
	if (solveFor == Solve::OutletProperties) {
		solveForOutletProperties();
	} else {
		solveForIsentropicEfficiency();
	}
}

void Turbine::solveForOutletProperties() {
	inletProperties = SteamProperties(inletPressure, inletQuantity, inletQuantityValue).calculate();
	auto const inletSpecificEnthalpy = inletProperties.specificEnthalpy;

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTROPY,
	                                   inletProperties.specificEntropy).calculate();
	auto const idealOutletSpecificEnthalpy = outletProperties.specificEnthalpy;

	auto const outletSpecificEnthalpy = inletSpecificEnthalpy
	                                    - isentropicEfficiency * (inletSpecificEnthalpy - idealOutletSpecificEnthalpy);

	outletProperties = SteamProperties(outletSteamPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
	                                   outletSpecificEnthalpy).calculate();

	calculateTurbineProperties(inletSpecificEnthalpy, outletSpecificEnthalpy);
}

void Turbine::solveForIsentropicEfficiency() {
	inletProperties = SteamProperties(inletPressure, inletQuantity, inletQuantityValue).calculate();
	auto const inletSpecificEnthalpy = inletProperties.specificEnthalpy;

	outletProperties = SteamProperties(outletSteamPressure, outletQuantity,
	                                   inletProperties.specificEntropy).calculate();
	auto const idealOutletSpecificEnthalpy = outletProperties.specificEnthalpy;

	outletProperties = SteamProperties(outletSteamPressure, outletQuantity,
	                                   outletQuantityValue).calculate();

	isentropicEfficiency = (inletSpecificEnthalpy - outletProperties.specificEnthalpy)
	                       / (inletSpecificEnthalpy - idealOutletSpecificEnthalpy);

	calculateTurbineProperties(inletSpecificEnthalpy, outletProperties.specificEnthalpy);
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
	outletEnergyFlow = outletSpecificEnthalpy * massFlow;
}

std::ostream &operator<<(std::ostream &stream, const Turbine &turbine) {
    stream << "Turbine["
           << "solveFor=" << static_cast< int >(turbine.solveFor)
           << ", inletPressure=" << turbine.inletPressure
           << ", inletQuantity=" << static_cast< int >(turbine.inletQuantity)
           << ", inletQuantityValue=" << turbine.inletQuantityValue
           << ", turbineProperty=" << static_cast< int >(turbine.turbineProperty)
           << ", isentropicEfficiency=" << turbine.isentropicEfficiency
           << ", generatorEfficiency=" << turbine.generatorEfficiency
           << ", massFlowOrPowerOut=" << turbine.massFlowOrPowerOut
           << ", outletSteamPressure=" << turbine.outletSteamPressure
           << ", outletQuantity=" << static_cast< int >(turbine.outletQuantity)
           << ", outletQuantityValue=" << turbine.outletQuantityValue
           << ", inletProperties=" << turbine.inletProperties
           << ", outletProperties=" << turbine.outletProperties
           << ", inletEnergyFlow=" << turbine.inletEnergyFlow
           << ", outletEnergyFlow=" << turbine.outletEnergyFlow
           << ", energyOut=" << turbine.energyOut
           << ", powerOut=" << turbine.powerOut
           << ", massFlow=" << turbine.massFlow
           << "]";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<Turbine> &turbine) {
    if (turbine == nullptr) {
        stream << "Turbine[nullptr]";
    } else {
        stream << *turbine;
    }
    return stream;
}

void Turbine::setSolveFor(Turbine::Solve solveFor) {
	this->solveFor = solveFor;
	calculate();
}

void Turbine::setInletPressure(double inletPressure) {
	this->inletPressure = inletPressure;
	calculate();
}

void Turbine::setIsentropicEfficiency(double isentropicEfficiency) {
	this->isentropicEfficiency = isentropicEfficiency / 100;
	calculate();
}

void Turbine::setGeneratorEfficiency(double generatorEfficiency) {
	this->generatorEfficiency = generatorEfficiency / 100;
	calculate();
}

void Turbine::setMassFlowOrPowerOut(double massFlowOrPowerOut) {
	this->massFlowOrPowerOut = massFlowOrPowerOut;
	calculate();
}

void Turbine::setOutletSteamPressure(double outletSteamPressure) {
	this->outletSteamPressure = outletSteamPressure;
	calculate();
}

void Turbine::setInletQuantity(SteamProperties::ThermodynamicQuantity inletQuantity) {
	this->inletQuantity = inletQuantity;
	calculate();
}

void Turbine::setOutletQuantity(SteamProperties::ThermodynamicQuantity outletQuantity) {
	this->outletQuantity = outletQuantity;
	calculate();
}

void Turbine::setInletQuantityValue(double inletQuantityValue) {
	this->inletQuantityValue = inletQuantityValue;
	calculate();
}

void Turbine::setOutletQuantityValue(double outletQuantityValue) {
	this->outletQuantityValue = outletQuantityValue;
	calculate();
}

void Turbine::setTurbineProperty(Turbine::TurbineProperty turbineProperty) {
	this->turbineProperty = turbineProperty;
	calculate();
}
