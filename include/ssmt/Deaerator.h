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

     *
     * */
    Deaerator(double deaeratorPressure, double ventRate, double feedwaterMassFlow,
              double waterPressure, SteamProperties::ThermodynamicQuantity waterQuantityType,
              double waterQuantityValue, double steamPressure,
              SteamProperties::ThermodynamicQuantity steamQuantityType, double steamQuantityValue);

	/**
     * Gets all of the feedwater properties
     * @return SteamSystemModelerTool::FluidProperties feedwater properties
     */
	SteamSystemModelerTool::FluidProperties const & getFeedwaterProperties() const { return feedwaterProperties; }

	/**
     * Gets all of the vented steam properties
     * @return SteamSystemModelerTool::FluidProperties, vented steam properties
     */
	SteamSystemModelerTool::FluidProperties const & getVentedSteamProperties() const { return ventedSteamProperties; }

	/**
     * Gets all of the inlet water properties
     * @return SteamSystemModelerTool::FluidProperties, inlet water properties
     */
	SteamSystemModelerTool::FluidProperties const & getInletWaterProperties() const { return inletWaterProperties; }

	/**
     * Gets all of the inlet steam properties
     * @return SteamSystemModelerTool::FluidProperties, inlet steam properties
     */
	SteamSystemModelerTool::FluidProperties const & getInletSteamProperties() const { return inletSteamProperties; }

	/**
     * Gets the deaerator pressure
     * @return double, pressure of the deaerator in MPa
     */
	double getDeaeratorPressure() const;

	/**
     * Gets the vent rate
     * @return double, vent rate as %
     */
	double getVentRate() const;

	/**
     * Gets the feedwater mass flow
     * @return double, feedwater mass flow in kg/hr
     */
	double getFeedwaterMassFlow() const;

	/**
     * Gets the water pressure
     * @return double, pressure of the water in MPa
     */
	double getWaterPressure() const;

	/**
     * Gets the quantity type for water
     * @return SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	double getWaterQuantityValue() const;

	/**
     * Gets the steam pressure
     * @return double, pressure of the steam in MPa
     */
	double getSteamPressure() const;

	/**
     * Gets the quantity value for steam
     * @return double, value of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	double getSteamQuantityValue() const;

	/**
     * Gets the quantity type for water
     * @return SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	SteamProperties::ThermodynamicQuantity getWaterQuantityType() const;

	/**
     * Gets the quantity type for steam
     * @return SteamProperties::ThermodynamicQuantity, type of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	SteamProperties::ThermodynamicQuantity getSteamQuantityType() const;

	/**
     * Sets the deaerator pressure
     * @param deaeratorPressure double, pressure of the deaerator in MPa
     */
	void setDeaeratorPressure(double deaeratorPressure);

	/**
     * Sets the vent rate
     * @param ventRate double, vent rate as %
     */
	void setVentRate(double ventRate);

	/**
	* Sets the feedwater mass flow
	* @param feedwaterMassFlow double, feedwater mass flow in kg/hr
	*/
	void setFeedwaterMassFlow(double feedwaterMassFlow);

	/**
     * Sets the pressure of the water
     * @param waterPressure double, pressure of water in MPa
     */
	void setWaterPressure(double waterPressure);

	/**
     * Sets the quantity value for water
     * @param waterQuantityValue double, value of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setWaterQuantityValue(double waterQuantityValue);

	/**
     * Sets the pressure of the steam
     * @param steamPressure double, pressure of steam in MPa
     */
	void setSteamPressure(double steamPressure);

	/**
     * Sets the quantity value for steam
     * @param steamQuantityValue double, value of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setSteamQuantityValue(double steamQuantityValue);

	/**
     * Sets the quantity type for water
     * @param waterQuantityType SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setWaterQuantityType(SteamProperties::ThermodynamicQuantity quantity);

	/**
     * Sets the quantity type for steam
     * @param steamQuantityType SteamProperties::ThermodynamicQuantity, type of quantity for steam (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setSteamQuantityType(SteamProperties::ThermodynamicQuantity quantity);

private:

    void calculateProperties();


    double deaeratorPressure, ventRate, feedwaterMassFlow, waterPressure, waterQuantityValue;
    double steamPressure, steamQuantityValue;
    SteamProperties::ThermodynamicQuantity waterQuantityType, steamQuantityType;

	SteamSystemModelerTool::FluidProperties feedwaterProperties, ventedSteamProperties, inletWaterProperties;
	SteamSystemModelerTool::FluidProperties inletSteamProperties;
};

#endif //AMO_TOOLS_SUITE_DEAERATOR_H
