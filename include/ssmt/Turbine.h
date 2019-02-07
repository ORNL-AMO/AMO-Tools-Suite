/**
 * @file
 * @brief Calculator for turbine
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

class Turbine {
public:
/**
     *
     * Turbine calculator class
     * Used to calculate 
     *
     * */
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
     * @param solveFor.
     * @param inletPressure double, inlet pressure in MPa
     * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantity,
     * @param inletQuantityValue double,
     * @param TurbineProperty,
     * @param turbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
     * @param isentropicEfficiency double, Isentropic Efficiency of Turbine, fraction
	 * @param generatorEfficiency double, Conversion Efficiency of Turbine, fraction
	 * @param massFlowOrPowerOut double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param outletSteamPressure double, 
     *
     * */
	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double isentropicEfficiency,
	        double generatorEfficiency, double massFlowOrPowerOut, double outletSteamPressure);

/**
     *
     * Constructor for the turbine calculator
     *
     * @param inletPressure double, inlet pressure in MPa
     * @param SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
     * @param inletQuantity,
     * @param inletQuantityValue double,
     * @param TurbineProperty,
     * @param turbineProperty, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param generatorEfficiency double, Conversion Efficiency of Turbine, fraction
	 * @param massFlowOrPowerOut double, known turbine property: mass flow rate (kg/hr) or power output (kW)
	 * @param outletSteamPressure double, 
	 * @param outletQuantity,
	 * @param outletQuantityValue double, 
     *
     * */
	Turbine(Solve solveFor, double inletPressure, SteamProperties::ThermodynamicQuantity inletQuantity,
	        double inletQuantityValue, TurbineProperty turbineProperty, double generatorEfficiency,
	        double massFlowOrPowerOut, double outletSteamPressure,
	        SteamProperties::ThermodynamicQuantity outletQuantity, double outletQuantityValue);

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
	 * @return double, 
	 */
	double getOutletSteamPressure() const { return outletSteamPressure; }
	/**
	 * Gets the Inlet Quantity
	 * 
	 * @return SteamProperties::ThermodynamicQuantity 
	 */
	SteamProperties::ThermodynamicQuantity getInletQuantity() const { return inletQuantity; }
	SteamProperties::ThermodynamicQuantity getOutletQuantity() const { return outletQuantity; }
	double getInletQuantityValue() const { return inletQuantityValue; }
	double getOutletQuantityValue() const { return outletQuantityValue; }
	TurbineProperty getTurbineProperty() const { return turbineProperty; }
	SteamSystemModelerTool::SteamPropertiesOutput const & getInletProperties() const { return inletProperties; }
	SteamSystemModelerTool::SteamPropertiesOutput const & getOutletProperties() const { return outletProperties; }
	double getInletEnergyFlow() const { return inletEnergyFlow; }
	double getOutletEnergyFlow() const { return outletEnergyFlow; }
	double getPowerOut() const { return powerOut; }
	double getEnergyOut() const { return energyOut; }
	double getMassFlow() const { return massFlow; }

	void setSolveFor(Solve solveFor);
	void setInletPressure(double inletPressure);
	void setIsentropicEfficiency(double isentropicEfficiency);
	void setGeneratorEfficiency(double generatorEfficiency);
	void setMassFlowOrPowerOut(double massFlowOrPowerOut);
	void setOutletSteamPressure(double outletSteamPressure);
	void setInletQuantity(SteamProperties::ThermodynamicQuantity inletQuantity);
	void setOutletQuantity(SteamProperties::ThermodynamicQuantity outletQuantity);
	void setInletQuantityValue(double inletQuantityValue);
	void setOutletQuantityValue(double outletQuantityValue);
	void setTurbineProperty(TurbineProperty turbineProperty);

private:
	void calculate();
	void solveForOutletProperties();
	void solveForIsentropicEfficiency();
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
