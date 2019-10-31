/**
 * @file
 * @brief Calculator for turbines for steam systems
 *
 * This contains the inputs for turbine related calculations.
 *
 * @author Allie Ledbetter (aeledbetter)
 * @bug No known bugs.
 *
 */
#ifndef AMO_TOOLS_SUITE_TURBINE_H
#define AMO_TOOLS_SUITE_TURBINE_H

#include "SteamProperties.h"
/**
     *
     * Turbine calculator class
     * Used to calculate turbine properties
     *
     * 
	 */
class Turbine {
public:
	///enum class for Solve
	enum class Solve {
		OutletProperties,
		IsentropicEfficiency
	};
	///enum class for TurbineProperty
	enum class TurbineProperty {
		MassFlow,
		PowerOut
	};
	/**
     *
     * Constructor for the turbine calculator
	 * 
     * @param solveFor, solves for unknown value
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantityValue double, Thermodynamic Property of the Inlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
     * @param TurbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
     * @param turbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
     * @param isentropicEfficiency double, Isentropic Efficiency of Turbine, fraction
	 * @param generatorEfficiency double, Conversion Efficiency of Turbine, fraction
	 * @param massFlowOrPowerOut double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param outletSteamPressure double, outlet pressure of the steam in MPa
     *
     * */
	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double isentropicEfficiency,
	        double generatorEfficiency, double massFlowOrPowerOut, double outletSteamPressure);

