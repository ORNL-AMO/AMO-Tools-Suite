// #ifndef AMO_TOOLS_SUITE_CALCULATOR_H
// #define AMO_TOOLS_SUITE_CALCULATOR_H

// #include "NanDataConverters.h"
#include <nan.h>
#include <node.h>
#include <string>
#include <stdexcept>
#include <array>
#include <cmath>
#include <vector>
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

#include <iostream>
#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "calculator/util/SteamReduction.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const &key, Local<Object> obj)
{
    auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("Get method in calculator.h: " + key + " not present in object").c_str());
    }
    return rObj->NumberValue();
}

std::vector<double> GetVector(const std::string &key, Local<Object> obj)
{
    auto const &arrayTmp = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
    auto const &jsArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<double> array;
    for (int i = 0; i < jsArray->Length(); i++)
    {
        v8::Local<v8::Value> jsElement = jsArray->Get(i);
        double val = jsElement->NumberValue();
        array.push_back(val);
    }
    return array;
}

template <typename T>
T GetEnumVal(std::string const &key, Local<Object> obj)
{
    auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetEnumVal method in calculator.h: " + key + " not present in object").c_str());
    }
    return static_cast<T>(rObj->IntegerValue());
}

bool GetBool(std::string const &key, Local<Object> obj)
{
    auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetBool method in calculator.h: Boolean value " + key + " not present in object").c_str());
    }
    return rObj->BooleanValue();
}

std::string GetStr(std::string const &key, Local<Object> obj)
{
    auto const &rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("GetStr method in calculator.h: String " + key + " not present in object").c_str());
    }
    v8::String::Utf8Value s(rObj);
    return std::string(*s);
}

bool isDefined(Local<Object> obj, std::string const &key)
{
    return !obj->Get(Nan::New<String>(key).ToLocalChecked())->IsUndefined();
}

inline void SetR(const std::string &key, double val)
{
    Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}

// ============== Electricity Reduction ==============

MultimeterData getMultimeterData(Local<Object> obj)
{
    auto multimeterDataV8 = obj->Get(Nan::New<String>("multimeterData").ToLocalChecked())->ToObject();
    return {
        static_cast<int>(Get("numberOfPhases", multimeterDataV8)),
        Get("supplyVoltage", multimeterDataV8),
        Get("averageCurrent", multimeterDataV8),
        Get("powerFactor", multimeterDataV8)};
}

NameplateData getNameplateData(Local<Object> obj)
{
    auto nameplateDataV8 = obj->Get(Nan::New<String>("nameplateData").ToLocalChecked())->ToObject();
    return {
        Get("ratedMotorPower", nameplateDataV8),
        GetBool("variableSpeedMotor", nameplateDataV8),
        Get("operationalFrequency", nameplateDataV8),
        Get("lineFrequency", nameplateDataV8),
        Get("motorAndDriveEfficiency", nameplateDataV8),
        Get("loadFactor", nameplateDataV8)};
}

PowerMeterData getPowerMeterData(Local<Object> obj)
{
    auto powerMeterDataV8 = obj->Get(Nan::New<String>("powerMeterData").ToLocalChecked())->ToObject();
    return {
        Get("power", powerMeterDataV8)};
}

