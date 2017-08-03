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
    HeatLoss(
            double inletPressure,
            SteamProperties::ThermodynamicQuantity quantityType,
            double quantityValue,
            double inletMassFlow,
            double percentHeatLoss)
            : inletPressure_(inletPressure),
              quantityType_(quantityType),
              quantityValue_(quantityValue),
              inletMassFlow_(inletMassFlow),
              percentHeatLoss_(percentHeatLoss)

    {
        inletEnergyFlow_ = 0.0;
        heatLoss_ = 0.0;
        outletMassFlow_ = 0.0;
        outletEnergyFlow_ = 0.0;

    }

    HeatLoss() = default;

    /**
     * Sets the inlet pressure
     *
     * @param inletPressure double, pressure of the inlet steam in MPa
     *
     * @return nothing
     */
    void setInletPressure(double inletPressure) {
        inletPressure_ = inletPressure;
    }

    /**
     * Gets the inlet pressure
     *
     * @return double, pressure of the inlet steam in MPa
     */
    double getInletPressure() const {
        return inletPressure_;
    }

    /**
     * Sets the quantity type
     *
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType) {
        quantityType_ = quantityType;
    }

    /**
     * Gets the quantity type
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getQuantityType() const {
        return quantityType_;
    }

    /**
     * Sets the quantity value
     *
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setQuantityValue(double quantityValue) {
        quantityValue_ = quantityValue;
    }

    /**
     * Gets the quantity value
     *
     * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getQuantityValue() const {
        return quantityValue_;
    }

    /**
     * Sets the inlet mass flow
     *
     * @param inletMassFlow double, mass flow of the inlet steam in kg/hr
     *
     * @return nothing
     */
    void setInletMassFlow(double inletMassFlow) {
        inletMassFlow_ = inletMassFlow;
    }

    /**
     * Gets the inlet mass flow
     *
     * @return double, mass flow of the inlet steam in kg/hr
     */
    double getInletMassFlow() const {
        return inletMassFlow_;
    }

    /**
     * Sets the percent heat loss
     *
     * @param percentHeatLoss double, heat loss as %
     *
     * @return nothing
     */
    void setPercentHeatLoss(double percentHeatLoss) {
        percentHeatLoss_ = percentHeatLoss;
    }

    /**
     * Gets the percent heat loss
     *
     * @return double, heat loss as %
     */
    double getPercentHeatLoss() const {
        return percentHeatLoss_;
    }

    /**
     * Calculates all of the properties of the inlet steam
     * @return std::unordered_map <std::string, double>, inlet steam properties
     */
    std::unordered_map <std::string, double> getInletProperties();

    /**
     * Calculates all of the properties of the outlet steam
     * @return std::unordered_map <std::string, double>, outlet steam properties
     */
    std::unordered_map <std::string, double> getOutletProperties();

    /**
     * Calculates the inlet energy flow
     * @return double, inlet steam energy flow in MJ/hr
     */
    double getInletEnergyFlow();

    /**
     * Calculates the heat loss
     * @return double, heat loss in MJ/hr
     */
    double getHeatLoss();

    /**
     * Calculates the outlet mass flow
     * @return double, outlet mass flow in kg/hr
     */
    double getOutletMassFlow();

    /**
     * Calculates the outlet energy flow
     * @return double, outlet energy flow in MJ/hr
     */
    double getOutletEnergyFlow();

private:
    // In values
    double inletPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity quantityType_;
    double quantityValue_ = 0.0;
    double inletMassFlow_ = 0.0;
    double percentHeatLoss_ = 0.0;


    // Out values
    std::unordered_map <std::string, double> inletProperties_;
    std::unordered_map <std::string, double> outletProperties_;
    double inletEnergyFlow_;
    double heatLoss_;
    double outletMassFlow_;
    double outletEnergyFlow_;
};



#endif //AMO_TOOLS_SUITE_HEATLOSS_H
