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
#include <stdexcept>
#include <array>
#include <cmath>

using namespace Nan;
using namespace v8;

Local <Object> inp;
Local <Object> r;

Local <Value> GetValue(std::string const &name, Local <Object> sourceObject) {
    Local <String> localName = Nan::New<String>(name).ToLocalChecked();

    Local <Value> value = sourceObject->Get(localName);
    if (value->IsUndefined()) {
        ThrowTypeError(std::string("GetValue method in ssmt.h: " + name + " not present in source object").c_str());
    }
    return value;
}

double GetDouble(std::string const &name) {
    Local <Value> value = GetValue(name, inp);
    return value->NumberValue();
}

bool GetBool(std::string const &name) {
    Local <Value> value = GetValue(name, inp);
    return value->BooleanValue();
}

void SetR(std::string const &nm, double n) {
    Local <String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local <Number> getNum = Nan::New<Number>(n);
    Nan::Set(r, getName, getNum);
}

void SetRobject(std::string const &nm, double n, Local <Object> obj) {
    Local <String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local <Number> getNum = Nan::New<Number>(n);
    Nan::Set(obj, getName, getNum);
}

SteamProperties::ThermodynamicQuantity thermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(GetDouble("thermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity feedwaterThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(GetDouble("feedwaterThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity waterThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(GetDouble("waterThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

SteamProperties::ThermodynamicQuantity steamThermodynamicQuantity() {
    unsigned val = static_cast<unsigned>(GetDouble("steamThermodynamicQuantity"));
    return static_cast<SteamProperties::ThermodynamicQuantity>(val);
}

NAN_METHOD(steamPropertiesData) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();


    if (GetBool("wantEntropy")) {
        std::vector<std::array<double, 3>> results;
        auto const pressure = GetDouble("pressure");

        for (double entropy = 0; entropy < 10.000001; entropy += 0.1) {
            auto const sp = SteamProperties(pressure, SteamProperties::ThermodynamicQuantity::ENTROPY,
                                            entropy).calculate();
            if (std::isnan(sp.pressure) || std::isnan(sp.temperature) || std::isnan(sp.specificEntropy)
                || sp.pressure < 0 || sp.temperature < 0 || sp.specificEntropy < 0) {
                continue;
            }
            results.push_back({{sp.pressure, sp.temperature, sp.specificEntropy}});
        }

        Handle <Array> data = Array::New(v8::Isolate::GetCurrent(), results.size());
        for (std::size_t i = 0; i < results.size(); i++) {
            auto obj = Nan::New<Object>();
            SetRobject("pressure", results.at(i).at(0), obj);
            SetRobject("temperature", results.at(i).at(1), obj);
            SetRobject("entropy", results.at(i).at(2), obj);
            data->Set(i, obj);
        }
        Nan::Set(r, Nan::New<String>("results").ToLocalChecked(), data);
        info.GetReturnValue().Set(r);
    } else {
        std::vector<std::array<double, 4>> results;
        double const temperature = GetDouble("temperature");

        auto const iterate = [&results, temperature](double pressureStart, double pressureEnd, double pressureStep) {
            const double a = 0.000000001;
            for (auto pressure = pressureStart; pressure <= pressureEnd + a; pressure += pressureStep) {
                auto const sp = SteamProperties(pressure, SteamProperties::ThermodynamicQuantity::TEMPERATURE,
                                                temperature).calculate();
                if (std::isnan(sp.pressure) || std::isnan(sp.temperature) || std::isnan(sp.specificEnthalpy)
                    || std::isnan(sp.specificVolume) || sp.pressure < 0 || sp.temperature < 0
                    || sp.specificEnthalpy < 0 || sp.specificVolume < 0) {
                    continue;
                }
                results.push_back({{sp.pressure, sp.temperature, sp.specificEnthalpy, sp.specificVolume}});
            }
        };

        iterate(0.0005, 0.01, 0.0005);
        iterate(0.015, 0.1, 0.005);
        iterate(0.11, 0.5, 0.01);
        iterate(0.55, 1, 0.05);
        iterate(1.1, 5, 0.1);
        iterate(5.5, 10, 0.5);
        iterate(11, 25, 1);
        iterate(30, 100, 5);

        Handle <Array> data = Array::New(v8::Isolate::GetCurrent(), results.size());
        for (std::size_t i = 0; i < results.size(); i++) {
            auto obj = Nan::New<Object>();
            SetRobject("pressure", results.at(i).at(0), obj);
            SetRobject("temperature", results.at(i).at(1), obj);
            SetRobject("enthalpy", results.at(i).at(2), obj);
            SetRobject("volume", results.at(i).at(3), obj);
            data->Set(i, obj);
        }
        Nan::Set(r, Nan::New<String>("results").ToLocalChecked(), data);
        info.GetReturnValue().Set(r);
    }
}

NAN_METHOD(saturatedPressure) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedPressure sp(GetDouble("saturatedTemperature"));
    SetR("saturatedPressure", sp.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedTemperature) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    SaturatedTemperature st(GetDouble("saturatedPressure"));
    SetR("saturatedTemperature", st.calculate());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenTemperature) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    double const pressure = SaturatedPressure(GetDouble("saturatedTemperature")).calculate();
    auto const results = SaturatedProperties(pressure, GetDouble("saturatedTemperature")).calculate();

    SetR("saturatedPressure", results.pressure);
    SetR("saturatedTemperature", results.temperature);
    SetR("liquidEnthalpy", results.liquidSpecificEnthalpy);
    SetR("gasEnthalpy", results.gasSpecificEnthalpy);
    SetR("evaporationEnthalpy", results.evaporationSpecificEnthalpy);
    SetR("liquidEntropy", results.liquidSpecificEntropy);
    SetR("gasEntropy", results.gasSpecificEntropy);
    SetR("evaporationEntropy", results.evaporationSpecificEntropy);
    SetR("liquidVolume", results.liquidSpecificVolume);
    SetR("gasVolume", results.gasSpecificVolume);
    SetR("evaporationVolume", results.evaporationSpecificVolume);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(saturatedPropertiesGivenPressure) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    double const temperature = SaturatedTemperature(GetDouble("saturatedPressure")).calculate();
    auto const results = SaturatedProperties(GetDouble("saturatedPressure"), temperature).calculate();
    SetR("saturatedPressure", results.pressure);
    SetR("saturatedTemperature", results.temperature);
    SetR("liquidEnthalpy", results.liquidSpecificEnthalpy);
    SetR("gasEnthalpy", results.gasSpecificEnthalpy);
    SetR("evaporationEnthalpy", results.evaporationSpecificEnthalpy);
    SetR("liquidEntropy", results.liquidSpecificEntropy);
    SetR("gasEntropy", results.gasSpecificEntropy);
    SetR("evaporationEntropy", results.evaporationSpecificEntropy);
    SetR("liquidVolume", results.liquidSpecificVolume);
    SetR("gasVolume", results.gasSpecificVolume);
    SetR("evaporationVolume", results.evaporationSpecificVolume);
    info.GetReturnValue().Set(r);
}


NAN_METHOD(steamProperties) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantity = thermodynamicQuantity();
        auto const results = SteamProperties(GetDouble("pressure"), quantity, GetDouble("quantityValue")).calculate();
        SetR("pressure", results.pressure);
        SetR("temperature", results.temperature);
        SetR("specificEnthalpy", results.specificEnthalpy);
        SetR("specificEntropy", results.specificEntropy);
        SetR("quality", results.quality);
        SetR("specificVolume", results.specificVolume);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in steamProperties - ssmt.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}

