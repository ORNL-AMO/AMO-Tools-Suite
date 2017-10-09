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
#include "ssmt/Header.h"
#include "ssmt/Turbine.h"
#include <string>


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

    auto const results = b.getSteamProperties();
    SetR("steamPressure", results.at("pressure"));
    SetR("steamTemperature", results.at("temperature"));
    SetR("steamSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("steamSpecificEntropy", results.at("specificEntropy"));
    SetR("steamQuality", results.at("quality"));
    SetR("steamMassFlow", results.at("steamMassFlow"));
    SetR("steamEnergyFlow", results.at("steamEnergyFlow"));

    auto const results2 = b.getBlowdownProperties();
    SetR("blowdownPressure", results2.at("pressure"));
    SetR("blowdownTemperature", results2.at("temperature"));
    SetR("blowdownSpecificEnthalpy", results2.at("specificEnthalpy"));
    SetR("blowdownSpecificEntropy", results2.at("specificEntropy"));
    SetR("blowdownQuality", results2.at("quality"));
    SetR("blowdownMassFlow", results2.at("blowdownMassFlow"));
    SetR("blowdownEnergyFlow", results2.at("blowdownEnergyFlow"));

	auto const results3 = b.getFeedwaterProperties();
    SetR("feedwaterPressure", results3.at("pressure"));
    SetR("feedwaterTemperature", results3.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results3.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results3.at("specificEntropy"));
    SetR("feedwaterQuality", results3.at("quality"));
    SetR("feedwaterMassFlow", results3.at("feedwaterMassFlow"));
    SetR("feedwaterEnergyFlow", results3.at("feedwaterEnergyFlow"));
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
    auto const results = hl.getInletProperties();

    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", results.at("massFlow"));
    SetR("inletEnergyFlow", results.at("energyFlow"));

    auto const results2 = hl.getOutletProperties();
    SetR("outletPressure", results2.at("pressure"));
    SetR("outletTemperature", results2.at("temperature"));
    SetR("outletSpecificEnthalpy", results2.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results2.at("specificEntropy"));
    SetR("outletQuality", results2.at("quality"));
    SetR("outletMassFlow", results2.at("massFlow"));
    SetR("outletEnergyFlow", results2.at("energyFlow"));
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

    auto const results = ft.getInletWaterProperties();
    SetR("inletWaterPressure", results.at("pressure"));
    SetR("inletWaterTemperature", results.at("temperature"));
    SetR("inletWaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletWaterSpecificEntropy", results.at("specificEntropy"));
    SetR("inletWaterQuality", results.at("quality"));
    SetR("inletWaterMassFlow", results.at("massFlow"));
    SetR("inletWaterEnergyFlow", results.at("energyFlow"));

    auto const results2 = ft.getOutletSaturatedProperties();
    SetR("outletGasPressure", results2.at("pressure"));
    SetR("outletGasTemperature", results2.at("temperature"));
    SetR("outletGasSpecificEnthalpy", results2.at("gasSpecificEnthalpy"));
    SetR("outletGasSpecificEntropy", results2.at("gasSpecificEntropy"));
    SetR("outletGasQuality", 1);
    SetR("outletGasMassFlow", results2.at("gasMassFlow"));
    SetR("outletGasEnergyFlow", results2.at("gasEnergyFlow"));

    SetR("outletLiquidPressure", results2.at("pressure"));
    SetR("outletLiquidTemperature", results2.at("temperature"));
    SetR("outletLiquidSpecificEnthalpy", results2.at("liquidSpecificEnthalpy"));
    SetR("outletLiquidSpecificEntropy", results2.at("liquidSpecificEntropy"));
    SetR("outletLiquidQuality", 0);
    SetR("outletLiquidMassFlow", results2.at("liquidMassFlow"));
    SetR("outletLiquidEnergyFlow", results2.at("liquidEnergyFlow"));

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

    auto results = pwod.getInletProperties();
    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", pwod.getInletMassFlow());
    SetR("inletEnergyFlow", pwod.getInletEnergyFlow());

    auto results2= pwod.getOutletProperties();
    SetR("outletPressure", results2.at("pressure"));
    SetR("outletTemperature", results2.at("temperature"));
    SetR("outletSpecificEnthalpy", results2.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results2.at("specificEntropy"));
    SetR("outletQuality", results2.at("quality"));
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

    auto results = pwd.getInletProperties();
    SetR("inletPressure", results.at("pressure"));
    SetR("inletTemperature", results.at("temperature"));
    SetR("inletSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("inletSpecificEntropy", results.at("specificEntropy"));
    SetR("inletQuality", results.at("quality"));
    SetR("inletMassFlow", pwd.getInletMassFlow());
    SetR("inletEnergyFlow", pwd.getInletEnergyFlow());

    auto results2 = pwd.getOutletProperties();
    SetR("outletPressure", results2.at("pressure"));
    SetR("outletTemperature", results2.at("temperature"));
    SetR("outletSpecificEnthalpy", results2.at("specificEnthalpy"));
    SetR("outletSpecificEntropy", results2.at("specificEntropy"));
    SetR("outletQuality", results2.at("quality"));
    SetR("outletMassFlow", pwd.getOutletMassFlow());
    SetR("outletEnergyFlow", pwd.getOutletEnergyFlow());

    auto results3 = pwd.getFeedwaterProperties();
    SetR("feedwaterPressure", results3.at("pressure"));
    SetR("feedwaterTemperature", results3.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results3.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results3.at("specificEntropy"));
    SetR("feedwaterQuality", results3.at("quality"));
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

    auto const results = d.getFeedwaterProperties();
    SetR("feedwaterPressure", results.at("pressure"));
    SetR("feedwaterTemperature", results.at("temperature"));
    SetR("feedwaterSpecificEnthalpy", results.at("specificEnthalpy"));
    SetR("feedwaterSpecificEntropy", results.at("specificEntropy"));
    SetR("feedwaterQuality", results.at("quality"));
    SetR("feedwaterMassFlow", results.at("massFlow"));
    SetR("feedwaterEnergyFlow", results.at("energyFlow"));

    auto const results2 = d.getVentedSteamProperties();
    SetR("ventedSteamPressure", results2.at("pressure"));
    SetR("ventedSteamTemperature", results2.at("temperature"));
    SetR("ventedSteamSpecificEnthalpy", results2.at("specificEnthalpy"));
    SetR("ventedSteamSpecificEntropy", results2.at("specificEntropy"));
    SetR("ventedSteamQuality", results2.at("quality"));
    SetR("ventedSteamMassFlow", results2.at("massFlow"));
    SetR("ventedSteamEnergyFlow", results2.at("energyFlow"));

    auto const results3 = d.getInletWaterProperties();
    SetR("inletWaterPressure", results3.at("pressure"));
    SetR("inletWaterTemperature", results3.at("temperature"));
    SetR("inletWaterSpecificEnthalpy", results3.at("specificEnthalpy"));
    SetR("inletWaterSpecificEntropy", results3.at("specificEntropy"));
    SetR("inletWaterQuality", results3.at("quality"));
    SetR("inletWaterMassFlow", results3.at("massFlow"));
    SetR("inletWaterEnergyFlow", results3.at("energyFlow"));

    auto const results4 = d.getInletSteamProperties();
    SetR("inletSteamPressure", results4.at("pressure"));
    SetR("inletSteamTemperature", results4.at("temperature"));
    SetR("inletSteamSpecificEnthalpy", results4.at("specificEnthalpy"));
    SetR("inletSteamSpecificEntropy", results4.at("specificEntropy"));
    SetR("inletSteamQuality", results4.at("quality"));
    SetR("inletSteamMassFlow", results4.at("massFlow"));
    SetR("inletSteamEnergyFlow", results4.at("energyFlow"));

    info.GetReturnValue().Set(r);
}

NAN_METHOD(header) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    auto const headerPressure = Get("headerPressure");

    Local<String> arrayStr = Nan::New<String>("inlets").ToLocalChecked();
    auto array = inp->ToObject()->Get(arrayStr);
    v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(array);

    auto pressureStr = Nan::New<String>("pressure").ToLocalChecked();
    auto temperatureStr = Nan::New<String>("temperature").ToLocalChecked();
	auto qualityStr = Nan::New<String>("quality").ToLocalChecked();
    auto massFlowStr = Nan::New<String>("massFlow").ToLocalChecked();
    auto specificEnthalpyStr = Nan::New<String>("specificEnthalpy").ToLocalChecked();
    auto specificEntropyStr = Nan::New<String>("specificEntropy").ToLocalChecked();
    auto energyFlowStr = Nan::New<String>("energyFlow").ToLocalChecked();

	std::vector<Inlet> inlets;

    for (size_t i = 0; i < arr->Length(); i++) {
        auto const pressure = arr->Get(i)->ToObject()->Get(pressureStr)->NumberValue();
	    unsigned val = arr->Get(i)->ToObject()->Get(Nan::New<String>("thermodynamicQuantity").ToLocalChecked())->NumberValue();
	    auto const quantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
//        auto const quantity = static_cast<SteamProperties::ThermodynamicQuantity>(arr->Get(i)->ToObject()->Get(Nan::New<String>("thermodynamicQuantity").ToLocalChecked())->NumberValue());
        auto const quantityValue = arr->Get(i)->ToObject()->Get(Nan::New<String>("quantityValue").ToLocalChecked())->NumberValue();
        auto const massFlow = arr->Get(i)->ToObject()->Get(massFlowStr)->NumberValue();
        inlets.emplace_back(Inlet(pressure, quantity, quantityValue, massFlow));

        Local<Object> obj = Nan::New<Object>();
        Local<String> inletNum = Nan::New<String>("inlet" + std::to_string(i + 1)).ToLocalChecked();
        auto const inletProps = inlets[i].getInletProperties();

        Nan::Set(obj, pressureStr, Nan::New<Number>(inletProps.at("pressure")));
        Nan::Set(obj, temperatureStr, Nan::New<Number>(inletProps.at("temperature")));
        Nan::Set(obj, qualityStr, Nan::New<Number>(inletProps.at("quality")));
        Nan::Set(obj, specificEnthalpyStr, Nan::New<Number>(inletProps.at("specificEnthalpy")));
        Nan::Set(obj, specificEntropyStr, Nan::New<Number>(inletProps.at("specificEntropy")));
        Nan::Set(obj, energyFlowStr, Nan::New<Number>(inlets[i].getInletEnergyFlow()));
        Nan::Set(obj, massFlowStr, Nan::New<Number>(inlets[i].getMassFlow()));

        Nan::Set(r, inletNum, obj);
    }

	auto header = Header(headerPressure, inlets);
    Local<String> headerStr = Nan::New<String>("header").ToLocalChecked();

    auto const headerProps = header.getHeaderProperties();

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, pressureStr, Nan::New<Number>(header.getHeaderPressure()));
    Nan::Set(obj, temperatureStr, Nan::New<Number>(headerProps.at("temperature")));
    Nan::Set(obj, qualityStr, Nan::New<Number>(headerProps.at("quality")));
    Nan::Set(obj, specificEnthalpyStr, Nan::New<Number>(headerProps.at("specificEnthalpy")));
    Nan::Set(obj, specificEntropyStr, Nan::New<Number>(headerProps.at("specificEntropy")));
    Nan::Set(obj, energyFlowStr, Nan::New<Number>(header.getInletEnergyFlow()));
    Nan::Set(obj, massFlowStr, Nan::New<Number>(header.getInletMassFlow()));

    Nan::Set(r, headerStr, obj);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(turbine) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

	unsigned val = inp->ToObject()->Get(Nan::New<String>("solveFor").ToLocalChecked())->NumberValue();
    Turbine::Solve solveFor = static_cast<Turbine::Solve>(val);
    val = inp->ToObject()->Get(Nan::New<String>("turbineProperty").ToLocalChecked())->NumberValue();
    Turbine::TurbineProperty turbineProperty = static_cast<Turbine::TurbineProperty>(val);
    val = inp->ToObject()->Get(Nan::New<String>("inletQuantity").ToLocalChecked())->NumberValue();
    SteamProperties::ThermodynamicQuantity inletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);

