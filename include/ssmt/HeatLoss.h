/**
 * @file
 * @brief Calculator for the heat loss for steam systems
 *
 * Calculates the energy (heat) loss and outlet steam properties given inlet steam conditions and a % heat loss.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"

#ifndef AMO_TOOLS_SUITE_HEATLOSS_H
#define AMO_TOOLS_SUITE_HEATLOSS_H

/**
 * Heat Loss calculator class
 * Used to calculate the heat energy loss and outlet steam properties
 */
class HeatLoss {
public:
    /**
     *
     * Constructor for the heat loss calculator
     *
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletMassFlow double, inlet mass flow in kg/hr
     * @param percentHeatLoss double, heat loss as %
     *
     * @return nothing
     *
     * */
    HeatLoss(double inletPressure, SteamProperties::ThermodynamicQuantity quantityType, double quantityValue,
             double inletMassFlow, double percentHeatLoss);

    std::unordered_map <std::string, double> & getInletProperties() { return inletProperties; };

    /**
     * Calculates all of the properties of the outlet steam
     * @return std::unordered_map <std::string, double>, outlet steam properties
     */
    std::unordered_map <std::string, double> & getOutletProperties() { return outletProperties; };

    /**
     * Calculates the inlet energy flow
     * @return double, inlet steam energy flow in MJ/hr
     */
//    double getInletEnergyFlow();

    /**
     * Calculates the heat loss
     * @return double, heat loss in MJ/hr
     */
    double getHeatLoss() const { return heatLoss; };

    /**
     * Calculates the outlet mass flow
     * @return double, outlet mass flow in kg/hr
     */
//    double getOutletMassFlow();

    /**
     * Calculates the outlet energy flow
     * @return double, outlet energy flow in MJ/hr
     */
//    double getOutletEnergyFlow();

private:
    // In values
    const double inletPressure, quantityValue, inletMassFlow, percentHeatLoss;
    std::unordered_map <std::string, double> inletProperties, outletProperties;
    const double inletEnergyFlow, outletEnergyFlow, heatLoss;
    SteamProperties::ThermodynamicQuantity quantityType;

    // Out values
};



#endif //AMO_TOOLS_SUITE_HEATLOSS_H
