#include <nan.h>
#include <node.h>
#include "fans/Fan.h"
#include "fans/FanShaftPower.h"
#include "fans/Planar.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	auto rObj = inp->ToObject()->Get(getName);
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in fan.h: " + nm + " not present in object").c_str());
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

void SetR(const char *nm, double n) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	Local<Number> getNum = Nan::New<Number>(n);
	Nan::Set(r, getName, getNum);
}

NAN_METHOD(fanPlaceholder) {
	inp = info[0]->ToObject();

	double const fanSpeed = Get("fanSpeed"), motorSpeed = Get("motorSpeed"), fanSpeedCorrected = Get("fanSpeedCorrected");
	double const densityCorrected = Get("densityCorrected"), pressureBarometricCorrected = Get("pressureBarometricCorrected");

	auto fanRatedInfo = FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);

//	std::string
//	FanInletFlange::FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
//	                               const double tdx, const double pbx)



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


	Local<Object> obj = Nan::New<Object>();
//	Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
//	Nan::Set(obj, pumpHead, Nan::New<Number>(rv["pumpHead"]));

	info.GetReturnValue().Set(obj);
}
