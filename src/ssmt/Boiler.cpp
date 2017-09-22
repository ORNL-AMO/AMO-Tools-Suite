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
	steamProperties = SteamProperties(steamPressure, quantityType, quantityValue).calculate();
	steamProperties["steamEnergyFlow"] = steamProperties.at("specificEnthalpy") * steamMassFlow / 1000;
	steamProperties["steamMassFlow"] = steamMassFlow;
	steamProperties["quality"] = 1; // TODO tell UI guys that there needs to be warning

	feedwaterProperties = SteamProperties(deaeratorPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
	feedwaterProperties["feedwaterMassFlow"] = steamMassFlow / (1 - blowdownRate / 100);
	feedwaterProperties["feedwaterEnergyFlow"] = feedwaterProperties.at("specificEnthalpy")
	                                             * feedwaterProperties.at("feedwaterMassFlow") / 1000;

	blowdownProperties = SteamProperties(steamPressure, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
	blowdownProperties["blowdownMassFlow"] = feedwaterProperties.at("feedwaterMassFlow") * (blowdownRate / 100);
	blowdownProperties["blowdownEnergyFlow"] = blowdownProperties.at("specificEnthalpy")
	                                           * blowdownProperties.at("blowdownMassFlow") / 1000;

	boilerEnergy = steamProperties.at("steamEnergyFlow") + blowdownProperties.at("blowdownEnergyFlow")
	               - feedwaterProperties.at("feedwaterEnergyFlow");
	fuelEnergy = boilerEnergy / (combustionEfficiency / 100);
}
