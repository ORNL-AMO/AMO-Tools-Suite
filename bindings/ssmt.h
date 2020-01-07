#ifndef AMO_TOOLS_SUITE_SSMT_H
#define AMO_TOOLS_SUITE_SSMT_H

#include "NanDataConverters.h"

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
#include "ssmt/HeatExchanger.h"
#include "ssmt/api/SteamModeler.h"
#include "steam/SteamModelerInputDataMapper.h"
#include "steam/SteamModelerOutputDataMapper.h"
#include <string>
#include <stdexcept>
#include <array>
#include <cmath>

SteamProperties::ThermodynamicQuantity thermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(getDouble("thermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity feedwaterThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(getDouble("feedwaterThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity waterThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(getDouble("waterThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity steamThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(getDouble("steamThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

NAN_METHOD(saturatedPressure) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    
    const double saturatedTemperature = getDouble("saturatedTemperature");

    SaturatedPressure sp(saturatedTemperature);
    setR("saturatedPressure", sp.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedTemperature) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double saturatedPressure = getDouble("saturatedPressure");

    SaturatedTemperature st(saturatedPressure);
    setR("saturatedTemperature", st.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenTemperature) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double saturatedTemperature = getDouble("saturatedTemperature");
    double const pressure = SaturatedPressure(saturatedTemperature).calculate();
    SteamSystemModelerTool::SaturatedPropertiesOutput const results = SaturatedProperties(pressure, saturatedTemperature).calculate();

    setR("saturatedPressure", results.pressure);
    setR("saturatedTemperature", results.temperature);
    setR("liquidEnthalpy", results.liquidSpecificEnthalpy);
    setR("gasEnthalpy", results.gasSpecificEnthalpy);
    setR("evaporationEnthalpy", results.evaporationSpecificEnthalpy);
    setR("liquidEntropy", results.liquidSpecificEntropy);
    setR("gasEntropy", results.gasSpecificEntropy);
    setR("evaporationEntropy", results.evaporationSpecificEntropy);
    setR("liquidVolume", results.liquidSpecificVolume);
    setR("gasVolume", results.gasSpecificVolume);
    setR("evaporationVolume", results.evaporationSpecificVolume);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenPressure) {

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double saturatedPressure = getDouble("saturatedPressure");
    double const temperature = SaturatedTemperature(saturatedPressure).calculate();
    SteamSystemModelerTool::SaturatedPropertiesOutput const results = SaturatedProperties(saturatedPressure, temperature).calculate();

    setR("saturatedPressure", results.pressure);
    setR("saturatedTemperature", results.temperature);
    setR("liquidEnthalpy", results.liquidSpecificEnthalpy);
    setR("gasEnthalpy", results.gasSpecificEnthalpy);
    setR("evaporationEnthalpy", results.evaporationSpecificEnthalpy);
    setR("liquidEntropy", results.liquidSpecificEntropy);
    setR("gasEntropy", results.gasSpecificEntropy);
    setR("evaporationEntropy", results.evaporationSpecificEntropy);
    setR("liquidVolume", results.liquidSpecificVolume);
    setR("gasVolume", results.gasSpecificVolume);
    setR("evaporationVolume", results.evaporationSpecificVolume);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(steamProperties) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double pressure = getDouble("pressure");
    const double quantityValue = getDouble("quantityValue");

    try {
        SteamProperties::ThermodynamicQuantity quantity = thermodynamicQuantity();
        SteamSystemModelerTool::SteamPropertiesOutput const results = SteamProperties(pressure, quantity, quantityValue).calculate();

        setR("pressure", results.pressure);
        setR("temperature", results.temperature);
        setR("specificEnthalpy", results.specificEnthalpy);
        setR("specificEntropy", results.specificEntropy);
        setR("quality", results.quality);
        setR("specificVolume", results.specificVolume);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in steamProperties - ssmt.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}

NAN_METHOD(boiler) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double deaeratorPressure = getDouble("deaeratorPressure");
    const double combustionEfficiency = getDouble("combustionEfficiency");
    const double blowdownRate = getDouble("blowdownRate");
    const double steamPressure = getDouble("steamPressure");
    const double quantityValue = getDouble("quantityValue");
    const double steamMassFlow = getDouble("steamMassFlow");
    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

        Boiler const b = Boiler(deaeratorPressure, combustionEfficiency,
                              blowdownRate, steamPressure, quantityType, quantityValue,
                              steamMassFlow);

        SteamSystemModelerTool::FluidProperties const results = b.getSteamProperties();
        setR("steamPressure", results.pressure);
        setR("steamTemperature", results.temperature);
        setR("steamSpecificEnthalpy", results.specificEnthalpy);
        setR("steamSpecificEntropy", results.specificEntropy);
        setR("steamQuality", results.quality);
        setR("steamMassFlow", results.massFlow);
        setR("steamEnergyFlow", results.energyFlow);

        SteamSystemModelerTool::FluidProperties const results2 = b.getBlowdownProperties();
        setR("blowdownPressure", results2.pressure);
        setR("blowdownTemperature", results2.temperature);
        setR("blowdownSpecificEnthalpy", results2.specificEnthalpy);
        setR("blowdownSpecificEntropy", results2.specificEntropy);
        setR("blowdownQuality", results2.quality);
        setR("blowdownMassFlow", results2.massFlow);
        setR("blowdownEnergyFlow", results2.energyFlow);

        SteamSystemModelerTool::FluidProperties const results3 = b.getFeedwaterProperties();
        setR("feedwaterPressure", results3.pressure);
        setR("feedwaterTemperature", results3.temperature);
        setR("feedwaterSpecificEnthalpy", results3.specificEnthalpy);
        setR("feedwaterSpecificEntropy", results3.specificEntropy);
        setR("feedwaterQuality", results3.quality);
        setR("feedwaterMassFlow", results3.massFlow);
        setR("feedwaterEnergyFlow", results3.energyFlow);
        setR("boilerEnergy", b.getBoilerEnergy());
        setR("fuelEnergy", b.getFuelEnergy());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in boiler - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(heatLoss) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

   const double inletPressure = getDouble("inletPressure");
   const double quantityValue = getDouble("quantityValue");
   const double inletMassFlow = getDouble("inletMassFlow");
   const double percentHeatLoss = getDouble("percentHeatLoss");
    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        HeatLoss const hl = HeatLoss(inletPressure, quantityType, quantityValue,
                                 inletMassFlow, percentHeatLoss);

        SteamSystemModelerTool::FluidProperties const results = hl.getInletProperties();

        setR("inletPressure", results.pressure);
        setR("inletTemperature", results.temperature);
        setR("inletSpecificEnthalpy", results.specificEnthalpy);
        setR("inletSpecificEntropy", results.specificEntropy);
        setR("inletQuality", results.quality);
        setR("inletMassFlow", results.massFlow);
        setR("inletEnergyFlow", results.energyFlow);

        SteamSystemModelerTool::FluidProperties const results2 = hl.getOutletProperties();
        setR("outletPressure", results2.pressure);
        setR("outletTemperature", results2.temperature);
        setR("outletSpecificEnthalpy", results2.specificEnthalpy);
        setR("outletSpecificEntropy", results2.specificEntropy);
        setR("outletQuality", results2.quality);
        setR("outletMassFlow", results2.massFlow);
        setR("outletEnergyFlow", results2.energyFlow);
        setR("heatLoss", hl.getHeatLoss());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in heatLoss - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(flashTank) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
  
    const double inletWaterPressure = getDouble("inletWaterPressure");
    const double quantityValue = getDouble("quantityValue");
    const double inletWaterMassFlow = getDouble("inletWaterMassFlow");
    const double tankPressure = getDouble("tankPressure");

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

        FlashTank const ft = FlashTank(inletWaterPressure, quantityType, quantityValue,
                                  inletWaterMassFlow, tankPressure);

        SteamSystemModelerTool::FluidProperties const results = ft.getInletWaterProperties();
        setR("inletWaterPressure", results.pressure);
        setR("inletWaterTemperature", results.temperature);
        setR("inletWaterSpecificEnthalpy", results.specificEnthalpy);
        setR("inletWaterSpecificEntropy", results.specificEntropy);
        setR("inletWaterQuality", results.quality);
        setR("inletWaterMassFlow", results.massFlow);
        setR("inletWaterEnergyFlow", results.energyFlow);

        SteamSystemModelerTool::FluidProperties const results2 = ft.getOutletGasSaturatedProperties();
        setR("outletGasPressure", results2.pressure);
        setR("outletGasTemperature", results2.temperature);
        setR("outletGasSpecificEnthalpy", results2.specificEnthalpy);
        setR("outletGasSpecificEntropy", results2.specificEntropy);
        setR("outletGasQuality", 1);
        setR("outletGasMassFlow", results2.massFlow);
        setR("outletGasEnergyFlow", results2.energyFlow);

        SteamSystemModelerTool::FluidProperties const results3 = ft.getOutletLiquidSaturatedProperties();
        setR("outletLiquidPressure", results3.pressure);
        setR("outletLiquidTemperature", results3.temperature);
        setR("outletLiquidSpecificEnthalpy", results3.specificEnthalpy);
        setR("outletLiquidSpecificEntropy", results3.specificEntropy);
        setR("outletLiquidQuality", 0);
        setR("outletLiquidMassFlow", results3.massFlow);
        setR("outletLiquidEnergyFlow", results3.energyFlow);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in flashTank - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithoutDesuperheating) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double inletPressure = getDouble("inletPressure");
    const double quantityValue = getDouble("quantityValue");
    const double inletMassFlow = getDouble("inletMassFlow");
    const double outletPressure = getDouble("outletPressure");

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        PrvWithoutDesuperheating const pwod = PrvWithoutDesuperheating(inletPressure, quantityType, quantityValue,
                                                   inletMassFlow, outletPressure);

        SteamSystemModelerTool::SteamPropertiesOutput const results = pwod.getInletProperties();
        setR("inletPressure", results.pressure);
        setR("inletTemperature", results.temperature);
        setR("inletSpecificEnthalpy", results.specificEnthalpy);
        setR("inletSpecificEntropy", results.specificEntropy);
        setR("inletQuality", results.quality);
        setR("inletMassFlow", pwod.getInletMassFlow());
        setR("inletEnergyFlow", pwod.getInletEnergyFlow());

        SteamSystemModelerTool::SteamPropertiesOutput const results2 = pwod.getOutletProperties();
        setR("outletPressure", results2.pressure);
        setR("outletTemperature", results2.temperature);
        setR("outletSpecificEnthalpy", results2.specificEnthalpy);
        setR("outletSpecificEntropy", results2.specificEntropy);
        setR("outletQuality", results2.quality);
        setR("outletMassFlow", pwod.getOutletMassFlow());
        setR("outletEnergyFlow", pwod.getOutletEnergyFlow());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in prvWithoutDesuperheating - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithDesuperheating) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double inletPressure = getDouble("inletPressure");
    const double quantityValue = getDouble("quantityValue");
    const double inletMassFlow = getDouble("inletMassFlow");
    const double outletPressure = getDouble("outletPressure");
    const double feedwaterPressure = getDouble("feedwaterPressure");
    const double feedwaterQuantityValue = getDouble("feedwaterQuantityValue");
    const double desuperheatingTemp = getDouble("desuperheatingTemp");

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        SteamProperties::ThermodynamicQuantity feedwaterQuantityType = feedwaterThermodynamicQuantity();

        PrvWithDesuperheating const pwd = PrvWithDesuperheating(inletPressure, quantityType, quantityValue,
                                               inletMassFlow, outletPressure, feedwaterPressure,
                                               feedwaterQuantityType, feedwaterQuantityValue, desuperheatingTemp);

        SteamSystemModelerTool::SteamPropertiesOutput const results = pwd.getInletProperties();
        setR("inletPressure", results.pressure);
        setR("inletTemperature", results.temperature);
        setR("inletSpecificEnthalpy", results.specificEnthalpy);
        setR("inletSpecificEntropy", results.specificEntropy);
        setR("inletQuality", results.quality);
        setR("inletMassFlow", pwd.getInletMassFlow());
        setR("inletEnergyFlow", pwd.getInletEnergyFlow());

        SteamSystemModelerTool::SteamPropertiesOutput const results2 = pwd.getOutletProperties();
        setR("outletPressure", results2.pressure);
        setR("outletTemperature", results2.temperature);
        setR("outletSpecificEnthalpy", results2.specificEnthalpy);
        setR("outletSpecificEntropy", results2.specificEntropy);
        setR("outletQuality", results2.quality);
        setR("outletMassFlow", pwd.getOutletMassFlow());
        setR("outletEnergyFlow", pwd.getOutletEnergyFlow());

        SteamSystemModelerTool::SteamPropertiesOutput const results3 = pwd.getFeedwaterProperties();
        setR("feedwaterPressure", results3.pressure);
        setR("feedwaterTemperature", results3.temperature);
        setR("feedwaterSpecificEnthalpy", results3.specificEnthalpy);
        setR("feedwaterSpecificEntropy", results3.specificEntropy);
        setR("feedwaterQuality", results3.quality);
        setR("feedwaterMassFlow", pwd.getFeedwaterMassFlow());
        setR("feedwaterEnergyFlow", pwd.getFeedwaterEnergyFlow());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in prvWithDesuperheating - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(deaerator) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double deaeratorPressure = getDouble("deaeratorPressure");
    const double ventRate = getDouble("ventRate");
    const double feedwaterMassFlow =  getDouble("feedwaterMassFlow");
    const double waterPressure = getDouble("waterPressure");
    const double waterQuantityValue = getDouble("waterQuantityValue");
    const double steamPressure = getDouble("steamPressure");
    const double steamQuantityValue = getDouble("steamQuantityValue");
    try {
        SteamProperties::ThermodynamicQuantity waterQuantityType = waterThermodynamicQuantity();
        SteamProperties::ThermodynamicQuantity steamQuantityType = steamThermodynamicQuantity();

        Deaerator d(deaeratorPressure, ventRate, feedwaterMassFlow,
                    waterPressure, waterQuantityType, waterQuantityValue,
                    steamPressure, steamQuantityType,
                    steamQuantityValue);

        SteamSystemModelerTool::FluidProperties const results = d.getFeedwaterProperties();
        setR("feedwaterPressure", results.pressure);
        setR("feedwaterTemperature", results.temperature);
        setR("feedwaterSpecificEnthalpy", results.specificEnthalpy);
        setR("feedwaterSpecificEntropy", results.specificEntropy);
        setR("feedwaterQuality", results.quality);
        setR("feedwaterMassFlow", results.massFlow);
        setR("feedwaterEnergyFlow", results.energyFlow);

        SteamSystemModelerTool::FluidProperties const results2 = d.getVentedSteamProperties();
        setR("ventedSteamPressure", results2.pressure);
        setR("ventedSteamTemperature", results2.temperature);
        setR("ventedSteamSpecificEnthalpy", results2.specificEnthalpy);
        setR("ventedSteamSpecificEntropy", results2.specificEntropy);
        setR("ventedSteamQuality", results2.quality);
        setR("ventedSteamMassFlow", results2.massFlow);
        setR("ventedSteamEnergyFlow", results2.energyFlow);

        SteamSystemModelerTool::FluidProperties const results3 = d.getInletWaterProperties();
        setR("inletWaterPressure", results3.pressure);
        setR("inletWaterTemperature", results3.temperature);
        setR("inletWaterSpecificEnthalpy", results3.specificEnthalpy);
        setR("inletWaterSpecificEntropy", results3.specificEntropy);
        setR("inletWaterQuality", results3.quality);
        setR("inletWaterMassFlow", results3.massFlow);
        setR("inletWaterEnergyFlow", results3.energyFlow);

        SteamSystemModelerTool::FluidProperties const results4 = d.getInletSteamProperties();
        setR("inletSteamPressure", results4.pressure);
        setR("inletSteamTemperature", results4.temperature);
        setR("inletSteamSpecificEnthalpy", results4.specificEnthalpy);
        setR("inletSteamSpecificEntropy", results4.specificEntropy);
        setR("inletSteamQuality", results4.quality);
        setR("inletSteamMassFlow", results4.massFlow);
        setR("inletSteamEnergyFlow", results4.energyFlow);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in deaerator - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(header) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    double const headerPressure = getDouble("headerPressure");

    Local<String> arrayStr = Nan::New<String>("inlets").ToLocalChecked();
    v8::Local<v8::Value> arrayTmp = Nan::Get(Nan::To<v8::Object>(inp).ToLocalChecked(), arrayStr).ToLocalChecked();
    v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(arrayTmp);

    Local<String> pressureStr = Nan::New<String>("pressure").ToLocalChecked();
    Local<String> temperatureStr = Nan::New<String>("temperature").ToLocalChecked();
    Local<String> qualityStr = Nan::New<String>("quality").ToLocalChecked();
    Local<String> massFlowStr = Nan::New<String>("massFlow").ToLocalChecked();
    Local<String> specificEnthalpyStr = Nan::New<String>("specificEnthalpy").ToLocalChecked();
    Local<String> specificEntropyStr = Nan::New<String>("specificEntropy").ToLocalChecked();
    Local<String> energyFlowStr = Nan::New<String>("energyFlow").ToLocalChecked();

    std::vector<Inlet> inlets;

    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

    for (std::size_t i = 0; i < arr->Length(); i++) {            
        double const pressure = Nan::To<double>(Nan::Get(Nan::To<v8::Object>(arr->Get(context, i).ToLocalChecked()).ToLocalChecked(), pressureStr).ToLocalChecked()).FromJust();
        unsigned val = static_cast<unsigned>(Nan::To<double>(Nan::Get(Nan::To<v8::Object>(arr->Get(context, i).ToLocalChecked()).ToLocalChecked(), Nan::New<String>("thermodynamicQuantity").ToLocalChecked()).ToLocalChecked()).FromJust());
        SteamProperties::ThermodynamicQuantity const quantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
        double const quantityValue = Nan::To<double>(Nan::Get(Nan::To<v8::Object>(arr->Get(context, i).ToLocalChecked()).ToLocalChecked(), Nan::New<String>("quantityValue").ToLocalChecked()).ToLocalChecked()).FromJust();
        double const massFlow = Nan::To<double>(Nan::Get(Nan::To<v8::Object>(arr->Get(context, i).ToLocalChecked()).ToLocalChecked(), massFlowStr).ToLocalChecked()).FromJust();

        inlets.emplace_back(Inlet(pressure, quantity, quantityValue, massFlow));

        Local<Object> obj = Nan::New<Object>();
        Local<String> inletNum = Nan::New<String>("inlet" + std::to_string(i + 1)).ToLocalChecked();
        SteamSystemModelerTool::SteamPropertiesOutput const inletProps = inlets[i].getInletProperties();

        Nan::Set(obj, pressureStr, Nan::New<Number>(inletProps.pressure));
        Nan::Set(obj, temperatureStr, Nan::New<Number>(inletProps.temperature));
        Nan::Set(obj, qualityStr, Nan::New<Number>(inletProps.quality));
        Nan::Set(obj, specificEnthalpyStr, Nan::New<Number>(inletProps.specificEnthalpy));
        Nan::Set(obj, specificEntropyStr, Nan::New<Number>(inletProps.specificEntropy));
        Nan::Set(obj, energyFlowStr, Nan::New<Number>(inlets[i].getInletEnergyFlow()));
        Nan::Set(obj, massFlowStr, Nan::New<Number>(inlets[i].getMassFlow()));

        Nan::Set(r, inletNum, obj);
    }

    try {
        Header header = Header(headerPressure, inlets);
        Local<String> headerStr = Nan::New<String>("header").ToLocalChecked();

        SteamSystemModelerTool::SteamPropertiesOutput const headerProps = header.getHeaderProperties();

        Local<Object> obj = Nan::New<Object>();

        Nan::Set(obj, pressureStr, Nan::New<Number>(header.getHeaderPressure()));
        Nan::Set(obj, temperatureStr, Nan::New<Number>(headerProps.temperature));
        Nan::Set(obj, qualityStr, Nan::New<Number>(headerProps.quality));
        Nan::Set(obj, specificEnthalpyStr, Nan::New<Number>(headerProps.specificEnthalpy));
        Nan::Set(obj, specificEntropyStr, Nan::New<Number>(headerProps.specificEntropy));
        Nan::Set(obj, energyFlowStr, Nan::New<Number>(header.getInletEnergyFlow()));
        Nan::Set(obj, massFlowStr, Nan::New<Number>(header.getInletMassFlow()));

        Nan::Set(r, headerStr, obj);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in header - ssmt.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}

NAN_METHOD(turbine) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double inletPressure = getDouble("inletPressure");
    const double inletQuantityValue = getDouble("inletQuantityValue");
    const double generatorEfficiency = getDouble("generatorEfficiency");
    const double massFlowOrPowerOut = getDouble("massFlowOrPowerOut");
    const double outletSteamPressure = getDouble("outletSteamPressure");

    unsigned val = static_cast<unsigned>(Nan::To<double>(Nan::Get(Nan::To<v8::Object>(inp).ToLocalChecked(), Nan::New<String>("solveFor").ToLocalChecked()).ToLocalChecked()).FromJust());

    Turbine::Solve solveFor = static_cast<Turbine::Solve>(val);
    val = static_cast<unsigned>(Nan::To<double>(Nan::Get(Nan::To<v8::Object>(inp).ToLocalChecked(), Nan::New<String>("turbineProperty").ToLocalChecked()).ToLocalChecked()).FromJust());

    Turbine::TurbineProperty turbineProperty = static_cast<Turbine::TurbineProperty>(val);
    val = static_cast<unsigned>(Nan::To<double>(Nan::Get(Nan::To<v8::Object>(inp).ToLocalChecked(), Nan::New<String>("inletQuantity").ToLocalChecked()).ToLocalChecked()).FromJust());

    SteamProperties::ThermodynamicQuantity inletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
    std::shared_ptr<Turbine> t;

    try {
        if (solveFor == Turbine::Solve::OutletProperties) {

	    const double isentropicEfficiency = getDouble("isentropicEfficiency");

            t = std::shared_ptr<Turbine>(
                    new Turbine(solveFor, inletPressure, inletQuantity, inletQuantityValue,
                                turbineProperty, isentropicEfficiency, generatorEfficiency,
                                massFlowOrPowerOut, outletSteamPressure));
        } else {

	const double outletQuantityValue = getDouble("outletQuantityValue");
            v8::Isolate *isolate = v8::Isolate::GetCurrent();
	        v8::Local<v8::Context> context = isolate->GetCurrentContext();
            unsigned val = static_cast<unsigned>(Nan::To<double>(Nan::Get(Nan::To<v8::Object>(inp).ToLocalChecked(), Nan::New<String>("outletQuantity").ToLocalChecked()).ToLocalChecked()).FromJust());
            SteamProperties::ThermodynamicQuantity const outletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
            t = std::shared_ptr<Turbine>(
                    new Turbine(solveFor, inletPressure, inletQuantity, inletQuantityValue,
                                turbineProperty, generatorEfficiency, massFlowOrPowerOut,
                                outletSteamPressure, outletQuantity, outletQuantityValue));
        }
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in turbine - ssmt.h: " + what).c_str());
    }

    SteamSystemModelerTool::SteamPropertiesOutput results = t->getInletProperties();
    setR("inletPressure", results.pressure);
    setR("inletTemperature", results.temperature);
    setR("inletSpecificEnthalpy", results.specificEnthalpy);
    setR("inletSpecificEntropy", results.specificEntropy);
    setR("inletQuality", results.quality);
    setR("inletEnergyFlow", t->getInletEnergyFlow());

    results = t->getOutletProperties();
    setR("outletPressure", results.pressure);
    setR("outletTemperature", results.temperature);
    setR("outletSpecificEnthalpy", results.specificEnthalpy);
    setR("outletSpecificEntropy", results.specificEntropy);
    setR("outletQuality", results.quality);
    setR("outletEnergyFlow", t->getOutletEnergyFlow());

    setR("massFlow", t->getMassFlow());
    setR("isentropicEfficiency", t->getIsentropicEfficiency());
    setR("energyOut", t->getEnergyOut());
    setR("powerOut", t->getPowerOut());
    setR("generatorEfficiency", t->getGeneratorEfficiency());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(heatExchanger) {
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double hotInletMassFlow = getDouble("hotInletMassFlow");
    const double hotInletEnergyFlow = getDouble("hotInletEnergyFlow");
    const double hotInletTemperature = getDouble("hotInletTemperature");
    const double hotInletPressure = getDouble("hotInletPressure");
    const double hotInletQuality = getDouble("hotInletQuality");
    const double hotInletSpecificVolume = getDouble("hotInletSpecificVolume");
    const double hotInletDensity = getDouble("hotInletDensity");
    const double hotInletSpecificEnthalpy = getDouble("hotInletSpecificEnthalpy");
    const double hotInletSpecificEntropy = getDouble("hotInletSpecificEntropy");

    const double coldInletMassFlow = getDouble("coldInletMassFlow");
    const double coldInletEnergyFlow = getDouble("coldInletEnergyFlow");
    const double coldInletTemperature = getDouble("coldInletTemperature");
    const double coldInletPressure = getDouble("coldInletPressure");
    const double coldInletQuality = getDouble("coldInletQuality");
    const double coldInletSpecificVolume = getDouble("coldInletSpecificVolume");
    const double coldInletDensity = getDouble("coldInletDensity");
    const double coldInletSpecificEnthalpy = getDouble("coldInletSpecificEnthalpy");
    const double coldInletSpecificEntropy = getDouble("coldInletSpecificEntropy");

    const double approachTemp = getDouble("approachTemp");

    const SteamSystemModelerTool::FluidProperties hotInlet(hotInletMassFlow, hotInletEnergyFlow, hotInletTemperature,
    hotInletPressure, hotInletQuality, hotInletSpecificVolume, hotInletDensity, hotInletSpecificEnthalpy,
    hotInletSpecificEntropy);

    const SteamSystemModelerTool::FluidProperties coldInlet(coldInletMassFlow, coldInletEnergyFlow, coldInletTemperature,
    coldInletPressure, coldInletQuality, coldInletSpecificVolume, coldInletDensity, coldInletSpecificEnthalpy,
    coldInletSpecificEntropy);

    HeatExchanger::Output const output = HeatExchanger(hotInlet, coldInlet, approachTemp).calculate();

    setR("hotOutletMassFlow", output.hotOutlet.massFlow);
    setR("hotOutletEnergyFlow", output.hotOutlet.energyFlow);
    setR("hotOutletTemperature", output.hotOutlet.temperature);
    setR("hotOutletPressure", output.hotOutlet.pressure);
    setR("hotOutletQuality", output.hotOutlet.quality);
    setR("hotOutletSpecificVolume", output.hotOutlet.specificVolume);
    setR("hotOutletDensity", output.hotOutlet.density);
    setR("hotOutletSpecificEnthalpy", output.hotOutlet.specificEnthalpy);
    setR("hotOutletSpecificEntropy", output.hotOutlet.specificEntropy);

    setR("coldOutletMassFlow", output.coldOutlet.massFlow);
    setR("coldOutletEnergyFlow", output.coldOutlet.energyFlow);
    setR("coldOutletTemperature", output.coldOutlet.temperature);
    setR("coldOutletPressure", output.coldOutlet.pressure);
    setR("coldOutletQuality", output.coldOutlet.quality);
    setR("coldOutletSpecificVolume", output.coldOutlet.specificVolume);
    setR("coldOutletDensity", output.coldOutlet.density);
    setR("coldOutletSpecificEnthalpy", output.coldOutlet.specificEnthalpy);
    setR("coldOutletSpecificEntropy", output.coldOutlet.specificEntropy);

    info.GetReturnValue().Set(r);
}

NAN_METHOD(steamModeler) {
    const std::string methodName = std::string("SteamModeler::") + std::string(__func__) + ": ";

    // std::cout << methodName << "begin: steam modeler" << std::endl;

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    info.GetReturnValue().Set(r);

    SteamModelerInputDataMapper inputDataMapper = SteamModelerInputDataMapper();
    SteamModeler steamModeler = SteamModeler();
    SteamModelerOutputDataMapper outputDataMapper = SteamModelerOutputDataMapper();

    // std::cout << methodName << "begin: input mapping" << std::endl;
    SteamModelerInput steamModelerInput = inputDataMapper.map();

    // catch C++ error and throw as JS error
    try {
        // std::cout << methodName << "begin: modeling" << std::endl;
        SteamModelerOutput steamModelerOutput = steamModeler.model(steamModelerInput);
        // std::cout << methodName << "begin: output mapping" << std::endl;
        outputDataMapper.map(steamModelerOutput);
    } catch (const std::runtime_error &e) {
        const std::string what = e.what();

        const HeaderInput &headerInput = steamModelerInput.getHeaderInput();
        const int headerCount = headerInput.getHeaderCount();

        const std::string failMsg =
                "ERROR calling SteamModeler: " + what + "; headerCount=" + std::to_string(headerCount);
        std::cout << methodName << failMsg << std::endl;

        Local<String> failMsgLocal = Nan::New<String>(failMsg).ToLocalChecked();
        ThrowError(failMsgLocal);
    }

    // std::cout << methodName << "end: steam modeler" << std::endl;
}

#endif //AMO_TOOLS_SUITE_SSMT_H
