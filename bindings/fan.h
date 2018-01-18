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
	auto const arrayTmp = plane->ToObject()->Get(Nan::New<String>("traverseData").ToLocalChecked());
	auto const & array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<std::vector <double> > traverseData(array->Length());
	for (std::size_t i = 0; i < array->Length(); i++) {
		auto const & innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		traverseData.at(i).resize(innerArray->Length());
		for (std::size_t j = 0; j < innerArray->Length(); j++) {
			traverseData.at(i).at(j) = innerArray->Get(j)->NumberValue();
		}
	}

	return traverseData;
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
