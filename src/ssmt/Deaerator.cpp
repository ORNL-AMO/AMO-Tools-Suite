/**
 * @file
 * @brief Contains the implementation of the deaerator calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "ssmt/Deaerator.h"

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
            {"gasSpecificEnthalpy", sp.at("gasSpecificEnthalpy")},
            {"gasSpecificEntropy", sp.at("gasSpecificEntropy")},
            {"quality", 1},
            {"massFlow", ventedSteamMassFlow},
            {"energyFlow", sp.at("gasSpecificEnthalpy") * ventedSteamMassFlow / 1000}
    };

    inletWaterProperties = SteamProperties(waterPressure, waterQuantityType, waterQuantityValue).calculate();
    inletSteamProperties = SteamProperties(steamPressure, steamQuantityType, steamQuantityValue).calculate();

    auto const totalDAMassFlow = ventedSteamMassFlow + feedwaterMassFlow;
    auto const totalOutletEnergyFlow = (feedwaterProperties["specificEnthalpy"] * feedwaterMassFlow
                                        + ventedSteamProperties["specificEnthalpy"] * ventedSteamMassFlow) / 1000;
    auto const minEnergyFlow = inletWaterProperties["specificEnthalpy"] * totalDAMassFlow / 1000;
    auto const neededEnergyFlow = totalOutletEnergyFlow - minEnergyFlow;
    auto const inletSteamMassFlow = 1000 * neededEnergyFlow
                                    / (inletSteamProperties["specificEnthalpy"] - inletWaterProperties["specificEnthalpy"]);

    auto const inletWaterMassFlow = totalDAMassFlow - inletSteamMassFlow;
    auto const inletSteamEnergyFlow = inletSteamProperties["specificEnthalpy"] * inletSteamMassFlow / 1000;
    auto const inletWaterEnergyFlow = inletWaterProperties["specificEnthalpy"] * inletWaterMassFlow / 1000;

    inletWaterProperties["massFlow"] = inletWaterMassFlow;
    inletWaterProperties["energyFlow"] = inletWaterEnergyFlow;

    inletSteamProperties["massFlow"] = inletSteamMassFlow;
    inletSteamProperties["energyFlow"] = inletSteamEnergyFlow;
}
