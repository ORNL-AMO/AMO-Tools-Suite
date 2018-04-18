/**
 * @file
 * @brief Contains the implementation of the deaerator calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "ssmt/Deaerator.h"

Deaerator::Deaerator(const double deaeratorPressure, const double ventRate, const double feedwaterMassFlow,
                     const double waterPressure, const SteamProperties::ThermodynamicQuantity waterQuantityType,
                     const double waterQuantityValue, const double steamPressure,
                     const SteamProperties::ThermodynamicQuantity steamQuantityType, const double steamQuantityValue)
        : deaeratorPressure(deaeratorPressure), ventRate(ventRate), feedwaterMassFlow(feedwaterMassFlow),
          waterPressure(waterPressure), waterQuantityValue(waterQuantityValue), steamPressure(steamPressure),
          steamQuantityValue(steamQuantityValue), waterQuantityType(waterQuantityType),
          steamQuantityType(steamQuantityType)
{
    calculateProperties();
}

void Deaerator::calculateProperties() {
    auto const sp = SaturatedProperties(deaeratorPressure, SaturatedTemperature(deaeratorPressure).calculate()).calculate();
	SteamSystemModelerTool::SteamPropertiesOutput steamProps = {sp.temperature, sp.pressure, 0, 0, 0, sp.liquidSpecificEnthalpy,
																sp.liquidSpecificEntropy};
	feedwaterProperties = {feedwaterMassFlow, steamProps.specificEnthalpy * feedwaterMassFlow / 1000, steamProps};

	steamProps = {sp.temperature, sp.pressure, 1, 0, 0, sp.gasSpecificEnthalpy,
				  sp.gasSpecificEntropy};
	auto const ventedSteamMassFlow = (ventRate / 100) * feedwaterMassFlow;
	ventedSteamProperties = {
			ventedSteamMassFlow, steamProps.specificEnthalpy * ventedSteamMassFlow / 1000, steamProps
	};

	auto inletWaterProps = SteamProperties(waterPressure, waterQuantityType, waterQuantityValue).calculate();
	auto inletSteamProps = SteamProperties(steamPressure, steamQuantityType, steamQuantityValue).calculate();

    auto const totalDAMassFlow = ventedSteamMassFlow + feedwaterMassFlow;
    auto const totalOutletEnergyFlow = (feedwaterProperties.specificEnthalpy * feedwaterMassFlow
                                        + ventedSteamProperties.specificEnthalpy * ventedSteamMassFlow) / 1000;
    auto const minEnergyFlow = inletWaterProps.specificEnthalpy * totalDAMassFlow / 1000;
    auto const neededEnergyFlow = totalOutletEnergyFlow - minEnergyFlow;
    auto const inletSteamMassFlow = 1000 * neededEnergyFlow / (inletSteamProps.specificEnthalpy
                                                               - inletWaterProps.specificEnthalpy);

    auto const inletWaterMassFlow = totalDAMassFlow - inletSteamMassFlow;
    auto const inletSteamEnergyFlow = inletSteamProps.specificEnthalpy * inletSteamMassFlow / 1000;
    auto const inletWaterEnergyFlow = inletWaterProps.specificEnthalpy * inletWaterMassFlow / 1000;

	inletWaterProperties = {
			inletWaterMassFlow, inletWaterEnergyFlow, inletWaterProps
	};

	inletSteamProperties = {
			inletSteamMassFlow, inletSteamEnergyFlow, inletSteamProps
	};
}

double Deaerator::getDeaeratorPressure() const { return deaeratorPressure; }
double Deaerator::getVentRate() const { return ventRate; }
double Deaerator::getFeedwaterMassFlow() const { return feedwaterMassFlow; }
double Deaerator::getWaterPressure() const { return waterPressure; }
double Deaerator::getWaterQuantityValue() const { return waterQuantityValue; }
double Deaerator::getSteamPressure() const { return steamPressure; }
double Deaerator::getSteamQuantityValue() const { return steamQuantityValue; }
SteamProperties::ThermodynamicQuantity Deaerator::getWaterQuantityType() const { return waterQuantityType; }
SteamProperties::ThermodynamicQuantity Deaerator::getSteamQuantityType() const { return steamQuantityType; }

void Deaerator::setDeaeratorPressure(double deaeratorPressure) {
	this->deaeratorPressure = deaeratorPressure;
	calculateProperties();
}

void Deaerator::setVentRate(double ventRate) {
	this->ventRate = ventRate;
	calculateProperties();
}

void Deaerator::setFeedwaterMassFlow(double feedwaterMassFlow) {
	this->feedwaterMassFlow = feedwaterMassFlow;
	calculateProperties();
}

void Deaerator::setWaterPressure(double waterPressure) {
	this->waterPressure = waterPressure;
	calculateProperties();
}

void Deaerator::setWaterQuantityValue(double waterQuantityValue) {
	this->waterQuantityValue = waterQuantityValue;
	calculateProperties();
}

void Deaerator::setSteamPressure(double steamPressure) {
	this->steamPressure = steamPressure;
	calculateProperties();
}

void Deaerator::setSteamQuantityValue(double steamQuantityValue) {
	this->steamQuantityValue = steamQuantityValue;
	calculateProperties();
}

void Deaerator::setWaterQuantityType(SteamProperties::ThermodynamicQuantity waterQuantityType) {
	this->waterQuantityType = waterQuantityType;
	calculateProperties();
}

void Deaerator::setSteamQuantityType(SteamProperties::ThermodynamicQuantity steamQuantityType) {
	this->steamQuantityType = steamQuantityType;
	calculateProperties();
}
