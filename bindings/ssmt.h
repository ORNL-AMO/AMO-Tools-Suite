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

NAN_METHOD(saturatedPressure) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    /**
     * Constructor for Saturated Pressure class
     * @param saturatedTemperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedPressure sp(Get("saturatedTemperature"));
    double saturatedPressure = sp.calculate();
    SetR("saturatedPressure", saturatedPressure);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedTemperature) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    /**
     * Constructor for the Saturated Temperature class
     * @param saturatedPressure double, saturatedPressure in MPa
     */
    SaturatedTemperature st(Get("saturatedPressure"));
    double saturatedTemperature = st.calculate();
    SetR("saturatedTemperature", saturatedTemperature);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenTemperature) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedPressure findPressure = SaturatedPressure(Get("saturatedTemperature");
    double pressure = findPressure.calculate();

    SaturatedProperties sp(pressure, Get("saturatedTemperature"));
    double saturatedPressure = sp.getSaturatedPressure();
    double saturatedTemperature = sp.getSaturatedTemperature();
    double liquidEnthalpy = sp.getLiquidEnthalpy();
    double gasEnthalpy = sp.getGasEnthalpy();
    double evaporationEnthalpy = sp.getEvaporationEnthalpy();
    double liquidEntropy = sp.getLiquidEntropy();
    double gasEntropy = sp.getGasEntropy();
    double evaporationEntropy = sp.getEvaporationEntropy();
    double liquidVolume = sp.getLiquidVolume();
    double gasVolume = sp.getGasVolume();
    double evaporationVolume = sp.getEvaporationVolume();
    SetR("saturatedPressure", saturatedPressure);
    SetR("saturatedTemperature", saturatedTemperature);
    SetR("liquidEnthalpy", liquidEnthalpy);
    SetR("gasEnthalpy", gasEnthalpy);
    SetR("evaporationEnthalpy", evaporationEnthalpy);
    SetR("liquidEntropy", liquidEntropy);
    SetR("gasEntropy", gasEntropy);
    SetR("evaporationEntropy", evaporationEntropy);
    SetR("liquidVolume", liquidVolume);
    SetR("gasVolume", gasVolume);
    SetR("evaporationVolume", evaporationVolume);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenPressure) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedTemperature findTemperature = SaturatedTemperature(Get("saturatedPressure");
    double temperature = findTemperature.calculate();

    SaturatedProperties sp(Get("saturatedPressure"), temperature);
    double saturatedPressure = sp.getSaturatedPressure();
    double saturatedTemperature = sp.getSaturatedTemperature();
    double liquidEnthalpy = sp.getLiquidEnthalpy();
    double gasEnthalpy = sp.getGasEnthalpy();
    double evaporationEnthalpy = sp.getEvaporationEnthalpy();
    double liquidEntropy = sp.getLiquidEntropy();
    double gasEntropy = sp.getGasEntropy();
    double evaporationEntropy = sp.getEvaporationEntropy();
    double liquidVolume = sp.getLiquidVolume();
    double gasVolume = sp.getGasVolume();
    double evaporationVolume = sp.getEvaporationVolume();
    SetR("saturatedPressure", saturatedPressure);
    SetR("saturatedTemperature", saturatedTemperature);
    SetR("liquidEnthalpy", liquidEnthalpy);
    SetR("gasEnthalpy", gasEnthalpy);
    SetR("evaporationEnthalpy", evaporationEnthalpy);
    SetR("liquidEntropy", liquidEntropy);
    SetR("gasEntropy", gasEntropy);
    SetR("evaporationEntropy", evaporationEntropy);
    SetR("liquidVolume", liquidVolume);
    SetR("gasVolume", gasVolume);
    SetR("evaporationVolume", evaporationVolume);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedProperties) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    SaturatedProperties sp(Get("saturatedPressure"), Get("saturatedTemperature"));
    double liquidEnthalpy = sp.getLiquidEnthalpy();
    double gasEnthalpy = sp.getGasEnthalpy();
    double evaporationEnthalpy = sp.getEvaporationEnthalpy();
    double liquidEntropy = sp.getLiquidEntropy();
    double gasEntropy = sp.getGasEntropy();
    double evaporationEntropy = sp.getEvaporationEntropy();
    double liquidVolume = sp.getLiquidVolume();
    double gasVolume = sp.getGasVolume();
    double evaporationVolume = sp.getEvaporationVolume();
    SetR("liquidEnthalpy", liquidEnthalpy);
    SetR("gasEnthalpy", gasEnthalpy);
    SetR("evaporationEnthalpy", evaporationEnthalpy);
    SetR("liquidEntropy", liquidEntropy);
    SetR("gasEntropy", gasEntropy);
    SetR("evaporationEntropy", evaporationEntropy);
    SetR("liquidVolume", liquidVolume);
    SetR("gasVolume", gasVolume);
    SetR("evaporationVolume", evaporationVolume);
    info.GetReturnValue().Set(r);
}


NAN_METHOD(steamProperties) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SteamProperties::ThermodynamicQuantity quantity = thermodynamicQuantity();

    SteamProperties sp(Get("pressure"), quantity, Get("quantityValue"));
    std::unordered_map <std::string, double> results = sp.calculate();
    double pressure = results["pressure"];
    double temperature = results["temperature"];
    double specificEnthalpy = results["specificEnthalpy"];
    double specificEntropy = results["specificEntropy"];
    double quality = results["quality"];
    double specificVolume = results["specificVolume"];
    SetR("pressure", pressure);
    SetR("temperature", temperature);
    SetR("specificEnthalpy", specificEnthalpy);
    SetR("specificEntropy", specificEntropy);
    SetR("quality", quality);
    SetR("specificVolume", specificVolume);
    info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
