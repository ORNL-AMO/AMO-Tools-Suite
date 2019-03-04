// #ifndef AMO_TOOLS_SUITE_CALCULATOR_H
// #define AMO_TOOLS_SUITE_CALCULATOR_H

// #include "NanDataConverters.h"
#include <nan.h>
#include <node.h>
#include <iostream>
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

template <typename T>
T GetEnumVal(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("GetEnumVal method in calculator.h: " + key + " not present in object").c_str());
	}
	return static_cast<T>(rObj->IntegerValue());
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

MultimeterData getMultimeterData(Local<Object> obj) {
    // auto multimeterDataV8 = inp->ToObject()->Get(Nan::New<String>("MultimeterData").ToLocalChecked())->ToObject();
    return {
        Get("numberOfPhases", obj),
        Get("supplyVoltage", obj),
        Get("averageCurrent", obj),
        Get("powerFactor", obj)
    };
}

NameplateData getNameplateData(Local<Object> obj) {
    // auto nameplateDataV8 = inp->ToObject()->Get(Nan::New<String>("NameplateData").ToLocalChecked())->ToObject();
    return {
        Get("ratedMotorPower", obj),
        Get("variableSpeedMotor", obj),
        Get("operationalFrequency", obj),
        Get("lineFrequency", obj),
        Get("motorAndDriveEfficiency", obj),
        Get("loadFactor", obj)
    };
}

PowerMeterData getPowerMeterData(Local<Object> obj) {
    // auto powerMeterDataV8 = inp->ToObject()->Get(Nan::New<String>("PowerMeterData").ToLocalChecked())->ToObject();
    return {
        Get("power", obj)
    };
}

OtherMethodData getOtherMethodData(Local<Object> obj) {
    // auto otherMethodDataV8 = inp->ToObject()->Get(Nan::New<String>("OtherMethodData").ToLocalChecked())->ToObject();
    return {
        Get("energy", obj)
    };
}

ElectricityReductionInput constructElectricityReductionInput(Local<Object> obj) {
    return {
        Get("hoursPerDay", obj),
        Get("daysPerMonth", obj),
        Get("monthsPerYear", obj),
        Get("electricityCost", obj),
        Get("measurementMethod", obj),
        getMultimeterData(obj),
        getNameplateData(obj),
        getPowerMeterData(obj),
        getOtherMethodData(obj)
    };
}

std::vector<ElectricityReductionInput> getElectricityReductionInputVector() {
    auto electricityReductionInputVecV8 = inp->ToObject()->Get(Nan::New<String>("electricityReductionInputVec").ToLocalChecked());


    // auto const electricityReductionInputVecTemp = electricityReductionInputVecV8->Get(Nan::New<String>("electricityRe"))
    auto const electricityReductionInputVecTemp = inp->ToObject()->Get(Nan::New<String>("electricityReductionInputVec").ToLocalChecked());
    auto const & electricityReductionInputArray = v8::Local<v8::Array>::Cast(electricityReductionInputVecTemp);
    std::vector<ElectricityReductionInput> inputVec;

    std::cout << "length here = " << electricityReductionInputArray->Length() << std::endl;

    for (std::size_t i = 0; i < electricityReductionInputArray->Length(); i++) {
        inputVec.emplace_back(constructElectricityReductionInput(electricityReductionInputArray->Get(i)->ToObject()));
    }
    return inputVec;
}


NAN_METHOD(electricityReduction) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    auto inputVec = getElectricityReductionInputVector();

    try {
        auto rv = ElectricityReduction(inputVec);
        // std::cout << "inputVec.Length().ToString() = " << inputVec->Length()->ToString() << std::endl;        
    } catch (std::runtime_error const & e) {
        // std::string const what = e.what();
        // throwLogicError(std::string("std::runtime_error thrown in electricityReduction - calculator.h: " + what).c_str());
    }
}



// NAN_METHOD(electricityReduction) {
//     inp = info[0]->ToObject();
//     r = Nan::New<Object>();

//     Local <String> arrayStr = Nan::New<String>("electricityReductionData").ToLocalChecked();
//     auto array = inp->ToObject()->Get(arrayStr);
//     auto const & arr = v8::Local<v8::Array>::Cast(array);
//     // v8::Local <v8::Array> arr = v8::Local<v8::Array>::Cast(array);

//     auto energyUseStr = Nan::New<String>("energyUse").ToLocalChecked();
//     auto energyCostStr = Nan::New<String>("energyCost").ToLocalChecked();
//     auto annualEnergySavingsStr = Nan::New<String>("annualEnergySavings").ToLocalChecked();
//     auto costSavingsStr = Nan::New<String>("costSavings").ToLocalChecked();

//     std::vector<ElectricityReductionInput> electricityReductionInputVec;

//     for (std::size_t i = 0; i < arr.Length(); i++) {
//         auto const hoursPerDay = arr->Get(i)->ToObject()->Get(hoursPerDay)->NumberValue();
//         auto const daysPerMonth = arr->Get(i)->ToObject()->Get(daysPerMonth)->NumberValue();
//         auto const monthsPerYear = arr->Get(i)->ToObject()->Get(monthsPerYear)->NumberValue();
//         auto const electricityCost = arr->Get(i)->ToObject()->Get(electricityCost)->NumberValue();
//         auto const measurementMethod = arr->Get(i)->ToObject()->Get(measurementMethod)->NumberValue();
//         auto const multimeterData = arr->Get(i)->ToObject()->Get(multimeterData)->ToObject();
//         auto const nameplateData = arr->Get(i)->ToObject()->Get(nameplateData)->ToObject();
//         auto const powerMeterData = arr->Get(i)->ToObject()->Get(powerMeterData)->ToObject();
//         auto const otherMethodData = arr->Get(i)->ToObject()->Get(otherMethodData)->ToObject();
//         auto const units = arr->Get(i)->ToObject()->Get(units)->NumberValue();
//         electricityReductionInputVec.emplace_back(
//             ElectricityReductionInput(hoursPerDay, daysPerMonth, monthsPerYear,
//                                       electricityCost, measurementMethod, multimeterData, 
//                                       nameplateData, powerMeterData, otherMethodData, units)
//         );

//         // Local <Object> obj = Nan::New<Object>();
//         // Local <String> electricityReductionInputNum = Nan::New<String>("electricityReductionInput" + std::to_string(i))
//         // auto const electricity
//     }

//     try {
//         auto electricityReduction = ElectricityReduction(electricityReductionInputVec).calculate();
//         Local <String> electricityReductionResultsStr = Nan::New<String>("electricityReductionResults");

//         auto const electricityReductionResults = electricityReduction.getOutput();
//         Local <Object> obj = Nan::New<Object>();

//         Nan::Set(obj, energyUseStr, Nan::New<Number>(electricityReductionResults.energyUse));
//         Nan::Set(obj, energyCostStr, Nan::New<Number>(electricityReductionResults.energyCost));
//         Nan::Set(obj, annualEnergySavingsStr, Nan::New<Number>(electricityReductionResults.annualEnergySavingsStr));
//         Nan::Set(obj, costSavingsStr, Nan::New<Number>(electricityReductionResults.costSavings));

//         Nan::Set(r, electricityReductionResultsStr, obj);
//     } catch {
//         std::string const what = e.what();
//         throwLogicError(std::string)"std::runtime_error thrown in electricityReduction - calculator.h: " + what).c_str();
//     }
//     info.GetReturnValue().Set(r);
// }
