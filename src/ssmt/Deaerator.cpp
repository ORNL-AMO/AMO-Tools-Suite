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
    feedwaterProperties = {
            {"temperature", sp.at("temperature")},
            {"pressure", sp.at("pressure")},
            {"specificEnthalpy", sp.at("liquidSpecificEnthalpy")},
            {"specificEntropy", sp.at("liquidSpecificEntropy")},
            {"quality", 0},
            {"massFlow", feedwaterMassFlow},
            {"energyFlow", sp.at("liquidSpecificEnthalpy") * feedwaterMassFlow / 1000}
    };

    auto const ventedSteamMassFlow = (ventRate / 100) * feedwaterMassFlow;
    ventedSteamProperties = {
            {"temperature", sp.at("temperature")},
            {"pressure", sp.at("pressure")},
            {"specificEnthalpy", sp.at("gasSpecificEnthalpy")},
            {"specificEntropy", sp.at("gasSpecificEntropy")},
            {"quality", 1},
            {"massFlow", ventedSteamMassFlow},
            {"energyFlow", sp.at("gasSpecificEnthalpy") * ventedSteamMassFlow / 1000}
    };

    inletWaterProperties = SteamProperties(waterPressure, waterQuantityType, waterQuantityValue).calculate();
    inletSteamProperties = SteamProperties(steamPressure, steamQuantityType, steamQuantityValue).calculate();

    auto const totalDAMassFlow = ventedSteamMassFlow + feedwaterMassFlow;
    auto const totalOutletEnergyFlow = (feedwaterProperties.at("specificEnthalpy") * feedwaterMassFlow
                                        + ventedSteamProperties.at("specificEnthalpy") * ventedSteamMassFlow) / 1000;
    auto const minEnergyFlow = inletWaterProperties.at("specificEnthalpy") * totalDAMassFlow / 1000;
    auto const neededEnergyFlow = totalOutletEnergyFlow - minEnergyFlow;
    auto const inletSteamMassFlow = 1000 * neededEnergyFlow / (inletSteamProperties.at("specificEnthalpy")
                                                               - inletWaterProperties.at("specificEnthalpy"));

    auto const inletWaterMassFlow = totalDAMassFlow - inletSteamMassFlow;
    auto const inletSteamEnergyFlow = inletSteamProperties.at("specificEnthalpy") * inletSteamMassFlow / 1000;
    auto const inletWaterEnergyFlow = inletWaterProperties.at("specificEnthalpy") * inletWaterMassFlow / 1000;

    inletWaterProperties["massFlow"] = inletWaterMassFlow;
    inletWaterProperties["energyFlow"] = inletWaterEnergyFlow;

    inletSteamProperties["massFlow"] = inletSteamMassFlow;
    inletSteamProperties["energyFlow"] = inletSteamEnergyFlow;
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
