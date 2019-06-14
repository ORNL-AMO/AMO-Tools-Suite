#include <nan.h>
#include <node.h>
#include <string>
#include <vector>
#include "fans/Planar.h"
#include "fans/Fan203.h"
#include "fans/FanShaftPower.h"
#include "fans/FanCurve.h"
#include "fans/FanEnergyIndex.h"
#include "results/Results.h"
#include "results/InputData.h"
#include "fans/CompressibilityFactor.h"

#include "calculator/pump/OptimalPumpShaftPower.h"
#include "calculator/motor/OptimalMotorShaftPower.h"
#include "calculator/motor/OptimalMotorPower.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

//NAN function for fetching DOUBLE value associated with provided key
double Get(std::string const &key, Local<Object> obj)
{
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined())
	{
		ThrowTypeError(std::string("Get method in fan.h: " + key + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

//NAN function for fetching ENUM value associated with provided key
template <typename T>
T GetEnumVal(std::string const &key, Local<Object> obj)
{
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined())
	{
		ThrowTypeError(std::string("GetEnumVal method in fan.h: " + key + " not present in object").c_str());
	}
	return static_cast<T>(rObj->IntegerValue());
}

//NAN function for fetching BOOLEAN value associated with provided key
bool GetBool(std::string const &key, Local<Object> obj)
{
	auto rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined())
	{
		ThrowTypeError(std::string("GetBool method in fan.h: Boolean value " + key + " not present in object").c_str());
	}
	return rObj->BooleanValue();
}

//NAN function for fetching STRING value associated with provided key
std::string GetStr(std::string const &key, Local<Object> obj)
{
	auto const &rObj = obj->ToObject()->Get(Nan::New<String>(key).ToLocalChecked());
	if (rObj->IsUndefined())
	{
		ThrowTypeError(std::string("GetStr method in fan.h: String " + key + " not present in object").c_str());
	}
	v8::String::Utf8Value s(rObj);
	return std::string(*s);
}

//NAN function for checking if an object parameter has been defined with a value
bool isDefined(Local<Object> obj, std::string const &key)
{
	return !obj->Get(Nan::New<String>(key).ToLocalChecked())->IsUndefined();
}

//NAN function for binding DOUBLE data to anonymous object
inline void SetR(const std::string &key, double val)
{
	Nan::Set(r, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}

//helper functions for building nested array of objects via NAN
std::vector<std::vector<double>> getTraverseInputData(Local<Object> obj)
{
	auto const &arrayTmp = obj->Get(Nan::New<String>("traverseData").ToLocalChecked());
	auto const &array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<std::vector<double>> traverseData(array->Length());
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		auto const &innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		traverseData.at(i).resize(innerArray->Length());
		for (std::size_t j = 0; j < innerArray->Length(); j++)
		{
			traverseData.at(i).at(j) = innerArray->Get(j)->NumberValue();
		}
	}
	return traverseData;
}

FlangePlane constructFlange(Local<Object> obj)
{
	//NAN init data
	const double area = Get("area", obj);
	const double dryBulbTemp = Get("dryBulbTemp", obj);
	const double barometricPressure = Get("barometricPressure", obj);

	//Create C++ obj and return
	FlangePlane flangePlane(area, dryBulbTemp, barometricPressure);
	return flangePlane;
}

MstPlane constructMst(Local<Object> obj)
{
	//NAN init data
	const double area = Get("area", obj);
	const double dryBulbTemp = Get("dryBulbTemp", obj);
	const double barometricPressure = Get("barometricPressure", obj);
	const double staticPressure = Get("staticPressure", obj);

	//Create C++ obj and return
	MstPlane mstPlane(area, dryBulbTemp, barometricPressure, staticPressure);
	return mstPlane;
}

TraversePlane constructTraverse(Local<Object> obj)
{
	//NAN init data
	const double area = Get("area", obj);
	const double dryBulbTemp = Get("dryBulbTemp", obj);
	const double barometricPressure = Get("barometricPressure", obj);
	const double staticPressure = Get("staticPressure", obj);
	const double pitotTubeCoefficient = Get("pitotTubeCoefficient", obj);
	const std::vector<std::vector<double>> traverseInputData = getTraverseInputData(obj);

	//Create C++ obj and return
	TraversePlane traversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData);
	return traversePlane;
}

