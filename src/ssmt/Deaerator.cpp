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
    auto const & sp = SaturatedProperties(deaeratorPressure, SaturatedTemperature(deaeratorPressure).calculate()).calculate();
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
