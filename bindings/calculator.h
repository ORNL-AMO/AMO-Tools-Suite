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

MultimeterData getMultimeterData(Local<Object> obj)
{
    auto multimeterDataV8 = obj->Get(Nan::New<String>("multimeterData").ToLocalChecked())->ToObject();
    auto test = Get("numberOfPhases", multimeterDataV8);
    return {
        static_cast<int>(Get("numberOfPhases", multimeterDataV8)),
        Get("supplyVoltage", multimeterDataV8),
        Get("averageCurrent", multimeterDataV8),
        Get("powerFactor", multimeterDataV8)
    };
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
        Get("loadFactor", nameplateDataV8)
    };
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
    auto test = Get("hoursPerDay", obj);
    return {
        static_cast<int>(Get("hoursPerDay", obj)),
        static_cast<int>(Get("daysPerMonth", obj)),
        static_cast<int>(Get("monthsPerYear", obj)),
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
        SetR("annualEnergySavings", rv.annualEnergySavings);
        SetR("costSavings", rv.costSavings);
        SetR("power", rv.power);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in electricityReduction - calculator.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}