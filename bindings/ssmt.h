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

double Get(std::string const & nm) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();

    auto rObj = inp->ToObject()->Get(getName);
    if (rObj->IsUndefined()) {
        ThrowTypeError(std::string("Get method in ssmt.h: " + nm + " not present in object").c_str());
    }
    return rObj->NumberValue();
}

void SetR(std::string const & nm, double n) {
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

    double const pressure = SaturatedPressure(Get("saturatedTemperature")).calculate();

    /**
     * Constructor for Saturated Properties class
     * @param pressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedProperties sp(pressure, Get("saturatedTemperature"));
    auto const results = sp.calculate();

    SetR("saturatedPressure", results.at("pressure"));
    SetR("saturatedTemperature", results.at("temperature"));
    SetR("liquidEnthalpy", results.at("liquidSpecificEnthalpy"));
    SetR("gasEnthalpy", results.at("gasSpecificEnthalpy"));
    SetR("evaporationEnthalpy", results.at("evaporationSpecificEnthalpy"));
    SetR("liquidEntropy", results.at("liquidSpecificEntropy"));
    SetR("gasEntropy", results.at("gasSpecificEntropy"));
    SetR("evaporationEntropy", results.at("evaporationSpecificEntropy"));
    SetR("liquidVolume", results.at("liquidSpecificVolume"));
    SetR("gasVolume", results.at("gasSpecificVolume"));
    SetR("evaporationVolume", results.at("evaporationSpecificVolume"));
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenPressure) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    double const temperature = SaturatedTemperature(Get("saturatedPressure")).calculate();

    /**
     * Constructor for Saturated Properties class
     * @param saturatedPressure double, saturated pressure in MPa
     * @param temperature double, saturated temperature in K
     * @return nothing
     */
    auto const results = SaturatedProperties(Get("saturatedPressure"), temperature).calculate();
    SetR("saturatedPressure", results.at("pressure"));
    SetR("saturatedTemperature", results.at("temperature"));
    SetR("liquidEnthalpy", results.at("liquidSpecificEnthalpy"));
    SetR("gasEnthalpy", results.at("gasSpecificEnthalpy"));
    SetR("evaporationEnthalpy", results.at("evaporationSpecificEnthalpy"));
    SetR("liquidEntropy", results.at("liquidSpecificEntropy"));
    SetR("gasEntropy", results.at("gasSpecificEntropy"));
    SetR("evaporationEntropy", results.at("evaporationSpecificEntropy"));
    SetR("liquidVolume", results.at("liquidSpecificVolume"));
    SetR("gasVolume", results.at("gasSpecificVolume"));
    SetR("evaporationVolume", results.at("evaporationSpecificVolume"));
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
    auto const results = SteamProperties(Get("pressure"), quantity, Get("quantityValue")).calculate();
    SetR("pressure", results.at("pressure"));
    SetR("temperature", results.at("temperature"));
    SetR("specificEnthalpy", results.at("specificEnthalpy"));
    SetR("specificEntropy", results.at("specificEntropy"));
    SetR("quality", results.at("quality"));
    SetR("specificVolume", results.at("specificVolume"));
    info.GetReturnValue().Set(r);
}