FanRatedInfo getFanRatedInfo()
{
	//NAN init data
	auto fanRatedInfoV8 = inp->ToObject()->Get(Nan::New<String>("FanRatedInfo").ToLocalChecked())->ToObject();
	const double fanSpeed = Get("fanSpeed", fanRatedInfoV8);
	const double motorSpeed = Get("motorSpeed", fanRatedInfoV8);
	const double fanSpeedCorrected = Get("fanSpeedCorrected", fanRatedInfoV8);
	const double densityCorrected = Get("densityCorrected", fanRatedInfoV8);
	const double pressureBarometricCorrected = Get("pressureBarometricCorrected", fanRatedInfoV8);

	//Create C++ obj and return
	FanRatedInfo fanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);
	return fanRatedInfo;
}

PlaneData getPlaneData()
{
	//NAN init data
	auto planeDataV8 = inp->ToObject()->Get(Nan::New<String>("PlaneData").ToLocalChecked())->ToObject();
	auto const addlTravTmp = planeDataV8->Get(Nan::New<String>("AddlTraversePlanes").ToLocalChecked());
	auto const &addlTravArray = v8::Local<v8::Array>::Cast(addlTravTmp);
	std::vector<TraversePlane> addlTravPlanes;
	//loop to construct array of traverse planes
	for (std::size_t i = 0; i < addlTravArray->Length(); i++)
	{
		addlTravPlanes.emplace_back(constructTraverse(addlTravArray->Get(i)->ToObject()));
	}
	FlangePlane fanInletFlange = constructFlange(planeDataV8->Get(Nan::New<String>("FanInletFlange").ToLocalChecked())->ToObject());
	FlangePlane fanEvaseOrOutletFlange = constructFlange(planeDataV8->Get(Nan::New<String>("FanEvaseOrOutletFlange").ToLocalChecked())->ToObject());
	TraversePlane flowTraverse = constructTraverse(planeDataV8->Get(Nan::New<String>("FlowTraverse").ToLocalChecked())->ToObject());
	MstPlane inletMstPlane = constructMst(planeDataV8->Get(Nan::New<String>("InletMstPlane").ToLocalChecked())->ToObject());
	MstPlane outletMstPlane = constructMst(planeDataV8->Get(Nan::New<String>("OutletMstPlane").ToLocalChecked())->ToObject());
	const double totalPressureLossBtwnPlanes1and4 = Get("totalPressureLossBtwnPlanes1and4", planeDataV8);
	const double totalPressureLossBtwnPlanes2and5 = Get("totalPressureLossBtwnPlanes2and5", planeDataV8);
	const bool plane5upstreamOfPlane2 = GetBool("plane5upstreamOfPlane2", planeDataV8);

	//Create C++ obj and return
	PlaneData planeData(fanInletFlange, fanEvaseOrOutletFlange, flowTraverse, std::move(addlTravPlanes), inletMstPlane, outletMstPlane, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);
	return planeData;
}

BaseGasDensity::GasType getGasType(Local<Object> obj)
{
	//NAN init data
	auto const &gasTypeStr = GetStr("gasType", obj);

	//perform logic and return C++ data
	if (gasTypeStr == "AIR")
	{
		return BaseGasDensity::GasType::AIR;
	}
	else if (gasTypeStr == "STANDARDAIR")
	{
		return BaseGasDensity::GasType::STANDARDAIR;
	}
	return BaseGasDensity::GasType::OTHERGAS;
};

BaseGasDensity::InputType getInputType(Local<Object> obj)
{
	//NAN init data
	auto const &inputTypeStr = GetStr("inputType", obj);

	//perform logic and return C++ data
	if (inputTypeStr == "relativeHumidity")
	{
		return BaseGasDensity::InputType::RelativeHumidity;
	}
	else if (inputTypeStr == "dewPoint")
	{
		return BaseGasDensity::InputType::DewPoint;
	}
	return BaseGasDensity::InputType::WetBulbTemp;
};

