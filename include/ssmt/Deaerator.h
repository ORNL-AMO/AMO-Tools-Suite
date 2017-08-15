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
    Deaerator(
            double deaeratorPressure,
            double ventRate,
            double feedwaterMassFlow,
            double waterPressure,
            SteamProperties::ThermodynamicQuantity waterQuantityType,
            double waterQuantityValue,
            double steamPressure,
            SteamProperties::ThermodynamicQuantity steamQuantityType,
            double steamQuantityValue)
            : deaeratorPressure_(deaeratorPressure),
              ventRate_(ventRate),
              feedwaterMassFlow_(feedwaterMassFlow),
              waterPressure_(waterPressure),
              waterQuantityType_(waterQuantityType),
              waterQuantityValue_(waterQuantityValue),
              steamPressure_(steamPressure),
              steamQuantityType_(steamQuantityType),
              steamQuantityValue_(steamQuantityValue)

    {
        feedwaterEnergyFlow_ = 0.0;
        ventedSteamMassFlow_ = 0.0;
        ventedSteamEnergyFlow_ = 0.0;
        inletWaterMassFlow_ = 0.0;
        inletWaterEnergyFlow_ = 0.0;
        inletSteamMassFlow_ = 0.0;
        inletSteamEnergyFlow_ = 0.0;

        totalDAMassFlow_ = 0.0;
        totalOutletEnergyFlow_ = 0.0;
        minEnergyFlow_ = 0.0;
        neededEnergyFlow_ = 0.0;

    }

    Deaerator() = default;

    /**
     * Sets the deaerator pressure
     *
     * @param deaeratorPressure double, pressure of the deaerator in MPa
     *
     * @return nothing
     */
    void setDeaeratorPressure(double deaeratorPressure) {
        deaeratorPressure_ = deaeratorPressure;
    }

    /**
     * Gets the deaerator pressure
     *
     * @return double, pressure of the deaerator in MPa
     */
    double getDeaeratorPressure() const {
        return deaeratorPressure_;
    }

    /**
     * Sets the vent rate
     *
     * @param ventRate double, vent rate as %
     *
     * @return nothing
     */
    void setVentRate(double ventRate) {
        ventRate_ = ventRate;
    }

    /**
     * Gets the vent rate
     *
     * @return double, vent rate as %
     */
    double getVentRate() const {
        return ventRate_;
    }

    /**
     * Sets the feedwater mass flow
     *
     * @param feedwaterMassFlow double, feedwater mass flow in kg/hr
     *
     * @return nothing
     */
    void setFeedwaterMassFlow(double feedwaterMassFlow) {
        feedwaterMassFlow_ = feedwaterMassFlow;
    }

    /**
     * Gets the feedwater mass flow
     *
     * @return double, feedwater mass flow in kg/hr
     */
    double getFeedwaterMassFlow() const {
        return feedwaterMassFlow_;
    }

    /**
     * Sets the pressure of the water
     *
     * @param waterPressure double, pressure of water in MPa
     *
     * @return nothing
     */
    void setWaterPressure(double waterPressure) {
        waterPressure_ = waterPressure;
    }

    /**
     * Gets the water pressure
     *
     * @return double, pressure of the water in MPa
     */
    double getWaterPressure() const {
        return waterPressure_;
    }

    /**
     * Sets the quantity type for water
     *
     * @param waterQuantityType SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setWaterQuantityType(SteamProperties::ThermodynamicQuantity waterQuantityType) {
        waterQuantityType_ = waterQuantityType;
    }

    /**
     * Gets the quantity type for water
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getWaterQuantityType() const {
        return waterQuantityType_;
    }

    /**
     * Sets the quantity value for water
     *
     * @param waterQuantityValue double, value of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setWaterQuantityValue(double waterQuantityValue) {
        waterQuantityValue_ = waterQuantityValue;
    }

    /**
     * Gets the quantity value for water
     *
     * @return double, value of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getWaterQuantityValue() const {
        return waterQuantityValue_;
    }

    /**
     * Sets the pressure of the steam
     *
     * @param steamPressure double, pressure of steam in MPa
     *
     * @return nothing
     */
    void setSteamPressure(double steamPressure) {
        steamPressure_ = steamPressure;
    }

    /**
     * Gets the steam pressure
     *
     * @return double, pressure of the steam in MPa
     */
    double getSteamPressure() const {
        return steamPressure_;
    }

    /**
     * Sets the quantity type for steam
     *
     * @param steamQuantityType SteamProperties::ThermodynamicQuantity, type of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setSteamQuantityType(SteamProperties::ThermodynamicQuantity steamQuantityType) {
        steamQuantityType_ = steamQuantityType;
    }

    /**
     * Gets the quantity type for steam
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getSteamQuantityType() const {
        return steamQuantityType_;
    }

    /**
     * Sets the quantity value for steam
     *
     * @param steamQuantityValue double, value of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     * @return nothing
     */
    void setSteamQuantityValue(double steamQuantityValue) {
        steamQuantityValue_ = steamQuantityValue;
    }

    /**
     * Gets the quantity value for steam
     *
     * @return double, value of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getSteamQuantityValue() const {
        return steamQuantityValue_;
    }

    /**
     * Calculates all of the properties of the feedwater
     * @return std::unordered_map <std::string, double>, feedwater properties
     */
    std::unordered_map <std::string, double> getFeedwaterProperties();

    /**
     * Calculates all of the properties of the vented steam
     * @return std::unordered_map <std::string, double>, vented steam properties
     */
    std::unordered_map <std::string, double> getVentedSteamProperties();

    /**
     * Calculates all of the properties of the inlet water
     * @return std::unordered_map <std::string, double>, inlet water properties
     */
    std::unordered_map <std::string, double> getInletWaterProperties();

    /**
     * Calculates all of the properties of the inlet steam
     * @return std::unordered_map <std::string, double>, inlet steam properties
     */
    std::unordered_map <std::string, double> getInletSteamProperties();

    /**
     * Calculates the feedwater energy flow
     * @return double, feedwater energy flow in MJ/hr
     */
    double getFeedwaterEnergyFlow();

    /**
     * Calculates the vented steam mass flow
     * @return double, vented steam mass flow in kg/hr
     */
    double getVentedSteamMassFlow();

    /**
     * Calculates the total deaerator mass flow
     * @return double, total deaerator mass flow in kg/hr
     */
    double getTotalDAMassFlow();

    /**
     * Calculates the total outlet energy flow
     * @return double, total outlet energy flow in MJ/hr
     */
    double getTotalOutletEnergyFlow();

    /**
     * Calculates the minimum inlet energy flow
     * @return double, minimum inlet energy flow in MJ/hr
     */
    double getMinEnergyFlow();

    /**
     * Calculates the additional energy flow needed
     * @return double, additional energy flow needed in MJ/hr
     */
    double getNeededEnergyFlow();

    /**
     * Calculates the vented steam energy flow
     * @return double, vented steam energy flow in MJ/hr
     */
    double getVentedSteamEnergyFlow();

    /**
     * Calculates the inlet water mass flow
     * @return double, inlet water mass flow in kg/hr
     */
    double getInletWaterMassFlow();

    /**
     * Calculates the inlet water energy flow
     * @return double, inlet water energy flow in MJ/hr
     */
    double getInletWaterEnergyFlow();

    /**
     * Calculates the inlet steam mass flow
     * @return double, inlet steam mass flow in kg/hr
     */
    double getInletSteamMassFlow();

    /**
     * Calculates the inlet steam energy flow
     * @return double, inlet steam energy flow in MJ/hr
     */
    double getInletSteamEnergyFlow();

private:
    // In values
    double deaeratorPressure_ = 0.0;
    double ventRate_ = 0.0;
    double feedwaterMassFlow_ = 0.0;
    double waterPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity waterQuantityType_;
    double waterQuantityValue_ = 0.0;
    double steamPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity steamQuantityType_;
    double steamQuantityValue_ = 0.0;

    // In-Out values
    double totalDAMassFlow_;
    double totalOutletEnergyFlow_;
    double minEnergyFlow_;
    double neededEnergyFlow_;


    // Out values
    std::unordered_map <std::string, double> feedwaterProperties_;
    std::unordered_map <std::string, double> ventedSteamProperties_;
    std::unordered_map <std::string, double> inletWaterProperties_;
    std::unordered_map <std::string, double> inletSteamProperties_;
    double feedwaterEnergyFlow_;
    double ventedSteamMassFlow_;
    double ventedSteamEnergyFlow_;
    double inletWaterMassFlow_;
    double inletWaterEnergyFlow_;
    double inletSteamMassFlow_;
    double inletSteamEnergyFlow_;
};







#endif //AMO_TOOLS_SUITE_DEAERATOR_H
