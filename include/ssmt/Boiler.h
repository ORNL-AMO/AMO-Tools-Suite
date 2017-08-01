/**
 * @file
 * @brief Calculator for boiler
 *
 * This contains the inputs for boiler related calculations.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"

#ifndef AMO_TOOLS_SUITE_BOILER_H
#define AMO_TOOLS_SUITE_BOILER_H

/**
 * Boiler calculator class
 * Used to determines the amount of fuel energy required to produce steam with
 *  specified properties at a given flow rate using general boiler operational characteristics
 */
class Boiler {
public:
    /**
     *
     * Constructor for the boiler calculator
     *
     * @param deaeratorPressure double, pressure of deaerator in MPa
     * @param combustionEfficiency double, combustion efficiency of the boiler as %
     * @param blowdownRate double, blowdown rate as a % of inlet mass flow
     * @param steamPressure double, pressure of steam in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param steamMassFlow double, steam mass flow in kg/hr
     *
     * @return nothing
     *
     * */
    Boiler(
            double deaeratorPressure,
            double combustionEfficiency,
            double blowdownRate,
            double steamPressure,
            SteamProperties::ThermodynamicQuantity quantityType,
            double quantityValue,
            double steamMassFlow)
            : deaeratorPressure_(deaeratorPressure),
              combustionEfficiency_(combustionEfficiency),
              blowdownRate_(blowdownRate),
              steamPressure_(steamPressure),
              quantityType_(quantityType),
              quantityValue_(quantityValue),
              steamMassFlow_(steamMassFlow)

    {
        steamProperties_;
        blowdownProperties_;
        feedwaterProperties_ ;
        steamEnergyFlow_ = 0.0;
        boilerEnergy_ = 0.0;
        fuelEnergy_ = 0.0;
        blowdownMassFlow_ = 0.0;
        blowdownEnergyFlow_ = 0.0;
        feedwaterMassFlow_ = 0.0;
        feedwaterEnergyFlow_ = 0.0;

    }

    Boiler() = default;

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
     * Sets the combustion efficiency of the boiler
     *
     * @param combustionEfficiency double, combustion efficiency as %
     *
     * @return nothing
     */
    void setCombustionEfficiency(double combustionEfficiency) {
        combustionEfficiency_ = combustionEfficiency;
    }

    /**
     * Gets the combustion efficiency of the boiler
     *
     * @return double, combustion efficiency as %
     */
    double getCombustionEfficiency() const {
        return combustionEfficiency_;
    }

    /**
     * Sets the blowdown rate
     *
     * @param blowdownRate double, blowdown rate as a % of inlet mass flow
     *
     * @return nothing
     */
    void setBlowdownRate(double blowdownRate) {
        blowdownRate_ = blowdownRate;
    }

    /**
     * Gets the blowdown rate
     *
     * @return double, blowdown rate as a % of inlet mass flow
     */
    double getBlowdownRate() const {
        return blowdownRate_;
    }

    /**
     * Sets the steam pressure
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
     * @return double, pressure of steam in MPa
     */
    double getSteamPressure() const {
        return steamPressure_;
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
     * Sets the steam mass flow
     *
     * @param steamMassFlow double, mass flow of steam in kg/hr
     *
     * @return nothing
     */
    void setSteamMassFlow(double steamMassFlow) {
        steamMassFlow_ = steamMassFlow;
    }

    /**
     * Gets the steam mass flow
     *
     * @return double, mass flow of steam in kg/hr
     */
    double getSteamMassFlow() const {
        return steamMassFlow_;
    }

    /**
     * Calculates all of the properties of the steam
     * @return std::unordered_map <std::string, double>, steam properties
     */
    std::unordered_map <std::string, double> getSteamProperties();

    /**
     * Calculates all of the steam properties of the blowdown
     * @return std::unordered_map <std::string, double>, steam properties of blowdown
     */
    std::unordered_map <std::string, double> getBlowdownProperties();

    /**
     * Calculates all of the steam properties of the feedwater
     * @return std::unordered_map <std::string, double>, steam properties of feedwater
     */
    std::unordered_map <std::string, double> getFeedwaterProperties();

    /**
     * Calculates the steam energy flow
     * @return double, steam energy flow MJ/hr
     */
    double getSteamEnergyFlow();

    /**
     * Calculates the boiler energy
     * @return double, boiler energy in MJ
     */
    double getBoilerEnergy();

    /**
     * Calculates the fuel energy
     * @return double, fuel energy in MJ
     */
    double getFuelEnergy();

    /**
     * Calculates the blowdown mass flow
     * @return double, blowdown mass flow in kg/hr
     */
    double getBlowdownMassFlow();

    /**
     * Calculates the blowdown energy flow
     * @return double, blowdown energy flow in MJ/hr
     */
    double getBlowdownEnergyFlow();

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
    double deaeratorPressure_ = 0.0;
    double combustionEfficiency_ = 0.0;
    double blowdownRate_ = 0.0;
    double steamPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity quantityType_;
    double quantityValue_ = 0.0;
    double steamMassFlow_ = 0.0;


    // Out values
    std::unordered_map <std::string, double> steamProperties_;
    std::unordered_map <std::string, double> blowdownProperties_;
    std::unordered_map <std::string, double> feedwaterProperties_;
    double steamEnergyFlow_;
    double boilerEnergy_;
    double fuelEnergy_;
    double blowdownMassFlow_;
    double blowdownEnergyFlow_;
    double feedwaterMassFlow_;
    double feedwaterEnergyFlow_;
};


#endif //AMO_TOOLS_SUITE_BOILER_H
