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

double Get(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

bool GetBool(std::string const & key, Local<Object> obj) {
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: Boolean value " + key + " not present in object").c_str());
	}
	return rObj->BooleanValue();
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
		auto const noInletBoxes = (isUndefined(planeType, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", innerObj));
		return {Get("length", innerObj), Get("width", innerObj), Get("tdx", innerObj), Get("pbx", innerObj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", innerObj), Get("tdx", innerObj), Get("pbx", innerObj)};
}

template <class Plane> Plane constructMst(std::string const & planeType) {
	auto innerObj = inp->ToObject()->Get(Nan::New<String>(planeType).ToLocalChecked())->ToObject();

	if (isUndefined(planeType, "circularDuctDiameter")) {
		auto const noInletBoxes = (isUndefined(planeType, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", innerObj));
		return {Get("length", innerObj), Get("width", innerObj), Get("tdx", innerObj), Get("pbx", innerObj), Get("psx", innerObj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", innerObj), Get("tdx", innerObj), Get("pbx", innerObj), Get("psx", innerObj)};
}

template <class Plane> Plane constructTraverse(Local<Object> obj) {
	if (isUndefined(obj, "circularDuctDiameter")) {
		unsigned const noInletBoxes = (isUndefined(obj, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", obj));
		return {Get("length", obj), Get("width", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj)};
}

PlaneData getPlaneData() {
	std::vector<AddlTravPlane> addlTravPlanes;
	auto const addlTravTmp = inp->ToObject()->Get(Nan::New<String>("AddlTraversePlanes").ToLocalChecked());
	auto const & addlTravArray = v8::Local<v8::Array>::Cast(addlTravTmp);
	for (std::size_t i = 0; i < addlTravArray->Length(); i++) {
		addlTravPlanes.emplace_back(constructTraverse<AddlTravPlane>(addlTravArray->Get(i)->ToObject()));
	}

	auto planeDataV8 = inp->ToObject()->Get(Nan::New<String>("PlaneData").ToLocalChecked())->ToObject();

	return {
			construct<FanInletFlange>("FanInletFlange"),
			construct<FanOrEvaseOutletFlange>("FanEvaseOrOutletFlange"),
			constructTraverse<FlowTraverse>(inp->ToObject()->Get(Nan::New<String>("FlowTraverse").ToLocalChecked())->ToObject()),
			std::move(addlTravPlanes),
			constructMst<InletMstPlane>("InletMstPlane"),
			constructMst<OutletMstPlane>("OutletMstPlane"),
			Get("totalPressureLossBtwnPlanes1and4", planeDataV8),
			Get("totalPressureLossBtwnPlanes2and5", planeDataV8),
			GetBool("plane5upstreamOfPlane2", planeDataV8)
	};
}

NAN_METHOD(fanPlaceholder) {
	inp = info[0]->ToObject();

	auto fanRatedInfoV8 = inp->ToObject()->Get(Nan::New<String>("FanRatedInfo").ToLocalChecked())->ToObject();
	auto const fanSpeed = Get("fanSpeed", fanRatedInfoV8), motorSpeed = Get("motorSpeed", fanRatedInfoV8);
	auto const fanSpeedCorrected = Get("fanSpeedCorrected", fanRatedInfoV8);
	auto const densityCorrected = Get("densityCorrected", fanRatedInfoV8);
	auto const pressureBarometricCorrected = Get("pressureBarometricCorrected", fanRatedInfoV8);

	auto fanRatedInfo = FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);
	auto planeData = getPlaneData();



//	Local<Object> obj = Nan::New<Object>();
//	Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
//	Nan::Set(obj, pumpHead, Nan::New<Number>(rv["pumpHead"]));

//	info.GetReturnValue().Set(addlTravPlanes.size());

	r = Nan::New<Object>();
//	SetR("addlTravPlanesSize", addlTravPlanes.size());
	info.GetReturnValue().Set(r);
}
