/**
 * @file
 * @brief Contains the implementation of the PRV calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include <iostream>
#include "ssmt/PRV.h"

PrvWithoutDesuperheating::PrvWithoutDesuperheating(const double inletPressure,
                                                   const SteamProperties::ThermodynamicQuantity quantityType,
                                                   const double quantityValue, const double inletMassFlow,
                                                   const double outletPressure)
        : inletPressure(inletPressure), quantityValue(quantityValue), inletMassFlow(inletMassFlow),
          outletPressure(outletPressure), quantityType(quantityType)
{
	calculateProperties();
}

void PrvWithoutDesuperheating::calculateProperties() {
	inletProperties = SteamProperties(inletPressure, quantityType, quantityValue).calculate();
  outletProperties = SteamProperties(outletPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                                     inletProperties.specificEnthalpy).calculate();
  inletEnergyFlow = inletProperties.specificEnthalpy * inletMassFlow;
}

PrvWithDesuperheating::PrvWithDesuperheating(const double inletPressure,
                                             const SteamProperties::ThermodynamicQuantity quantityType,
                                             const double quantityValue, const double inletMassFlow,
                                             const double outletPressure, const double feedwaterPressure,
                                             const SteamProperties::ThermodynamicQuantity feedwaterQuantityType,
                                             const double feedwaterQuantityValue, const double desuperheatingTemp)
        : PrvWithoutDesuperheating(inletPressure, quantityType, quantityValue, inletMassFlow, outletPressure),
          feedwaterPressure(feedwaterPressure),
          feedwaterQuantityValue(feedwaterQuantityValue), desuperheatingTemp(desuperheatingTemp),
          feedwaterQuantityType(feedwaterQuantityType)
{
    calculateProperties();
}

void PrvWithDesuperheating::calculateProperties() {
	inletProperties = SteamProperties(inletPressure, quantityType, quantityValue).calculate();
	feedwaterProperties = SteamProperties(feedwaterPressure, feedwaterQuantityType, feedwaterQuantityValue).calculate();
  outletProperties= SteamProperties(outletPressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                                    desuperheatingTemp).calculate();

  inletEnergyFlow = inletProperties.specificEnthalpy * inletMassFlow;
  feedwaterMassFlow = inletMassFlow * (inletProperties.specificEnthalpy - outletProperties.specificEnthalpy)
                          / (outletProperties.specificEnthalpy - feedwaterProperties.specificEnthalpy);

	feedwaterEnergyFlow = feedwaterMassFlow * feedwaterProperties.specificEnthalpy;
    outletMassFlow = inletMassFlow + feedwaterMassFlow;
	outletEnergyFlow = outletMassFlow * outletProperties.specificEnthalpy;
}
