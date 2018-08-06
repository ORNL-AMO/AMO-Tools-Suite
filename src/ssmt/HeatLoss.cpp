/**
 * @file
 * @brief Contains the implementation of the heat loss calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/HeatLoss.h"

HeatLoss::HeatLoss(const double inletPressure, const SteamProperties::ThermodynamicQuantity quantityType,
                   const double quantityValue, const double inletMassFlow, const double percentHeatLoss)
        : inletPressure(inletPressure), quantityValue(quantityValue), inletMassFlow(inletMassFlow),
          percentHeatLoss(percentHeatLoss / 100), quantityType(quantityType)
{
	calculateProperties();
}

void HeatLoss::calculateProperties() {
	auto sp = SteamProperties(inletPressure, quantityType, quantityValue).calculate();
	inletEnergyFlow = sp.specificEnthalpy * inletMassFlow / 1000;
	outletEnergyFlow = inletEnergyFlow * (1 - percentHeatLoss);

	inletProperties = {inletMassFlow, inletEnergyFlow, sp};

	sp = SteamProperties(inletPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
	                     1000 * outletEnergyFlow / inletMassFlow).calculate();
	outletProperties = {inletMassFlow, outletEnergyFlow, sp};

	heatLoss = inletEnergyFlow - outletEnergyFlow;
}

void HeatLoss::setInletPressure(double inletPressure) {
	this->inletPressure = inletPressure;
	calculateProperties();
}

void HeatLoss::setQuantityValue(double quantityValue) {
	this->quantityValue = quantityValue;
	calculateProperties();
}

void HeatLoss::setInletMassFlow(double inletMassFlow) {
	this->inletMassFlow = inletMassFlow;
	calculateProperties();
}

void HeatLoss::setPercentHeatLoss(double percentHeatLoss) {
	this->percentHeatLoss = percentHeatLoss;
	calculateProperties();
}

void HeatLoss::setQuantityType(SteamProperties::ThermodynamicQuantity quantityType) {
	this->quantityType = quantityType;
	calculateProperties();
}