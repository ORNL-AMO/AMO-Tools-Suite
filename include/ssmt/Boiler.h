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
           SteamProperties::ThermodynamicQuantity quantityType, double quantityValue, double steamMassFlow)
            : deaeratorPressure_(deaeratorPressure), combustionEfficiency_(combustionEfficiency),
              blowdownRate_(blowdownRate), steamPressure_(steamPressure), quantityType_(quantityType),
              quantityValue_(quantityValue), steamMassFlow_(steamMassFlow)
    {
        steamProperties_ = SteamProperties(steamPressure_, quantityType_, quantityValue_).calculate();
        steamProperties_["steamEnergyFlow"] = steamProperties_["specificEnthalpy"] * steamMassFlow_ / 1000;
        steamProperties_["steamMassFlow"] = steamMassFlow_;
        feedwaterProperties_ = SteamProperties(deaeratorPressure_, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
	    feedwaterProperties_["feedwaterMassFlow"] = steamMassFlow_ / (1 - blowdownRate / 100);
        feedwaterProperties_["feedwaterEnergyFlow"] = feedwaterProperties_["specificEnthalpy"] * feedwaterProperties_["feedwaterMassFlow"] / 1000;

        blowdownProperties_ = SteamProperties(steamPressure_, SteamProperties::ThermodynamicQuantity::QUALITY, 0).calculate();
        blowdownProperties_["blowdownMassFlow"] = feedwaterProperties_["feedwaterMassFlow"] * (blowdownRate_ / 100);
        blowdownProperties_["blowdownEnergyFlow"] = blowdownProperties_["specificEnthalpy"] * blowdownProperties_["blowdownMassFlow"] / 1000;

        boilerEnergy_ = steamProperties_["steamEnergyFlow"] + blowdownProperties_["blowdownEnergyFlow"] - feedwaterProperties_["feedwaterEnergyFlow"];
        fuelEnergy_ = boilerEnergy_ / (combustionEfficiency_ / 100);
    }

    /**
     * Calculates all of the properties of the steam
     * @return std::unordered_map <std::string, double>, steam properties
     */
    std::unordered_map <std::string, double> getSteamProperties() const;

    /**
     * Calculates all of the steam properties of the blowdown
     * @return std::unordered_map <std::string, double>, steam properties of blowdown
     */
    std::unordered_map <std::string, double> getBlowdownProperties() const;

    /**
     * Calculates all of the steam properties of the feedwater
     * @return std::unordered_map <std::string, double>, steam properties of feedwater
     */
    std::unordered_map <std::string, double> getFeedwaterProperties();

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


private:
    const double deaeratorPressure_, combustionEfficiency_, blowdownRate_, steamPressure_;
    const SteamProperties::ThermodynamicQuantity quantityType_;
    const double quantityValue_, steamMassFlow_;

    std::unordered_map <std::string, double> steamProperties_;
    std::unordered_map <std::string, double> blowdownProperties_;
    std::unordered_map <std::string, double> feedwaterProperties_;
    double boilerEnergy_, fuelEnergy_;
};


#endif //AMO_TOOLS_SUITE_BOILER_H
