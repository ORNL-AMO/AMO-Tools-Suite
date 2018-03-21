#include <nan.h>
#include <node.h>
#include <string>
#include <vector>
#include "fans/Planar.h"
#include "fans/Fan.h"
#include "fans/FanShaftPower.h"
#include "fans/FanCurve.h"

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

bool isDefined(Local<Object> obj, std::string const & key) {
	return !obj->Get(Nan::New<String>(key).ToLocalChecked())->IsUndefined();
}

inline void SetR(const std::string & key, double val) {
	Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
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

FlangePlane constructFlange(Local<Object> obj) {
	return {Get("area", obj), Get("dryBulbTemp", obj), Get("barometricPressure", obj)};
}

MstPlane constructMst(Local<Object> obj) {
	return {Get("area", obj), Get("dryBulbTemp", obj), Get("barometricPressure", obj), Get("staticPressure", obj)};
}

TraversePlane constructTraverse(Local<Object> obj) {
	return {Get("area", obj), Get("dryBulbTemp", obj), Get("barometricPressure", obj), Get("staticPressure", obj), Get("pitotTubeCoefficient", obj), getTraverseInputData(obj)};
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
	std::vector<TraversePlane> addlTravPlanes;

	for (std::size_t i = 0; i < addlTravArray->Length(); i++) {
		addlTravPlanes.emplace_back(constructTraverse(addlTravArray->Get(i)->ToObject()));
	}

	return {
			constructFlange(planeDataV8->Get(Nan::New<String>("FanInletFlange").ToLocalChecked())->ToObject()),
			constructFlange(planeDataV8->Get(Nan::New<String>("FanEvaseOrOutletFlange").ToLocalChecked())->ToObject()),
			constructTraverse(planeDataV8->Get(Nan::New<String>("FlowTraverse").ToLocalChecked())->ToObject()),
			std::move(addlTravPlanes),
			constructMst(planeDataV8->Get(Nan::New<String>("InletMstPlane").ToLocalChecked())->ToObject()),
			constructMst(planeDataV8->Get(Nan::New<String>("OutletMstPlane").ToLocalChecked())->ToObject()),
			Get("totalPressureLossBtwnPlanes1and4", planeDataV8),
			Get("totalPressureLossBtwnPlanes2and5", planeDataV8),
			GetBool("plane5upstreamOfPlane2", planeDataV8)
	};
}

BaseGasDensity::GasType getGasType(Local<Object> obj) {
	auto const & gasTypeStr = GetStr("gasType", obj);
	if (gasTypeStr == "AIR") {
		return BaseGasDensity::GasType::AIR;
	} else if (gasTypeStr == "STANDARDAIR") {
		return BaseGasDensity::GasType::STANDARDAIR;
	}
	return BaseGasDensity::GasType::OTHERGAS;
};

BaseGasDensity::InputType getInputType(Local<Object> obj) {
	auto const & inputTypeStr = GetStr("inputType", obj);
	if (inputTypeStr == "relativeHumidity") {
		return BaseGasDensity::InputType::RelativeHumidity;
	} else if (inputTypeStr == "dewPoint") {
		return BaseGasDensity::InputType::DewPoint;
	}
	return BaseGasDensity::InputType::WetBulbTemp;
};


NAN_METHOD(getBaseGasDensityRelativeHumidity) {
	inp = info[0]->ToObject();
	try {
		info.GetReturnValue().Set(
				BaseGasDensity(
						Get("dryBulbTemp", inp->ToObject()),
						Get("staticPressure", inp->ToObject()),
						Get("barometricPressure", inp->ToObject()),
						Get("relativeHumidity", inp->ToObject()),
						getGasType(inp->ToObject()),
						getInputType(inp->ToObject()),
						Get("specificGravity", inp->ToObject())
				).getGasDensity()
		);
	} catch (std::runtime_error const & e) {
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityRelativeHumidity - fan.h: " + what).c_str());
	}
}

NAN_METHOD(getBaseGasDensityDewPoint) {
	inp = info[0]->ToObject();
	try {
		info.GetReturnValue().Set(
				BaseGasDensity(
						Get("dryBulbTemp", inp->ToObject()),
						Get("staticPressure", inp->ToObject()),
						Get("barometricPressure", inp->ToObject()),
						Get("dewPoint", inp->ToObject()),
						getGasType(inp->ToObject()),
						getInputType(inp->ToObject()),
						Get("specificGravity", inp->ToObject())
				).getGasDensity()
		);
	} catch (std::runtime_error const & e) {
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityDewPoint - fan.h: " + what).c_str());
	}
}

NAN_METHOD(getBaseGasDensityWetBulb) {
	inp = info[0]->ToObject();
	try {
		info.GetReturnValue().Set(
				BaseGasDensity(
						Get("dryBulbTemp", inp->ToObject()),
						Get("staticPressure", inp->ToObject()),
						Get("barometricPressure", inp->ToObject()),
						Get("wetBulbTemp", inp->ToObject()),
						getGasType(inp->ToObject()),
						getInputType(inp->ToObject()),
						Get("specificGravity", inp->ToObject()),
						Get("specificHeatGas", inp->ToObject())
				).getGasDensity()
		);
	} catch (std::runtime_error const & e) {
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityWetBulb - fan.h: " + what).c_str());
	}
}

BaseGasDensity getBaseGasDensity() {
	auto baseGasDensityV8 = inp->ToObject()->Get(Nan::New<String>("BaseGasDensity").ToLocalChecked())->ToObject();
	return {
			Get("dryBulbTemp", baseGasDensityV8),
			Get("staticPressure", baseGasDensityV8),
			Get("barometricPressure", baseGasDensityV8),
			Get("gasDensity", baseGasDensityV8),
			getGasType(baseGasDensityV8)
	};
}

FanShaftPower getFanShaftPower() {
	auto fanShaftPowerV8 = inp->ToObject()->Get(Nan::New<String>("FanShaftPower").ToLocalChecked())->ToObject();
	return {
			Get("motorShaftPower", fanShaftPowerV8),
			Get("efficiencyMotor", fanShaftPowerV8),
			Get("efficiencyVFD", fanShaftPowerV8),
			Get("efficiencyBelt", fanShaftPowerV8),
			Get("sumSEF", fanShaftPowerV8)
	};
}

NAN_METHOD(getVelocityPressureData) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	auto const travPlane = constructTraverse(inp->ToObject());
	SetR("pv3", travPlane.getPv3Value());
	SetR("percent75Rule", travPlane.get75percentRule() * 100);
	info.GetReturnValue().Set(r);
}


