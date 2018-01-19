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

double Get(std::string const & key) {
	auto const & rObj = inp->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

double Get(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

std::string GetStr(std::string const & key) {
	auto const & obj = inp->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (obj->IsUndefined()) {
		ThrowTypeError(std::string("GetStr method in fan.h: " + key + " not present in object").c_str());
	}
	v8::String::Utf8Value s(obj);
	return std::string(*s);
}

bool isUndefined(std::string const & objName, std::string const & key) {
	auto const & obj = inp->ToObject()->Get(Nan::New<String>(objName).ToLocalChecked());
	if (obj->IsUndefined()) {
		ThrowTypeError(std::string("isUndefined method in fan.h: " + objName + " is undefined").c_str());
	}
	auto const & innerObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	return innerObj->IsUndefined();
}

bool isUndefined(Local<Object> obj, std::string const & key) {
	return obj->Get(Nan::New<String>(key).ToLocalChecked())->IsUndefined();
}

void SetR(const char *nm, double n) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	Local<Number> getNum = Nan::New<Number>(n);
	Nan::Set(r, getName, getNum);
}

std::vector <std::vector<double>> getTraverseInputData(std::string const & innerObj) {
	auto const & plane = inp->ToObject()->Get(Nan::New<String>(innerObj).ToLocalChecked());
	auto const & arrayTmp = plane->ToObject()->Get(Nan::New<String>("traverseData").ToLocalChecked());
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

std::vector <std::vector<double>> getTraverseInputData(Local<Object> innerObj) {
//	auto const & plane = inp->ToObject()->Get(Nan::New<String>(innerObj).ToLocalChecked());
	auto const & arrayTmp = innerObj->Get(Nan::New<String>("traverseData").ToLocalChecked());
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
	auto innerObj = inp->ToObject()->Get(Nan::New<String>(planeType).ToLocalChecked())->ToObject();

	if (isUndefined(planeType, "circularDuctDiameter")) {
		return {Get("length", innerObj), Get("width", innerObj), Get("tdx", innerObj), Get("pbx", innerObj)};
	}
	return {Get("circularDuctDiameter", innerObj), Get("tdx", innerObj), Get("pbx", innerObj)};
}

//template <class Plane> Plane constructTraverse(std::string const & planeType) {
//	auto innerObj = inp->ToObject()->Get(Nan::New<String>(planeType).ToLocalChecked())->ToObject();
//
//	if (isUndefined(planeType, "circularDuctDiameter")) {
//		return {Get("length", innerObj), Get("width", innerObj), Get("tdx", innerObj), Get("pbx", innerObj), Get("psx", innerObj), Get("pitotTubeCoefficient", innerObj), getTraverseInputData(planeType)};
//	}
//	return {Get("circularDuctDiameter", innerObj), Get("tdx", innerObj), Get("pbx", innerObj), Get("psx", innerObj), Get("pitotTubeCoefficient", innerObj), getTraverseInputData(planeType)};
//}

template <class Plane> Plane constructTraverse(Local<Object> obj) {
//	auto innerObj = inp->ToObject()->Get(Nan::New<String>(planeType).ToLocalChecked())->ToObject();

	if (isUndefined(obj, "circularDuctDiameter")) {
		return {Get("length", obj), Get("width", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj)};
	}
	return {Get("circularDuctDiameter", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj)};
}

NAN_METHOD(fanPlaceholder) {
	inp = info[0]->ToObject();

	double const fanSpeed = Get("fanSpeed"), motorSpeed = Get("motorSpeed"), fanSpeedCorrected = Get("fanSpeedCorrected");
	double const densityCorrected = Get("densityCorrected"), pressureBarometricCorrected = Get("pressureBarometricCorrected");

	auto fanRatedInfo = FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);

	auto fanInletFlange = construct<FanInletFlange>("FanInletFlange");
	auto fanOrEvaseOutletFlange = construct<FanOrEvaseOutletFlange>("FanEvaseOrOutletFlange");
//	auto flowTraverse = constructTraverse<FlowTraverse>("FlowTraverse");
	auto flowTraverse = constructTraverse<FlowTraverse>(inp->ToObject()->Get(Nan::New<String>("FlowTraverse").ToLocalChecked())->ToObject());

	// now extract and create the vector of AddlTravPlanes
//	std::vector<AddlTravPlane> addlTravPlanes;
//	auto const addlTravTmp = inp->ToObject()->Get(Nan::New<String>("AddlTraversePlanes").ToLocalChecked());
//	auto const & addlTravArray = v8::Local<v8::Array>::Cast(addlTravTmp);
//	for (std::size_t i = 0; i < addlTravArray->Length(); i++) {
//		addlTravPlanes.emplace_back(constructTraverse<AddlTravPlane>())
//	}


//	auto addlTraverse = constructTraverse<AddlTravPlane>("AddlTraverse");

	Local<Object> obj = Nan::New<Object>();
//	Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
//	Nan::Set(obj, pumpHead, Nan::New<Number>(rv["pumpHead"]));

	info.GetReturnValue().Set(obj);
}
