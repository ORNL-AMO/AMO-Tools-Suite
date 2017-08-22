//
// Created by qkf on 7/28/2017.
//

#ifndef AMO_TOOLS_SUITE_SSMT_H
#define AMO_TOOLS_SUITE_SSMT_H

#include <nan.h>
#include <node.h>
#include <iostream>
#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/HeatLoss.h"
#include "ssmt/Boiler.h"
#include "ssmt/HeatLoss.h"
#include "ssmt/FlashTank.h"
#include "ssmt/PRV.h"
#include "ssmt/Deaerator.h"


using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(const char *nm) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();

    auto rObj = inp->ToObject()->Get(getName);
    if (rObj->IsUndefined()) {
        std::cout<<nm;
        //assert(!"defined");
    }
    return rObj->NumberValue();
}

void SetR(const char *nm, double n) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Number> getNum = Nan::New<Number>(n);
    Nan::Set(r, getName, getNum);
}

SteamProperties::ThermodynamicQuantity thermodynamicQuantity() {
    return (SteamProperties::ThermodynamicQuantity)(int)Get("thermodynamicQuantity");
}

SteamProperties::ThermodynamicQuantity feedwaterThermodynamicQuantity() {
    return (SteamProperties::ThermodynamicQuantity)(int)Get("feedwaterThermodynamicQuantity");
}

SteamProperties::ThermodynamicQuantity waterThermodynamicQuantity() {
    return (SteamProperties::ThermodynamicQuantity)(int)Get("waterThermodynamicQuantity");
}

SteamProperties::ThermodynamicQuantity steamThermodynamicQuantity() {
    return (SteamProperties::ThermodynamicQuantity)(int)Get("steamThermodynamicQuantity");
}