NAN_METHOD(fanResultsExisting)
{
	//NAN initialize data
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	const double fanSpeed = Get("fanSpeed", inp);
	const double airDensity = Get("airDensity", inp);
	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);
	double specifiedDriveEfficiency;
	if (drive1 == Motor::Drive::SPECIFIED)
	{
		specifiedDriveEfficiency = Get("specifiedDriveEfficiency", inp);
	}
	else
	{
		specifiedDriveEfficiency = 100.0;
	}
	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
	double const motorRatedPower = Get("motorRatedPower", inp);
	double const motorRpm = Get("motorRpm", inp);
	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
	double const specifiedEfficiency = Get("specifiedEfficiency", inp);
	double const motorRatedVoltage = Get("motorRatedVoltage", inp);
	double const fullLoadAmps = Get("fullLoadAmps", inp);
	double const sizeMargin = Get("sizeMargin", inp);
	double const measuredPower = Get("measuredPower", inp);
	double const measuredVoltage = Get("measuredVoltage", inp);
	double const measuredAmps = Get("measuredAmps", inp);
	double const flowRate = Get("flowRate", inp);
	double const inletPressure = Get("inletPressure", inp);
	double const outletPressure = Get("outletPressure", inp);
	double const compressibilityFactor = Get("compressibilityFactor", inp);
	double const operatingHours = Get("operatingHours", inp);
	double const unitCost = Get("unitCost", inp);
	Motor::LoadEstimationMethod const loadEstimationMethod = GetEnumVal<Motor::LoadEstimationMethod>("loadEstimationMethod", inp);

	//Calculation procedure
	specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
	Fan::Input input(fanSpeed, airDensity, drive1, specifiedDriveEfficiency);
	Motor motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
	Fan::FieldDataBaseline fanFieldData(measuredPower, measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure,
										compressibilityFactor, loadEstimationMethod);
	FanResult result(input, motor, operatingHours, unitCost);
	auto output = result.calculateExisting(fanFieldData);
	//perform conversions for return object
	output.fanEfficiency = Conversion(output.fanEfficiency).fractionToPercent();
	output.motorEfficiency = Conversion(output.motorEfficiency).fractionToPercent();
	output.motorPowerFactor = Conversion(output.motorPowerFactor).fractionToPercent();
	output.driveEfficiency = Conversion(output.driveEfficiency).fractionToPercent();

	//NAN create return obj
	SetR("fanEfficiency", output.fanEfficiency);
	SetR("motorRatedPower", output.motorRatedPower);
	SetR("motorShaftPower", output.motorShaftPower);
	SetR("fanShaftPower", output.fanShaftPower);
	SetR("motorEfficiency", output.motorEfficiency);
	SetR("motorPowerFactor", output.motorPowerFactor);
	SetR("motorCurrent", output.motorCurrent);
	SetR("motorPower", output.motorPower);
	SetR("loadFactor", output.loadFactor);
	SetR("driveEfficiency", output.driveEfficiency);
	SetR("annualEnergy", output.annualEnergy);
	SetR("annualCost", output.annualCost);
	SetR("estimatedFLA", output.estimatedFLA);
	SetR("fanEnergyIndex", output.fanEnergyIndex);
	//NAN return obj
	info.GetReturnValue().Set(r);
}

