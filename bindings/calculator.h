// #ifndef AMO_TOOLS_SUITE_CALCULATOR_H
// #define AMO_TOOLS_SUITE_CALCULATOR_H

#include <nan.h>
#include <node.h>
#include <string>
#include <stdexcept>
#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include "calculator/util/ElectricityReduction.h"
#include "calculator/util/NaturalGasReduction.h"
#include "calculator/util/CompressedAirReduction.h"
#include "calculator/util/CompressedAirPressureReduction.h"
#include "calculator/util/WaterReduction.h"
#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include "calculator/util/insulation/pipes/InsulatedPipeCalculator.h"
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"
#include "calculator/util/insulation/tanks/InsulatedTankInput.h"
#include "calculator/util/insulation/tanks/InsulatedTankCalculator.h"
#include "calculator/util/insulation/tanks/InsulatedTankOutput.h"

#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "calculator/util/SteamReduction.h"
#include "calculator/util/Conversion.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

// double Get(std::string const &key)
// {
//     Local<String> getName = Nan::New<String>(key).ToLocalChecked();
//     auto rObj = Nan::To<Object>(inp).ToLocalChecked()->Get(GetCurrent(), getName);
//     if (rObj->IsUndefined())
//     {
//         ThrowTypeError(std::string("Get method in calculator.h: " + key + " not present in object").c_str());
//     }
//     return Nan::To<double>(rObj).FromJust();
// }

double GetDouble(std::string const &key, Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetDouble method in calculator.h: " + key + " not present in object").c_str());
    }
    return Nan::To<double>(rObj).FromJust();
}

std::vector<double> GetVector(std::string const &key, Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("GetVector method in calculator.h: " + key + " not present in object").c_str());
    }
    Local<Array> jsArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<double> array;
    for (unsigned int i = 0; i < jsArray->Length(); i++)
    {
        v8::Local<v8::Value> jsElement = jsArray->Get(context, i).ToLocalChecked();
        double val = Nan::To<double>(jsElement).FromJust();
        array.push_back(val);
    }
    return array;
}

template <typename T>
T GetEnumVal(std::string const &key, Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetEnumVal method in calculator.h: Enum value " + key + " not present in object").c_str());
    }
    return static_cast<T>(Nan::To<double>(rObj).FromJust());
}

bool GetBool(std::string const &key, Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetBool method in calculator.h: Boolean value " + key + " not present in object").c_str());
    }
    return rObj->BooleanValue(context).ToChecked();
}

std::string GetStr(std::string const &key, Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetStr method in calculator.h: String " + key + " not present in object").c_str());
    }
    v8::String::Utf8Value s(isolate, rObj);
    return std::string(*s);
}

//NAN function for checking if an object parameter has been defined with a value
bool isDefined(Local<Object> obj, std::string const &key)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(key).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    return !rObj->IsUndefined();
}

//NAN function for binding DOUBLE data to anonymous object
inline void SetR(const std::string &key, double val)
{
    Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}

// ============== Electricity Reduction ==============

MultimeterData getMultimeterData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("multimeterData").ToLocalChecked();
    Local<Object> multimeterDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (multimeterDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("ElectricityReduction: getMultimeterData method in calculator.h: multimeterData not present in object").c_str());
    }
    int numberOfPhases = static_cast<int>(GetDouble("numberOfPhases", multimeterDataV8));
    double supplyVoltage = GetDouble("supplyVoltage", multimeterDataV8);
    double averageCurrent = GetDouble("averageCurrent", multimeterDataV8);
    double powerFactor = GetDouble("powerFactor", multimeterDataV8);
    return {
        numberOfPhases,
        supplyVoltage,
        averageCurrent,
        powerFactor
    };
}

NameplateData getNameplateData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("nameplateData").ToLocalChecked();
    Local<Object> nameplateDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (nameplateDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("ElectricityReduction: getNameplateData method in calculator.h: nameplateData not present in object").c_str());
    }
    double ratedMotorPower = GetDouble("ratedMotorPower", nameplateDataV8);
    bool variableSpeedMotor = GetBool("variableSpeedMotor", nameplateDataV8);
    double operationalFrequency = GetDouble("operationalFrequency", nameplateDataV8);
    double lineFrequency = GetDouble("lineFrequency", nameplateDataV8);
    double motorAndDriveEfficiency = GetDouble("motorAndDriveEfficiency", nameplateDataV8);
    double loadFactor = GetDouble("loadFactor", nameplateDataV8);
    return {
        ratedMotorPower,
        variableSpeedMotor,
        operationalFrequency,
        lineFrequency,
        motorAndDriveEfficiency,
        loadFactor
    };
}

