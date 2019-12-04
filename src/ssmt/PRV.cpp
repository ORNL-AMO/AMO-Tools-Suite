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

std::ostream &operator<<(std::ostream &stream, const PrvWithoutDesuperheating &prv) {
    stream << "PrvWithoutDesuperheating["
           << "inletPressure=" << prv.inletPressure
           << ", inletMassFlow=" << prv.inletMassFlow
           << ", inletEnergyFlow=" << prv.inletEnergyFlow
           << ", quantityValue=" << prv.quantityValue
           << ", quantityType=" << static_cast< int >(prv.quantityType)
           << ", inletProperties=" << prv.inletProperties
           << ", outletPressure=" << prv.outletPressure
           << ", outletProperties=" << prv.outletProperties
           << "]";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<PrvWithoutDesuperheating> &prv) {
    if (prv == nullptr) {
        stream << "PrvWithoutDesuperheating[nullptr]";
    } else {
        stream << *prv;
    }
    return stream;
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


std::ostream &operator<<(std::ostream &stream, const PrvWithDesuperheating &prv) {
    stream << "PrvWithDesuperheating["
           << "inletPressure=" << prv.inletPressure
           << ", inletMassFlow=" << prv.inletMassFlow
           << ", inletEnergyFlow=" << prv.inletEnergyFlow
           << ", quantityValue=" << prv.quantityValue
           << ", quantityType=" << static_cast< int >(prv.quantityType)
           << ", inletProperties=" << prv.inletProperties
           << ", outletPressure=" << prv.outletPressure
           << ", outletProperties=" << prv.outletProperties

           << ", feedwaterPressure=" << prv.feedwaterPressure
           << ", feedwaterQuantityValue=" << prv.feedwaterQuantityValue
           << ", desuperheatingTemp=" << prv.desuperheatingTemp
           << ", feedwaterQuantityType=" << static_cast< int >(prv.feedwaterQuantityType)
           << ", feedwaterProperties=" << prv.feedwaterProperties
           << ", inletEnergyFlow=" << prv.inletEnergyFlow
           << ", outletMassFlow=" << prv.outletMassFlow
           << ", outletEnergyFlow=" << prv.outletEnergyFlow
           << ", feedwaterMassFlow=" << prv.feedwaterMassFlow
           << ", feedwaterEnergyFlow=" << prv.feedwaterEnergyFlow
           << "]";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<PrvWithDesuperheating> &prv) {
    if (prv == nullptr) {
        stream << "PrvWithDesuperheating[nullptr]";
    } else {
        stream << *prv;
    }
    return stream;
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