NAN_METHOD(boiler) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

        auto const b = Boiler(GetDouble("deaeratorPressure"), GetDouble("combustionEfficiency"),
                              GetDouble("blowdownRate"),
                              GetDouble("steamPressure"), quantityType, GetDouble("quantityValue"),
                              GetDouble("steamMassFlow"));

        auto const results = b.getSteamProperties();
        SetR("steamPressure", results.pressure);
        SetR("steamTemperature", results.temperature);
        SetR("steamSpecificEnthalpy", results.specificEnthalpy);
        SetR("steamSpecificEntropy", results.specificEntropy);
        SetR("steamQuality", results.quality);
        SetR("steamMassFlow", results.massFlow);
        SetR("steamEnergyFlow", results.energyFlow);

        auto const results2 = b.getBlowdownProperties();
        SetR("blowdownPressure", results2.pressure);
        SetR("blowdownTemperature", results2.temperature);
        SetR("blowdownSpecificEnthalpy", results2.specificEnthalpy);
        SetR("blowdownSpecificEntropy", results2.specificEntropy);
        SetR("blowdownQuality", results2.quality);
        SetR("blowdownMassFlow", results2.massFlow);
        SetR("blowdownEnergyFlow", results2.energyFlow);

        auto const results3 = b.getFeedwaterProperties();
        SetR("feedwaterPressure", results3.pressure);
        SetR("feedwaterTemperature", results3.temperature);
        SetR("feedwaterSpecificEnthalpy", results3.specificEnthalpy);
        SetR("feedwaterSpecificEntropy", results3.specificEntropy);
        SetR("feedwaterQuality", results3.quality);
        SetR("feedwaterMassFlow", results3.massFlow);
        SetR("feedwaterEnergyFlow", results3.energyFlow);
        SetR("boilerEnergy", b.getBoilerEnergy());
        SetR("fuelEnergy", b.getFuelEnergy());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in boiler - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(heatLoss) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        auto const hl = HeatLoss(GetDouble("inletPressure"), quantityType, GetDouble("quantityValue"),
                                 GetDouble("inletMassFlow"),
                                 GetDouble("percentHeatLoss"));
        auto const results = hl.getInletProperties();

        SetR("inletPressure", results.pressure);
        SetR("inletTemperature", results.temperature);
        SetR("inletSpecificEnthalpy", results.specificEnthalpy);
        SetR("inletSpecificEntropy", results.specificEntropy);
        SetR("inletQuality", results.quality);
        SetR("inletMassFlow", results.massFlow);
        SetR("inletEnergyFlow", results.energyFlow);

        auto const results2 = hl.getOutletProperties();
        SetR("outletPressure", results2.pressure);
        SetR("outletTemperature", results2.temperature);
        SetR("outletSpecificEnthalpy", results2.specificEnthalpy);
        SetR("outletSpecificEntropy", results2.specificEntropy);
        SetR("outletQuality", results2.quality);
        SetR("outletMassFlow", results2.massFlow);
        SetR("outletEnergyFlow", results2.energyFlow);
        SetR("heatLoss", hl.getHeatLoss());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in heatLoss - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(flashTank) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();

        auto const ft = FlashTank(GetDouble("inletWaterPressure"), quantityType, GetDouble("quantityValue"),
                                  GetDouble("inletWaterMassFlow"), GetDouble("tankPressure"));

        auto const results = ft.getInletWaterProperties();
        SetR("inletWaterPressure", results.pressure);
        SetR("inletWaterTemperature", results.temperature);
        SetR("inletWaterSpecificEnthalpy", results.specificEnthalpy);
        SetR("inletWaterSpecificEntropy", results.specificEntropy);
        SetR("inletWaterQuality", results.quality);
        SetR("inletWaterMassFlow", results.massFlow);
        SetR("inletWaterEnergyFlow", results.energyFlow);

        auto const results2 = ft.getOutletGasSaturatedProperties();
        SetR("outletGasPressure", results2.pressure);
        SetR("outletGasTemperature", results2.temperature);
        SetR("outletGasSpecificEnthalpy", results2.specificEnthalpy);
        SetR("outletGasSpecificEntropy", results2.specificEntropy);
        SetR("outletGasQuality", 1);
        SetR("outletGasMassFlow", results2.massFlow);
        SetR("outletGasEnergyFlow", results2.energyFlow);

        auto const results3 = ft.getOutletLiquidSaturatedProperties();
        SetR("outletLiquidPressure", results3.pressure);
        SetR("outletLiquidTemperature", results3.temperature);
        SetR("outletLiquidSpecificEnthalpy", results3.specificEnthalpy);
        SetR("outletLiquidSpecificEntropy", results3.specificEntropy);
        SetR("outletLiquidQuality", 0);
        SetR("outletLiquidMassFlow", results3.massFlow);
        SetR("outletLiquidEnergyFlow", results3.energyFlow);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in flashTank - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithoutDesuperheating) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        auto const pwod = PrvWithoutDesuperheating(GetDouble("inletPressure"), quantityType, GetDouble("quantityValue"),
                                                   GetDouble("inletMassFlow"), GetDouble("outletPressure"));

        auto const results = pwod.getInletProperties();
        SetR("inletPressure", results.pressure);
        SetR("inletTemperature", results.temperature);
        SetR("inletSpecificEnthalpy", results.specificEnthalpy);
        SetR("inletSpecificEntropy", results.specificEntropy);
        SetR("inletQuality", results.quality);
        SetR("inletMassFlow", pwod.getInletMassFlow());
        SetR("inletEnergyFlow", pwod.getInletEnergyFlow());

        auto const results2 = pwod.getOutletProperties();
        SetR("outletPressure", results2.pressure);
        SetR("outletTemperature", results2.temperature);
        SetR("outletSpecificEnthalpy", results2.specificEnthalpy);
        SetR("outletSpecificEntropy", results2.specificEntropy);
        SetR("outletQuality", results2.quality);
        SetR("outletMassFlow", pwod.getOutletMassFlow());
        SetR("outletEnergyFlow", pwod.getOutletEnergyFlow());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in prvWithoutDesuperheating - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(prvWithDesuperheating) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity quantityType = thermodynamicQuantity();
        SteamProperties::ThermodynamicQuantity feedwaterQuantityType = feedwaterThermodynamicQuantity();

        auto const pwd = PrvWithDesuperheating(GetDouble("inletPressure"), quantityType, GetDouble("quantityValue"),
                                               GetDouble("inletMassFlow"),
                                               GetDouble("outletPressure"), GetDouble("feedwaterPressure"),
                                               feedwaterQuantityType,
                                               GetDouble("feedwaterQuantityValue"), GetDouble("desuperheatingTemp"));

        auto const results = pwd.getInletProperties();
        SetR("inletPressure", results.pressure);
        SetR("inletTemperature", results.temperature);
        SetR("inletSpecificEnthalpy", results.specificEnthalpy);
        SetR("inletSpecificEntropy", results.specificEntropy);
        SetR("inletQuality", results.quality);
        SetR("inletMassFlow", pwd.getInletMassFlow());
        SetR("inletEnergyFlow", pwd.getInletEnergyFlow());

        auto const results2 = pwd.getOutletProperties();
        SetR("outletPressure", results2.pressure);
        SetR("outletTemperature", results2.temperature);
        SetR("outletSpecificEnthalpy", results2.specificEnthalpy);
        SetR("outletSpecificEntropy", results2.specificEntropy);
        SetR("outletQuality", results2.quality);
        SetR("outletMassFlow", pwd.getOutletMassFlow());
        SetR("outletEnergyFlow", pwd.getOutletEnergyFlow());

        auto const results3 = pwd.getFeedwaterProperties();
        SetR("feedwaterPressure", results3.pressure);
        SetR("feedwaterTemperature", results3.temperature);
        SetR("feedwaterSpecificEnthalpy", results3.specificEnthalpy);
        SetR("feedwaterSpecificEntropy", results3.specificEntropy);
        SetR("feedwaterQuality", results3.quality);
        SetR("feedwaterMassFlow", pwd.getFeedwaterMassFlow());
        SetR("feedwaterEnergyFlow", pwd.getFeedwaterEnergyFlow());
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in prvWithDesuperheating - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(deaerator) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    try {
        SteamProperties::ThermodynamicQuantity waterQuantityType = waterThermodynamicQuantity();
        SteamProperties::ThermodynamicQuantity steamQuantityType = steamThermodynamicQuantity();

        Deaerator d(GetDouble("deaeratorPressure"), GetDouble("ventRate"), GetDouble("feedwaterMassFlow"),
                    GetDouble("waterPressure"),
                    waterQuantityType, GetDouble("waterQuantityValue"), GetDouble("steamPressure"), steamQuantityType,
                    GetDouble("steamQuantityValue"));

        auto const results = d.getFeedwaterProperties();
        SetR("feedwaterPressure", results.pressure);
        SetR("feedwaterTemperature", results.temperature);
        SetR("feedwaterSpecificEnthalpy", results.specificEnthalpy);
        SetR("feedwaterSpecificEntropy", results.specificEntropy);
        SetR("feedwaterQuality", results.quality);
        SetR("feedwaterMassFlow", results.massFlow);
        SetR("feedwaterEnergyFlow", results.energyFlow);

        auto const results2 = d.getVentedSteamProperties();
        SetR("ventedSteamPressure", results2.pressure);
        SetR("ventedSteamTemperature", results2.temperature);
        SetR("ventedSteamSpecificEnthalpy", results2.specificEnthalpy);
        SetR("ventedSteamSpecificEntropy", results2.specificEntropy);
        SetR("ventedSteamQuality", results2.quality);
        SetR("ventedSteamMassFlow", results2.massFlow);
        SetR("ventedSteamEnergyFlow", results2.energyFlow);

        auto const results3 = d.getInletWaterProperties();
        SetR("inletWaterPressure", results3.pressure);
        SetR("inletWaterTemperature", results3.temperature);
        SetR("inletWaterSpecificEnthalpy", results3.specificEnthalpy);
        SetR("inletWaterSpecificEntropy", results3.specificEntropy);
        SetR("inletWaterQuality", results3.quality);
        SetR("inletWaterMassFlow", results3.massFlow);
        SetR("inletWaterEnergyFlow", results3.energyFlow);

        auto const results4 = d.getInletSteamProperties();
        SetR("inletSteamPressure", results4.pressure);
        SetR("inletSteamTemperature", results4.temperature);
        SetR("inletSteamSpecificEnthalpy", results4.specificEnthalpy);
        SetR("inletSteamSpecificEntropy", results4.specificEntropy);
        SetR("inletSteamQuality", results4.quality);
        SetR("inletSteamMassFlow", results4.massFlow);
        SetR("inletSteamEnergyFlow", results4.energyFlow);
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in deaerator - ssmt.h: " + what).c_str());
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(header) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    auto const headerPressure = GetDouble("headerPressure");

    Local <String> arrayStr = Nan::New<String>("inlets").ToLocalChecked();
    auto array = inp->ToObject()->Get(arrayStr);
    v8::Local <v8::Array> arr = v8::Local<v8::Array>::Cast(array);

    auto pressureStr = Nan::New<String>("pressure").ToLocalChecked();
    auto temperatureStr = Nan::New<String>("temperature").ToLocalChecked();
    auto qualityStr = Nan::New<String>("quality").ToLocalChecked();
    auto massFlowStr = Nan::New<String>("massFlow").ToLocalChecked();
    auto specificEnthalpyStr = Nan::New<String>("specificEnthalpy").ToLocalChecked();
    auto specificEntropyStr = Nan::New<String>("specificEntropy").ToLocalChecked();
    auto energyFlowStr = Nan::New<String>("energyFlow").ToLocalChecked();

    std::vector<Inlet> inlets;

    for (std::size_t i = 0; i < arr->Length(); i++) {
        auto const pressure = arr->Get(i)->ToObject()->Get(pressureStr)->NumberValue();
        unsigned val = static_cast<unsigned>(arr->Get(i)->ToObject()->Get(
                Nan::New<String>("thermodynamicQuantity").ToLocalChecked())->NumberValue());
        auto const quantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
        auto const quantityValue = arr->Get(i)->ToObject()->Get(
                Nan::New<String>("quantityValue").ToLocalChecked())->NumberValue();
        auto const massFlow = arr->Get(i)->ToObject()->Get(massFlowStr)->NumberValue();
        inlets.emplace_back(Inlet(pressure, quantity, quantityValue, massFlow));

        Local <Object> obj = Nan::New<Object>();
        Local <String> inletNum = Nan::New<String>("inlet" + std::to_string(i + 1)).ToLocalChecked();
        auto const inletProps = inlets[i].getInletProperties();

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
        auto header = Header(headerPressure, inlets);
        Local <String> headerStr = Nan::New<String>("header").ToLocalChecked();

        auto const headerProps = header.getHeaderProperties();

        Local <Object> obj = Nan::New<Object>();

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
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    unsigned val = static_cast<unsigned>(inp->ToObject()->Get(
            Nan::New<String>("solveFor").ToLocalChecked())->NumberValue());
    Turbine::Solve solveFor = static_cast<Turbine::Solve>(val);
    val = static_cast<unsigned>(inp->ToObject()->Get(
            Nan::New<String>("turbineProperty").ToLocalChecked())->NumberValue());
    Turbine::TurbineProperty turbineProperty = static_cast<Turbine::TurbineProperty>(val);
    val = static_cast<unsigned>(inp->ToObject()->Get(
            Nan::New<String>("inletQuantity").ToLocalChecked())->NumberValue());
    SteamProperties::ThermodynamicQuantity inletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
    std::unique_ptr<Turbine> t;

    try {
        if (solveFor == Turbine::Solve::OutletProperties) {
            t = std::unique_ptr<Turbine>(
                    new Turbine(solveFor, GetDouble("inletPressure"), inletQuantity, GetDouble("inletQuantityValue"),
                                turbineProperty, GetDouble("isentropicEfficiency"), GetDouble("generatorEfficiency"),
                                GetDouble("massFlowOrPowerOut"), GetDouble("outletSteamPressure")));
        } else {
            unsigned val = static_cast<unsigned>(inp->ToObject()->Get(
                    Nan::New<String>("outletQuantity").ToLocalChecked())->NumberValue());
            auto const outletQuantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
            t = std::unique_ptr<Turbine>(
                    new Turbine(solveFor, GetDouble("inletPressure"), inletQuantity, GetDouble("inletQuantityValue"),
                                turbineProperty, GetDouble("generatorEfficiency"), GetDouble("massFlowOrPowerOut"),
                                GetDouble("outletSteamPressure"), outletQuantity, GetDouble("outletQuantityValue")));
        }
    } catch (std::runtime_error const &e) {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in turbine - ssmt.h: " + what).c_str());
    }

    auto results = t->getInletProperties();
    SetR("inletPressure", results.pressure);
    SetR("inletTemperature", results.temperature);
    SetR("inletSpecificEnthalpy", results.specificEnthalpy);
    SetR("inletSpecificEntropy", results.specificEntropy);
    SetR("inletQuality", results.quality);
    SetR("inletEnergyFlow", t->getInletEnergyFlow());

    results = t->getOutletProperties();
    SetR("outletPressure", results.pressure);
    SetR("outletTemperature", results.temperature);
    SetR("outletSpecificEnthalpy", results.specificEnthalpy);
    SetR("outletSpecificEntropy", results.specificEntropy);
    SetR("outletQuality", results.quality);
    SetR("outletEnergyFlow", t->getOutletEnergyFlow());

    SetR("massFlow", t->getMassFlow());
    SetR("isentropicEfficiency", t->getIsentropicEfficiency());
    SetR("energyOut", t->getEnergyOut());
    SetR("powerOut", t->getPowerOut());
    SetR("generatorEfficiency", t->getGeneratorEfficiency());
    info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_SSMT_H
