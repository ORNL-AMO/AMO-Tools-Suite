/**
 * @file
 * @brief Calculator for the steam properties after after a pressure drop for steam systems
 *
 * Calculates the properties of steam after a pressure drop with optional desuperheating.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "SteamProperties.h"

#ifndef AMO_TOOLS_SUITE_PRV_H
#define AMO_TOOLS_SUITE_PRV_H

/**
* PRV without Desuperheating calculator class
* Used to calculate the heat steam properties
*/
class PrvWithoutDesuperheating {
public:
    /**
     * Constructor for the PRV without desuperheating calculator
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletMassFlow double, inlet mass flow in kg/hr
     * @param outletPressure double, outlet pressure in MPa
     */
    PrvWithoutDesuperheating(double inletPressure, SteamProperties::ThermodynamicQuantity quantityType,
                             double quantityValue, double inletMassFlow, double outletPressure);

    /**
     * Gets the inlet pressure
     *
     * @return double, pressure of the inlet steam in MPa
     */
    double getInletPressure() const {
        return inletPressure;
    }

    /**
     * Gets the quantity type
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getQuantityType() const {
        return quantityType;
    }

    /**
     * Gets the quantity value
     *
     * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getQuantityValue() const {
        return quantityValue;
    }

    /**
     * Gets the inlet mass flow
     *
     * @return double, mass flow of the inlet steam in kg/hr
     */
    double getInletMassFlow() const {
        return inletMassFlow;
    }

    /**
     * Gets the outlet pressure
     *
     * @return double, outlet pressure in MPa
     */
    double getOutletPressure() const {
        return outletPressure;
    }

    /**
     * Gets all of the properties of the inlet steam
     * @return SteamSystemModelerTool::SteamPropertiesOutput , inlet steam properties
     */
    SteamSystemModelerTool::SteamPropertiesOutput const & getInletProperties() const { return inletProperties; };

    /**
     * Gets all of the properties of the outlet steam
     * @return SteamSystemModelerTool::SteamPropertiesOutput , outlet steam properties
     */
    SteamSystemModelerTool::SteamPropertiesOutput const & getOutletProperties() const { return outletProperties; };

    /**
     * Gets the inlet energy flow
     * @return double, inlet steam energy flow in MJ/hr
     */
    double getInletEnergyFlow() const { return inletEnergyFlow; }

    /**
     * Gets the outlet mass flow;
     * note: without desuperheating, it is the same as inletMassFlow because outlet == inlet.
     * @return double, outlet mass flow in kg/hr
     */
    virtual double getOutletMassFlow() const { return inletMassFlow; }

    /**
     * Gets the outlet energy flow;
     * note: without desuperheating, it is the same as inletEnergyFlow because outlet == inlet.
     * @return double, outlet energy flow in MJ/hr
     */
    virtual double getOutletEnergyFlow() const { return inletEnergyFlow; }

    /**
     * Sets the inlet pressure
     *
     * @param inletPressure double, pressure of the inlet steam in MPa
     *
     */
    void setInletPressure(double inletPressure) {
        this->inletPressure = inletPressure;
        calculateProperties();
    }

    /**
     * Sets the quantity type
     *
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     */
    void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType) {
        this->quantityType = quantityType;
        calculateProperties();
    }
    /**
     * Sets the quantity value
     *
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     */
    void setQuantityValue(double quantityValue) {
        this->quantityValue = quantityValue;
        calculateProperties();
    }

    /**
     * Sets the inlet mass flow
     *
     * @param inletMassFlow double, mass flow of the inlet steam in kg/hr
     *
     */
    void setInletMassFlow(double inletMassFlow) {
        this->inletMassFlow = inletMassFlow;
        calculateProperties();
    }

    /**
     * Sets the outlet pressure
     *
     * @param outletPressure double, outlet pressure in MPa
     *
     */
    void setOutletPressure(double outletPressure) {
        this->outletPressure = outletPressure;
        calculateProperties();
    }

protected:
    virtual void calculateProperties();

    double inletPressure, quantityValue, inletMassFlow, outletPressure;
    SteamSystemModelerTool::SteamPropertiesOutput inletProperties, outletProperties;
    SteamProperties::ThermodynamicQuantity quantityType;

private:
    double inletEnergyFlow;
};



