#ifndef AMO_TOOLS_SUITE_CALCULATOR_H
#define AMO_TOOLS_SUITE_CALCULATOR_H

#include "NanDataConverters.h"
#include <string>
#include <stdexcept>
#include <array>
#include <cmath>
// #include <nan.h>
#include <vector>
#include "calculator/util/ElectricityReduction.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in calculator.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

bool GetBool(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("GetBool method in calculator.h: Boolean value " + key + " not present in object").c_str());
	}
	return rObj->BooleanValue();
}

std::string GetStr(std::string const & key, Local<Object> obj) {
	auto const & rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("GetStr method in calculator.h: String " + key + " not present in object").c_str());
	}
	v8::String::Utf8Value s(rObj);
	return std::string(*s);
}

bool isDefined(Local<Object> obj, std::string const & key) {
	return !obj->Get(Nan::New<String>(key).ToLocalChecked())->IsUndefined();
}

inline void SetR(const std::string & key, double val) {
	Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}



NAN_METHOD(electricityReduction) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Local <String> arrayStr = Nan::New<String>("electricityReductionData").ToLocalChecked();
    auto array = inp->ToObject()->Get(arrayStr);
    v8::Local <v8::Array> arr = v8::Local<v8::Array>::Cast(array);

    auto energyUseStr = Nan::New<String>("energyUse").ToLocalChecked();
    auto energyCostStr = Nan::New<String>("energyCost").ToLocalChecked();
    auto annualEnergySavingsStr = Nan::New<String>("annualEnergySavings").ToLocalChecked();
    auto costSavingsStr = Nan::New<String>("costSavings").ToLocalChecked();

    std::vector<electricityReductionInputVec> electricityReductionInputVec;

    for (std::size_t i = 0; i < arr.Length(); i++) {
        auto const hoursPerDay = arr->Get(i)->ToObject()->Get(hoursPerDay)->NumberValue();
        auto const daysPerMonth = arr->Get(i)->ToObject()->Get(daysPerMonth)->NumberValue();
        auto const monthsPerYear = arr->Get(i)->ToObject()->Get(monthsPerYear)->NumberValue();
        auto const electricityCost = arr->Get(i)->ToObject()->Get(electricityCost)->NumberValue();
        auto const measurementMethod = arr->Get(i)->ToObject()->Get(measurementMethod)->NumberValue();
        auto const multimeterData = arr->Get(i)->ToObject()->Get(multimeterData)->ToObject();
        auto const nameplateData = arr->Get(i)->ToObject()->Get(nameplateData)->ToObject();
        auto const powerMeterData = arr->Get(i)->ToObject()->Get(powerMeterData)->ToObject();
        auto const otherMethodData = arr->Get(i)->ToObject()->Get(otherMethodData)->ToObject();
        auto const units = arr->Get(i)->ToObject()->Get(units)->NumberValue();
        electricityReductionInputVec.emplace_back(
            ElectricityReductionInput(hoursPerDay, daysPerMonth, monthsPerYear,
                                      electricityCost, measurementMethod, multimeterData, 
                                      nameplateData, powerMeterData, otherMethodData, units)
        );

        // Local <Object> obj = Nan::New<Object>();
        // Local <String> electricityReductionInputNum = Nan::New<String>("electricityReductionInput" + std::to_string(i))
        // auto const electricity
    }

    try {
        auto electricityReduction = ElectricityReduction(electricityReductionInputVec).calculate();
        Local <String> electricityReductionResultsStr = Nan::New<String>("electricityReductionResults");

        auto const electricityReductionResults = electricityReduction.getOutput();
        Local <Object> obj = Nan::New<Object>();

        Nan::Set(obj, energyUseStr, Nan::New<Number>(electricityReductionResults.energyUse));
        Nan::Set(obj, energyCostStr, Nan::New<Number>(electricityReductionResults.energyCost));
        Nan::Set(obj, annualEnergySavingsStr, Nan::New<Number>(electricityReductionResults.annualEnergySavingsStr));
        Nan::Set(obj, costSavingsStr, Nan::New<Number>(electricityReductionResults.costSavings));

        Nan::Set(r, electricityReductionResultsStr, obj);
    } catch {
        std::string const what = e.what();
        throwLogicError(std::string)"std::runtime_error thrown in electricityReduction - calculator.h: " + what).c_str();
    }
    info.GetReturnValue().Set(r);
}
