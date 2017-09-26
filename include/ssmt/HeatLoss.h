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

    std::unordered_map <std::string, double> const & getInletProperties() const { return inletProperties; };

    /**
     * gets all of the properties of the outlet steam
     * @return std::unordered_map <std::string, double>, outlet steam properties
     */
    std::unordered_map <std::string, double> const & getOutletProperties() const { return outletProperties; };

    void calculateProperties();

    /**
     * Calculates the heat loss
     * @return double, heat loss in MJ/hr
     */
    double getHeatLoss() const { return heatLoss; }
    double getInletPressure() const { return inletPressure; };
    double getQuantityValue() const { return quantityValue; };
    double getInletMassFlow() const { return inletMassFlow; };
    double getPercentHeatLoss() const { return percentHeatLoss; };
    SteamProperties::ThermodynamicQuantity getQuantityType() const { return quantityType; };

    void setInletPressure(double inletPressure);
    void setQuantityValue(double quantityValue);
    void setInletMassFlow(double inletMassFlow);
    void setPercentHeatLoss(double percentHeatLoss);
    void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType);;


private:
    double inletPressure, quantityValue, inletMassFlow, percentHeatLoss;
    std::unordered_map <std::string, double> inletProperties;
    double inletEnergyFlow, outletEnergyFlow;
    std::unordered_map <std::string, double> outletProperties;

    double heatLoss;
    SteamProperties::ThermodynamicQuantity quantityType;
};

#endif //AMO_TOOLS_SUITE_HEATLOSS_H
