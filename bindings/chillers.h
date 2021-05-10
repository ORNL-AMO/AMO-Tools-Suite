#ifndef AMO_TOOLS_SUITE_CHILLERS_H
#define AMO_TOOLS_SUITE_CHILLERS_H

#include <nan.h>
#include <node.h>
#include <string>
#include <stdexcept>
#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include "./NanDataConverters.h"
#include "chillers/CoolingTower.h"

using namespace Nan;
using namespace v8;

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
    return Nan::To<bool>(rObj).FromJust();
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

CoolingTowerOperatingConditionsData getCoolingTowerOperatingConditionsData(Local<Object> obj)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>("operatingConditionsData").ToLocalChecked();
    Local<Object> coolingTowerOperatingConditionsDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (coolingTowerOperatingConditionsDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CoolingTowerMakeupWater: getCoolingTowerOperatingConditionsData method in chillers.h: operatingConditionsData not present in object").c_str());
    }
    double flowRate = GetDouble("flowRate", coolingTowerOperatingConditionsDataV8);
    double coolingLoad = GetDouble("coolingLoad", coolingTowerOperatingConditionsDataV8);
    int operationalHours = static_cast<int>(GetDouble("operationalHours", coolingTowerOperatingConditionsDataV8));
    double lossCorrectionFactor = GetDouble("lossCorrectionFactor", coolingTowerOperatingConditionsDataV8);
    return {
        flowRate,
        coolingLoad,
        operationalHours,
        lossCorrectionFactor};
}

CoolingTowerWaterConservationData getCoolingTowerWaterConservationData(Local<Object> obj, bool hasDriftEliminators)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName;
    if(hasDriftEliminators)
    {
        getName = Nan::New<String>("waterConservationModificationData").ToLocalChecked();
    }
    else
    {
        getName = Nan::New<String>("waterConservationBaselineData").ToLocalChecked();
    }
    Local<Object> coolingTowerWaterConservationDataV8 = Nan::To<Object>(obj->Get(context, getName).ToLocalChecked()).ToLocalChecked();
    if (coolingTowerWaterConservationDataV8->IsUndefined())
    {
        ThrowTypeError(std::string("CoolingTowerMakeupWater: getCoolingTowerWaterConservationData method in chillers.h: neither waterConservationBaselineData nor waterConservationModificationData are present in object").c_str());
    }
    int cyclesOfConcentration = static_cast<int>(GetDouble("cyclesOfConcentration", coolingTowerWaterConservationDataV8));
    double driftLossFactor = GetDouble("driftLossFactor", coolingTowerWaterConservationDataV8);
    return {
        cyclesOfConcentration,
        driftLossFactor};
}

NAN_METHOD(coolingTowerMakeupWater)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    try
    {
        v8::Isolate *isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        Local<String> getName = Nan::New<String>("coolingTowerMakeupWaterCalculator").ToLocalChecked();
        Local<Object> coolingTowerMakeupWaterCalculatorV8 = Nan::To<Object>(inp->Get(context, getName).ToLocalChecked()).ToLocalChecked();

        CoolingTowerOperatingConditionsData operatingConditionsData = getCoolingTowerOperatingConditionsData(coolingTowerMakeupWaterCalculatorV8);
        CoolingTowerWaterConservationData waterConservationBaselineData = getCoolingTowerWaterConservationData(coolingTowerMakeupWaterCalculatorV8, false);
        CoolingTowerWaterConservationData waterConservationModificationData = getCoolingTowerWaterConservationData(coolingTowerMakeupWaterCalculatorV8, true);

        CoolingTowerMakeupWaterCalculator coolingTowerMakeupWaterCalculator(operatingConditionsData, waterConservationBaselineData, waterConservationModificationData);
        CoolingTowerMakeupWaterCalculator::Output results = coolingTowerMakeupWaterCalculator.calculate();
        SetR("wcBaseline", results.wcBaseline);
        SetR("wcModification", results.wcModification);
        SetR("waterSavings", results.waterSavings);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in coolingTowerMakeupWater - chillers.h: " + what).c_str());
    }
    info.GetReturnValue().Set(r);
}


NAN_METHOD(coolingTowerBasinHeaterEnergyConsumption)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double ratedCapacity = getDouble("ratedCapacity", inp);
        const double ratedTempSetPoint = getDouble("ratedTempSetPoint", inp);
        const double ratedTempDryBulb = getDouble("ratedTempDryBulb", inp);
        const double ratedWindSpeed = getDouble("ratedWindSpeed", inp);

        const double operatingTempDryBulb = getDouble("operatingTempDryBulb", inp);
        const double operatingWindSpeed = getDouble("operatingWindSpeed", inp);
        const double operatingHours = getDouble("operatingHours", inp);

        const double baselineTempSetPoint = getDouble("baselineTempSetPoint", inp);
        const double modTempSetPoint = getDouble("modTempSetPoint", inp);
        const double panLossRatio = getDouble("panLossRatio", inp);

        auto output = CoolingTower::BasinHeaterEnergyConsumption(
                ratedCapacity,ratedTempSetPoint,ratedTempDryBulb,ratedWindSpeed,
                operatingTempDryBulb,operatingWindSpeed,operatingHours,
                baselineTempSetPoint, modTempSetPoint, panLossRatio);

        setR("baselinePower", output.baselinePower);
        setR("baselineEnergy", output.baselineEnergy);
        setR("modPower", output.modPower);
        setR("modEnergy", output.modEnergy);
        setR("savingsEnergy", output.savingsEnergy);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Cooling Tower Basin Heater Energy Consumption - calculator: " + what).c_str());
    }
}