OtherMethodData getOtherMethodData(Local<Object> obj)
{
    auto otherMethodDataV8 = obj->Get(Nan::New<String>("otherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("energy", otherMethodDataV8)};
}

ElectricityReductionInput constructElectricityReductionInput(Local<Object> obj)
{
    return {
        static_cast<int>(Get("operatingHours", obj)),
        Get("electricityCost", obj),
        static_cast<int>(Get("measurementMethod", obj)),
        getMultimeterData(obj),
        getNameplateData(obj),
        getPowerMeterData(obj),
        getOtherMethodData(obj),
        static_cast<int>(Get("units", obj))};
}

ElectricityReduction getElectricityReductionInputVector()
{
    auto electricityReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("electricityReductionInputVec").ToLocalChecked());
    auto const electricityReductionInputVecTemp = inp->ToObject()->Get(Nan::New<String>("electricityReductionInputVec").ToLocalChecked());
    auto const &electricityReductionInputArray = v8::Local<v8::Array>::Cast(electricityReductionInputVecTemp);
    std::vector<ElectricityReductionInput> inputVec;
    for (std::size_t i = 0; i < electricityReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructElectricityReductionInput(electricityReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(electricityReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = ElectricityReduction(getElectricityReductionInputVector()).calculate();
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
    auto flowMeterMethodDataV8 = obj->Get(Nan::New<String>("flowMeterMethodData").ToLocalChecked())->ToObject();
    return {
        Get("flowRate", flowMeterMethodDataV8)};
}

AirMassFlowMeasuredData getAirMassFlowMeasuredData(Local<Object> obj)
{
    auto airMassFlowMeasuredDataV8 = obj->Get(Nan::New<String>("airMassFlowMeasuredData").ToLocalChecked())->ToObject();
    return {
        Get("areaOfDuct", airMassFlowMeasuredDataV8),
        Get("airVelocity", airMassFlowMeasuredDataV8)};
}

AirMassFlowNameplateData getAirMassFlowNameplateData(Local<Object> obj)
{
    auto airMassFlowNameplateDataV8 = obj->Get(Nan::New<String>("airMassFlowNameplateData").ToLocalChecked())->ToObject();
    return {
        Get("airFlow", airMassFlowNameplateDataV8)};
}

AirMassFlowData getAirMassFlowData(Local<Object> obj)
{
    auto airMassFlowDataV8 = obj->Get(Nan::New<String>("airMassFlowData").ToLocalChecked())->ToObject();
    return {
        GetBool("isNameplate", airMassFlowDataV8),
        getAirMassFlowMeasuredData(airMassFlowDataV8),
        getAirMassFlowNameplateData(airMassFlowDataV8),
        Get("inletTemperature", airMassFlowDataV8),
        Get("outletTemperature", airMassFlowDataV8),
        Get("systemEfficiency", airMassFlowDataV8) / 100};
}

WaterMassFlowData getWaterMassFlowData(Local<Object> obj)
{
    auto waterMassFlowDataV8 = obj->Get(Nan::New<String>("waterMassFlowData").ToLocalChecked())->ToObject();
    return {
        Get("waterFlow", waterMassFlowDataV8),
        Get("inletTemperature", waterMassFlowDataV8),
        Get("outletTemperature", waterMassFlowDataV8),
        Get("systemEfficiency", waterMassFlowDataV8) / 100};
}

NaturalGasOtherMethodData naturalGasGetOtherMethodData(Local<Object> obj)
{
    auto otherMethodDataV8 = obj->Get(Nan::New<String>("otherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("consumption", otherMethodDataV8)};
}

NaturalGasReductionInput constructNaturalGasReductionInput(Local<Object> obj)
{
    return {
        static_cast<int>(Get("operatingHours", obj)),
        Get("fuelCost", obj),
        static_cast<int>(Get("measurementMethod", obj)),
        getFlowMeterMethodData(obj),
        naturalGasGetOtherMethodData(obj),
        getAirMassFlowData(obj),
        getWaterMassFlowData(obj),
        static_cast<int>(Get("units", obj))};
}

NaturalGasReduction getNaturalGasReductionInputVector()
{
    auto naturalGasReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("naturalGasReductionInputVec").ToLocalChecked());
    auto const naturalGasReductionInputVecTemp = inp->ToObject()->Get(Nan::New<String>("naturalGasReductionInputVec").ToLocalChecked());
    auto const &naturalGasReductionInputArray = v8::Local<v8::Array>::Cast(naturalGasReductionInputVecTemp);
    std::vector<NaturalGasReductionInput> inputVec;
    for (std::size_t i = 0; i < naturalGasReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructNaturalGasReductionInput(naturalGasReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(naturalGasReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = NaturalGasReduction(getNaturalGasReductionInputVector()).calculate();
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
    auto flowMeterMethodDataV8 = obj->Get(Nan::New<String>("flowMeterMethodData").ToLocalChecked())->ToObject();
    return {
        Get("meterReading", flowMeterMethodDataV8)};
}

BagMethodData getBagMethodData(Local<Object> obj)
{
    auto bagMethodDataV8 = obj->Get(Nan::New<String>("bagMethodData").ToLocalChecked())->ToObject();
    return {
        Get("height", bagMethodDataV8),
        Get("diameter", bagMethodDataV8),
        Get("fillTime", bagMethodDataV8)};
}

PressureMethodData getPressureMethodData(Local<Object> obj)
{
    auto pressureMethodDataV8 = obj->Get(Nan::New<String>("pressureMethodData").ToLocalChecked())->ToObject();
    return {
        static_cast<int>(Get("nozzleType", pressureMethodDataV8)),
        static_cast<int>(Get("numberOfNozzles", pressureMethodDataV8)),
        Get("supplyPressure", pressureMethodDataV8)};
}

CompressedAirOtherMethodData getCompressedAirOtherMethodData(Local<Object> obj)
{
    auto otherMethodDataV8 = obj->Get(Nan::New<String>("otherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("consumption", otherMethodDataV8)};
}

CompressorElectricityData getCompressorElectricityData(Local<Object> obj)
{
    auto compressorElectricityDataV8 = obj->Get(Nan::New<String>("compressorElectricityData").ToLocalChecked())->ToObject();
    return {
        Get("compressorControlAdjustment", compressorElectricityDataV8) / 100,
        Get("compressorSpecificPower", compressorElectricityDataV8)};
}

CompressedAirReductionInput constructCompressedAirReductionInput(Local<Object> obj)
{
    return {
        static_cast<int>(Get("hoursPerYear", obj)),
        static_cast<int>(Get("utilityType", obj)),
        Get("utilityCost", obj),
        static_cast<int>(Get("measurementMethod", obj)),
        getCompressedAirFlowMeterMethodData(obj),
        getBagMethodData(obj),
        getPressureMethodData(obj),
        getCompressedAirOtherMethodData(obj),
        getCompressorElectricityData(obj),
        static_cast<int>(Get("units", obj))};
}

CompressedAirReduction getCompressedAirReductionInputVec()
{
    // auto compressedAirReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("compressedAirReductionInpuptVec").ToLocalChecked());
    auto const compressedAirReductionInputVecTemp = inp->ToObject()->Get(Nan::New<String>("compressedAirReductionInputVec").ToLocalChecked());
    auto const &compressedAirReductionInputArray = v8::Local<v8::Array>::Cast(compressedAirReductionInputVecTemp);
    std::vector<CompressedAirReductionInput> inputVec;
    for (std::size_t i = 0; i < compressedAirReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructCompressedAirReductionInput(compressedAirReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(compressedAirReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = CompressedAirReduction(getCompressedAirReductionInputVec()).calculate();
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
    auto meteredFlowMethodDataV8 = obj->Get(Nan::New<String>("meteredFlowMethodData").ToLocalChecked())->ToObject();
    return {
        Get("meterReading", meteredFlowMethodDataV8)};
}

VolumeMeterMethodData getVolumeMeterMethodData(Local<Object> obj)
{
    auto volumeMeterMethodDataV8 = obj->Get(Nan::New<String>("volumeMeterMethodData").ToLocalChecked())->ToObject();
    return {
        Get("finalMeterReading", volumeMeterMethodDataV8),
        Get("initialMeterReading", volumeMeterMethodDataV8),
        Get("elapsedTime", volumeMeterMethodDataV8)};
}

BucketMethodData getBucketMethodData(Local<Object> obj)
{
    auto bucketMethodDataV8 = obj->Get(Nan::New<String>("bucketMethodData").ToLocalChecked())->ToObject();
    return {
        Get("bucketVolume", bucketMethodDataV8),
        Get("bucketFillTime", bucketMethodDataV8)};
}

WaterOtherMethodData getWaterOtherMethodData(Local<Object> obj)
{
    auto otherMethodDataV8 = obj->Get(Nan::New<String>("otherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("consumption", otherMethodDataV8)};
}

WaterReductionInput constructWaterReductionInput(Local<Object> obj)
{
    return {
        static_cast<int>(Get("hoursPerYear", obj)),
        Get("waterCost", obj),
        static_cast<int>(Get("measurementMethod", obj)),
        getMeteredFlowMethodData(obj),
        getVolumeMeterMethodData(obj),
        getBucketMethodData(obj),
        getWaterOtherMethodData(obj)};
}

WaterReduction getWaterReductionInputVec()
{
    auto waterReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("waterReductionInputVec").ToLocalChecked());
    auto const &waterReductionInputArray = v8::Local<v8::Array>::Cast(waterReductionInputVecV8);
    std::vector<WaterReductionInput> inputVec;
    for (std::size_t i = 0; i < waterReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructWaterReductionInput(waterReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(waterReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = WaterReduction(getWaterReductionInputVec()).calculate();
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
    return {
        GetBool("isBaseline", obj),
        static_cast<int>(Get("hoursPerYear", obj)),
        Get("electricityCost", obj),
        Get("compressorPower", obj),
        Get("pressure", obj),
        Get("proposedPressure", obj)};
}

CompressedAirPressureReduction getCompressedAirPressureReductionInputVec()
{
    auto const compressedAirPressureReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("compressedAirPressureReductionInputVec").ToLocalChecked());
    auto const &compressedAirPressureReductionInputArray = v8::Local<v8::Array>::Cast(compressedAirPressureReductionInputVecV8);
    std::vector<CompressedAirPressureReductionInput> inputVec;
    for (std::size_t i = 0; i < compressedAirPressureReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructCompressedAirPressureReductionInput(compressedAirPressureReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(compressedAirPressureReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = CompressedAirPressureReduction(getCompressedAirPressureReductionInputVec()).calculate();
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
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    int operatingHours = static_cast<int>(Get("operatingHours", inp));
    double pipeLength = Get("pipeLength", inp);
    double pipeDiameter = Get("pipeDiameter", inp);
    double pipeThickness = Get("pipeThickness", inp);
    double pipeTemperature = Get("pipeTemperature", inp);
    double ambientTemperature = Get("ambientTemperature", inp);
    double windVelocity = Get("windVelocity", inp);
    double systemEfficiency = Get("systemEfficiency", inp) / 100.0;
    double insulationThickness = Get("insulationThickness", inp);
    double pipeEmissivity = Get("pipeEmissivity", inp);
    double jacketEmissivity = Get("jacketEmissivity", inp);
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
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    int operatingHours = static_cast<int>(Get("operatingHours", inp));
    double tankHeight = Get("tankHeight", inp);
    double tankDiameter = Get("tankDiameter", inp);
    double tankThickness = Get("tankThickness", inp);
    double tankEmissivity = Get("tankEmissivity", inp);
    double tankConductivity = Get("tankConductivity", inp);
    double tankTemperature = Get("tankTemperature", inp);
    double ambientTemperature = Get("ambientTemperature", inp);
    double systemEfficiency = Get("systemEfficiency", inp) / 100.0;
    double insulationThickness = Get("insulationThickness", inp);
    double insulationConductivity = Get("insulationConductivity", inp);
    double jacketEmissivity = Get("jacketEmissivity", inp);

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
    auto flowMeterMethodDataV8 = obj->Get(Nan::New<String>("flowMeterMethodData").ToLocalChecked())->ToObject();
    return {
        Get("flowRate", flowMeterMethodDataV8)};
}

SteamMassFlowMeasuredData getSteamMassFlowMeasuredData(Local<Object> obj)
{
    auto massFlowMeasuredDataV8 = obj->Get(Nan::New<String>("massFlowMeasuredData").ToLocalChecked())->ToObject();
    return {
        Get("areaOfDuct", massFlowMeasuredDataV8),
        Get("airVelocity", massFlowMeasuredDataV8)};
}

SteamMassFlowNameplateData getSteamMassFlowNameplateData(Local<Object> obj)
{
    auto massFlowNameplateDataV8 = obj->Get(Nan::New<String>("massFlowNameplateData").ToLocalChecked())->ToObject();
    return {
        Get("flowRate", massFlowNameplateDataV8)};
}

SteamMassFlowMethodData getSteamAirMassFlowMethodData(Local<Object> obj)
{
    auto massFlowMethodDataV8 = obj->Get(Nan::New<String>("airMassFlowMethodData").ToLocalChecked())->ToObject();
    return {
        GetBool("isNameplate", massFlowMethodDataV8),
        getSteamMassFlowMeasuredData(massFlowMethodDataV8),
        getSteamMassFlowNameplateData(massFlowMethodDataV8),
        Get("inletTemperature", massFlowMethodDataV8),
        Get("outletTemperature", massFlowMethodDataV8)};
}

SteamMassFlowMethodData getSteamWaterMassFlowMethodData(Local<Object> obj)
{
    auto massFlowMethodDataV8 = obj->Get(Nan::New<String>("waterMassFlowMethodData").ToLocalChecked())->ToObject();
    return {
        GetBool("isNameplate", massFlowMethodDataV8),
        getSteamMassFlowMeasuredData(massFlowMethodDataV8),
        getSteamMassFlowNameplateData(massFlowMethodDataV8),
        Get("inletTemperature", massFlowMethodDataV8),
        Get("outletTemperature", massFlowMethodDataV8)};
}

SteamOtherMethodData getSteamOtherMethodData(Local<Object> obj)
{
    auto otherMethodDataV8 = obj->Get(Nan::New<String>("otherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("consumption", otherMethodDataV8)};
}

SteamReductionInput constructSteamReductionInput(Local<Object> obj)
{
    return {
        static_cast<int>(Get("hoursPerYear", obj)),
        static_cast<int>(Get("utilityType", obj)),
        Get("utilityCost", obj),
        static_cast<int>(Get("measurementMethod", obj)),
        Get("systemEfficiency", obj) / 100.0,
        Get("pressure", obj),
        getSteamFlowMeterMethodData(obj),
        getSteamAirMassFlowMethodData(obj),
        getSteamWaterMassFlowMethodData(obj),
        getSteamOtherMethodData(obj),
        static_cast<int>(Get("units", obj))};
}

SteamReduction getSteamReductionInputVec()
{
    auto const steamReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("steamReductionInputVec").ToLocalChecked());
    auto const &steamReductionInputArray = v8::Local<v8::Array>::Cast(steamReductionInputVecV8);
    std::vector<SteamReductionInput> inputVec;
    for (std::size_t i = 0; i < steamReductionInputArray->Length(); i++)
    {
        inputVec.emplace_back(constructSteamReductionInput(steamReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}

NAN_METHOD(steamReduction)
{
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    try
    {
        auto rv = SteamReduction(getSteamReductionInputVec()).calculate();
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