/**
     *
     * Constructor for the turbine calculator
     *
	 * @param solveFor, solves for the unknown value
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantityValue double, Thermodynamic Property of the Inlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
     * @param TurbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
     * @param turbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param generatorEfficiency double, Conversion Efficiency of Turbine, fraction
	 * @param massFlowOrPowerOut double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param outletSteamPressure double, outlet pressure of the steam in MPa
	 * @param outletQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 * @param outletQuantityValue double, Thermodynamic Property of the outlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
     *
     * */
	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double generatorEfficiency,
	        double massFlowOrPowerOut, double outletSteamPressure,
	        SteamProperties::ThermodynamicQuantity outletQuantity, double outletQuantityValue);
	/**
	 * Solves for the unknown value
	 * 
	 * @return unknown value
	 */

	Solve getSolveFor() const { return solveFor; }
	/**
	 * Gets the inlet pressure 
	 * 
	 * @return double, Pressure of the inlet steam in MPa
	 */
	double getInletPressure() const { return inletPressure; }
	/**
	 * Gets the Isentropic Efficiency
	 * 
	 * @return double, Isentropic Efficiency of Turbine, fraction
	 */
	double getIsentropicEfficiency() const { return isentropicEfficiency * 100; }
	/**
	 * Gets the Generator Efficiency
	 * 
	 * @return double, Conversion Efficiency of Turbine, fraction
	 */
	double getGeneratorEfficiency() const { return generatorEfficiency * 100; }
	/**
	 * Gets the Mass Flow Or Power Out
	 * 
	 * @return double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 */
	double getMassFlowOrPowerOut() const { return massFlowOrPowerOut; }
	/**
	 * Gets the Outlet Steam Pressure
	 * 
	 * @return double, outlet pressure of the steam in MPa
	 */
	double getOutletSteamPressure() const { return outletSteamPressure; }
	/**
	 * Gets the Inlet Quantity
	 * 
	 * @return SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless) 
	 */
	SteamProperties::ThermodynamicQuantity getInletQuantity() const { return inletQuantity; }
	/**
	 * Gets the Outlet Quantity
	 * 
	 * @return SteamProperties::ThermodynamicQuantity, type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
	SteamProperties::ThermodynamicQuantity getOutletQuantity() const { return outletQuantity; }
	/**
	 * Gets the Inlet Quantity Value
	 * 
	 * @return double, Thermodynamic Property of the Inlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
	 */
	double getInletQuantityValue() const { return inletQuantityValue; }
	/**
	 * Gets the Outlet Quantity Value
	 * 
	 * @return double, Thermodynamic Property of the outlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
	 */
	double getOutletQuantityValue() const { return outletQuantityValue; }
	/**
	 * Gets the Turbine Property
	 * 
	 * @return known turbine property: mass flow rate (kg/hr) or power output (kW)
	 */
	TurbineProperty getTurbineProperty() const { return turbineProperty; }
	/**
	 * Gets the Inlet Properties
	 * 
	 * @return SteamSystemModelerTool::SteamPropertiesOutput, inlet steam properties
	 */
	SteamSystemModelerTool::SteamPropertiesOutput const & getInletProperties() const { return inletProperties; }
	/**
	 * Gets the Outlet Properties 
	 * 
	 * @return SteamSystemModelerTool::SteamPropertiesOutput, outlet steam properties
	 */
	SteamSystemModelerTool::SteamPropertiesOutput const & getOutletProperties() const { return outletProperties; }
	/**
	 * Gets the Inlet Energy Flow
	 * 
	 * @return double, inlet steam energy flow in MJ/hr
	 */
	double getInletEnergyFlow() const { return inletEnergyFlow; }
	/**
	 * Gets the Outlet Energy Flow
	 * note: without desuperheating, it is the same as inletMassFlow because outlet == inlet.
	 * @return double, outlet steam energy flow in MJ/hr
	 */
	double getOutletEnergyFlow() const { return outletEnergyFlow; }
	/**
	 * Gets the Power Out
	 * 
	 * @return double, power output in kW
	 */
	double getPowerOut() const { return powerOut; }
	/**
	 *  Gets the Energy Out
	 * 
	 * @return double, energy output in MJ/hr 
	 */
	double getEnergyOut() const { return energyOut; }
	/**
	 * Gets the Mass Flow 
	 * 
	 * @return double, Mass flow rate in kg/hr
	 */
	double getMassFlow() const { return massFlow; }
	/**
	 * Sets the Solve For value
	 * 
	 * @param solveFor, solves for the unknown value
	 */
	void setSolveFor(Solve solveFor);
	/**
	 * Sets the inlet pressure
	 * 
	 * @param inletPressure double, inlet pressure in MPa
	 */
	void setInletPressure(double inletPressure);
	/**
	 * Sets the Isentropic Efficiency
	 * 
	 * @param isentropicEfficiency double, Isentropic Efficiency of Turbine, fraction
	 */
	void setIsentropicEfficiency(double isentropicEfficiency);
	/**
	 * Sets the Generator Efficiency
	 * 
	 * @param generatorEfficiency double, Conversion Efficiency of Turbine, fraction
	 */
	void setGeneratorEfficiency(double generatorEfficiency);
	/**
	 * @brief Sets the Mass Flow Or Power Out
	 * 
	 * @param massFlowOrPowerOut double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 */
	void setMassFlowOrPowerOut(double massFlowOrPowerOut);
	/**
	 * Sets the Outlet Steam Pressure
	 * 
	 * @param outletSteamPressure double, outlet pressure of the steam in MPa
	 */
	void setOutletSteamPressure(double outletSteamPressure);
	/**
	 * Sets the Inlet Quantity
	 * 
	 * @param inletQuantity, inlet type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless) 
	 */
	void setInletQuantity(SteamProperties::ThermodynamicQuantity inletQuantity);
	/**
	 * Sets the Outlet Quantity 
	 * 
	 * @param outletQuantity, outlet type of quantity for water (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
	 */
	void setOutletQuantity(SteamProperties::ThermodynamicQuantity outletQuantity);
	/**
	 * Sets the Inlet Quantity Value
	 * 
	 * @param inletQuantityValue double, Thermodynamic Property of the Inlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
	 */
	void setInletQuantityValue(double inletQuantityValue);
	/**
	 * Sets the Outlet Quantity Value
	 * 
	 * @param outletQuantityValue double, Thermodynamic Property of the Inlet used for calculations- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unitless)
	 */
	void setOutletQuantityValue(double outletQuantityValue);
	/**
	 * Sets the Turbine Property 
	 * 
	 * @param Turbineproperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param turbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 */
	void setTurbineProperty(TurbineProperty turbineProperty);

private:
	/**
	 * @param calculate, calculates the needed value
	 * 
	 */
	void calculate();
	/**
	 * @param solveFOrOutletProperties, solves for outlet properties
	 * 
	 */
	void solveForOutletProperties();
	/**
	 * @param solveForIsentropicEfficiency, solves for Isentropic Efficiency 
	 * 
	 */
	void solveForIsentropicEfficiency();
	/**
	 * Calculates Turbine Properties
	 * 
	 * @param inletSpecificEnthalpy, double in kJ/kg
	 * @param outletSpecificEnthalpy, double in kJ/kg/K
	 */
	void calculateTurbineProperties(double inletSpecificEnthalpy, double outletSpecificEnthalpy);

	Solve solveFor;
	double inletPressure, isentropicEfficiency, generatorEfficiency, massFlowOrPowerOut, outletSteamPressure;
	SteamProperties::ThermodynamicQuantity inletQuantity, outletQuantity;
	double inletQuantityValue, outletQuantityValue = 0;
	TurbineProperty turbineProperty;

	SteamSystemModelerTool::SteamPropertiesOutput inletProperties, outletProperties;

	double inletEnergyFlow, outletEnergyFlow = 0, energyOut, powerOut, massFlow;
};

#endif //AMO_TOOLS_SUITE_TURBINE_H
