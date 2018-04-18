/**
 * @file
 * @brief Contains the implementation of the boiler calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/Boiler.h"

Boiler::Boiler(const double deaeratorPressure, const double combustionEfficiency, const double blowdownRate,
               const double steamPressure, const SteamProperties::ThermodynamicQuantity quantityType,
               const double quantityValue, const double steamMassFlow)
		: deaeratorPressure(deaeratorPressure), combustionEfficiency(combustionEfficiency),
		  blowdownRate(blowdownRate), steamPressure(steamPressure), quantityType(quantityType),
		  quantityValue(quantityValue), steamMassFlow(steamMassFlow)
{
	calculateProperties();
}

void Boiler::calculateProperties() {
	auto sp = SteamProperties(steamPressure, quantityType, quantityValue).calculate();
	steamProperties = {steamMassFlow, sp.specificEnthalpy * steamMassFlow / 1000, sp};
	steamProperties.quality = 1; // TODO question tell UI guys that there needs to be a warning

//	steamProperties["steamEnergyFlow"] = steamProperties.at("specificEnthalpy") * steamMassFlow / 1000;
//	steamProperties["steamMassFlow"] = steamMassFlow;
//	steamProperties["quality"] = 1; // TODO tell UI guys that there needs to be warning

	sp = SteamProperties(deaeratorPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
	feedwaterProperties = {steamMassFlow / (1 - blowdownRate / 100),
	                       sp.specificEnthalpy * (steamMassFlow / (1 - blowdownRate / 100)) / 1000, sp};

//	feedwaterProperties = SteamProperties(deaeratorPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
//	feedwaterProperties["feedwaterMassFlow"] = steamMassFlow / (1 - blowdownRate / 100);
//	feedwaterProperties["feedwaterEnergyFlow"] = feedwaterProperties.at("specificEnthalpy")
//	                                             * feedwaterProperties.at("feedwaterMassFlow") / 1000;

	sp = SteamProperties(steamPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
	double const blowdownMassFlow = feedwaterProperties.massFlow * (blowdownRate / 100);
	blowdownProperties = {blowdownMassFlow, sp.specificEnthalpy * blowdownMassFlow / 1000, sp};

//	blowdownProperties = SteamProperties(steamPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
//	blowdownProperties["blowdownMassFlow"] = feedwaterProperties.at("feedwaterMassFlow") * (blowdownRate / 100);
//	blowdownProperties["blowdownEnergyFlow"] = blowdownProperties.at("specificEnthalpy")
//	                                           * blowdownProperties.at("blowdownMassFlow") / 1000;


	boilerEnergy = steamProperties.energyFlow + blowdownProperties.energyFlow - feedwaterProperties.energyFlow;

//	boilerEnergy = steamProperties.at("steamEnergyFlow") + blowdownProperties.at("blowdownEnergyFlow")
//	               - feedwaterProperties.at("feedwaterEnergyFlow");
	fuelEnergy = boilerEnergy / (combustionEfficiency / 100);
}

double Boiler::getDeaeratorPressure() const { return deaeratorPressure; }
double Boiler::getCombustionEfficiency() const { return combustionEfficiency; }
double Boiler::getBlowdownRate() const { return blowdownRate; }
double Boiler::getSteamPressure() const { return steamPressure; }
double Boiler::getQuantityValue() const { return quantityValue; }
double Boiler::getSteamMassFlow() const { return steamMassFlow; }
SteamProperties::ThermodynamicQuantity Boiler::getQuantityType() const { return quantityType; }

void Boiler::setDeaeratorPressure(double deaeratorPressure) {
	this->deaeratorPressure = deaeratorPressure;
	calculateProperties();
}

void Boiler::setCombustionEfficiency(double combustionEfficiency) {
	this->combustionEfficiency = combustionEfficiency;
	calculateProperties();
}

void Boiler::setBlowdownRate(const double blowdownRate) {
	this->blowdownRate = blowdownRate;
	calculateProperties();
}

void Boiler::setSteamPressure(const double steamPressure) {
	this->steamPressure = steamPressure;
	calculateProperties();
}

void Boiler::setQuantityType(SteamProperties::ThermodynamicQuantity quantity) {
	this->quantityType = quantity;
	calculateProperties();
}

void Boiler::setQuantityValue(const double quantityValue) {
	this->quantityValue = quantityValue;
	calculateProperties();
}

void Boiler::setSteamMassFlow(const double steamMassFlow) {
	this->steamMassFlow = steamMassFlow;
	calculateProperties();
}