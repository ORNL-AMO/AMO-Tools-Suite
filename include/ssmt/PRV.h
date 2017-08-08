/**
 * @file
 * @brief Calculator for the steam properties after after a pressure drop for steam systems
 *
 * Calculates the properties of steam after a pressure drop with optional desuperheating.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"

#ifndef AMO_TOOLS_SUITE_PRV_H
#define AMO_TOOLS_SUITE_PRV_H

/**
* PRV without Desuperheating calculator class
* Used to calculate the heat steam properties
*/
class PrvWithoutDesuperheating {
public:
    /**
     *
     * Constructor for the PRV without desuperheating calculator
     *
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletMassFlow double, inlet mass flow in kg/hr
     * @param outletPressure double, houtlet pressure in MPa
     *
     * @return nothing
     *
     * */
    PrvWithoutDesuperheating(
            double inletPressure,
            SteamProperties::ThermodynamicQuantity quantityType,
            double quantityValue,
            double inletMassFlow,
            double outletPressure)
            : inletPressure_(inletPressure),
              quantityType_(quantityType),
              quantityValue_(quantityValue),
              inletMassFlow_(inletMassFlow),
              outletPressure_(outletPressure)

    {
        inletEnergyFlow_ = 0.0;
        outletMassFlow_ = 0.0;
        outletEnergyFlow_ = 0.0;

    }

    PrvWithoutDesuperheating() = default;

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
     * Sets the outlet pressure
     *
     * @param outletPressure double, outlet pressure in MPa
     *
     * @return nothing
     */
    void setOutletPressure(double outletPressure) {
        outletPressure_ = outletPressure;
    }

    /**
     * Gets the outlet pressure
     *
     * @return double, outlet pressure in MPa
     */
    double getOutletPressure() const {
        return outletPressure_;
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
    double outletPressure_ = 0.0;


    // Out values
    std::unordered_map <std::string, double> inletProperties_;
    std::unordered_map <std::string, double> outletProperties_;
    double inletEnergyFlow_;
    double outletMassFlow_;
    double outletEnergyFlow_;
};



/**
* PRV with Desuperheating calculator class
* Used to calculate the heat steam properties
*/
class PrvWithDesuperheating {
public:
    /**
     *
     * Constructor for the PRV with desuperheating calculator
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
    PrvWithoutDesuperheating(
            double inletPressure,
            SteamProperties::ThermodynamicQuantity quantityType,
            double quantityValue,
            double inletMassFlow,
            double outletPressure,
            double feedwaterPressure,
            SteamProperties::ThermodynamicQuantity feedwaterQuantityType,
            double feedwaterQuantityValue,
            double desuperheatingTemp)
            : inletPressure_(inletPressure),
              quantityType_(quantityType),
              quantityValue_(quantityValue),
              inletMassFlow_(inletMassFlow),
              outletPressure_(outletPressure),
              feedwaterPressure_(feedwaterPressure),
              feedwaterQuantityType_(feedwaterQuantityType),
              feedwaterQuantityValue_(feedwaterQuantityValue),
              desuperheatingTemp_(desuperheatingTemp)

    {
        inletEnergyFlow_ = 0.0;
        outletMassFlow_ = 0.0;
        outletEnergyFlow_ = 0.0;
        feedwaterMassFlow_ = 0.0;
        feedwaterEnergyFlow_ = 0.0;

    }

    PrvWithDesuperheating() = default;

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
     * Sets the outlet pressure
     *
     * @param outletPressure double, outlet pressure in MPa
     *
     * @return nothing
     */
    void setOutletPressure(double outletPressure) {
        outletPressure_ = outletPressure;
    }

    /**
     * Gets the outlet pressure
     *
     * @return double, outlet pressure in MPa
     */
    double getOutletPressure() const {
        return outletPressure_;
    }

    /**
     * Sets the feedwater pressure
     *
     * @param feedwaterPressure double, feedwater pressure in MPa
     *
     * @return nothing
     */
    void setFeedwaterPressure(double feedwaterPressure) {
        feedwaterPressure_ = feedwaterPressure;
    }

    /**
     * Gets the feedwater pressure
     *
     * @return double, feedwater pressure in MPa
     */
    double getFeedwaterPressure() const {
        return feedwaterPressure_;
    }

    /**
     * Sets the feedwater quantity type
     *
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setFeedwaterQuantityType(SteamProperties::ThermodynamicQuantity feedwaterQuantityType) {
        feedwaterQuantityType_ = feedwaterQuantityType;
    }

    /**
     * Gets the feedwater quantity type
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getFeedwaterQuantityType() const {
        return feedwaterQuantityType_;
    }

    /**
     * Sets the feedwater quantity value
     *
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setFeedwaterQuantityValue(double feedwaterQuantityValue) {
        feedwaterQuantityValue_ = feedwaterQuantityValue;
    }

    /**
     * Gets the feedwater quantity value
     *
     * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getFeedwaterQuantityValue() const {
        return feedwaterQuantityValue_;
    }

    /**
     * Sets the desuperheating temperature
     *
     * @param desuperheatingTemp double, desuperheating temperature in K
     *
     * @return nothing
     */
    void setDesuperheatingTemp(double desuperheatingTemp) {
        desuperheatingTemp_ = desuperheatingTemp;
    }

    /**
     * Gets the desuperheating temperature
     *
     * @return double, desuperheating temperature in K
     */
    double getDesuperheatingTemp() const {
        return desuperheatingTemp_;
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
     * Calculates all of the properties of the feedwater steam
     * @return std::unordered_map <std::string, double>, feedwater steam properties
     */
    std::unordered_map <std::string, double> getFeedwaterProperties();

    /**
     * Calculates the inlet energy flow
     * @return double, inlet steam energy flow in MJ/hr
     */
    double getInletEnergyFlow();

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

    /**
     * Calculates the feedwater mass flow
     * @return double, feedwater mass flow in kg/hr
     */
    double getFeedwaterMassFlow();

    /**
     * Calculates the feedwater energy flow
     * @return double, feedwater energy flow in MJ/hr
     */
    double getFeedwaterEnergyFlow();

private:
    // In values
    double inletPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity quantityType_;
    double quantityValue_ = 0.0;
    double inletMassFlow_ = 0.0;
    double outletPressure_ = 0.0;
    double feedwaterPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity feedwaterQuantityType_;
    double feedwaterQuantityValue_ = 0.0;
    double desuperheatingTemp_ = 0.0;


    // Out values
    std::unordered_map <std::string, double> inletProperties_;
    std::unordered_map <std::string, double> outletProperties_;
    std::unordered_map <std::string, double> feedwaterProperties_;
    double inletEnergyFlow_;
    double outletMassFlow_;
    double outletEnergyFlow_;
    double feedwaterMassFlow_;
    double feedwaterEnergyFlow_;
};


#endif //AMO_TOOLS_SUITE_PRV_H