PowerMeterData getPowerMeterData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("powerMeterData").ToLocalChecked();
    Local<Object> powerMeterDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (powerMeterDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("ElectricityReduction: getPowerMeterData method in calculator.h: powerMeterData not present in object").c_str());
    }
    double power = GetDouble("power", powerMeterDataV8);
    return {power};
}

OtherMethodData getOtherMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("otherMethodData").ToLocalChecked();
    Local<Object> otherMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (otherMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("ElectricityReduction: getOtherMethodData method in calculator.h: otherMethodData not present in object").c_str());
    }
    double energy = GetDouble("energy", otherMethodDataV8);
    return {energy};
}

ElectricityReductionInput constructElectricityReductionInput(Local<Object> obj)
{
    int operatingHours = static_cast<int>(GetDouble("operatingHours", obj));
    double electricityCost = GetDouble("electricityCost", obj);
    int measurementMethod = static_cast<int>(GetDouble("measurementMethod", obj));
    MultimeterData multimeterData = getMultimeterData(obj);
    NameplateData nameplateData = getNameplateData(obj);
    PowerMeterData powerMeterData = getPowerMeterData(obj);
    OtherMethodData otherMethodData = getOtherMethodData(obj);
    int units = static_cast<int>(GetDouble("units", obj));
    return {
        operatingHours,
        electricityCost,
        measurementMethod,
        multimeterData,
        nameplateData,
        powerMeterData,
        otherMethodData,
        units
    };
}

std::vector<ElectricityReductionInput> getElectricityReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("electricityReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("ElectricityReduction: getElectricityReductionInputVector method in calculator.h: electricityReductionInputVec not present in object").c_str());
    }
    Local<Array> electricityReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<ElectricityReductionInput> inputVec;
    for (std::size_t i = 0; i < electricityReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructElectricityReductionInput(Nan::To<Object>(electricityReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(electricityReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<ElectricityReductionInput> inputVec = getElectricityReductionInputVec();
        ElectricityReduction::Output rv = ElectricityReduction(inputVec).calculate();
        SetR("energyUse", rv.energyUse);
        SetR("energyCost", rv.energyCost);
        SetR("power", rv.power);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in electricityReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}
// ============== END Electricity Reduction ==============

// ============== Natural Gas ==============

FlowMeterMethodData getFlowMeterMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("flowMeterMethodData").ToLocalChecked();
    Local<Object> flowMeterMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (flowMeterMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getFlowMeterMethodData method in calculator.h: flowMeterMethodData not present in object").c_str());
    }
    double flowRate = GetDouble("flowRate", flowMeterMethodDataV8);
    return {flowRate};
}

AirMassFlowMeasuredData getAirMassFlowMeasuredData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("airMassFlowMeasuredData").ToLocalChecked();
    Local<Object> airMassFlowMeasuredDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (airMassFlowMeasuredDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getAirMassFlowMeasuredData method in calculator.h: airMassFlowMeasuredData not present in object").c_str());
    }
    double areaOfDuct = GetDouble("areaOfDuct", airMassFlowMeasuredDataV8);
    double airVelocity = GetDouble("airVelocity", airMassFlowMeasuredDataV8);
    return {
        areaOfDuct,
        airVelocity
    };
}

AirMassFlowNameplateData getAirMassFlowNameplateData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("airMassFlowNameplateData").ToLocalChecked();
    Local<Object> airMassFlowNameplateDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (airMassFlowNameplateDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getAirMassFlowNameplateData method in calculator.h: airMassFlowNameplateData not present in object").c_str());
    }
    double airFlow = GetDouble("airFlow", airMassFlowNameplateDataV8);
    return {
        airFlow
    };
}