NAN_METHOD(fanResultsModified)
{
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	//NAN init data
	const double fanSpeed = Get("fanSpeed", inp);
	const double airDensity = Get("airDensity", inp);
	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);
	double specifiedDriveEfficiency;
	if (drive1 == Motor::Drive::SPECIFIED)
	{
		specifiedDriveEfficiency = Get("specifiedDriveEfficiency", inp);
	}
	else
	{
		specifiedDriveEfficiency = 100.0;
	}
	double const measuredVoltage = Get("measuredVoltage", inp);
	double const measuredAmps = Get("measuredAmps", inp);
	double const flowRate = Get("flowRate", inp);
	double const inletPressure = Get("inletPressure", inp);
	double const outletPressure = Get("outletPressure", inp);
	double const compressibilityFactor = Get("compressibilityFactor", inp);
	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
	double const motorRatedPower = Get("motorRatedPower", inp);
	double const motorRpm = Get("motorRpm", inp);
	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
	double const specifiedEfficiency = Get("specifiedEfficiency", inp);
	double const motorRatedVoltage = Get("motorRatedVoltage", inp);
	double const fullLoadAmps = Get("fullLoadAmps", inp);
	double const sizeMargin = Get("sizeMargin", inp);
	const double operatingHours = Get("operatingHours", inp);
	const double unitCost = Get("unitCost", inp);
	double fanEfficiency = Get("fanEfficiency", inp);

	//Calculation procedure
	fanEfficiency = Conversion(fanEfficiency).percentToFraction();
	specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
	Fan::Input input(fanSpeed, airDensity, drive1, specifiedDriveEfficiency);
	Fan::FieldDataModified fanFieldData(measuredVoltage, measuredAmps, flowRate, inletPressure,
										outletPressure, compressibilityFactor);
	Motor motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
	FanResult result(input, motor, operatingHours, unitCost);
	auto output = result.calculateModified(fanFieldData, fanEfficiency);
	//perform conversions for return object
	output.fanEfficiency = Conversion(output.fanEfficiency).fractionToPercent();
	output.motorEfficiency = Conversion(output.motorEfficiency).fractionToPercent();
	output.motorPowerFactor = Conversion(output.motorPowerFactor).fractionToPercent();
	output.driveEfficiency = Conversion(output.driveEfficiency).fractionToPercent();

	//NAN create return obj
	SetR("fanEfficiency", output.fanEfficiency);
	SetR("motorRatedPower", output.motorRatedPower);
	SetR("motorShaftPower", output.motorShaftPower);
	SetR("fanShaftPower", output.fanShaftPower);
	SetR("motorEfficiency", output.motorEfficiency);
	SetR("motorPowerFactor", output.motorPowerFactor);
	SetR("motorCurrent", output.motorCurrent);
	SetR("motorPower", output.motorPower);
	SetR("loadFactor", output.loadFactor);
	SetR("driveEfficiency", output.driveEfficiency);
	SetR("annualEnergy", output.annualEnergy);
	SetR("annualCost", output.annualCost);
	SetR("estimatedFLA", output.estimatedFLA);
	SetR("fanEnergyIndex", output.fanEnergyIndex);
	//NAN return obj
	info.GetReturnValue().Set(r);
}

// NAN_METHOD(fanResultsOptimal) {
// 	inp = info[0]->ToObject();
// 	r = Nan::New<Object>();

// 	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);

// 	double specifiedDriveEfficiency;
//     if (drive1 == Motor::Drive::SPECIFIED) {
//         specifiedDriveEfficiency = Get("specifiedDriveEfficiency", inp) / 100;
//     }
//     else {
//         specifiedDriveEfficiency = 1;
//     }

// 	Fan::Input input = {Get("fanSpeed", inp), Get("airDensity", inp), drive1, specifiedDriveEfficiency};

// 	double const measuredVoltage = Get("measuredVoltage", inp);
// 	double const measuredAmps = Get("measuredAmps", inp);
// 	double const flowRate = Get("flowRate", inp);
// 	double const inletPressure = Get("inletPressure", inp);
// 	double const outletPressure = Get("outletPressure", inp);
// 	double const compressibilityFactor = Get("compressibilityFactor", inp);
// 	Fan::FieldDataModified fanFieldData = {measuredVoltage, measuredAmps, flowRate, inletPressure,
// 	                                                 outletPressure, compressibilityFactor};

// 	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
// 	double const motorRatedPower = Get("motorRatedPower", inp);
// 	double const motorRpm = Get("motorRpm", inp);
// 	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
// 	double const specifiedEfficiency = Get("specifiedEfficiency", inp);
// 	double const motorRatedVoltage = Get("motorRatedVoltage", inp);
// 	double const fullLoadAmps = Get("fullLoadAmps", inp);
// 	double const sizeMargin = Get("sizeMargin", inp);

// 	Motor motor = {lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin};

