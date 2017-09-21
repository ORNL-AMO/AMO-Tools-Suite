/**
 * @file
 * @brief Calculator for the deaerator for steam systems
 *
 * Calculates the required water and steam flows for a required feedwater mass flow.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"
#include "SaturatedProperties.h"

#ifndef AMO_TOOLS_SUITE_DEAERATOR_H
#define AMO_TOOLS_SUITE_DEAERATOR_H

/**
 * Deaerator calculator class
 * Used to calculate the required water and steam flows for a required feedwater mass flow.
 */
class Deaerator {
public:
    /**
     *
     * Constructor for the deaerator calculator
     *
     * @param deaeratorPressure double, deaerator pressure in MPa
     * @param ventRate double, vent rate as %
     * @param feedwaterMassFlow double, mass flow of the feedwater in kg/hr
     * @param waterPressure double, pressure of water in MPa
     * @param waterQuantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param waterQuantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param steamPressure double, pressure of steam in MPa
     * @param steamQuantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param steamQuantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)

     * @return nothing
     *
     * */
    Deaerator(const double deaeratorPressure, const double ventRate, const double feedwaterMassFlow,
              const double waterPressure, const SteamProperties::ThermodynamicQuantity waterQuantityType,
              const double waterQuantityValue, const double steamPressure,
              const SteamProperties::ThermodynamicQuantity steamQuantityType, const double steamQuantityValue)
            : deaeratorPressure(deaeratorPressure), ventRate(ventRate), feedwaterMassFlow(feedwaterMassFlow),
              waterPressure(waterPressure), waterQuantityType(waterQuantityType),
              waterQuantityValue(waterQuantityValue), steamPressure(steamPressure),
              steamQuantityType(steamQuantityType), steamQuantityValue(steamQuantityValue)
    {
        calculateProperties();
    }

	std::unordered_map<std::string, double> getFeedwaterProperties() { return feedwaterProperties; }
    std::unordered_map<std::string, double> getVentedSteamProperties() { return ventedSteamProperties; }
    std::unordered_map<std::string, double> getInletWaterProperties() { return inletWaterProperties; }
    std::unordered_map<std::string, double> getInletSteamProperties() { return inletSteamProperties; }

private:

    void calculateProperties();

    const double deaeratorPressure = 0, ventRate = 0, feedwaterMassFlow = 0, waterPressure = 0, waterQuantityValue = 0;
    const double steamPressure = 0, steamQuantityValue = 0;
    const SteamProperties::ThermodynamicQuantity waterQuantityType, steamQuantityType;

    std::unordered_map <std::string, double> feedwaterProperties, ventedSteamProperties, inletWaterProperties;
    std::unordered_map <std::string, double> inletSteamProperties;
};

#endif //AMO_TOOLS_SUITE_DEAERATOR_H