NAN_METHOD(boiler) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

    auto const b = Boiler(Get("deaeratorPressure"), Get("combustionEfficiency"), Get("blowdownRate"), Get("steamPressure"), quantityType, Get("quantityValue"), Get("steamMassFlow"));

    std::unordered_map <std::string, double> results = b.getSteamProperties();
    SetR("steamPressure", results.at("pressure"));
    SetR("steamTemperature", results.at("temperature"));
    SetR("steamSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("steamSpecificEntropy", results.at("specificEntropy"));
    SetR("steamQuality", results.at("quality"));
    SetR("steamMassFlow", results.at("steamMassFlow"));
    SetR("steamEnergyFlow", results.at("steamEnergyFlow"));

    results = b.getBlowdownProperties();
    SetR("blowdownPressure", results.at("pressure"));
    SetR("blowdownTemperature", results.at("temperature"));
    SetR("blowdownSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("blowdownSpecificEntropy", results.at("specificEntropy"));
    SetR("blowdownQuality", results.at("quality"));
    SetR("blowdownMassFlow", results.at("blowdownMassFlow"));
    SetR("blowdownEnergyFlow", results.at("blowdownEnergyFlow"));

	results = b.getFeedwaterProperties();
    SetR("feedwaterPressure", results.at("pressure"));
    SetR("feedwaterTemperature", results.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results.at("specificEntropy"));
    SetR("feedwaterQuality", results.at("quality"));
    SetR("feedwaterMassFlow", results.at("feedwaterMassFlow"));
    SetR("feedwaterEnergyFlow", results.at("feedwaterEnergyFlow"));
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
    auto hl = HeatLoss(Get("inletPressure"), quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("percentHeatLoss"));
    std::unordered_map <std::string, double> results = hl.getInletProperties();

    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", results.at("massFlow"));
    SetR("inletEnergyFlow", results.at("energyFlow"));

    results = hl.getOutletProperties();
    SetR("outletPressure", results.at("pressure"));
    SetR("outletTemperature", results.at("temperature"));
    SetR("outletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results.at("specificEntropy"));
    SetR("outletQuality", results.at("quality"));
    SetR("outletMassFlow", results.at("massFlow"));
    SetR("outletEnergyFlow", results.at("energyFlow"));
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
    auto const ft = FlashTank(Get("inletWaterPressure"), quantityType, Get("quantityValue"), Get("inletWaterMassFlow"), Get("tankPressure"));

    auto results = ft.getInletWaterProperties();
    SetR("inletWaterPressure", results.at("pressure"));
    SetR("inletWaterTemperature", results.at("temperature"));
    SetR("inletWaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletWaterSpecificEntropy", results.at("specificEntropy"));
    SetR("inletWaterQuality", results.at("quality"));
    SetR("inletWaterMassFlow", results.at("massFlow"));
    SetR("inletWaterEnergyFlow", results.at("energyFlow"));

    results = ft.getOutletSaturatedProperties();
    SetR("outletGasPressure", results.at("pressure"));
    SetR("outletGasTemperature", results.at("temperature"));
    SetR("outletGasSpecificEnthalpy", results.at("gasSpecificEnthalpy"));
    SetR("outletGasSpecificEntropy", results.at("gasSpecificEntropy"));
    SetR("outletGasQuality", 1);
    SetR("outletGasMassFlow", results.at("gasMassFlow"));
    SetR("outletGasEnergyFlow", results.at("gasEnergyFlow"));

    SetR("outletLiquidPressure", results.at("pressure"));
    SetR("outletLiquidTemperature", results.at("temperature"));
    SetR("outletLiquidSpecificEnthalpy", results.at("liquidSpecificEnthalpy"));
    SetR("outletLiquidSpecificEntropy", results.at("liquidSpecificEntropy"));
    SetR("outletLiquidQuality", 0);
    SetR("outletLiquidMassFlow", results.at("liquidMassFlow"));
    SetR("outletLiquidEnergyFlow", results.at("liquidEnergyFlow"));

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
    auto pwod = PrvWithoutDesuperheating(Get("inletPressure"),quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("outletPressure"));

    std::unordered_map <std::string, double> results = pwod.getInletProperties();
    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", pwod.getInletMassFlow());
    SetR("inletEnergyFlow", pwod.getInletEnergyFlow());

    results = pwod.getOutletProperties();
    SetR("outletPressure", results.at("pressure"));
    SetR("outletTemperature", results.at("temperature"));
    SetR("outletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results.at("specificEntropy"));
    SetR("outletQuality", results.at("quality"));
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
    auto pwd = PrvWithDesuperheating(Get("inletPressure"), quantityType, Get("quantityValue"), Get("inletMassFlow"), Get("outletPressure"), Get("feedwaterPressure"), feedwaterQuantityType, Get("feedwaterQuantityValue"), Get("desuperheatingTemp"));

    std::unordered_map <std::string, double> results = pwd.getInletProperties();
    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", pwd.getInletMassFlow());
    SetR("inletEnergyFlow", pwd.getInletEnergyFlow());

    results = pwd.getOutletProperties();
    SetR("outletPressure", results.at("pressure"));
    SetR("outletTemperature", results.at("temperature"));
    SetR("outletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results.at("specificEntropy"));
    SetR("outletQuality", results.at("quality"));
    SetR("outletMassFlow", pwd.getOutletMassFlow());
    SetR("outletEnergyFlow", pwd.getOutletEnergyFlow());

    SetR("feedwaterPressure", results.at("pressure"));
    SetR("feedwaterTemperature", results.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results.at("specificEntropy"));
    SetR("feedwaterQuality", results.at("quality"));
    SetR("feedwaterMassFlow", pwd.getFeedwaterMassFlow());
    SetR("feedwaterEnergyFlow", pwd.getFeedwaterEnergyFlow());

    info.GetReturnValue().Set(r);
}

NAN_METHOD(deaerator) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity waterQuantityType = waterThermodynamicQuantity();
    SteamProperties::ThermodynamicQuantity steamQuantityType = steamThermodynamicQuantity();

    Deaerator d(Get("deaeratorPressure"), Get("ventRate"), Get("feedwaterMassFlow"), Get("waterPressure"),
                waterQuantityType, Get("waterQuantityValue"), Get("steamPressure"), steamQuantityType,
                Get("steamQuantityValue"));

    std::unordered_map <std::string, double> results = d.getFeedwaterProperties();
    SetR("feedwaterPressure", results.at("pressure"));
    SetR("feedwaterTemperature", results.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results.at("specificEntropy"));
    SetR("feedwaterQuality", results.at("quality"));
    SetR("feedwaterMassFlow", results.at("massFlow"));
    SetR("feedwaterEnergyFlow", results.at("energyFlow"));

    results = d.getVentedSteamProperties();
    SetR("ventedSteamPressure", results.at("pressure"));
    SetR("ventedSteamTemperature", results.at("temperature"));
    SetR("ventedSteamSpecificEnthalpy", results.at("gasSpecificEnthalpy"));
    SetR("ventedSteamSpecificEntropy", results.at("gasSpecificEntropy"));
    SetR("ventedSteamQuality", results.at("quality"));
    SetR("ventedSteamMassFlow", results.at("massFlow"));
    SetR("ventedSteamEnergyFlow", results.at("energyFlow"));

    results = d.getInletWaterProperties();
    SetR("inletWaterPressure", results.at("pressure"));
    SetR("inletWaterTemperature", results.at("temperature"));
    SetR("inletWaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletWaterSpecificEntropy", results.at("specificEntropy"));
    SetR("inletWaterQuality", results.at("quality"));
    SetR("inletWaterMassFlow", results.at("massFlow"));
    SetR("inletWaterEnergyFlow", results.at("energyFlow"));

    results = d.getInletSteamProperties();
    SetR("inletSteamPressure", results.at("pressure"));
    SetR("inletSteamTemperature", results.at("temperature"));
    SetR("inletSteamSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSteamSpecificEntropy", results.at("specificEntropy"));
    SetR("inletSteamQuality", results.at("quality"));
    SetR("inletSteamMassFlow", results.at("massFlow"));
    SetR("inletSteamEnergyFlow", results.at("energyFlow"));

    info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