// 	FanResult result = {input, motor, Get("operatingHours", inp), Get("unitCost", inp)};

// 	auto const output = GetBool("isSpecified", inp) ? result.calculateOptimal(fanFieldData, Get("userInputFanEfficiency", inp) / 100)
// 	                                                : result.calculateOptimal(fanFieldData, GetEnumVal<OptimalFanEfficiency::FanType>("fanType", inp));

// 	SetR("fanEfficiency", output.fanEfficiency * 100);
// 	SetR("motorRatedPower", output.motorRatedPower);
// 	SetR("motorShaftPower", output.motorShaftPower);
// 	SetR("fanShaftPower", output.fanShaftPower);
// 	SetR("motorEfficiency", output.motorEfficiency * 100);
// 	SetR("motorPowerFactor", output.motorPowerFactor * 100);
// 	SetR("motorCurrent", output.motorCurrent);
// 	SetR("motorPower", output.motorPower);
// 	SetR("annualEnergy", output.annualEnergy);
// 	SetR("annualCost", output.annualCost);
// 	SetR("estimatedFLA", output.estimatedFLA);
// 	SetR("fanEnergyIndex", output.fanEnergyIndex);
// 	info.GetReturnValue().Set(r);
// }

NAN_METHOD(getBaseGasDensityRelativeHumidity)
{
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = Get("dryBulbTemp", inp);
		const double staticPressure = Get("staticPressure", inp);
		const double barometricPressure = Get("barometricPressure", inp);
		const double relativeHumidity = Get("relativeHumidity", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = Get("specificGravity", inp);

		//Calculation procedure
		double result = BaseGasDensity(
							dryBulbTemp,
							staticPressure,
							barometricPressure,
							relativeHumidity,
							gasType,
							inputType,
							specificGravity)
							.getGasDensity();

		//NAN return single value
		info.GetReturnValue().Set(result);
	}
	catch (std::runtime_error const &e)
	{
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityRelativeHumidity - fan.h: " + what).c_str());
	}
}

NAN_METHOD(getBaseGasDensityDewPoint)
{
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = Get("dryBulbTemp", inp);
		const double staticPressure = Get("staticPressure", inp);
		const double barometricPressure = Get("barometricPressure", inp);
		const double dewPoint = Get("dewPoint", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = Get("specificGravity", inp);

		//Calculation procedure
		double result = BaseGasDensity(
							dryBulbTemp,
							staticPressure,
							barometricPressure,
							dewPoint,
							gasType,
							inputType,
							specificGravity)
							.getGasDensity();

		//NAN return single value
		info.GetReturnValue().Set(result);
	}
	catch (std::runtime_error const &e)
	{
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityDewPoint - fan.h: " + what).c_str());
	}
}

NAN_METHOD(getBaseGasDensityWetBulb)
{
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = Get("dryBulbTemp", inp);
		const double staticPressure = Get("staticPressure", inp);
		const double barometricPressure = Get("barometricPressure", inp);
		const double wetBulbTemp = Get("wetBulbTemp", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = Get("specificGravity", inp);
		const double specificHeatGas = Get("specificHeatGas", inp);

		//Calculation procedure
		double result = BaseGasDensity(
							dryBulbTemp,
							staticPressure,
							barometricPressure,
							wetBulbTemp,
							gasType,
							inputType,
							specificGravity,
							specificHeatGas)
							.getGasDensity();

		//NAN return single value
		info.GetReturnValue().Set(result);
	}
	catch (std::runtime_error const &e)
	{
		info.GetReturnValue().Set(0);
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getBaseGasDensityWetBulb - fan.h: " + what).c_str());
	}
}

BaseGasDensity getBaseGasDensity()
{
	//NAN data init
	auto baseGasDensityV8 = inp->ToObject()->Get(Nan::New<String>("BaseGasDensity").ToLocalChecked())->ToObject();
	const double dryBulbTemp = Get("dryBulbTemp", baseGasDensityV8);
	const double staticPressure = Get("staticPressure", baseGasDensityV8);
	const double barometricPressure = Get("barometricPressure", baseGasDensityV8);
	const double gasDensity = Get("gasDensity", baseGasDensityV8);
	const BaseGasDensity::GasType gasType = getGasType(baseGasDensityV8);

	//Create C++ obj and return
	BaseGasDensity baseGasDensity(dryBulbTemp, staticPressure, barometricPressure, gasDensity, gasType);
	return baseGasDensity;
}