AirMassFlowData getAirMassFlowData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("airMassFlowData").ToLocalChecked();
    Local<Object> airMassFlowDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (airMassFlowDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getAirMassFlowData method in calculator.h: airMassFlowData not present in object").c_str());
    }
    bool isNameplate = GetBool("isNameplate", airMassFlowDataV8);
    AirMassFlowMeasuredData measuredData = getAirMassFlowMeasuredData(airMassFlowDataV8);
    AirMassFlowNameplateData nameplateData = getAirMassFlowNameplateData(airMassFlowDataV8);
    double inletTemperature = GetDouble("inletTemperature", airMassFlowDataV8);
    double outletTemperature = GetDouble("outletTemperature", airMassFlowDataV8);
    double systemEfficiency = Conversion(GetDouble("systemEfficiency", airMassFlowDataV8)).percentToFraction();
    return {
        isNameplate,
        measuredData,
        nameplateData,
        inletTemperature,
        outletTemperature,
        systemEfficiency
    };
}

WaterMassFlowData getWaterMassFlowData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("waterMassFlowData").ToLocalChecked();
    Local<Object> waterMassFlowDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (waterMassFlowDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getWaterMassFlowData method in calculator.h: waterMassFlowData not present in object").c_str());
    }
    double waterFlow = GetDouble("waterFlow", waterMassFlowDataV8);
    double inletTemperature = GetDouble("inletTemperature", waterMassFlowDataV8);
    double outletTemperature = GetDouble("outletTemperature", waterMassFlowDataV8);
    double systemEfficiency = Conversion(GetDouble("systemEfficiency", waterMassFlowDataV8)).percentToFraction();
    return {
        waterFlow,
        inletTemperature,
        outletTemperature,
        systemEfficiency
    };
}

NaturalGasOtherMethodData naturalGasGetOtherMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("otherMethodData").ToLocalChecked();
    Local<Object> otherMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (otherMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: naturalGasGetOtherMethodData method in calculator.h: otherMethodData not present in object").c_str());
    }
    double consumption = GetDouble("consumption", otherMethodDataV8);
    return {
        consumption};
}

NaturalGasReductionInput constructNaturalGasReductionInput(Local<Object> obj)
{
    int operatingHours = static_cast<int>(GetDouble("operatingHours", obj));
    double fuelCost = GetDouble("fuelCost", obj);
    int measurementMethod = static_cast<int>(GetDouble("measurementMethod", obj));
    FlowMeterMethodData flowMeterMethodData = getFlowMeterMethodData(obj);
    NaturalGasOtherMethodData otherMethodData = naturalGasGetOtherMethodData(obj);
    AirMassFlowData airMassFlowData = getAirMassFlowData(obj);
    WaterMassFlowData waterMassFlowData = getWaterMassFlowData(obj);
    int units = static_cast<int>(GetDouble("units", obj));
    return {
        operatingHours,
        fuelCost,
        measurementMethod,
        flowMeterMethodData,
        otherMethodData,
        airMassFlowData,
        waterMassFlowData,
        units};
}

std::vector<NaturalGasReductionInput> getNaturalGasReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("naturalGasReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("NaturalGasReduction: getNaturalGasReductionInputVector method in calculator.h: naturalGasReductionInputVec not present in object").c_str());
    }
    Local<Array> naturalGasReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<NaturalGasReductionInput> inputVec;
    for (std::size_t i = 0; i < naturalGasReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructNaturalGasReductionInput(Nan::To<Object>(naturalGasReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(naturalGasReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<NaturalGasReductionInput> inputVec = getNaturalGasReductionInputVec();
        NaturalGasReduction::Output rv = NaturalGasReduction(inputVec).calculate();
        SetR("energyUse", rv.energyUse);
        SetR("energyCost", rv.energyCost);
        SetR("heatFlow", rv.heatFlow);
        SetR("totalFlow", rv.totalFlow);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in naturalGasReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}
// ============== END Natural Gas ==============

// ============== Compressed Air ==============

CompressedAirFlowMeterMethodData getCompressedAirFlowMeterMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("flowMeterMethodData").ToLocalChecked();
    Local<Object> flowMeterMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (flowMeterMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getCompressedAirFlowMeterMethodData method in calculator.h: flowMeterMethodData not present in object").c_str());
    }
    double meterReading = GetDouble("meterReading", flowMeterMethodDataV8);
    return {meterReading};
}

BagMethodData getBagMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("bagMethodData").ToLocalChecked();
    Local<Object> bagMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (bagMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getBagMethodData method in calculator.h: bagMethodData not present in object").c_str());
    }
    double height = GetDouble("height", bagMethodDataV8);
    double diameter = GetDouble("diameter", bagMethodDataV8);
    double fillTime = GetDouble("fillTime", bagMethodDataV8);
    return {
        height,
        diameter,
        fillTime};
}

PressureMethodData getPressureMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("pressureMethodData").ToLocalChecked();
    Local<Object> pressureMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (pressureMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getPressureMethodData method in calculator.h: pressureMethodData not present in object").c_str());
    }
    int nozzleType = static_cast<int>(GetDouble("nozzleType", pressureMethodDataV8));
    int numberOfNozzles = static_cast<int>(GetDouble("numberOfNozzles", pressureMethodDataV8));
    double supplyPressure = GetDouble("supplyPressure", pressureMethodDataV8);
    return {
        nozzleType,
        numberOfNozzles,
        supplyPressure};
}

