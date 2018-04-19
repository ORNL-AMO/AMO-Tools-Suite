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
#include "SteamSystemModelerTool.h"

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
     * */
    Boiler(double deaeratorPressure, double combustionEfficiency, double blowdownRate, double steamPressure,
           SteamProperties::ThermodynamicQuantity quantityType, double quantityValue, double steamMassFlow);

    SteamSystemModelerTool::FluidProperties const & getSteamProperties() const { return steamProperties; }

    SteamSystemModelerTool::FluidProperties const & getBlowdownProperties() const { return blowdownProperties; }

    SteamSystemModelerTool::FluidProperties const & getFeedwaterProperties() const { return feedwaterProperties; }

    /**
	 * Gets the deaerator pressure
	 * @return double, pressure of the deaerator in MPa
	 */
    double getDeaeratorPressure() const;

    /**
     * Gets the combustion efficiency of the boiler
     * @return double, combustion efficiency as %
     */
    double getCombustionEfficiency() const;

    /**
	* Gets the blowdown rate
	* @return double, blowdown rate as a % of inlet mass flow
	*/
    double getBlowdownRate() const;

    /**
     * Gets the steam pressure
     * @return double, pressure of steam in MPa
     */
    double getSteamPressure() const;

    /**
	 * Gets the quantity value
	 * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
    double getQuantityValue() const;

    /**
	 * Gets the steam mass flow
	 * @return double, mass flow of steam in kg/hr
	 */
    double getSteamMassFlow() const;

    /**
	 * Gets the quantity type
	 * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
    SteamProperties::ThermodynamicQuantity getQuantityType() const;

    /**
    * Sets the deaerator pressure
    * @param deaeratorPressure double, pressure of the deaerator in MPa
    */
    void setDeaeratorPressure(double deaeratorPressure);

    /**
    * Sets the combustion efficiency of the boiler
    * @param combustionEfficiency double, combustion efficiency as %
    */
    void setCombustionEfficiency(double combustionEfficiency);

    /**
	 * Sets the blowdown rate
	 * @param blowdownRate double, blowdown rate as a % of inlet mass flow
	 */
    void setBlowdownRate(double blowdownRate);

    /**
	 * Sets the steam pressure
	 * @param steamPressure double, pressure of steam in MPa
	 */
    void setSteamPressure(double steamPressure);

    /**
	 * Sets the quantity value
	 * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
    void setQuantityValue(double quantityValue);

    /**
     * Sets the steam mass flow
     * @param steamMassFlow double, mass flow of steam in kg/hr
     */
    void setSteamMassFlow(double steamMassFlow);

    /**
    * Sets the quantity type
    * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
    */
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

    SteamSystemModelerTool::FluidProperties steamProperties, blowdownProperties, feedwaterProperties;
    double boilerEnergy, fuelEnergy;
};


#endif //AMO_TOOLS_SUITE_BOILER_H
