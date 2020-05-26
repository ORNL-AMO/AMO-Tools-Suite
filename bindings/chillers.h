#include "calculator.h"
#include "chillers/CoolingTower.h"

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