FanShaftPower getFanShaftPower()
{
	//NAN data init
	auto fanShaftPowerV8 = inp->ToObject()->Get(Nan::New<String>("FanShaftPower").ToLocalChecked())->ToObject();
	const double motorShaftPower = Get("motorShaftPower", fanShaftPowerV8);
	const double efficiencyMotor = Get("efficiencyMotor", fanShaftPowerV8);
	const double efficiencyVFD = Get("efficiencyVFD", fanShaftPowerV8);
	const double efficiencyBelt = Get("efficiencyBelt", fanShaftPowerV8);
	const double sumSEF = Get("sumSEF", fanShaftPowerV8);

	//Create C++ obj and return
	FanShaftPower fanShaftPower(motorShaftPower, efficiencyMotor, efficiencyVFD, efficiencyBelt, sumSEF);
	return fanShaftPower;
}

NAN_METHOD(getVelocityPressureData)
{
	//NAN init data
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	auto const travPlane = constructTraverse(inp->ToObject());

	//Calculation procedure
	double pv3 = travPlane.getPv3Value();
	double percent75Rule = travPlane.get75percentRule();
	percent75Rule = Conversion(percent75Rule).fractionToPercent();

	//NAN construct return obj
	SetR("pv3", pv3);
	SetR("percent75Rule", percent75Rule);

	//NAN return obj
	info.GetReturnValue().Set(r);
}

NAN_METHOD(getPlaneResults)
{
	Local<Object> rv = Nan::New<Object>();
	inp = info[0]->ToObject();

	try
	{
		//NAN fetching PlaneData data
		PlaneData planeData = getPlaneData();
		BaseGasDensity baseGasDensity = getBaseGasDensity();

		//assign output and perform C++ calculation
		auto const output = PlaneData::NodeBinding::calculate(planeData, baseGasDensity);

		//iterate through traverse planes and build data array to be injected in to return object
		Handle<Array> addlTravPlanes = Array::New(v8::Isolate::GetCurrent(), output.addlTravPlanes.size());
		std::size_t index = 0;

		auto const setData = [&rv, &addlTravPlanes, &index](const PlaneData::NodeBinding::Data &data, std::string const &name,
															bool isArray = false, bool isStaticPressure = false, const double staticPressure = 0) {
			//NAN assigning data to array of child-objects
			r = Nan::New<Object>();
			SetR("gasDensity", data.gasDensity);
			SetR("gasVolumeFlowRate", data.gasVolumeFlowRate);
			SetR("gasVelocity", data.gasVelocity);
			SetR("gasVelocityPressure", data.gasVelocityPressure);
			SetR("gasTotalPressure", data.gasTotalPressure);
			if (isStaticPressure)
			{
				SetR("staticPressure", staticPressure);
			}

			if (isArray)
			{
				addlTravPlanes->Set(index, r);
			}
			else
			{
				Nan::Set(rv, Nan::New<String>(name).ToLocalChecked(), r);
			}
		};

		for (auto const &data : output.addlTravPlanes)
		{
			setData(data, "", true);
			index++;
		}
		Nan::Set(rv, Nan::New<String>("AddlTraversePlanes").ToLocalChecked(), addlTravPlanes);
		setData(output.fanInletFlange, "FanInletFlange", false, true, output.fanInletFlange.staticPressure);
		setData(output.fanOrEvaseOutletFlange, "FanOrEvaseOutletFlange", false, true, output.fanOrEvaseOutletFlange.staticPressure);
		setData(output.flowTraverse, "FlowTraverse");
		setData(output.inletMstPlane, "InletMstPlane");
		setData(output.outletMstPlane, "OutletMstPlane");
	}
	catch (std::runtime_error const &e)
	{
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in getPlaneResults - fan.h: " + what).c_str());
	}

	info.GetReturnValue().Set(rv);
}