CompressedAirOtherMethodData getCompressedAirOtherMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("otherMethodData").ToLocalChecked();
    Local<Object> otherMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (otherMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getCompressedAirOtherMethodData method in calculator.h: otherMethodData not present in object").c_str());
    }
    double consumption = GetDouble("consumption", otherMethodDataV8);
    return {consumption};
}

OrificeMethodData getOrificeMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("orificeMethodData").ToLocalChecked();
    Local<Object> orificeMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (orificeMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getOrificeMethodData method in calculator.h: orificeMethodData not present in object").c_str());
    }
    double airTemp = GetDouble("compressorAirTemp", orificeMethodDataV8);
    double atmPressure = GetDouble("atmosphericPressure", orificeMethodDataV8);
    double dischargeCoef = GetDouble("dischargeCoefficient", orificeMethodDataV8);
    double diameter = GetDouble("orificeDiameter", orificeMethodDataV8);
    double supplyPressure = GetDouble("supplyPressure", orificeMethodDataV8);
    int numOrifices = static_cast<int>(GetDouble("numberOfOrifices", orificeMethodDataV8));
    return {
        airTemp,
        atmPressure,
        dischargeCoef,
        diameter,
        supplyPressure,
        numOrifices};
}

DecibelsMethodData getDecibelsMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("decibelsMethodData").ToLocalChecked();
    Local<Object> decibelsMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (decibelsMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getDecibelsMethodData method in calculator.h: decibelsMethodData not present in object").c_str());
    }
    double linePressure = GetDouble("linePressure", decibelsMethodDataV8);
    double decibels = GetDouble("decibels", decibelsMethodDataV8);
    double decibelRatingA = GetDouble("decibelRatingA", decibelsMethodDataV8);
    double pressureA = GetDouble("pressureA", decibelsMethodDataV8);
    double firstFlowA = GetDouble("firstFlowA", decibelsMethodDataV8);
    double secondFlowA = GetDouble("secondFlowA", decibelsMethodDataV8);
    double decibelRatingB = GetDouble("decibelRatingB", decibelsMethodDataV8);
    double pressureB = GetDouble("pressureB", decibelsMethodDataV8);
    double firstFlowB = GetDouble("firstFlowB", decibelsMethodDataV8);
    double secondFlowB = GetDouble("secondFlowB", decibelsMethodDataV8);
    return {
        linePressure,
        decibels,
        decibelRatingA,
        pressureA,
        firstFlowA,
        secondFlowA,
        decibelRatingB,
        pressureB,
        firstFlowB,
        secondFlowB};
}

EstimateMethodData getEstimateMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("estimateMethodData").ToLocalChecked();
    Local<Object> estimateMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (estimateMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getEstimateMethodData method in calculator.h: estimateMethodData not present in object").c_str());
    }
    double leakRateEstimate = GetDouble("leakRateEstimate", estimateMethodDataV8);
    return {
        leakRateEstimate};
}