//    Turbine::Solve solveFor = static_cast<Turbine::Solve>(inp->ToObject()->Get(Nan::New<String>("solveFor").ToLocalChecked())->NumberValue());
//    Turbine::TurbineProperty turbineProperty = static_cast<Turbine::TurbineProperty>(inp->ToObject()->Get(Nan::New<String>("turbineProperty").ToLocalChecked())->NumberValue());
//    SteamProperties::ThermodynamicQuantity inletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(inp->ToObject()->Get(Nan::New<String>("inletQuantity").ToLocalChecked())->NumberValue());

	std::unique_ptr<Turbine> t;

    if (solveFor == Turbine::Solve::OutletProperties) {
        t = std::unique_ptr<Turbine>(new Turbine(solveFor, Get("inletPressure"), inletQuantity, Get("inletQuantityValue"),
                    turbineProperty, Get("isentropicEfficiency"), Get("generatorEfficiency"),
                    Get("massFlowOrPowerOut"), Get("outletSteamPressure")));
    } else {
        auto const outletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(inp->ToObject()->Get(Nan::New<String>("outletQuantity").ToLocalChecked())->NumberValue());
        t = std::unique_ptr<Turbine>(new Turbine(solveFor, Get("inletPressure"), inletQuantity, Get("inletQuantityValue"),
                    turbineProperty, Get("generatorEfficiency"), Get("massFlowOrPowerOut"),
                    Get("outletSteamPressure"), outletQuantity, Get("outletQuantityValue")));
    }

    SetR("inletPressure", t->getInletProperties().at("pressure"));
    SetR("inletTemperature", t->getInletProperties().at("temperature"));
    SetR("inletSpecificEnthalpy", t->getInletProperties().at("specificEnthalpy"));
    SetR("inletSpecificEntropy", t->getInletProperties().at("specificEntropy"));
    SetR("inletQuality", t->getInletProperties().at("quality"));
    SetR("inletEnergyFlow", t->getInletEnergyFlow());

    SetR("outletPressure", t->getOutletProperties().at("pressure"));
    SetR("outletTemperature", t->getOutletProperties().at("temperature"));
    SetR("outletSpecificEnthalpy", t->getOutletProperties().at("specificEnthalpy"));
    SetR("outletSpecificEntropy", t->getOutletProperties().at("specificEntropy"));
    SetR("outletQuality", t->getOutletProperties().at("quality"));
    SetR("outletEnergyFlow", t->getOutletEnergyFlow());

    SetR("massFlow", t->getMassFlow());
    SetR("isentropicEfficiency", t->getIsentropicEfficiency());
    SetR("energyOut", t->getEnergyOut());
    SetR("powerOut", t->getPowerOut());
    SetR("generatorEfficiency", t->getGeneratorEfficiency());
	info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