NAN_METHOD(fan203)
{
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	try
	{
		//NAN init data
		FanRatedInfo fanRatedInfo = getFanRatedInfo();
		PlaneData planeData = getPlaneData();
		BaseGasDensity baseGasDensity = getBaseGasDensity();
		FanShaftPower fanShaftPower = getFanShaftPower();

		//Calculation procedure
		auto const rv = Fan203(fanRatedInfo, planeData, baseGasDensity, fanShaftPower).calculate();

		//NAN return resutls
		SetR("fanEfficiencyTotalPressure", rv.fanEfficiencyTotalPressure);
		SetR("fanEfficiencyStaticPressure", rv.fanEfficiencyStaticPressure);
		SetR("fanEfficiencyStaticPressureRise", rv.fanEfficiencyStaticPressureRise);
		SetR("flow", rv.asTested.flow);
		SetR("pressureTotal", rv.asTested.pressureTotal);
		SetR("pressureStatic", rv.asTested.pressureStatic);
		SetR("staticPressureRise", rv.asTested.staticPressureRise);
		SetR("power", rv.asTested.power);
		SetR("kpc", rv.asTested.kpc);
		SetR("flowCorrected", rv.converted.flow);
		SetR("pressureTotalCorrected", rv.converted.pressureTotal);
		SetR("pressureStaticCorrected", rv.converted.pressureStatic);
		SetR("staticPressureRiseCorrected", rv.converted.staticPressureRise);
		SetR("powerCorrected", rv.converted.power);
		SetR("kpcCorrected", rv.converted.kpc);
	}
	catch (std::runtime_error const &e)
	{
		std::string const what = e.what();
		ThrowError(std::string("std::runtime_error thrown in fan203 - fan.h: " + what).c_str());
	}

	//NAN return obj
	info.GetReturnValue().Set(r);
}

FanCurveType getFanCurveType()
{
	//NAN init data
	std::string const curveTypeStr = GetStr("curveType", inp);

	//perform logic and return value
	if (curveTypeStr == "StaticPressureRise")
	{
		return FanCurveType::StaticPressureRise;
	}
	else if (curveTypeStr == "FanTotalPressure")
	{
		return FanCurveType::FanTotalPressure;
	}
	return FanCurveType::FanStaticPressure;
}

FanCurveData getFanBaseCurveData()
{

	auto const &arrayTmp = inp->ToObject()->Get(Nan::New<String>("BaseCurveData").ToLocalChecked());
	auto const &array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::BaseCurve> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		auto const &innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		curveData.emplace_back(FanCurveData::BaseCurve(innerArray->Get(0)->NumberValue(),
													   innerArray->Get(1)->NumberValue(),
													   innerArray->Get(2)->NumberValue()));
	}
	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
	// return {getFanCurveType(), std::move(curveData)};
}
FanCurveData getFanRatedPointCurveData()
{
	auto const &arrayTmp = inp->ToObject()->Get(Nan::New<String>("RatedPointCurveData").ToLocalChecked());
	auto const &array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::RatedPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		auto const &innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
		curveData.emplace_back(FanCurveData::RatedPoint(innerArray->Get(0)->NumberValue(),
														innerArray->Get(1)->NumberValue(),
														innerArray->Get(2)->NumberValue(),
														innerArray->Get(3)->NumberValue(),
														innerArray->Get(4)->NumberValue(),
														innerArray->Get(5)->NumberValue()));
	}

	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
	// return {getFanCurveType(), std::move(curveData)};
}
FanCurveData getFanBaseOperatingPointCurveData()
{
	auto const &arrayTmp = inp->ToObject()->Get(Nan::New<String>("BaseOperatingPointCurveData").ToLocalChecked());
	auto const &array = v8::Local<v8::Array>::Cast(arrayTmp);

	std::vector<FanCurveData::BaseOperatingPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		auto const &innerArray = v8::Local<v8::Array>::Cast(array->Get(i)->ToObject());
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
	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
	// return {getFanCurveType(), std::move(curveData)};
}