CompressorElectricityData getCompressorElectricityData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("compressorElectricityData").ToLocalChecked();
    Local<Object> compressorElectricityDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (compressorElectricityDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getCompressorElectricityData method in calculator.h: compressorElectricityData not present in object").c_str());
    }
    double compressorControlAdjustment = Conversion(GetDouble("compressorControlAdjustment", compressorElectricityDataV8)).percentToFraction();
    //double compressorControlAdjustment = GetDouble("compressorControlAdjustment", compressorElectricityDataV8);
    double compressorSpecificPower = GetDouble("compressorSpecificPower", compressorElectricityDataV8);
    return {
        compressorControlAdjustment,
        compressorSpecificPower};
}

CompressedAirReductionInput constructCompressedAirReductionInput(Local<Object> obj)
{
    int hoursPerYear = static_cast<int>(GetDouble("hoursPerYear", obj));
    int utilityType = static_cast<int>(GetDouble("utilityType", obj));
    double utilityCost = GetDouble("utilityCost", obj);
    int measurementMethod = static_cast<int>(GetDouble("measurementMethod", obj));
    CompressedAirFlowMeterMethodData airFlowData = getCompressedAirFlowMeterMethodData(obj);
    BagMethodData bagMethodData = getBagMethodData(obj);
    PressureMethodData pressureMethodData = getPressureMethodData(obj);
    CompressedAirOtherMethodData otherMethodData = getCompressedAirOtherMethodData(obj);
    OrificeMethodData orificeMethodData = getOrificeMethodData(obj);
    DecibelsMethodData decibelsMethodData = getDecibelsMethodData(obj);
    EstimateMethodData estimateMethodData = getEstimateMethodData(obj);
    CompressorElectricityData electricityData = getCompressorElectricityData(obj);
    int units = static_cast<int>(GetDouble("units", obj));
    return {
        hoursPerYear,
        utilityType,
        utilityCost,
        measurementMethod,
        airFlowData,
        bagMethodData,
        pressureMethodData,
        otherMethodData,
        orificeMethodData,
        decibelsMethodData,
        estimateMethodData,
        electricityData,
        units};
}

std::vector<CompressedAirReductionInput> getCompressedAirReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("compressedAirReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirReduction: getCompressedAirReductionInputVec method in calculator.h: compressedAirReductionInputVec not present in object").c_str());
    }
    Local<Array> compressedAirReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<CompressedAirReductionInput> inputVec;
    for (std::size_t i = 0; i < compressedAirReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructCompressedAirReductionInput(Nan::To<Object>(compressedAirReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(compressedAirReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<CompressedAirReductionInput> inputVec = getCompressedAirReductionInputVec();
        CompressedAirReduction::Output rv = CompressedAirReduction(inputVec).calculate();
        SetR("energyUse", rv.energyUse);
        SetR("energyCost", rv.energyCost);
        SetR("flowRate", rv.flowRate);
        SetR("singleNozzleFlowRate", rv.singleNozzleFlowRate);
        SetR("consumption", rv.consumption);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in compressedAirReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}

// ========== END Compressed Air ==============

// ========== Start Water Reduction ===========

MeteredFlowMethodData getMeteredFlowMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("meteredFlowMethodData").ToLocalChecked();
    Local<Object> meteredFlowMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (meteredFlowMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("WaterReduction: getMeteredFlowMethodData method in calculator.h: meteredFlowMethodData not present in object").c_str());
    }
    double meterReading = GetDouble("meterReading", meteredFlowMethodDataV8);
    return {meterReading};
}

VolumeMeterMethodData getVolumeMeterMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("volumeMeterMethodData").ToLocalChecked();
    Local<Object> volumeMeterMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (volumeMeterMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("WaterReduction: getVolumeMeterMethodData method in calculator.h: volumeMeterMethodData not present in object").c_str());
    }
    double finalMeterReading = GetDouble("finalMeterReading", volumeMeterMethodDataV8);
    double initialMeterReading = GetDouble("initialMeterReading", volumeMeterMethodDataV8);
    double elapsedTime = GetDouble("elapsedTime", volumeMeterMethodDataV8);
    return {
        finalMeterReading,
        initialMeterReading,
        elapsedTime};
}

BucketMethodData getBucketMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("bucketMethodData").ToLocalChecked();
    Local<Object> bucketMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (bucketMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("WaterReduction: getBucketMethodData method in calculator.h: bucketMethodData not present in object").c_str());
    }
    double bucketVolume = GetDouble("bucketVolume", bucketMethodDataV8);
    double bucketFillTime = GetDouble("bucketFillTime", bucketMethodDataV8);
    return {
        bucketVolume,
        bucketFillTime};
}

