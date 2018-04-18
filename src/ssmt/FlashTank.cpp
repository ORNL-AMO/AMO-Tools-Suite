/**
 * @file
 * @brief Contains the implementation of the flash tank calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/FlashTank.h"

FlashTank::FlashTank(const double inletWaterPressure, const SteamProperties::ThermodynamicQuantity quantityType,
          const double quantityValue, const double inletWaterMassFlow, const double tankPressure)
		: inletWaterPressure(inletWaterPressure), quantityValue(quantityValue), inletWaterMassFlow(inletWaterMassFlow),
		  tankPressure(tankPressure), quantityType(quantityType)
{
	calculateProperties();
}

void FlashTank::calculateProperties() {
	auto sp =  SteamProperties(inletWaterPressure, quantityType, quantityValue).calculate();
    inletWaterProperties = {inletWaterMassFlow, inletWaterMassFlow * sp.specificEnthalpy / 1000, sp};

//    inletWaterProperties = SteamProperties(inletWaterPressure, quantityType, quantityValue).calculate();
//	inletWaterProperties["massFlow"] = inletWaterMassFlow;
//	inletWaterProperties["energyFlow"] = inletWaterMassFlow * inletWaterProperties.at("specificEnthalpy") / 1000;

//	if (quantityType == SteamProperties::ThermodynamicQuantity::QUALITY) inletWaterProperties["quality"] = quantityValue;
//	else inletWaterProperties["quality"] = 0;

    auto saturatedProperties = SaturatedProperties(tankPressure, SaturatedTemperature(tankPressure).calculate()).calculate();
	double const liquidMassFlow = inletWaterMassFlow * (inletWaterProperties.specificEnthalpy - saturatedProperties.at("gasSpecificEnthalpy"))
						  / (saturatedProperties.at("liquidSpecificEnthalpy") - saturatedProperties.at("gasSpecificEnthalpy"));
	// TODO question density is 0 below bc saturated properties doesn't return density, same with both sp objects here
    sp = {
			saturatedProperties.at("temperature"), saturatedProperties.at("pressure"), 0,
			saturatedProperties.at("liquidSpecificVolume"), 0,
			saturatedProperties.at("liquidSpecificEnthalpy"), saturatedProperties.at("liquidSpecificEntropy")
	};
	outletLiquidSaturatedProperties = {
            liquidMassFlow,
			liquidMassFlow * saturatedProperties.at("liquidSpecificEnthalpy") / 1000,
            sp
	};

	sp = {
			saturatedProperties.at("temperature"), saturatedProperties.at("pressure"), 1,
			saturatedProperties.at("gasSpecificVolume"), 0,
			saturatedProperties.at("gasSpecificEnthalpy"), saturatedProperties.at("gasSpecificEntropy")
	};
	double const gasMassFlow = inletWaterMassFlow - outletLiquidSaturatedProperties.massFlow;
	outletGasSaturatedProperties = {gasMassFlow, gasMassFlow * sp.specificEnthalpy / 1000, sp};

//	outletSaturatedProperties = SaturatedProperties(tankPressure, SaturatedTemperature(tankPressure).calculate()).calculate();
//    outletSaturatedProperties["liquidMassFlow"] = inletWaterMassFlow
//                                                  * (inletWaterProperties.at("specificEnthalpy")
//                                                     - outletSaturatedProperties.at("gasSpecificEnthalpy"))
//                                                  / (outletSaturatedProperties.at("liquidSpecificEnthalpy")
//                                                     - outletSaturatedProperties.at("gasSpecificEnthalpy"));

//    outletSaturatedProperties["gasMassFlow"] = inletWaterMassFlow - outletSaturatedProperties.at("liquidMassFlow");
//	outletSaturatedProperties["gasQuality"] = 1;
//
//    outletSaturatedProperties["gasEnergyFlow"] = outletSaturatedProperties.at("gasMassFlow")
//                                                 * outletSaturatedProperties.at("gasSpecificEnthalpy") / 1000;

//    outletSaturatedProperties["liquidEnergyFlow"] = outletSaturatedProperties.at("liquidMassFlow")
//                                                    * outletSaturatedProperties.at("liquidSpecificEnthalpy") / 1000;
//	outletSaturatedProperties["liquidQuality"] = 0;
}

double FlashTank::getInletWaterPressure() const { return inletWaterPressure; }

double FlashTank::getQuantityValue() const { return quantityValue; }

double FlashTank::getInletWaterMassFlow() const { return inletWaterMassFlow; }

double FlashTank::getTankPressure() const { return tankPressure; }

SteamProperties::ThermodynamicQuantity FlashTank::getQuantityType() const { return quantityType; }

void FlashTank::setInletWaterPressure(double inletWaterPressure) {
	this->inletWaterPressure = inletWaterPressure;
	calculateProperties();
}

void FlashTank::setQuantityValue(double quantityValue) {
	this->quantityValue = quantityValue;
	calculateProperties();
}

void FlashTank::setInletWaterMassFlow(double inletWaterMassFlow) {
	this->inletWaterMassFlow = inletWaterMassFlow;
	calculateProperties();
}

void FlashTank::setTankPressure(double tankPressure) {
	this->tankPressure = tankPressure;
	calculateProperties();
}

void FlashTank::setQuantityType(SteamProperties::ThermodynamicQuantity quantityType) {
	this->quantityType = quantityType;
	calculateProperties();
}