void returnResultData(std::vector<ResultData> const &results)
{
	std::size_t index = 0;
	Handle<Array> outerArray = Array::New(v8::Isolate::GetCurrent(), results.size());
	for (auto const &row : results)
	{
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
NAN_METHOD(fanCurve)
{
	//NAN init data
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	//fetch bool values to check if defined objects were supplied
	const bool baseCurveDataDefined = isDefined(inp, "BaseCurveData");
	const bool ratedPointCurveDataDefined = isDefined(inp, "RatedPointCurveData");

	//NAN data fetching
	const double density = Get("density", inp);
	const double densityCorrected = Get("densityCorrected", inp);
	const double speed = Get("speed", inp);
	const double speedCorrected = Get("speedCorrected", inp);
	const double pressureBarometric = Get("pressureBarometric", inp);
	const double pressureBarometricCorrected = Get("pressureBarometricCorrected", inp);
	const double pt1Factor = Get("pt1Factor", inp);
	const double gamma = Get("gamma", inp);
	const double gammaCorrected = Get("gammaCorrected", inp);
	const double area1 = Get("area1", inp);
	const double area2 = Get("area2", inp);

	if (baseCurveDataDefined)
	{
		FanCurveData fanCurveData = getFanBaseCurveData();
		//Create C++ obj and calculate
		auto const rv = FanCurve(density, densityCorrected, speed,
								 speedCorrected, pressureBarometric, pressureBarometricCorrected, pt1Factor,
								 gamma, gammaCorrected, area1, area2,
								 fanCurveData)
							.calculate();

		//Construct return object
		returnResultData(rv);
	}
	else if (ratedPointCurveDataDefined)
	{
		FanCurveData fanCurveData = getFanRatedPointCurveData();
		//Create C++ obj and calculate
		auto const rv = FanCurve(density, densityCorrected, speed,
								 speedCorrected, pressureBarometric, pressureBarometricCorrected, pt1Factor,
								 gamma, gammaCorrected, area1, area2,
								 fanCurveData)
							.calculate();

		//Construct return object
		returnResultData(rv);
	}
	else
	{
		FanCurveData fanCurveData = getFanBaseOperatingPointCurveData();
		//Create C++ obj and calculate
		auto const rv = FanCurve(density, densityCorrected, speed,
								 speedCorrected, pressureBarometric, pressureBarometricCorrected, pt1Factor,
								 gamma, gammaCorrected, area1, area2,
								 fanCurveData)
							.calculate();

		//Construct return object
		returnResultData(rv);
	}
	//NAN return obj
	info.GetReturnValue().Set(r);
}

NAN_METHOD(optimalFanEfficiency)
{
	//NAN init data
	inp = info[0]->ToObject();
	auto const fanType = GetEnumVal<OptimalFanEfficiency::FanType>("fanType", inp);
	double const fanSpeed = Get("fanSpeed", inp);
	double const flowRate = Get("flowRate", inp);
	double const inletPressure = Get("inletPressure", inp);
	double const outletPressure = Get("outletPressure", inp);
	double const compressibility = Get("compressibility", inp);

	//Create C++ obj and calculate
	double efficiency = OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure,
											 compressibility)
							.calculate();
	efficiency = Conversion(efficiency).fractionToPercent();

	//NAN returning single value
	info.GetReturnValue().Set(efficiency);
}

NAN_METHOD(compressibilityFactor)
{
	//NAN init data
	inp = info[0]->ToObject();
	const double moverShaftPower = Get("moverShaftPower", inp);
	const double inletPressure = Get("inletPressure", inp);
	const double outletPressure = Get("outletPressure", inp);
	const double barometricPressure = Get("barometricPressure", inp);
	const double flowRate = Get("flowRate", inp);
	const double specificHeatRatio = Get("specificHeatRatio", inp);

	//Create C++ obj and calculate
	double const compressibilityFactor = CompressibilityFactor(
											 moverShaftPower, inletPressure, outletPressure,
											 barometricPressure, flowRate, specificHeatRatio)
											 .calculate();

	//NAN returning single value
	info.GetReturnValue().Set(compressibilityFactor);
}
