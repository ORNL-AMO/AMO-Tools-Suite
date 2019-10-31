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
#include "SteamSystemModelerTool.h"

#ifndef AMO_TOOLS_SUITE_HEATLOSS_H
#define AMO_TOOLS_SUITE_HEATLOSS_H

/**
 * Heat Loss calculator class
 * Used to calculate the heat energy loss and outlet steam properties
 */
class HeatLoss {
public:
    /**
     * Constructor for the heat loss calculator
     *
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletMassFlow double, inlet mass flow in kg/hr
     * @param percentHeatLoss double, heat loss as %
     *
     * */
    HeatLoss(double inletPressure, SteamProperties::ThermodynamicQuantity quantityType, double quantityValue,
             double inletMassFlow, double percentHeatLoss);

    /**
     * Gets all of the inlet properties
     * @return SteamSystemModelerTool::FluidProperties, inlet properties
     */
    SteamSystemModelerTool::FluidProperties const & getInletProperties() const { return inletProperties; };

    /**
     * Gets all of the outlet steam properties
     * @return SteamSystemModelerTool::FluidProperties, outlet steam properties
     */
    SteamSystemModelerTool::FluidProperties const & getOutletProperties() const { return outletProperties; };

    /**
     * Gets the heat loss
     * @return double, heat loss in MJ/hr
     */
    double getHeatLoss() const { return heatLoss; }

    /**
     * Gets the inlet pressure
     * @return double, pressure of the inlet steam in MPa
     */
    double getInletPressure() const { return inletPressure; };

    /**
	 * Gets the quantity value
	 * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
    double getQuantityValue() const { return quantityValue; };

    /**
     * Gets the inlet mass flow
     * @return double, mass flow of the inlet steam in kg/hr
     */
    double getInletMassFlow() const { return inletMassFlow; };

    /**
     * Gets the percent heat loss
     * @return double, heat loss as %
     */
    double getPercentHeatLoss() const { return percentHeatLoss; };

    /**
	 * Gets the quantity type
	 * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
    SteamProperties::ThermodynamicQuantity getQuantityType() const { return quantityType; };

    /**
	 * Sets the inlet pressure
	 * @param inletPressure double, pressure of the inlet steam in MPa
	 */
    void setInletPressure(double inletPressure);

    /**
     * Sets the quantity value
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    void setQuantityValue(double quantityValue);

    /**
	 * Sets the inlet mass flow
	 * @param inletMassFlow double, mass flow of the inlet steam in kg/hr
	 */
    void setInletMassFlow(double inletMassFlow);

    /**
     * Sets the percent heat loss
     * @param percentHeatLoss double, heat loss as %
     */
    void setPercentHeatLoss(double percentHeatLoss);

    /**
     * Sets the quantity type
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType);

private:
    void calculateProperties();

    double inletPressure, quantityValue, inletMassFlow, percentHeatLoss;
    SteamSystemModelerTool::FluidProperties inletProperties;
    double inletEnergyFlow, outletEnergyFlow;
    SteamSystemModelerTool::FluidProperties outletProperties;

    double heatLoss;
    SteamProperties::ThermodynamicQuantity quantityType;
};

#endif //AMO_TOOLS_SUITE_HEATLOSS_H
