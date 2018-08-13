/**
 * @file
 * @brief Calculator for the flash tank for steam systems
 *
 * Calculates the mass flows and properties of any resulting outlet gas and/or liquid for given inlet conditions.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"
#include "SaturatedProperties.h"
#include "SteamSystemModelerTool.h"

#ifndef AMO_TOOLS_SUITE_FLASHTANK_H
#define AMO_TOOLS_SUITE_FLASHTANK_H

/**
 * Heat Loss calculator class
 * Used to calculate the heat energy loss and outlet steam properties
 */
class FlashTank {
public:
    /**
     * Constructor for the flash tank calculator
     *
     * @param inletWaterPressure double, inlet water pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletWaterMassFlow double, inlet water mass flow in kg/hr
     * @param tankPressure double, pressure of the tank in MPa
     *
     * */
    FlashTank(double inletWaterPressure, SteamProperties::ThermodynamicQuantity quantityType, double quantityValue,
              double inletWaterMassFlow, double tankPressure);


    /**
     * Gets all of the properties of the inlet water
     * @return SteamSystemModelerTool::FluidProperties, inlet water properties
     */
    SteamSystemModelerTool::FluidProperties const & getInletWaterProperties() const { return inletWaterProperties; };

    /**
     * Gets all of the saturated properties of the outlet gas and liquid
     * @return SteamSystemModelerTool::FluidProperties, outlet gas and liquid saturated properties
     */
    SteamSystemModelerTool::FluidProperties const & getOutletGasSaturatedProperties() const { return outletGasSaturatedProperties; }
	SteamSystemModelerTool::FluidProperties const & getOutletLiquidSaturatedProperties() const { return outletLiquidSaturatedProperties; }

	/**
     * Gets the inlet water pressure
     * @return double, pressure of the inlet water in MPa
     */
    double getInletWaterPressure() const;

	/**
     * Gets the quantity value
     * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getQuantityValue() const;

	/**
     * Gets the inlet water mass flow
     * @return double, mass flow of the inlet water in kg/hr
     */
    double getInletWaterMassFlow() const;

	/**
     * Gets the pressure of the tank
     * @return double, tank pressure in MPa
     */
    double getTankPressure() const;

	/**
     * Gets the quantity type
     * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	SteamProperties::ThermodynamicQuantity getQuantityType() const;

	/**
     * Sets the inlet water pressure
     * @param inletWaterPressure double, pressure of the inlet water in MPa
     */
	void setInletWaterPressure(double inletWaterPressure);

	/**
     * Sets the quantity value
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setQuantityValue(double quantityValue);

	/**
     * Sets the inlet water mass flow
     * @param inletWaterMassFlow double, mass flow of the inlet water in kg/hr
     */
	void setInletWaterMassFlow(double inletWaterMassFlow);

	/**
     * Sets the pressure of the tank
     * @param tankPressure double, tank pressure in MPa
     */
	void setTankPressure(double tankPressure);

	/**
     * Sets the quantity type
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
	void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType);

private:
    void calculateProperties();

    double inletWaterPressure, quantityValue, inletWaterMassFlow, tankPressure;
    SteamProperties::ThermodynamicQuantity quantityType;

    SteamSystemModelerTool::FluidProperties inletWaterProperties, outletLiquidSaturatedProperties, outletGasSaturatedProperties;
};



#endif //AMO_TOOLS_SUITE_FLASHTANK_H
