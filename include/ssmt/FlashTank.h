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
    FlashTank(double inletWaterPressure, SteamProperties::ThermodynamicQuantity quantityType, double quantityValue,
              double inletWaterMassFlow, double tankPressure);


    /**
     * Calculates all of the properties of the inlet water
     * @return std::unordered_map <std::string, double>, inlet water properties
     */
    std::unordered_map <std::string, double> const & getInletWaterProperties() const { return inletWaterProperties; };

    /**
     * Calculates all of the saturated properties of the outlet gas and liquid
     * @return std::unordered_map <std::string, double>, outlet gas and liquid saturated properties
     */
    std::unordered_map <std::string, double> const & getOutletSaturatedProperties() const { return outletSaturatedProperties; }

    double getInletWaterPressure() const;
    double getQuantityValue() const;
    double getInletWaterMassFlow() const;
    double getTankPressure() const;
	SteamProperties::ThermodynamicQuantity getQuantityType() const;

	void setInletWaterPressure(double inletWaterPressure);
	void setQuantityValue(double quantityValue);
	void setInletWaterMassFlow(double inletWaterMassFlow);
	void setTankPressure(double tankPressure);
	void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType);

private:
    void calculateProperties();

    double inletWaterPressure, quantityValue, inletWaterMassFlow, tankPressure;
    SteamProperties::ThermodynamicQuantity quantityType;

    std::unordered_map <std::string, double> inletWaterProperties, outletSaturatedProperties;
};



#endif //AMO_TOOLS_SUITE_FLASHTANK_H