NAN_METHOD(saturatedPressure) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    /**
     * Constructor for Saturated Pressure class
     * @param saturatedTemperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedPressure sp(Get("saturatedTemperature"));
    SetR("saturatedPressure", sp.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedTemperature) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    /**
     * Constructor for the Saturated Temperature class
     * @param saturatedPressure double, saturatedPressure in MPa
     * @return nothing
     */
    SaturatedTemperature st(Get("saturatedPressure"));
    SetR("saturatedTemperature", st.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenTemperature) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    double pressure = SaturatedPressure(Get("saturatedTemperature")).calculate();

    /**
     * Constructor for Saturated Properties class
     * @param pressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedProperties sp(pressure, Get("saturatedTemperature"));
    std::unordered_map <std::string, double> results = sp.calculate();

    SetR("saturatedPressure", results["pressure"]);
    SetR("saturatedTemperature", results["temperature"]);
    SetR("liquidEnthalpy", results["liquidSpecificEnthalpy"]);
    SetR("gasEnthalpy", results["gasSpecificEnthalpy"]);
    SetR("evaporationEnthalpy", results["evaporationSpecificEnthalpy"]);
    SetR("liquidEntropy", results["liquidSpecificEntropy"]);
    SetR("gasEntropy", results["gasSpecificEntropy"]);
    SetR("evaporationEntropy", results["evaporationSpecificEntropy"]);
    SetR("liquidVolume", results["liquidSpecificVolume"]);
    SetR("gasVolume", results["gasSpecificVolume"]);
    SetR("evaporationVolume", results["evaporationSpecificVolume"]);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenPressure) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedTemperature findTemperature = SaturatedTemperature(Get("saturatedPressure"));
    double temperature = findTemperature.calculate();

    /**
     * Constructor for Saturated Properties class
     * @param saturatedPressure double, saturated pressure in MPa
     * @param temperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedProperties sp(Get("saturatedPressure"), temperature);
    std::unordered_map <std::string, double> results = sp.calculate();
    SetR("saturatedPressure", results["pressure"]);
    SetR("saturatedTemperature", results["temperature"]);
    SetR("liquidEnthalpy", results["liquidSpecificEnthalpy"]);
    SetR("gasEnthalpy", results["gasSpecificEnthalpy"]);
    SetR("evaporationEnthalpy", results["evaporationSpecificEnthalpy"]);
    SetR("liquidEntropy", results["liquidSpecificEntropy"]);
    SetR("gasEntropy", results["gasSpecificEntropy"]);
    SetR("evaporationEntropy", results["evaporationSpecificEntropy"]);
    SetR("liquidVolume", results["liquidSpecificVolume"]);
    SetR("gasVolume", results["gasSpecificVolume"]);
    SetR("evaporationVolume", results["evaporationSpecificVolume"]);
    info.GetReturnValue().Set(r);
}


NAN_METHOD(steamProperties) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantity = thermodynamicQuantity();

    /**
     * Constructor for Steam Properties class
     * @param pressure double, saturated pressure in MPa
     * @param quantity SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, specific enthalpy in kJ/kg, specific entropy in kJ/kg/K, or saturated quality - unitless)
     * @param quantityValue double, value of either temperature in K, specific enthalpy in kJ/kg, specific entropy in kJ/kg/K, or saturated quality - unitless
     * @return nothing
     */
    SteamProperties sp(Get("pressure"), quantity, Get("quantityValue"));
    std::unordered_map <std::string, double> results = sp.calculate();
    SetR("pressure", results["pressure"]);
    SetR("temperature", results["temperature"]);
    SetR("specificEnthalpy", results["specificEnthalpy"]);
    SetR("specificEntropy", results["specificEntropy"]);
    SetR("quality", results["quality"]);
    SetR("specificVolume", results["specificVolume"]);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(boiler) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

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
 * @return nothing
 *
 * */
    Boiler b(Get("deaeratorPressure"), Get("combustionEfficiency"), Get("blowdownRate"), Get("steamPressure"), quantityType, Get("quantityValue"), Get("steamMassFlow"));

    std::unordered_map <std::string, double> results = b.getSteamProperties();
    SetR("steamPressure", results["pressure"]);
    SetR("steamTemperature", results["temperature"]);
    SetR("steamSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("steamSpecificEntropy", results["specificEntropy"]);
    SetR("steamQuality", results["quality"]);
    SetR("steamMassFlow", b.getSteamMassFlow());
    SetR("steamEnergyFlow", b.getSteamEnergyFlow());

    results = b.getBlowdownProperties();
    SetR("blowdownPressure", results["pressure"]);
    SetR("blowdownTemperature", results["temperature"]);
    SetR("blowdownSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("blowdownSpecificEntropy", results["specificEntropy"]);
    SetR("blowdownQuality", results["quality"]);
    SetR("blowdownMassFlow", b.getBlowdownMassFlow());
    SetR("blowdownEnergyFlow", b.getBlowdownEnergyFlow());

	results = b.getFeedwaterProperties();
    SetR("feedwaterPressure", results["pressure"]);
    SetR("feedwaterTemperature", results["temperature"]);
    SetR("feedwaterSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("feedwaterSpecificEntropy", results["specificEntropy"]);
    SetR("feedwaterQuality", results["quality"]);
    SetR("feedwaterMassFlow", b.getFeedwaterMassFlow());
    SetR("feedwaterEnergyFlow", b.getFeedwaterEnergyFlow());
    SetR("boilerEnergy", b.getBoilerEnergy());
    SetR("fuelEnergy", b.getFuelEnergy());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(heatLoss) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
    /**
 *
 * Constructor for the heat loss calculator
 *
 * @param inletPressure double, inlet pressure in MPa
 * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
 * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
 * @param inletMassFlow double, inlet mass flow in kg/hr
 * @param percentHeatLoss double, heat loss as %
 *
 * @return nothing
 *
 * */
    HeatLoss hl(Get("inletPressure"), quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("percentHeatLoss"));
    std::unordered_map <std::string, double> results = hl.getInletProperties();

    SetR("inletPressure", results["pressure"]);
    SetR("inletTemperature", results["temperature"]);
    SetR("inletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("inletSpecificEntropy", results["specificEntropy"]);
    SetR("inletQuality", results["quality"]);
    SetR("inletMassFlow", hl.getInletMassFlow());
    SetR("inletEnergyFlow", hl.getInletEnergyFlow());

    results = hl.getOutletProperties();
    SetR("outletPressure", results["pressure"]);
    SetR("outletTemperature", results["temperature"]);
    SetR("outletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("outletSpecificEntropy", results["specificEntropy"]);
    SetR("outletQuality", results["quality"]);
    SetR("outletMassFlow", hl.getOutletMassFlow());
    SetR("outletEnergyFlow", hl.getOutletEnergyFlow());
    SetR("heatLoss", hl.getHeatLoss());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(flashTank) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

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
    FlashTank ft(Get("inletWaterPressure"), quantityType, Get("quantityValue"), Get("inletWaterMassFlow"), Get("tankPressure"));

    std::unordered_map <std::string, double> results = ft.getInletWaterProperties();
    SetR("inletWaterPressure", results["pressure"]);
    SetR("inletWaterTemperature", results["temperature"]);
    SetR("inletWaterSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("inletWaterSpecificEntropy", results["specificEntropy"]);
    SetR("inletWaterQuality", results["quality"]);
    SetR("inletWaterMassFlow", ft.getInletWaterMassFlow());
    SetR("inletWaterEnergyFlow", ft.getInletWaterEnergyFlow());

    results = ft.getOutletSaturatedProperties();
    SetR("outletGasPressure", results["saturatedPressure"]);
    SetR("outletGasTemperature", results["saturatedTemperature"]);
    SetR("outletGasSpecificEnthalpy", results["gasSpecificEnthalpy"]);
    SetR("outletGasSpecificEntropy", results["gasSpecificEntropy"]);
    SetR("outletGasQuality", 1);
    SetR("outletGasMassFlow", ft.getOutletGasMassFlow());
    SetR("outletGasEnergyFlow", ft.getOutletGasEnergyFlow());

    SetR("outletLiquidPressure", results["saturatedPressure"]);
    SetR("outletLiquidTemperature", results["saturatedTemperature"]);
    SetR("outletLiquidSpecificEnthalpy", results["liquidSpecificEnthalpy"]);
    SetR("outletLiquidSpecificEntropy", results["liquidSpecificEntropy"]);
    SetR("outletLiquidQuality", 0);
    SetR("outletLiquidMassFlow", ft.getOutletLiquidMassFlow());
    SetR("outletLiquidEnergyFlow", ft.getOutletLiquidEnergyFlow());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithoutDesuperheating) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

   /**
    *
    * Constructor for the PRV without desuperheating calculator
    *
    * @param inletPressure double, inlet pressure in MPa
    * @param quantityType SteamProperties::ThermodynamicQuantity, type of quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
    * @param quantityValue double, value of the quantity (either temperature in K, enthalpy in kJ/kg, entropy in kJ/kg/K, or quality - unitless)
    * @param inletMassFlow double, inlet mass flow in kg/hr
    * @param outletPressure double, houtlet pressure in MPa
    *
    * @return nothing
    *
    * */
    PrvWithoutDesuperheating pwod(Get("inletPressure"),quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("outletPressure"));

    std::unordered_map <std::string, double> results = pwod.getInletProperties();
    SetR("inletPressure", results["pressure"]);
    SetR("inletTemperature", results["temperature"]);
    SetR("inletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("inletSpecificEntropy", results["specificEntropy"]);
    SetR("inletQuality", results["quality"]);
    SetR("inletMassFlow", pwod.getInletMassFlow());
    SetR("inletEnergyFlow", pwod.getInletEnergyFlow());

    results = pwod.getOutletProperties();
    SetR("outletPressure", results["pressure"]);
    SetR("outletTemperature", results["temperature"]);
    SetR("outletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("outletSpecificEntropy", results["specificEntropy"]);
    SetR("outletQuality", results["quality"]);
    SetR("outletMassFlow", pwod.getOutletMassFlow());
    SetR("outletEnergyFlow", pwod.getOutletEnergyFlow());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithDesuperheating) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
    SteamProperties::ThermodynamicQuantity feedwaterQuantityType = feedwaterThermodynamicQuantity();

    /**
     *
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
     *
     * @return nothing
     *
     * */
    PrvWithDesuperheating pwd(Get("inletPressure"), quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("outletPressure"), Get("feedwaterPressure"), feedwaterQuantityType, Get("feedwaterQuantityValue"), Get("desuperheatingTemp"));

    std::unordered_map <std::string, double> results = pwd.getInletProperties();
    SetR("inletPressure", results["pressure"]);
    SetR("inletTemperature", results["temperature"]);
    SetR("inletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("inletSpecificEntropy", results["specificEntropy"]);
    SetR("inletQuality", results["quality"]);
    SetR("inletMassFlow", pwd.getInletMassFlow());
    SetR("inletEnergyFlow", pwd.getInletEnergyFlow());

    results = pwd.getOutletProperties();
    SetR("outletPressure", results["pressure"]);
    SetR("outletTemperature", results["temperature"]);
    SetR("outletSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("outletSpecificEntropy", results["specificEntropy"]);
    SetR("outletQuality", results["quality"]);
    SetR("outletMassFlow", pwd.getOutletMassFlow());
    SetR("outletEnergyFlow", pwd.getOutletEnergyFlow());

    SetR("feedwaterPressure", results["pressure"]);
    SetR("feedwaterTemperature", results["temperature"]);
    SetR("feedwaterSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("feedwaterSpecificEntropy", results["specificEntropy"]);
    SetR("feedwaterQuality", results["quality"]);
    SetR("feedwaterMassFlow", pwd.getFeedwaterMassFlow());
    SetR("feedwaterEnergyFlow", pwd.getFeedwaterEnergyFlow());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(deaerator) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity waterQuantityType = waterThermodynamicQuantity();
    SteamProperties::ThermodynamicQuantity steamQuantityType = steamThermodynamicQuantity();

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

     * @return nothing
     *
     * */
    Deaerator d(Get("deaeratorPressure"), Get("ventRate"), Get("feedwaterMassFlow"), Get("waterPressure"), waterQuantityType, Get("waterQuantityValue"), Get("steamPressure"), steamQuantityType, Get("steamQuantityValue"));

    std::unordered_map <std::string, double> results = d.getFeedwaterProperties();
    SetR("feedwaterPressure", results["pressure"]);
    SetR("feedwaterTemperature", results["temperature"]);
    SetR("feedwaterSpecificEnthalpy", results["specificEnthalpy"]);
    SetR("feedwaterSpecificEntropy", results["specificEntropy"]);
    SetR("feedwaterQuality", results["quality"]);
    SetR("feedwaterMassFlow", d.getFeedwaterMassFlow());
    SetR("feedwaterEnergyFlow", d.getFeedwaterEnergyFlow());

    results = d.getVentedSteamProperties();
    SetR("ventedSteamPressure", results["saturatedPressure"]);
    SetR("ventedSteamTemperature", results["saturatedTemperature"]);
    SetR("ventedSteamSpecificEnthalpy", results["gasSpecificEnthalpy"]);
    SetR("ventedSteamSpecificEntropy", results["gasSpecificEntropy"]);
    SetR("ventedSteamQuality", results["quality"]);
    SetR("ventedSteamMassFlow", d.getVentedSteamMassFlow());
    SetR("ventedSteamEnergyFlow", d.getVentedSteamEnergyFlow());

    results = d.getInletWaterProperties();
    SetR("inletWaterPressure", results["saturatedPressure"]);
    SetR("inletWaterTemperature", results["saturatedTemperature"]);
    SetR("inletWaterSpecificEnthalpy", results["liquidSpecificEnthalpy"]);
    SetR("inletWaterSpecificEntropy", results["liquidSpecificEntropy"]);
    SetR("inletWaterQuality", results["quality"]);
    SetR("inletWaterMassFlow", d.getInletWaterMassFlow());
    SetR("inletWaterEnergyFlow", d.getInletWaterEnergyFlow());

    results = d.getInletSteamProperties();
    SetR("inletSteamPressure", results["saturatedPressure"]);
    SetR("inletSteamTemperature", results["saturatedTemperature"]);
    SetR("inletSteamSpecificEnthalpy", results["liquidSpecificEnthalpy"]);
    SetR("inletSteamSpecificEntropy", results["liquidSpecificEntropy"]);
    SetR("inletSteamQuality", results["quality"]);
    SetR("inletSteamMassFlow", d.getInletSteamMassFlow());
    SetR("inletSteamEnergyFlow", d.getInletSteamEnergyFlow());

    info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
