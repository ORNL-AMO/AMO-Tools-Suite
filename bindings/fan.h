#include <nan.h>
#include <node.h>
#include <string>
#include <vector>
#include "fans/Planar.h"
#include "fans/Fan.h"
#include "fans/FanShaftPower.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & key, std::string const & innerObj = "") {
	Local<String> getName = Nan::New<String>(key).ToLocalChecked();
	Local<String> innerObjName = Nan::New<String>(innerObj).ToLocalChecked();

	auto rObj = (innerObj.empty()) ? inp->ToObject()->Get(getName) : inp->ToObject()->Get(innerObjName)->ToObject()->Get(getName);
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

std::string GetStr(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	auto obj = inp->ToObject()->Get(getName);
	if (obj->IsUndefined()) {
		ThrowTypeError(std::string("GetStr method in fan.h: " + nm + " not present in object").c_str());
	}
	v8::String::Utf8Value s(obj);
	return std::string(*s);
}

bool isUndefined(std::string const & objName, std::string const & key) {
	Local<String> objName_ = Nan::New<String>(objName).ToLocalChecked();
	Local<String> key_ = Nan::New<String>(key).ToLocalChecked();
	auto obj = inp->ToObject()->Get(objName_);
	if (obj->IsUndefined()) {
		ThrowTypeError(std::string("isUndefined method in fan.h: " + objName + " is undefined").c_str());
	}
	auto innerObj = obj->ToObject()->Get(key_);
	return innerObj->IsUndefined();
}

void SetR(const char *nm, double n) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	Local<Number> getNum = Nan::New<Number>(n);
	Nan::Set(r, getName, getNum);
}

std::vector <std::vector<double>> getTraverseInputData(std::string const & innerObj) {
	auto const plane = inp->ToObject()->Get(Nan::New<String>(innerObj).ToLocalChecked());
	auto const array = plane->ToObject()->Get(Nan::New<String>("traverseData").ToLocalChecked());

	return {
			{
					0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130
			},
			{
					0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865
			},
			{
					0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569
			}
	};

//	Local<String> arrayStr = Nan::New<String>("inlets").ToLocalChecked();
//	auto array = inp->ToObject()->Get(arrayStr);
//	v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(array);
//
//	auto pressureStr = Nan::New<String>("pressure").ToLocalChecked();
//	auto temperatureStr = Nan::New<String>("temperature").ToLocalChecked();
//	auto qualityStr = Nan::New<String>("quality").ToLocalChecked();
//	auto massFlowStr = Nan::New<String>("massFlow").ToLocalChecked();
//	auto specificEnthalpyStr = Nan::New<String>("specificEnthalpy").ToLocalChecked();
//	auto specificEntropyStr = Nan::New<String>("specificEntropy").ToLocalChecked();
//	auto energyFlowStr = Nan::New<String>("energyFlow").ToLocalChecked();
//
//	std::vector<Inlet> inlets;
//
//	for (std::size_t i = 0; i < arr->Length(); i++) {
//		auto const pressure = arr->Get(i)->ToObject()->Get(pressureStr)->NumberValue();
//		unsigned val = static_cast<unsigned>(arr->Get(i)->ToObject()->Get(Nan::New<String>("thermodynamicQuantity").ToLocalChecked())->NumberValue());
//		auto const quantity = static_cast<SteamProperties::ThermodynamicQuantity>(val);
//		auto const quantityValue = arr->Get(i)->ToObject()->Get(Nan::New<String>("quantityValue").ToLocalChecked())->NumberValue();
//		auto const massFlow = arr->Get(i)->ToObject()->Get(massFlowStr)->NumberValue();
//		inlets.emplace_back(Inlet(pressure, quantity, quantityValue, massFlow));
//
//		Local<Object> obj = Nan::New<Object>();
//		Local<String> inletNum = Nan::New<String>("inlet" + std::to_string(i + 1)).ToLocalChecked();
//		auto const inletProps = inlets[i].getInletProperties();
//
//		Nan::Set(obj, pressureStr, Nan::New<Number>(inletProps.at("pressure")));
//		Nan::Set(obj, temperatureStr, Nan::New<Number>(inletProps.at("temperature")));
//		Nan::Set(obj, qualityStr, Nan::New<Number>(inletProps.at("quality")));
//		Nan::Set(obj, specificEnthalpyStr, Nan::New<Number>(inletProps.at("specificEnthalpy")));
//		Nan::Set(obj, specificEntropyStr, Nan::New<Number>(inletProps.at("specificEntropy")));
//		Nan::Set(obj, energyFlowStr, Nan::New<Number>(inlets[i].getInletEnergyFlow()));
//		Nan::Set(obj, massFlowStr, Nan::New<Number>(inlets[i].getMassFlow()));
//
//		Nan::Set(r, inletNum, obj);
//	}
}


template <class Plane> Plane construct(std::string const & planeType) {
	if (isUndefined(planeType, "circularDuctDiameter")) {
		return {Get("length", planeType), Get("width", planeType), Get("tdx", planeType), Get("pbx", planeType)};
	}
	return {Get("circularDuctDiameter", planeType), Get("tdx", planeType), Get("pbx", planeType)};
}

template <class Plane> Plane constructTraverse(std::string const & planeType) {
	if (isUndefined(planeType, "circularDuctDiameter")) {
		return {Get("length", planeType), Get("width", planeType), Get("tdx", planeType), Get("pbx", planeType), Get("psx", planeType), Get("pitotTubeCoefficient", planeType), getTraverseInputData(planeType)};
	}
	return {Get("circularDuctDiameter", planeType), Get("tdx", planeType), Get("pbx", planeType), Get("psx", planeType), Get("pitotTubeCoefficient", planeType), getTraverseInputData(planeType)};
}

NAN_METHOD(fanPlaceholder) {
	inp = info[0]->ToObject();

	double const fanSpeed = Get("fanSpeed"), motorSpeed = Get("motorSpeed"), fanSpeedCorrected = Get("fanSpeedCorrected");
	double const densityCorrected = Get("densityCorrected"), pressureBarometricCorrected = Get("pressureBarometricCorrected");

	auto fanRatedInfo = FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);

	auto fanInletFlange = construct<FanInletFlange>("FanInletFlange");
	auto fanOrEvaseOutletFlange = construct<FanOrEvaseOutletFlange>("FanEvaseOrOutletFlange");
	auto flowTraverse = constructTraverse<FlowTraverse>("FlowTraverse");

	Local<Object> obj = Nan::New<Object>();
//	Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
//	Nan::Set(obj, pumpHead, Nan::New<Number>(rv["pumpHead"]));

	info.GetReturnValue().Set(obj);
}