/**
* PRV with Desuperheating calculator class
* Used to calculate the heat steam properties
*/
class PrvWithDesuperheating : public PrvWithoutDesuperheating {
public:
    /**
     * Constructor for the PRV with desuperheating calculator
     *
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletMassFlow double, inlet mass flow in kg/hr
     * @param outletPressure double, outlet pressure in MPa
     * @param feedwaterPressure double, pressure of feedwater in MPa
     * @param feedwaterQuantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param feedwaterQuantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param desuperheatingTemp double, desuperheating temperature in K
     */
    PrvWithDesuperheating(double inletPressure, SteamProperties::ThermodynamicQuantity quantityType,
                          double quantityValue, double inletMassFlow, double outletPressure, double feedwaterPressure,
                          SteamProperties::ThermodynamicQuantity feedwaterQuantityType, double feedwaterQuantityValue,
                          double desuperheatingTemp);

    /**
     * Sets the feedwater pressure
     *
     * @param feedwaterPressure double, feedwater pressure in MPa
     *
     */
    void setFeedwaterPressure(double feedwaterPressure) {
        this->feedwaterPressure = feedwaterPressure;
		calculateProperties();
    }

    /**
     * Gets the feedwater pressure
     *
     * @return double, feedwater pressure in MPa
     */
    double getFeedwaterPressure() const { return feedwaterPressure; }

    /**
     * Sets the feedwater quantity type
     *
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     */
    void setFeedwaterQuantityType(SteamProperties::ThermodynamicQuantity feedwaterQuantityType) {
        this->feedwaterQuantityType = feedwaterQuantityType;
		calculateProperties();
    }

    /**
     * Gets the feedwater quantity type
     *
     * @return SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    SteamProperties::ThermodynamicQuantity getFeedwaterQuantityType() const { return feedwaterQuantityType; }

    /**
     * Sets the feedwater quantity value
     *
     * @param quantityValue double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     *
     */
    void setFeedwaterQuantityValue(double feedwaterQuantityValue) {
        this->feedwaterQuantityValue = feedwaterQuantityValue;
		calculateProperties();
    }

    /**
     * Gets the feedwater quantity value
     *
     * @return double, value of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     */
    double getFeedwaterQuantityValue() const { return feedwaterQuantityValue; }

    /**
     * Sets the desuperheating temperature
     *
     * @param desuperheatingTemp double, desuperheating temperature in K
     *
     */
    void setDesuperheatingTemp(double desuperheatingTemp) {
        this->desuperheatingTemp = desuperheatingTemp;
		calculateProperties();
    }

    /**
     * Gets the desuperheating temperature
     *
     * @return double, desuperheating temperature in K
     */
    double getDesuperheatingTemp() const { return desuperheatingTemp; }

    /**
     * Gets all of the properties of the feedwater steam
     * @return SteamSystemModelerTool::SteamPropertiesOutput, feedwater steam properties
     */
    SteamSystemModelerTool::SteamPropertiesOutput const & getFeedwaterProperties() const { return feedwaterProperties; };


    /**
     * Gets the outlet mass flow
     * @return double, outlet mass flow in kg/hr
     */
    double getOutletMassFlow() const { return outletMassFlow; };

    /**
     * Gets the outlet energy flow
     * @return double, outlet energy flow in MJ/hr
     */
    double getOutletEnergyFlow() const { return outletEnergyFlow; };

    /**
     * Gets the feedwater mass flow
     * @return double, feedwater mass flow in kg/hr
     */
    double getFeedwaterMassFlow() const { return feedwaterMassFlow; };

    /**
     * Gets the feedwater energy flow
     * @return double, feedwater energy flow in MJ/hr
     */
    double getFeedwaterEnergyFlow() const { return feedwaterEnergyFlow; };

protected:
    void calculateProperties() override;

private:
    // In values
    double feedwaterPressure, feedwaterQuantityValue, desuperheatingTemp;
    SteamProperties::ThermodynamicQuantity feedwaterQuantityType;

    // Out values
    SteamSystemModelerTool::SteamPropertiesOutput feedwaterProperties;
    double inletEnergyFlow, outletMassFlow, outletEnergyFlow, feedwaterMassFlow, feedwaterEnergyFlow;
};

#endif //AMO_TOOLS_SUITE_PRV_H
