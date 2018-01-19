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

std::string GetStr(std::string const & key, Local<Object> obj) {
	auto const & rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("GetStr method in fan.h: String " + key + " not present in object").c_str());
	}
	v8::String::Utf8Value s(rObj);
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

inline void SetR(const char *key, double val) {
	Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
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

std::vector <std::vector<double>> getTraverseInputData(Local<Object> obj) {
	auto const & arrayTmp = obj->Get(Nan::New<String>("traverseData").ToLocalChecked());
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

template <class Plane> Plane construct(Local<Object> obj) {
	if (isUndefined(obj, "circularDuctDiameter")) {
		auto const noInletBoxes = (isUndefined(obj, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", obj));
		return {Get("length", obj), Get("width", obj), Get("tdx", obj), Get("pbx", obj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", obj), Get("tdx", obj), Get("pbx", obj)};
}

template <class Plane> Plane constructMst(Local<Object> obj) {
	if (isUndefined(obj, "circularDuctDiameter")) {
		auto const noInletBoxes = (isUndefined(obj, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", obj));
		return {Get("length", obj), Get("width", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj)};
}

template <class Plane> Plane constructTraverse(Local<Object> obj) {
	if (isUndefined(obj, "circularDuctDiameter")) {
		unsigned const noInletBoxes = (isUndefined(obj, "noInletBoxes")) ? 1 : static_cast<unsigned>(Get("noInletBoxes", obj));
		return {Get("length", obj), Get("width", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj), noInletBoxes};
	}
	return {Get("circularDuctDiameter", obj), Get("tdx", obj), Get("pbx", obj), Get("psx", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj)};
}

FanRatedInfo getFanRatedInfo() {
	auto fanRatedInfoV8 = inp->ToObject()->Get(Nan::New<String>("FanRatedInfo").ToLocalChecked())->ToObject();
	return {
			Get("fanSpeed", fanRatedInfoV8),
			Get("motorSpeed", fanRatedInfoV8),
			Get("fanSpeedCorrected", fanRatedInfoV8),
			Get("densityCorrected", fanRatedInfoV8),
			Get("pressureBarometricCorrected", fanRatedInfoV8)
	};
}

PlaneData getPlaneData() {
	auto planeDataV8 = inp->ToObject()->Get(Nan::New<String>("PlaneData").ToLocalChecked())->ToObject();

	auto const addlTravTmp = planeDataV8->Get(Nan::New<String>("AddlTraversePlanes").ToLocalChecked());
	auto const & addlTravArray = v8::Local<v8::Array>::Cast(addlTravTmp);
	std::vector<AddlTravPlane> addlTravPlanes;

	for (std::size_t i = 0; i < addlTravArray->Length(); i++) {
		addlTravPlanes.emplace_back(constructTraverse<AddlTravPlane>(addlTravArray->Get(i)->ToObject()));
	}

	return {
			construct<FanInletFlange>(planeDataV8->Get(Nan::New<String>("FanInletFlange").ToLocalChecked())->ToObject()),
			construct<FanOrEvaseOutletFlange>(planeDataV8->Get(Nan::New<String>("FanEvaseOrOutletFlange").ToLocalChecked())->ToObject()),
			constructTraverse<FlowTraverse>(planeDataV8->Get(Nan::New<String>("FlowTraverse").ToLocalChecked())->ToObject()),
			std::move(addlTravPlanes),
			constructMst<InletMstPlane>(planeDataV8->Get(Nan::New<String>("InletMstPlane").ToLocalChecked())->ToObject()),
			constructMst<OutletMstPlane>(planeDataV8->Get(Nan::New<String>("OutletMstPlane").ToLocalChecked())->ToObject()),
			Get("totalPressureLossBtwnPlanes1and4", planeDataV8),
			Get("totalPressureLossBtwnPlanes2and5", planeDataV8),
			GetBool("plane5upstreamOfPlane2", planeDataV8)
	};
}

BaseGasDensity getBaseGasDensity() {
	auto baseGasDensityV8 = inp->ToObject()->Get(Nan::New<String>("BaseGasDensity").ToLocalChecked())->ToObject();
	auto gasTypeStr = GetStr("gasType", baseGasDensityV8);
	BaseGasDensity::GasType gasType;

	if (gasTypeStr == "AIR") {
		gasType = BaseGasDensity::GasType::AIR;
	} else if (gasTypeStr == "STANDARDAIR") {
		gasType = BaseGasDensity::GasType::STANDARDAIR;
	} else {
		gasType = BaseGasDensity::GasType::OTHERGAS;
	}

	return {
			Get("dryBulbTemp", baseGasDensityV8),
			Get("staticPressure", baseGasDensityV8),
			Get("barometricPressure", baseGasDensityV8),
			Get("gasDensity", baseGasDensityV8),
			gasType
	};
}

FanShaftPower getFanShaftPower() {
	auto fanShaftPowerV8 = inp->ToObject()->Get(Nan::New<String>("FanShaftPower").ToLocalChecked())->ToObject();
	auto const isMethodOne = GetBool("isMethodOne", fanShaftPowerV8);

	if (isMethodOne) {
		return {
				Get("hi", fanShaftPowerV8),
				Get("efficiencyMotor", fanShaftPowerV8),
				Get("efficiencyVFD", fanShaftPowerV8),
				Get("efficiencyBelt", fanShaftPowerV8),
				Get("sumSEF", fanShaftPowerV8)
		};
	}

	return {
			Get("voltage", fanShaftPowerV8),
			Get("amps", fanShaftPowerV8),
			Get("powerFactorAtLoad", fanShaftPowerV8),
			Get("efficiencyMotor", fanShaftPowerV8),
			Get("efficiencyVFD", fanShaftPowerV8),
			Get("efficiencyBelt", fanShaftPowerV8),
			Get("sumSEF", fanShaftPowerV8)
	};
}

NAN_METHOD(fanPlaceholder) {
	inp = info[0]->ToObject();

	auto const rv = Fan(getFanRatedInfo(), getPlaneData(), getBaseGasDensity(), getFanShaftPower()).calculate();

	r = Nan::New<Object>();
	SetR("fanEfficiencyTp", rv.at("fanEfficiencyTp"));
	SetR("fanEfficiencySp", rv.at("fanEfficiencySp"));
	SetR("fanEfficiencySpr", rv.at("fanEfficiencySpr"));
	SetR("Qc", rv.at("Qc"));
	SetR("Ptc", rv.at("Ptc"));
	SetR("Psc", rv.at("Psc"));
	SetR("SPRc", rv.at("SPRc"));
	SetR("Hc", rv.at("Hc"));
	SetR("Kpc", rv.at("Kpc"));
	info.GetReturnValue().Set(r);
}
