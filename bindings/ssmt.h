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
#include "ssmt/Boiler.h"
#include "ssmt/HeatLoss.h"
#include "ssmt/FlashTank.h"


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
     * @return nothing
     */
    SaturatedTemperature st(Get("saturatedPressure"));
    double saturatedTemperature = st.calculate();
    SetR("saturatedTemperature", saturatedTemperature);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenTemperature) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedPressure findPressure = SaturatedPressure(Get("saturatedTemperature"));
    double pressure = findPressure.calculate();

    /**
     * Constructor for Saturated Properties class
     * @param pressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in K
     * @return nothing
     */
    SaturatedProperties sp(pressure, Get("saturatedTemperature"));
    std::unordered_map <std::string, double> results = sp.calculate();
    //double saturatedPressure = results["pressure"];
    double saturatedPressure = results["pressure"];
    double saturatedTemperature = results["temperature"];
    double liquidEnthalpy = results["liquidSpecificEnthalpy"];
    double gasEnthalpy = results["gasSpecificEnthalpy"];
    double evaporationEnthalpy = results["evaporationSpecificEnthalpy"];
    double liquidEntropy = results["liquidSpecificEntropy"];
    double gasEntropy = results["gasSpecificEntropy"];
    double evaporationEntropy = results["evaporationSpecificEntropy"];
    double liquidVolume = results["liquidSpecificVolume"];
    double gasVolume = results["gasSpecificVolume"];
    double evaporationVolume = results["evaporationSpecificVolume"];
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
    double saturatedPressure = results["pressure"];
    double saturatedTemperature = results["temperature"];
    double liquidEnthalpy = results["liquidSpecificEnthalpy"];
    double gasEnthalpy = results["gasSpecificEnthalpy"];
    double evaporationEnthalpy = results["evaporationSpecificEnthalpy"];
    double liquidEntropy = results["liquidSpecificEntropy"];
    double gasEntropy = results["gasSpecificEntropy"];
    double evaporationEntropy = results["evaporationSpecificEntropy"];
    double liquidVolume = results["liquidSpecificVolume"];
    double gasVolume = results["gasSpecificVolume"];
    double evaporationVolume = results["evaporationSpecificVolume"];
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
        std::unordered_map <std::string, double> steamResults = b.getSteamProperties();
        std::unordered_map <std::string, double> blowdownResults = b.getBlowdownProperties();
        std::unordered_map <std::string, double> feedwaterResults = b.getFeedwaterProperties();
        double steamPressure = steamResults["pressure"];
        double steamTemperature = steamResults["temperature"];
        double steamSpecificEnthalpy = steamResults["specificEnthalpy"];
        double steamSpecificEntropy = steamResults["specificEntropy"];
        double steamQuality = steamResults["quality"];
        double steamMassFlow = b.getSteamMassFlow();
        double steamEnergyFlow = b.getSteamEnergyFlow();

        double blowdownPressure = blowdownResults["pressure"];
        double blowdownTemperature = blowdownResults["temperature"];
        double blowdownSpecificEnthalpy = blowdownResults["specificEnthalpy"];
        double blowdownSpecificEntropy = blowdownResults["specificEntropy"];
        double blowdownQuality = blowdownResults["quality"];
        double blowdownMassFlow = b.getBlowdownMassFlow();
        double blowdownEnergyFlow = b.getBlowdownEnergyFlow();

        double feedwaterPressure = feedwaterResults["pressure"];
        double feedwaterTemperature = feedwaterResults["temperature"];
        double feedwaterSpecificEnthalpy = feedwaterResults["specificEnthalpy"];
        double feedwaterSpecificEntropy = feedwaterResults["specificEntropy"];
        double feedwaterQuality = feedwaterResults["quality"];
        double feedwaterMassFlow = b.getFeedwaterMassFlow();
        double feedwaterEnergyFlow = b.getFeedwaterEnergyFlow();

        double boilerEnergy = b.getBoilerEnergy();
        double fuelEnergy = b.getFuelEnergy();

        SetR("steamPressure", steamPressure);
        SetR("steamTemperature", steamTemperature);
        SetR("steamSpecificEnthalpy", steamSpecificEnthalpy);
        SetR("steamSpecificEntropy", steamSpecificEntropy);
        SetR("steamQuality", steamQuality);
        SetR("steamMassFlow", steamMassFlow);
        SetR("steamEnergyFlow", steamEnergyFlow);

        SetR("blowdownPressure", blowdownPressure);
        SetR("blowdownTemperature", blowdownTemperature);
        SetR("blowdownSpecificEnthalpy", blowdownSpecificEnthalpy);
        SetR("blowdownSpecificEntropy", blowdownSpecificEntropy);
        SetR("blowdownQuality", blowdownQuality);
        SetR("blowdownMassFlow", blowdownMassFlow);
        SetR("blowdownEnergyFlow", blowdownEnergyFlow);

        SetR("feedwaterPressure", feedwaterPressure);
        SetR("feedwaterTemperature", feedwaterTemperature);
        SetR("feedwaterSpecificEnthalpy", feedwaterSpecificEnthalpy);
        SetR("feedwaterSpecificEntropy", feedwaterSpecificEntropy);
        SetR("feedwaterQuality", feedwaterQuality);
        SetR("feedwaterMassFlow", feedwaterMassFlow);
        SetR("feedwaterEnergyFlow", feedwaterEnergyFlow);

        SetR("boilerEnergy", boilerEnergy);
        SetR("fuelEnergy", fuelEnergy);

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
        std::unordered_map <std::string, double> inletResults = hl.getInletProperties();
        std::unordered_map <std::string, double> outletResults = hl.getOutletProperties();
        double inletPressure = inletResults["pressure"];
        double inletTemperature = inletResults["temperature"];
        double inletSpecificEnthalpy = inletResults["specificEnthalpy"];
        double inletSpecificEntropy = inletResults["specificEntropy"];
        double inletQuality = inletResults["quality"];
        double inletMassFlow = hl.getInletMassFlow();
        double inletEnergyFlow = hl.getInletEnergyFlow();

        double outletPressure = outletResults["pressure"];
        double outletTemperature = outletResults["temperature"];
        double outletSpecificEnthalpy = outletResults["specificEnthalpy"];
        double outletSpecificEntropy = outletResults["specificEntropy"];
        double outletQuality = outletResults["quality"];
        double outletMassFlow = hl.getOutletMassFlow();
        double outletEnergyFlow = hl.getOutletEnergyFlow();

        double heatLoss = hl.getHeatLoss();

        SetR("inletPressure", inletPressure);
        SetR("inletTemperature", inletTemperature);
        SetR("inletSpecificEnthalpy", inletSpecificEnthalpy);
        SetR("inletSpecificEntropy", inletSpecificEntropy);
        SetR("inletQuality", inletQuality);
        SetR("inletMassFlow", inletMassFlow);
        SetR("inletEnergyFlow", inletEnergyFlow);

        SetR("outletPressure", outletPressure);
        SetR("outletTemperature", outletTemperature);
        SetR("outletSpecificEnthalpy", outletSpecificEnthalpy);
        SetR("outletSpecificEntropy", outletSpecificEntropy);
        SetR("outletQuality", outletQuality);
        SetR("outletMassFlow", outletMassFlow);
        SetR("outletEnergyFlow", outletEnergyFlow);

        SetR("heatLoss", heatLoss);

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
        std::unordered_map <std::string, double> inletWaterResults = ft.getInletWaterProperties();
        std::unordered_map <std::string, double> outletSaturatedResults = ft.getOutletSaturatedProperties();

        double inletWaterPressure = inletWaterResults["pressure"];
        double inletWaterTemperature = inletWaterResults["temperature"];
        double inletWaterSpecificEnthalpy = inletWaterResults["specificEnthalpy"];
        double inletWaterSpecificEntropy = inletWaterResults["specificEntropy"];
        double inletWaterQuality = inletWaterResults["quality"];
        double inletWaterMassFlow = ft.getInletWaterMassFlow();
        double inletWaterEnergyFlow = ft.getInletWaterEnergyFlow();

        double outletGasPressure = outletSaturatedResults["saturatedPressure"];
        double outletGasTemperature = outletSaturatedResults["saturatedTemperature"];
        double outletGasSpecificEnthalpy = outletSaturatedResults["gasSpecificEnthalpy"];
        double outletGasSpecificEntropy = outletSaturatedResults["gasSpecificEntropy"];
        double outletGasQuality = 1;
        double outletGasMassFlow = ft.getOutletGasMassFlow();
        double outletGasEnergyFlow = ft.getOutletGasEnergyFlow();

        double outletLiquidPressure = outletSaturatedResults["saturatedPressure"];
        double outletLiquidTemperature = outletSaturatedResults["saturatedTemperature"];
        double outletLiquidSpecificEnthalpy = outletSaturatedResults["liquidSpecificEnthalpy"];
        double outletLiquidSpecificEntropy = outletSaturatedResults["liquidSpecificEntropy"];
        double outletLiquidQuality = 0;
        double outletLiquidMassFlow = ft.getOutletLiquidMassFlow();
        double outletLiquidEnergyFlow = ft.getOutletLiquidEnergyFlow();

        SetR("inletWaterPressure", inletWaterPressure);
        SetR("inletWaterTemperature", inletWaterTemperature);
        SetR("inletWaterSpecificEnthalpy", inletWaterSpecificEnthalpy);
        SetR("inletWaterSpecificEntropy", inletWaterSpecificEntropy);
        SetR("inletWaterQuality", inletWaterQuality);
        SetR("inletWaterMassFlow", inletWaterMassFlow);
        SetR("inletWaterEnergyFlow", inletWaterEnergyFlow);

        SetR("outletGasPressure", outletGasPressure);
        SetR("outletGasTemperature", outletGasTemperature);
        SetR("outletGasSpecificEnthalpy", outletGasSpecificEnthalpy);
        SetR("outletGasSpecificEntropy", outletGasSpecificEntropy);
        SetR("outletGasQuality", outletGasQuality);
        SetR("outletGasMassFlow", outletGasMassFlow);
        SetR("outletGasEnergyFlow", outletGasEnergyFlow);

        SetR("outletLiquidPressure", outletLiquidPressure);
        SetR("outletLiquidTemperature", outletLiquidTemperature);
        SetR("outletLiquidSpecificEnthalpy", outletLiquidSpecificEnthalpy);
        SetR("outletLiquidSpecificEntropy", outletLiquidSpecificEntropy);
        SetR("outletLiquidQuality", outletLiquidQuality);
        SetR("outletLiquidMassFlow", outletLiquidMassFlow);
        SetR("outletLiquidEnergyFlow", outletLiquidEnergyFlow);

        info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
