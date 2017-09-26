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
    Boiler(double deaeratorPressure, double combustionEfficiency, double blowdownRate, double steamPressure,
           SteamProperties::ThermodynamicQuantity quantityType, double quantityValue, double steamMassFlow);

    std::unordered_map <std::string, double> const & getSteamProperties() const { return steamProperties; }

    std::unordered_map <std::string, double> const & getBlowdownProperties() const { return blowdownProperties; }

    std::unordered_map <std::string, double> const & getFeedwaterProperties() const { return feedwaterProperties; }

    double getDeaeratorPressure() const;
    double getCombustionEfficiency() const;
    double getBlowdownRate() const;
    double getSteamPressure() const;
    double getQuantityValue() const;
    double getSteamMassFlow() const;
    SteamProperties::ThermodynamicQuantity getQuantityType() const;

    void setDeaeratorPressure(double deaeratorPressure);
    void setCombustionEfficiency(double combustionEfficiency);
    void setBlowdownRate(double blowdownRate);
    void setSteamPressure(double steamPressure);
    void setQuantityValue(double quantityValue);
    void setSteamMassFlow(double steamMassFlow);
    void setQuantityType(SteamProperties::ThermodynamicQuantity quantity);

    /**
     * Returns the boiler energy
     * @return double, boiler energy in MJ
     */
    double getBoilerEnergy() const { return boilerEnergy; };

    /**
     * Returns the fuel energy
     * @return double, fuel energy in MJ
     */
    double getFuelEnergy() const { return fuelEnergy; };


private:
    void calculateProperties();

    double deaeratorPressure, combustionEfficiency, blowdownRate, steamPressure;
    SteamProperties::ThermodynamicQuantity quantityType;
    double quantityValue, steamMassFlow;

    std::unordered_map <std::string, double> steamProperties;
    std::unordered_map <std::string, double> blowdownProperties;
    std::unordered_map <std::string, double> feedwaterProperties;
    double boilerEnergy, fuelEnergy;
};


#endif //AMO_TOOLS_SUITE_BOILER_H
