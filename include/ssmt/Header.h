#ifndef AMO_TOOLS_SUITE_HEADER_H
#define AMO_TOOLS_SUITE_HEADER_H

#include <string>
#include <vector>
#include "SteamProperties.h"

class Inlet {
public:
	/**
 	* Constructor for the Inlet class, to be used in combination with the Header class, shares the same units as Header
 	*
 	* @param pressure double, inlet pressure in MPa
	* @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
    * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
    * @param massFlow double, inlet mass flow in kg/hr
	* */
	Inlet(double pressure, SteamProperties::ThermodynamicQuantity quantityType, double quantityValue, double massFlow);

	double getPressure() const { return pressure; }
	double getQuantityValue() const { return quantityValue; }
	double getMassFlow() const { return massFlow; }
	SteamProperties::ThermodynamicQuantity getQuantityType() const { return quantityType; }
	double getInletEnergyFlow() const { return  inletEnergyFlow; }
	SteamSystemModelerTool::SteamPropertiesOutput const & getInletProperties() const { return inletProperties; }

	void setPressure(double pressure);
	void setQuantityValue(double quantityValue);
	void setMassFlow(double massFlow);
	void setQuantityType(SteamProperties::ThermodynamicQuantity quantityType);

private:
	void calculate();

	double pressure, quantityValue, massFlow;
	SteamProperties::ThermodynamicQuantity quantityType;
	double inletEnergyFlow;
	SteamSystemModelerTool::SteamPropertiesOutput inletProperties;
};

class Header {
public:
	/**
 	* Constructor for the Header class
 	*
 	* @param headerPressure double, inlet pressure in MPa
 	* @param inletVec std::vector<Inlet>, a vector of Inlet objects, will be std::moved into a class member variable
	* */
	Header(double headerPressure, std::vector<Inlet> & inletVec);

	/**
     * Gets the header pressure
     * @return double, header pressure in MPa */
	double getHeaderPressure() const { return headerPressure; }

	/**
     * Gets specific enthalpy
     * @return double, specific enthalpy in kj / kg */
	double getSpecificEnthalpy() const { return specificEnthalpy; }

	/**
     * Gets total combined inlet energy flow of all inlets
     * @return double, inlet energy flow in kj / hr */
	double getInletEnergyFlow() const { return inletEnergyFlow; }

	/**
     * Gets total combined inlet mass flow of all inlets
     * @return double, inlet mass flow in kg / hr */
	double getInletMassFlow() const { return inletMassFlow; }

	/**
     * Gets vector of inlet objects
     * @return std::vector<Inlet> const &, inlet vector */
	std::vector<Inlet> const & getInlets() const { return inlets; }

	/**
     * Gets the Header properties
     * @return SteamSystemModelerTool::SteamPropertiesOutput const &, header properties */
	SteamSystemModelerTool::SteamPropertiesOutput const & getHeaderProperties() const { return headerProperties; }

	/**
     * Sets the Header pressure - units of MPa
     */
	void setHeaderPressure(double headerPressure);

	/**
     * Sets the Inlet object vector, inlets parameter will be std::moved into the member variable vector
     */
	void setInlets(std::vector<Inlet> & inlets);

private:
	void calculate();
	double headerPressure, specificEnthalpy, inletEnergyFlow, inletMassFlow;
	std::vector<Inlet> inlets;
	SteamSystemModelerTool::SteamPropertiesOutput headerProperties;
};

#endif //AMO_TOOLS_SUITE_HEADER_H