NAN_METHOD(coolingTowerFanEnergyConsumption)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double ratedFanPower = getDouble("ratedFanPower", inp);

        const double waterLeavingTemp = getDouble("waterLeavingTemp", inp);
        const double waterEnteringTemp = getDouble("waterEnteringTemp", inp);
        const double operatingTempWetBulb = getDouble("operatingTempWetBulb", inp);
        const double operatingHours = getDouble("operatingHours", inp);

        const int baselineSpeedType = getInteger("baselineSpeedType");
        const int modSpeedType = getInteger("modSpeedType");

        auto output = CoolingTower::FanEnergyConsumption(
                ratedFanPower,
                waterLeavingTemp,waterEnteringTemp,operatingTempWetBulb,operatingHours,
                (CoolingTower::FanControlSpeedType)baselineSpeedType,(CoolingTower::FanControlSpeedType)modSpeedType);

        setR("baselinePower", output.baselinePower);
        setR("baselineEnergy", output.baselineEnergy);
        setR("modPower", output.modPower);
        setR("modEnergy", output.modEnergy);
        setR("savingsEnergy", output.savingsEnergy);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Cooling Tower Fan Energy Consumption - calculator: " + what).c_str());
    }
}

NAN_METHOD(chillerCapacityEfficiency)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const int chillerType = getInteger("chillerType");
        const int condenserCoolingType = getInteger("condenserCoolingType");
        const int compressorConfigType = getInteger("compressorConfigType");

        const double ariCapacity = getDouble("ariCapacity", inp);
        const double ariEfficiency = getDouble("ariEfficiency", inp);
        const double maxCapacityRatio = getDouble("maxCapacityRatio", inp);

        const double operatingHours = getDouble("operatingHours", inp);
        const double waterFlowRate = getDouble("waterFlowRate", inp);
        const double waterDeltaT = getDouble("waterDeltaT", inp);

        const double baselineWaterSupplyTemp = getDouble("baselineWaterSupplyTemp", inp);
        const double baselineWaterEnteringTemp = getDouble("baselineWaterEnteringTemp", inp);
        const double modWaterSupplyTemp = getDouble("modWaterSupplyTemp", inp);
        const double modWaterEnteringTemp = getDouble("modWaterEnteringTemp", inp);

        auto output = ChillerEfficiency::ChillerCapacityEfficiency(
                (ChillerEfficiency::ChillerType)chillerType, (ChillerEfficiency::CondenserCoolingType)condenserCoolingType, (ChillerEfficiency::CompressorConfigType)compressorConfigType,
                ariCapacity,ariEfficiency, maxCapacityRatio, operatingHours, waterFlowRate, waterDeltaT,
                baselineWaterSupplyTemp, baselineWaterEnteringTemp,
                modWaterSupplyTemp, modWaterEnteringTemp);

        setR("baselineActualEfficiency", output.baselineActualEfficiency);
        setR("baselineActualCapacity", output.baselineActualCapacity);
        setR("baselinePower", output.baselinePower);
        setR("baselineEnergy", output.baselineEnergy);
        setR("modActualEfficiency", output.modActualEfficiency);
        setR("modActualCapacity", output.modActualCapacity);
        setR("modPower", output.modPower);
        setR("modEnergy", output.modEnergy);
        setR("savingsEnergy", output.savingsEnergy);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Chiller Capacity Efficiency Energy Consumption - calculator: " + what).c_str());
    }
}

NAN_METHOD(chillerStaging)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const int chillerType = getInteger("chillerType");
        const int condenserCoolingType = getInteger("condenserCoolingType");
        const int compressorConfigType = getInteger("compressorConfigType");

        const double ariCapacity = getDouble("ariCapacity", inp);
        const double ariEfficiency = getDouble("ariEfficiency", inp);
        const double maxCapacityRatio = getDouble("maxCapacityRatio", inp);

        const double operatingHours = getDouble("operatingHours", inp);
        const double waterSupplyTemp = getDouble("waterSupplyTemp", inp);
        const double waterEnteringTemp = getDouble("waterEnteringTemp", inp);

        std::vector<double> baselineLoadList = GetVector("baselineLoadList", inp);
        std::vector<double> modLoadList = GetVector("modLoadList", inp);

        auto output = ChillerEfficiency::ChillerStagingEfficiency(
                (ChillerEfficiency::ChillerType)chillerType, (ChillerEfficiency::CondenserCoolingType)condenserCoolingType, (ChillerEfficiency::CompressorConfigType)compressorConfigType,
                ariCapacity, ariEfficiency, maxCapacityRatio, operatingHours, waterSupplyTemp, waterEnteringTemp,
                baselineLoadList, modLoadList);

        setR("baselineTotalPower", output.baselineTotalPower);
        setR("baselineTotalEnergy", output.baselineTotalEnergy);
        setR("modTotalPower", output.modTotalPower);
        setR("modTotalEnergy", output.modTotalEnergy);
        setR("savingsEnergy", output.savingsEnergy);

        auto baselinePowers = New<Array>(output.baselinePowerList.size());
        auto modPowers = New<Array>(output.baselinePowerList.size());
        for (unsigned i = 0; i < baselinePowers->Length(); i++) {
            baselinePowers->Set(Nan::GetCurrentContext(), i, New(output.baselinePowerList[i]));
            modPowers->Set(Nan::GetCurrentContext(), i, New(output.modPowerList[i]));
        }
        Nan::Set(r, New("baselinePowerList").ToLocalChecked(), baselinePowers);
        Nan::Set(r, New("modPowerList").ToLocalChecked(), modPowers);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Chiller Staging Energy Consumption - calculator: " + what).c_str());
    }
}
#endif //AMO_TOOLS_SUITE_CHILLERS_H