NAN_METHOD(getPlaneResults) {
	Local<Object> rv = Nan::New<Object>();
	inp = info[0]->ToObject();

	try {
		auto planeData = getPlaneData();
		auto baseGasDensity = getBaseGasDensity();
		auto const output = PlaneData::NodeBinding::calculate(planeData, baseGasDensity);
		Handle<Array> addlTravPlanes = Array::New(v8::Isolate::GetCurrent(), output.addlTravPlanes.size());
		std::size_t index = 0;

		auto const setData = [&rv, &addlTravPlanes, &index](const PlaneData::NodeBinding::Data & data, std::string const & name,
													bool isArray = false, bool isStaticPressure = false, const double staticPressure = 0) {
			r = Nan::New<Object>();
			SetR("gasDensity", data.gasDensity);
			SetR("gasVolumeFlowRate", data.gasVolumeFlowRate);
			SetR("gasVelocity", data.gasVelocity);
			SetR("gasVelocityPressure", data.gasVelocityPressure);
			SetR("gasTotalPressure", data.gasTotalPressure);
			if (isStaticPressure) {
				SetR("staticPressure", staticPressure);
			}

			if (isArray) {
				addlTravPlanes->Set(index, r);
			} else {
				Nan::Set(rv, Nan::New<String>(name).ToLocalChecked(), r);
			}
		};

		for (auto const & data : output.addlTravPlanes) {
			setData(data, "", true);
			index++;
		}
		Nan::Set(rv, Nan::New<String>("AddlTraversePlanes").ToLocalChecked(), addlTravPlanes);

		setData(output.fanInletFlange, "FanInletFlange", false, true, output.fanInletFlange.staticPressure);
		setData(output.fanOrEvaseOutletFlange, "FanOrEvaseOutletFlange", false, true, output.fanOrEvaseOutletFlange.staticPressure);
		setData(output.flowTraverse, "FlowTraverse");
		setData(output.inletMstPlane, "InletMstPlane");
		setData(output.outletMstPlane, "OutletMstPlane");
	} catch (std::runtime_error const & e) {
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getPlaneResults - fan.h: " + what).c_str());
	}

	info.GetReturnValue().Set(rv);
}

NAN_METHOD(fan203) {
	inp = info[0]->ToObject();

	r = Nan::New<Object>();
	try {
		auto const rv = Fan(getFanRatedInfo(), getPlaneData(), getBaseGasDensity(), getFanShaftPower()).calculate();
		SetR("fanEfficiencyTotalPressure", rv.fanEfficiencyTotalPressure);
		SetR("fanEfficiencyStaticPressure", rv.fanEfficiencyStaticPressure);
		SetR("fanEfficiencyStaticPressureRise", rv.fanEfficiencyStaticPressureRise);
		SetR("flowCorrected", rv.flowCorrected);
		SetR("pressureTotalCorrected", rv.pressureTotalCorrected);
		SetR("pressureStaticCorrected", rv.pressureStaticCorrected);
		SetR("staticPressureRiseCorrected", rv.staticPressureRiseCorrected);
		SetR("powerCorrected", rv.powerCorrected);
		SetR("kpc", rv.kpc);
	} catch (std::runtime_error const & e) {
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in fan203 - fan.h: " + what).c_str());
	}

	info.GetReturnValue().Set(r);
}