WaterOtherMethodData getWaterOtherMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("otherMethodData").ToLocalChecked();
    Local<Object> otherMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (otherMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("WaterReduction: getWaterOtherMethodData method in calculator.h: otherMethodData not present in object").c_str());
    }
    double consumption = GetDouble("consumption", otherMethodDataV8);
    return {
        consumption};
}

WaterReductionInput constructWaterReductionInput(Local<Object> obj)
{
    int hoursPerYear = static_cast<int>(GetDouble("hoursPerYear", obj));
    double waterCost = GetDouble("waterCost", obj);
    int measurementMethod = static_cast<int>(GetDouble("measurementMethod", obj));
    MeteredFlowMethodData meteredFlowMethodData = getMeteredFlowMethodData(obj);
    VolumeMeterMethodData volumeMeterMethodData = getVolumeMeterMethodData(obj);
    BucketMethodData bucketMethodData = getBucketMethodData(obj);
    WaterOtherMethodData otherMethodData = getWaterOtherMethodData(obj);
    return {
        hoursPerYear,
        waterCost,
        measurementMethod,
        meteredFlowMethodData,
        volumeMeterMethodData,
        bucketMethodData,
        otherMethodData};
}

std::vector<WaterReductionInput> getWaterReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("waterReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("WaterReduction: getWaterReductionInputVec method in calculator.h: waterReductionInputVec not present in object").c_str());
    }
    Local<Array> waterReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<WaterReductionInput> inputVec;
    for (std::size_t i = 0; i < waterReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructWaterReductionInput(Nan::To<Object>(waterReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(waterReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<WaterReductionInput> inputVec = getWaterReductionInputVec();
        WaterReduction::Output rv = WaterReduction(inputVec).calculate();
        SetR("waterUse", rv.waterUse);
        SetR("waterCost", rv.waterCost);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in waterReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}

// ========== END water reduction =============

// ========== Start CA Pressure Reduction ===========
CompressedAirPressureReductionInput constructCompressedAirPressureReductionInput(Local<Object> obj)
{
    bool isBaseline = GetBool("isBaseline", obj);
    int hoursPerYear = static_cast<int>(GetDouble("hoursPerYear", obj));
    double electricityCost = GetDouble("electricityCost", obj);
    double compressorPower = GetDouble("compressorPower", obj);
    double pressure = GetDouble("pressure", obj);
    double proposedPressure = GetDouble("proposedPressure", obj);
    return {
        isBaseline,
        hoursPerYear,
        electricityCost,
        compressorPower,
        pressure,
        proposedPressure};
}

std::vector<CompressedAirPressureReductionInput> getCompressedAirPressureReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("compressedAirPressureReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("CompressedAirPressureReduction: getCompressedAirPressureReductionInputVec method in calculator.h: compressedAirPressureReductionInputVec not present in object").c_str());
    }
    Local<Array> compressedAirPressureReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<CompressedAirPressureReductionInput> inputVec;
    for (std::size_t i = 0; i < compressedAirPressureReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructCompressedAirPressureReductionInput(Nan::To<Object>(compressedAirPressureReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(compressedAirPressureReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<CompressedAirPressureReductionInput> inputVec = getCompressedAirPressureReductionInputVec();
        CompressedAirPressureReduction::Output rv = CompressedAirPressureReduction(inputVec).calculate();
        SetR("energyUse", rv.energyUse);
        SetR("energyCost", rv.energyCost);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in compressedAirPressureReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}
// ========== END CA Pressure Reduction ===========

// ========== Start Pipe Insulation Reduction ===========
NAN_METHOD(pipeInsulationReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    int operatingHours = static_cast<int>(GetDouble("operatingHours", inp));
    double pipeLength = GetDouble("pipeLength", inp);
    double pipeDiameter = GetDouble("pipeDiameter", inp);
    double pipeThickness = GetDouble("pipeThickness", inp);
    double pipeTemperature = GetDouble("pipeTemperature", inp);
    double ambientTemperature = GetDouble("ambientTemperature", inp);
    double windVelocity = GetDouble("windVelocity", inp);
    double systemEfficiency = Conversion(GetDouble("systemEfficiency", inp)).percentToFraction();
    double insulationThickness = GetDouble("insulationThickness", inp);
    double pipeEmissivity = GetDouble("pipeEmissivity", inp);
    double jacketEmissivity = GetDouble("jacketEmissivity", inp);
    std::vector<double> pipeMaterialCoefficients = GetVector("pipeMaterialCoefficients", inp);
    std::vector<double> insulationMaterialCoefficients = GetVector("insulationMaterialCoefficients", inp);

    InsulatedPipeInput input(
        operatingHours,
        pipeLength,
        pipeDiameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        systemEfficiency,
        insulationThickness,
        pipeEmissivity,
        jacketEmissivity,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients);
    InsulatedPipeCalculator calculator(input);
    InsulatedPipeOutput output = calculator.calculate();

    SetR("heatLength", output.getHeatLength());
    SetR("annualHeatLoss", output.getAnnualHeatLoss());
    info.GetReturnValue().Set(r);
}
// ========== END Pipe Insulation Reduction ===========

// ========== Start Tank Insulation Reduction ===========
NAN_METHOD(tankInsulationReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    int operatingHours = static_cast<int>(GetDouble("operatingHours", inp));
    double tankHeight = GetDouble("tankHeight", inp);
    double tankDiameter = GetDouble("tankDiameter", inp);
    double tankThickness = GetDouble("tankThickness", inp);
    double tankEmissivity = GetDouble("tankEmissivity", inp);
    double tankConductivity = GetDouble("tankConductivity", inp);
    double tankTemperature = GetDouble("tankTemperature", inp);
    double ambientTemperature = GetDouble("ambientTemperature", inp);
    double systemEfficiency = Conversion(GetDouble("systemEfficiency", inp)).percentToFraction();
    double insulationThickness = GetDouble("insulationThickness", inp);
    double insulationConductivity = GetDouble("insulationConductivity", inp);
    double jacketEmissivity = GetDouble("jacketEmissivity", inp);

    InsulatedTankInput input(
        operatingHours,
        tankHeight,
        tankDiameter,
        tankThickness,
        tankEmissivity,
        tankConductivity,
        tankTemperature,
        ambientTemperature,
        systemEfficiency,
        insulationThickness,
        insulationConductivity,
        jacketEmissivity);
    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();

    SetR("heatLoss", output.getHeatLoss());
    SetR("annualHeatLoss", output.getAnnualHeatLoss());
    info.GetReturnValue().Set(r);
}
// ========== END Tank Insulation Reduction ===========

// ============ Start Steam Reduction =============
SteamFlowMeterMethodData getSteamFlowMeterMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("flowMeterMethodData").ToLocalChecked();
    Local<Object> flowMeterMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (flowMeterMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamFlowMeterMethodData method in calculator.h: flowMeterMethodData not present in object").c_str());
    }
    double flowRate = GetDouble("flowRate", flowMeterMethodDataV8);
    return {flowRate};
}

SteamMassFlowMeasuredData getSteamMassFlowMeasuredData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("massFlowMeasuredData").ToLocalChecked();
    Local<Object> massFlowMeasuredDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (massFlowMeasuredDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamMassFlowMeasuredData method in calculator.h: massFlowMeasuredData not present in object").c_str());
    }
    double areaOfDuct = GetDouble("areaOfDuct", massFlowMeasuredDataV8);
    double airVelocity = GetDouble("airVelocity", massFlowMeasuredDataV8);
    return {
        areaOfDuct,
        airVelocity};
}

SteamMassFlowNameplateData getSteamMassFlowNameplateData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("massFlowNameplateData").ToLocalChecked();
    Local<Object> massFlowNameplateDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (massFlowNameplateDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamMassFlowNameplateData method in calculator.h: massFlowNameplateData not present in object").c_str());
    }
    double flowRate = GetDouble("flowRate", massFlowNameplateDataV8);
    return {flowRate};
}

SteamMassFlowMethodData getSteamAirMassFlowMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("airMassFlowMethodData").ToLocalChecked();
    Local<Object> massFlowMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (massFlowMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamAirMassFlowMethodData method in calculator.h: airMassFlowMethodData not present in object").c_str());
    }
    bool isNameplate = GetBool("isNameplate", massFlowMethodDataV8);
    SteamMassFlowMeasuredData measuredData = getSteamMassFlowMeasuredData(massFlowMethodDataV8);
    SteamMassFlowNameplateData nameplateData = getSteamMassFlowNameplateData(massFlowMethodDataV8);
    double inletTemperature = GetDouble("inletTemperature", massFlowMethodDataV8);
    double outletTemperature = GetDouble("outletTemperature", massFlowMethodDataV8);
    return {
        isNameplate,
        measuredData,
        nameplateData,
        inletTemperature,
        outletTemperature};
}

SteamMassFlowMethodData getSteamWaterMassFlowMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("waterMassFlowMethodData").ToLocalChecked();
    Local<Object> massFlowMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (massFlowMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamWaterMassFlowMethodData method in calculator.h: waterMassFlowMethodData not present in object").c_str());
    }
    bool isNameplate = GetBool("isNameplate", massFlowMethodDataV8);
    SteamMassFlowMeasuredData measuredData = getSteamMassFlowMeasuredData(massFlowMethodDataV8);
    SteamMassFlowNameplateData nameplateData = getSteamMassFlowNameplateData(massFlowMethodDataV8);
    double inletTemperature = GetDouble("inletTemperature", massFlowMethodDataV8);
    double outletTemperature = GetDouble("outletTemperature", massFlowMethodDataV8);
    return {
        isNameplate,
        measuredData,
        nameplateData,
        inletTemperature,
        outletTemperature};
}

SteamOtherMethodData getSteamOtherMethodData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("otherMethodData").ToLocalChecked();
    Local<Object> otherMethodDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (otherMethodDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamOtherMethodData method in calculator.h: otherMethodData not present in object").c_str());
    }
    double consumption = GetDouble("consumption", otherMethodDataV8);
    return {consumption};
}

