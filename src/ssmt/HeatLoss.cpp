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
        : inletPressure(inletPressure), quantityValue(quantityValue),
          inletMassFlow(inletMassFlow), percentHeatLoss(percentHeatLoss / 100),
          inletProperties(SteamProperties(this->inletPressure, quantityType, this->quantityValue).calculate()),
          inletEnergyFlow(inletProperties.at("specificEnthalpy") * this->inletMassFlow / 1000),
          outletEnergyFlow(inletEnergyFlow * (1 - this->percentHeatLoss)),
          outletProperties(SteamProperties(this->inletPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                                           outletEnergyFlow / this->inletMassFlow).calculate()),
          heatLoss(inletEnergyFlow - outletEnergyFlow), quantityType(quantityType)
{
	inletProperties["massFlow"] = inletMassFlow;
	inletProperties["energyFlow"] = inletEnergyFlow;
	outletProperties["massFlow"] = inletMassFlow;
	outletProperties["energyFlow"] = outletEnergyFlow;
}
