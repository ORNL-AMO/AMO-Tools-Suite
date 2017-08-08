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

#ifndef AMO_TOOLS_SUITE_FLASHTANK_H
#define AMO_TOOLS_SUITE_FLASHTANK_H

/**
 * Heat Loss calculator class
 * Used to calculate the heat energy loss and outlet steam properties
 */
class FlashTank {
public:
    /**
     *
     * Constructor for the flash tank calculator
     *
     * @param inletWaterPressure double, inlet water pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletWaterMassFlow double, inlet water mass flow in kg/hr
     * @param tankPressure double, pressure of the tank in MPa
     *
     * @return nothing
     *
     * */
    FlashTank(
            double inletWaterPressure,
            SteamProperties::ThermodynamicQuantity quantityType,
            double quantityValue,
            double inletWaterMassFlow,
            double tankPressure)
            : inletWaterPressure_(inletWaterPressure),
              quantityType_(quantityType),
              quantityValue_(quantityValue),
              inletWaterMassFlow_(inletWaterMassFlow),
              tankPressure_(tankPressure)

    {
        inletWaterEnergyFlow_ = 0.0;
        outletGasMassFlow_ = 0.0;
        outletGasEnergyFlow_ = 0.0;
        outletLiquidMassFlow_ = 0.0;
        outletLiquidEnergyFlow_ = 0.0;

    }

    FlashTank() = default;

    /**
     * Sets the inlet water pressure
     *
     * @param inletWaterPressure double, pressure of the inlet water in MPa
     *
     * @return nothing
     */
    void setInletWaterPressure(double inletWaterPressure) {
        inletWaterPressure_ = inletWaterPressure;
    }

    /**
     * Gets the inlet water pressure
     *
     * @return double, pressure of the inlet water in MPa
     */
    double getInletWaterPressure() const {
        return inletWaterPressure_;
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
     * Sets the inlet water mass flow
     *
     * @param inletWaterMassFlow double, mass flow of the inlet water in kg/hr
     *
     * @return nothing
     */
    void setInletWaterMassFlow(double inletWaterMassFlow) {
        inletWaterMassFlow_ = inletWaterMassFlow;
    }

    /**
     * Gets the inlet water mass flow
     *
     * @return double, mass flow of the inlet water in kg/hr
     */
    double getInletWaterMassFlow() const {
        return inletWaterMassFlow_;
    }

    /**
     * Sets the pressure of the tank
     *
     * @param tankPressure double, tank pressure in MPa
     *
     * @return nothing
     */
    void setTankPressure(double tankPressure) {
        tankPressure_ = tankPressure;
    }

    /**
     * Gets the pressure of the tank
     *
     * @return double, tank pressure in MPa
     */
    double getTankPressure() const {
        return tankPressure_;
    }

    /**
     * Calculates all of the properties of the inlet water
     * @return std::unordered_map <std::string, double>, inlet water properties
     */
    std::unordered_map <std::string, double> getInletWaterProperties();

    /**
     * Calculates all of the saturated properties of the outlet gas and liquid
     * @return std::unordered_map <std::string, double>, outlet gas and liquid saturated properties
     */
    std::unordered_map <std::string, double> getOutletSaturatedProperties();

    /**
     * Calculates the inlet water energy flow
     * @return double, inlet water energy flow in MJ/hr
     */
    double getInletWaterEnergyFlow();

    /**
     * Calculates the outlet gas mass flow
     * @return double, outlet gas mass flow in kg/hr
     */
    double getOutletGasMassFlow();

    /**
     * Calculates the outlet gas energy flow
     * @return double, outlet gas energy flow in MJ/hr
     */
    double getOutletGasEnergyFlow();

    /**
     * Calculates the outlet liquid mass flow
     * @return double, outlet liquid mass flow in kg/hr
     */
    double getOutletLiquidMassFlow();

    /**
     * Calculates the outlet liquid energy flow
     * @return double, outlet liquid energy flow in MJ/hr
     */
    double getOutletLiquidEnergyFlow();

private:
    // In values
    double inletWaterPressure_ = 0.0;
    SteamProperties::ThermodynamicQuantity quantityType_;
    double quantityValue_ = 0.0;
    double inletWaterMassFlow_ = 0.0;
    double tankPressure_ = 0.0;


    // Out values
    std::unordered_map <std::string, double> inletWaterProperties_;
    std::unordered_map <std::string, double> outletSaturatedProperties_;
    double inletWaterEnergyFlow_;
    double outletGasMassFlow_;
    double outletGasEnergyFlow_;
    double outletLiquidMassFlow_;
    double outletLiquidEnergyFlow_;
};



#endif //AMO_TOOLS_SUITE_FLASHTANK_H