FanCurveType getFanCurveType() {
	auto const curveTypeStr = GetStr("curveType", inp);
	if (curveTypeStr == "StaticPressureRise") {
		return FanCurveType::StaticPressureRise;
	} else if (curveTypeStr == "FanTotalPressure") {
		return FanCurveType::FanTotalPressure;
	}
	return FanCurveType::FanStaticPressure;
}

FanCurveData getFanBaseCurveData() {

	auto const & arrayTmp = inp->ToObject()->Get(Nan::New<String>("BaseCurveData").ToLocalChecked());
	auto const & array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::BaseCurve> curveData;
	for (std::size_t i = 0; i < array->Length(); i++) {
		auto const & innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		curveData.emplace_back(FanCurveData::BaseCurve(innerArray->Get(0)->NumberValue(),
		                                               innerArray->Get(1)->NumberValue(),
		                                               innerArray->Get(2)->NumberValue()));
	}

	return {getFanCurveType(), std::move(curveData)};
}
FanCurveData getFanRatedPointCurveData() {
	auto const & arrayTmp = inp->ToObject()->Get(Nan::New<String>("RatedPointCurveData").ToLocalChecked());
	auto const & array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::RatedPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++) {
		auto const & innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		curveData.emplace_back(FanCurveData::RatedPoint(innerArray->Get(0)->NumberValue(),
		                                                innerArray->Get(1)->NumberValue(),
		                                                innerArray->Get(2)->NumberValue(),
		                                                innerArray->Get(3)->NumberValue(),
		                                                innerArray->Get(4)->NumberValue(),
		                                                innerArray->Get(5)->NumberValue()));
	}
	return {getFanCurveType(), std::move(curveData)};
}
FanCurveData getFanBaseOperatingPointCurveData() {
	auto const & arrayTmp = inp->ToObject()->Get(Nan::New<String>("BaseOperatingPointCurveData").ToLocalChecked());
	auto const & array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::BaseOperatingPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++) {
		auto const & innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		curveData.emplace_back(FanCurveData::BaseOperatingPoint(innerArray->Get(0)->NumberValue(),
		                                                        innerArray->Get(1)->NumberValue(),
		                                                        innerArray->Get(2)->NumberValue(),
		                                                        innerArray->Get(3)->NumberValue(),
		                                                        innerArray->Get(4)->NumberValue(),
		                                                        innerArray->Get(5)->NumberValue(),
		                                                        innerArray->Get(6)->NumberValue(),
		                                                        innerArray->Get(7)->NumberValue(),
		                                                        innerArray->Get(8)->NumberValue()));
	}

	return {getFanCurveType(), std::move(curveData)};
}

void returnResultData(std::vector<ResultData> const & results) {
	std::size_t index = 0;
	Handle<Array> outerArray = Array::New(v8::Isolate::GetCurrent(), results.size());
	for (auto const & row : results) {
		Handle<Array> array = Array::New(v8::Isolate::GetCurrent(), 4);
		array->Set(0, Nan::New<Number>(row.flow));
		array->Set(1, Nan::New<Number>(row.pressure));
		array->Set(2, Nan::New<Number>(row.power));
		array->Set(3, Nan::New<Number>(row.efficiency));
		outerArray->Set(index, array);
		index++;
	}
	Nan::Set(r, Nan::New<String>("ResultData").ToLocalChecked(), outerArray);
}

// fan performance curves
NAN_METHOD(fanCurve) {
	inp = info[0]->ToObject();

	r = Nan::New<Object>();
	if (isDefined(inp->ToObject(), "BaseCurveData")) {
		auto const rv = FanCurve(Get("density", inp), Get("densityCorrected", inp), Get("speed", inp),
		                         Get("speedCorrected", inp), Get("pressureBarometric", inp), Get("pressureBarometricCorrected", inp), Get("pt1Factor", inp),
		                         Get("gamma", inp), Get("gammaCorrected", inp), Get("area1", inp), Get("area2", inp),
		                         getFanBaseCurveData()).calculate();
		returnResultData(rv);
	} else if (isDefined(inp->ToObject(), "RatedPointCurveData")) {
		auto const rv = FanCurve(Get("density", inp), Get("densityCorrected", inp), Get("speed", inp),
		                         Get("speedCorrected", inp), Get("pressureBarometric", inp), Get("pressureBarometricCorrected", inp), Get("pt1Factor", inp),
		                         Get("gamma", inp), Get("gammaCorrected", inp), Get("area1", inp), Get("area2", inp),
		                         getFanRatedPointCurveData()).calculate();
		returnResultData(rv);
	} else {
		auto const rv = FanCurve(Get("density", inp), Get("densityCorrected", inp), Get("speed", inp),
		                         Get("speedCorrected", inp), Get("pressureBarometric", inp), Get("pressureBarometricCorrected", inp), Get("pt1Factor", inp),
		                         Get("gamma", inp), Get("gammaCorrected", inp), Get("area1", inp), Get("area2", inp),
		                         getFanBaseOperatingPointCurveData()).calculate();
		returnResultData(rv);
	}

	info.GetReturnValue().Set(r);
}