SteamReductionInput constructSteamReductionInput(Local<Object> obj)
{
    int hoursPerYear = static_cast<int>(GetDouble("hoursPerYear", obj));
    int utilityType = static_cast<int>(GetDouble("utilityType", obj));
    double utilityCost = GetDouble("utilityCost", obj);
    int measurementMethod = static_cast<int>(GetDouble("measurementMethod", obj));
    double systemEfficiency = Conversion(GetDouble("systemEfficiency", obj)).percentToFraction();
    double pressure = GetDouble("pressure", obj);
    SteamFlowMeterMethodData steamFlowMeterMethodData = getSteamFlowMeterMethodData(obj);
    SteamMassFlowMethodData steamAirMassFlowMethodData = getSteamAirMassFlowMethodData(obj);
    SteamMassFlowMethodData steamWaterMassFlowMethodData = getSteamWaterMassFlowMethodData(obj);
    SteamOtherMethodData otherMethodData = getSteamOtherMethodData(obj);
    int units = static_cast<int>(GetDouble("units", obj));
    return {
        hoursPerYear,
        utilityType,
        utilityCost,
        measurementMethod,
        systemEfficiency,
        pressure,
        steamFlowMeterMethodData,
        steamAirMassFlowMethodData,
        steamWaterMassFlowMethodData,
        otherMethodData,
        units};
}

std::vector<SteamReductionInput> getSteamReductionInputVec()
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("steamReductionInputVec").ToLocalChecked();
    Local<Value> arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (arrayTmp->IsUndefined())
    {
        ThrowTypeError(std::string("SteamReduction: getSteamReductionInputVec method in calculator.h: steamReductionInputVec not present in object").c_str());
    }
    Local<Array> steamReductionInputArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<SteamReductionInput> inputVec;
    for (std::size_t i = 0; i < steamReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructSteamReductionInput(Nan::To<Object>(steamReductionInputArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
    }
    return inputVec;
}

NAN_METHOD(steamReduction)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        std::vector<SteamReductionInput> inputVec = getSteamReductionInputVec();
        SteamReduction::Output rv = SteamReduction(inputVec).calculate();
        SetR("steamUse", rv.steamUse);
        SetR("energyUse", rv.energyUse);
        SetR("energyCost", rv.energyCost);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in steamReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}
// ============ END Steam Reduction =============
