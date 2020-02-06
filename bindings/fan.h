#include "NanDataConverters.h"

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
#include "calculator/util/Conversion.h"

#include "calculator/pump/OptimalPumpShaftPower.h"
#include "calculator/motor/OptimalMotorShaftPower.h"
#include "calculator/motor/OptimalMotorPower.h"

using namespace Nan;
using namespace v8;

//NAN function for fetching ENUM value associated with provided key
template <typename T>
T GetEnumVal(std::string const &key, Local<Object> obj)
{
	Local<String> getName = Nan::New<String>(key).ToLocalChecked();
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
	if (rObj->IsUndefined())
	{
		ThrowTypeError(std::string("GetEnumVal method in fan.h: " + key + " not present in object").c_str());
	}
	return static_cast<T>(Nan::To<int32_t>(rObj).FromJust());
}

//NAN function for checking if an object parameter has been defined with a value
bool isDefined(Local<Object> obj, std::string const &key)
{
	Local<String> getName = Nan::New<String>(key).ToLocalChecked();
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> rObj = Nan::To<Object>(obj).ToLocalChecked()->Get(context, getName).ToLocalChecked();
	return !rObj->IsUndefined();
}

//helper functions for building nested array of objects via NAN
std::vector<std::vector<double>> getTraverseInputData(Local<Object> obj)
{
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();

	v8::Local<v8::Value> arrayTmp = Nan::Get(Nan::To<v8::Object>(obj).ToLocalChecked(), Nan::New<String>("traverseData").ToLocalChecked()).ToLocalChecked();
	Local<Array> array = v8::Local<v8::Array>::Cast(arrayTmp);
	std::vector<std::vector<double>> traverseData(array->Length());

	for (std::size_t i = 0; i < array->Length(); i++)
	{
		Local<Array> const innerArray = v8::Local<v8::Array>::Cast(Nan::To<Object>(array->Get(context, i).ToLocalChecked()).ToLocalChecked());
		traverseData.at(i).resize(innerArray->Length());
		for (std::size_t j = 0; j < innerArray->Length(); j++)
		{
			traverseData.at(i).at(j) = Nan::To<double>(innerArray->Get(context, j).ToLocalChecked()).FromJust();
		}
	}
	return traverseData;
}

FlangePlane constructFlange(Local<Object> obj)
{
	//NAN init data
	const double area = getDouble("area", obj);
	const double dryBulbTemp = getDouble("dryBulbTemp", obj);
	const double barometricPressure = getDouble("barometricPressure", obj);

	//Create C++ obj and return
	FlangePlane flangePlane(area, dryBulbTemp, barometricPressure);
	return flangePlane;
}

MstPlane constructMst(Local<Object> obj)
{
	//NAN init data
	const double area = getDouble("area", obj);
	const double dryBulbTemp = getDouble("dryBulbTemp", obj);
	const double barometricPressure = getDouble("barometricPressure", obj);
	const double staticPressure = getDouble("staticPressure", obj);

	//Create C++ obj and return
	MstPlane mstPlane(area, dryBulbTemp, barometricPressure, staticPressure);
	return mstPlane;
}

TraversePlane constructTraverse(Local<Object> obj)
{
	//NAN init data
	const double area = getDouble("area", obj);
	const double dryBulbTemp = getDouble("dryBulbTemp", obj);
	const double barometricPressure = getDouble("barometricPressure", obj);
	const double staticPressure = getDouble("staticPressure", obj);
	const double pitotTubeCoefficient = getDouble("pitotTubeCoefficient", obj);
	const std::vector<std::vector<double>> traverseInputData = getTraverseInputData(obj);

	//Create C++ obj and return
	TraversePlane traversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData);
	return traversePlane;
}

FanRatedInfo getFanRatedInfo()
{
	//NAN init data
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<String> fanRatedInfoStringV8 = Nan::New<String>("FanRatedInfo").ToLocalChecked();
	Local<Object> fanRatedInfoV8 = Nan::To<Object>(Nan::To<Object>(inp).ToLocalChecked()->Get(context, fanRatedInfoStringV8).ToLocalChecked()).ToLocalChecked();

	const double fanSpeed = getDouble("fanSpeed", fanRatedInfoV8);
	const double motorSpeed = getDouble("motorSpeed", fanRatedInfoV8);
	const double fanSpeedCorrected = getDouble("fanSpeedCorrected", fanRatedInfoV8);
	const double densityCorrected = getDouble("densityCorrected", fanRatedInfoV8);
	const double pressureBarometricCorrected = getDouble("pressureBarometricCorrected", fanRatedInfoV8);

	//Create C++ obj and return
	FanRatedInfo fanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);
	return fanRatedInfo;
}

PlaneData getPlaneData()
{
	//NAN init data
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<String> planeDataStringV8 = Nan::New<String>("PlaneData").ToLocalChecked();
	Local<Object> planeDataV8 = Nan::To<Object>(Nan::To<Object>(inp).ToLocalChecked()->Get(context, planeDataStringV8).ToLocalChecked()).ToLocalChecked();

	// Local<Value> const &addlTravTmp = planeDataV8->Get(Nan::New<String>("AddlTraversePlanes").ToLocalChecked());
	Local<Value> const &addlTravTmp = Nan::Get(planeDataV8, Nan::New<String>("AddlTraversePlanes").ToLocalChecked()).ToLocalChecked();
	Local<Array> const &addlTravArray = v8::Local<v8::Array>::Cast(addlTravTmp);
	std::vector<TraversePlane> addlTravPlanes;
	//loop to construct array of traverse planes
	for (std::size_t i = 0; i < addlTravArray->Length(); i++)
	{
		addlTravPlanes.emplace_back(constructTraverse(Nan::To<Object>(addlTravArray->Get(context, i).ToLocalChecked()).ToLocalChecked()));
	}
	FlangePlane fanInletFlange = constructFlange(Nan::To<Object>(planeDataV8->Get(context, Nan::New<String>("FanInletFlange").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
	FlangePlane fanEvaseOrOutletFlange = constructFlange(Nan::To<Object>(planeDataV8->Get(context, Nan::New<String>("FanEvaseOrOutletFlange").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
	TraversePlane flowTraverse = constructTraverse(Nan::To<Object>(planeDataV8->Get(context, Nan::New<String>("FlowTraverse").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
	MstPlane inletMstPlane = constructMst(Nan::To<Object>(planeDataV8->Get(context, Nan::New<String>("InletMstPlane").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
	MstPlane outletMstPlane = constructMst(Nan::To<Object>(planeDataV8->Get(context, Nan::New<String>("OutletMstPlane").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
	const double totalPressureLossBtwnPlanes1and4 = getDouble("totalPressureLossBtwnPlanes1and4", planeDataV8);
	const double totalPressureLossBtwnPlanes2and5 = getDouble("totalPressureLossBtwnPlanes2and5", planeDataV8);
	const bool plane5upstreamOfPlane2 = getBool("plane5upstreamOfPlane2", planeDataV8);

	//Create C++ obj and return
	PlaneData planeData(fanInletFlange, fanEvaseOrOutletFlange, flowTraverse, std::move(addlTravPlanes), inletMstPlane, outletMstPlane, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);
	return planeData;
}

BaseGasDensity::GasType getGasType(Local<Object> obj)
{
	//NAN init data
	std::string const &gasTypeStr = getString("gasType", obj);

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
	std::string const &inputTypeStr = getString("inputType", obj);

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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	const double fanSpeed = getDouble("fanSpeed", inp);
	const double airDensity = getDouble("airDensity", inp);
	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);
	double specifiedDriveEfficiency;
	if (drive1 == Motor::Drive::SPECIFIED)
	{
		specifiedDriveEfficiency = getDouble("specifiedDriveEfficiency", inp);
	}
	else
	{
		specifiedDriveEfficiency = 100.0;
	}
	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
	double const motorRatedPower = getDouble("motorRatedPower", inp);
	double const motorRpm = getDouble("motorRpm", inp);
	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
	double const specifiedEfficiency = getDouble("specifiedEfficiency", inp);
	double const motorRatedVoltage = getDouble("motorRatedVoltage", inp);
	double const fullLoadAmps = getDouble("fullLoadAmps", inp);
	double const sizeMargin = getDouble("sizeMargin", inp);
	double const measuredPower = getDouble("measuredPower", inp);
	double const measuredVoltage = getDouble("measuredVoltage", inp);
	double const measuredAmps = getDouble("measuredAmps", inp);
	double const flowRate = getDouble("flowRate", inp);
	double const inletPressure = getDouble("inletPressure", inp);
	double const outletPressure = getDouble("outletPressure", inp);
	double const compressibilityFactor = getDouble("compressibilityFactor", inp);
	double const operatingHours = getDouble("operatingHours", inp);
	double const unitCost = getDouble("unitCost", inp);
	Motor::LoadEstimationMethod const loadEstimationMethod = GetEnumVal<Motor::LoadEstimationMethod>("loadEstimationMethod", inp);

	//Calculation procedure
	specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
	Fan::Input input(fanSpeed, airDensity, drive1, specifiedDriveEfficiency);
	Motor motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
	Fan::FieldDataBaseline fanFieldData(measuredPower, measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure,
										compressibilityFactor, loadEstimationMethod);
	FanResult result(input, motor, operatingHours, unitCost);
	FanResult::Output output = result.calculateExisting(fanFieldData);
	//perform conversions for return object
	output.fanEfficiency = Conversion(output.fanEfficiency).fractionToPercent();
	output.motorEfficiency = Conversion(output.motorEfficiency).fractionToPercent();
	output.motorPowerFactor = Conversion(output.motorPowerFactor).fractionToPercent();
	output.driveEfficiency = Conversion(output.driveEfficiency).fractionToPercent();

	//NAN create return obj
	setR("fanEfficiency", output.fanEfficiency);
	setR("motorRatedPower", output.motorRatedPower);
	setR("motorShaftPower", output.motorShaftPower);
	setR("fanShaftPower", output.fanShaftPower);
	setR("motorEfficiency", output.motorEfficiency);
	setR("motorPowerFactor", output.motorPowerFactor);
	setR("motorCurrent", output.motorCurrent);
	setR("motorPower", output.motorPower);
	setR("loadFactor", output.loadFactor);
	setR("driveEfficiency", output.driveEfficiency);
	setR("annualEnergy", output.annualEnergy);
	setR("annualCost", output.annualCost);
	setR("estimatedFLA", output.estimatedFLA);
	setR("fanEnergyIndex", output.fanEnergyIndex);
	//NAN return obj
	info.GetReturnValue().Set(r);
}

NAN_METHOD(fanResultsModified)
{
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	//NAN init data
	const double fanSpeed = getDouble("fanSpeed", inp);
	const double airDensity = getDouble("airDensity", inp);
	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);
	double specifiedDriveEfficiency;
	if (drive1 == Motor::Drive::SPECIFIED)
	{
		specifiedDriveEfficiency = getDouble("specifiedDriveEfficiency", inp);
	}
	else
	{
		specifiedDriveEfficiency = 100.0;
	}
	double const measuredVoltage = getDouble("measuredVoltage", inp);
	double const measuredAmps = getDouble("measuredAmps", inp);
	double const flowRate = getDouble("flowRate", inp);
	double const inletPressure = getDouble("inletPressure", inp);
	double const outletPressure = getDouble("outletPressure", inp);
	double const compressibilityFactor = getDouble("compressibilityFactor", inp);
	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
	double const motorRatedPower = getDouble("motorRatedPower", inp);
	double const motorRpm = getDouble("motorRpm", inp);
	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
	double const specifiedEfficiency = getDouble("specifiedEfficiency", inp);
	double const motorRatedVoltage = getDouble("motorRatedVoltage", inp);
	double const fullLoadAmps = getDouble("fullLoadAmps", inp);
	double const sizeMargin = getDouble("sizeMargin", inp);
	const double operatingHours = getDouble("operatingHours", inp);
	const double unitCost = getDouble("unitCost", inp);
	double fanEfficiency = getDouble("fanEfficiency", inp);

	//Calculation procedure
	fanEfficiency = Conversion(fanEfficiency).percentToFraction();
	specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
	Fan::Input input(fanSpeed, airDensity, drive1, specifiedDriveEfficiency);
	Fan::FieldDataModified fanFieldData(measuredVoltage, measuredAmps, flowRate, inletPressure,
										outletPressure, compressibilityFactor);
	Motor motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
	FanResult result(input, motor, operatingHours, unitCost);
	FanResult::Output output = result.calculateModified(fanFieldData, fanEfficiency);
	//perform conversions for return object
	output.fanEfficiency = Conversion(output.fanEfficiency).fractionToPercent();
	output.motorEfficiency = Conversion(output.motorEfficiency).fractionToPercent();
	output.motorPowerFactor = Conversion(output.motorPowerFactor).fractionToPercent();
	output.driveEfficiency = Conversion(output.driveEfficiency).fractionToPercent();

	//NAN create return obj
	setR("fanEfficiency", output.fanEfficiency);
	setR("motorRatedPower", output.motorRatedPower);
	setR("motorShaftPower", output.motorShaftPower);
	setR("fanShaftPower", output.fanShaftPower);
	setR("motorEfficiency", output.motorEfficiency);
	setR("motorPowerFactor", output.motorPowerFactor);
	setR("motorCurrent", output.motorCurrent);
	setR("motorPower", output.motorPower);
	setR("loadFactor", output.loadFactor);
	setR("driveEfficiency", output.driveEfficiency);
	setR("annualEnergy", output.annualEnergy);
	setR("annualCost", output.annualCost);
	setR("estimatedFLA", output.estimatedFLA);
	setR("fanEnergyIndex", output.fanEnergyIndex);
	//NAN return obj
	info.GetReturnValue().Set(r);
}

// NAN_METHOD(fanResultsOptimal) {
// 	inp = Nan::To<Object>(info[0]).ToLocalChecked();
// 	r = Nan::New<Object>();

// 	Motor::Drive drive1 = GetEnumVal<Motor::Drive>("drive", inp);

// 	double specifiedDriveEfficiency;
//     if (drive1 == Motor::Drive::SPECIFIED) {
//         specifiedDriveEfficiency = getDouble("specifiedDriveEfficiency", inp) / 100;
//     }
//     else {
//         specifiedDriveEfficiency = 1;
//     }

// 	Fan::Input input = {getDouble("fanSpeed", inp), getDouble("airDensity", inp), drive1, specifiedDriveEfficiency};

// 	double const measuredVoltage = getDouble("measuredVoltage", inp);
// 	double const measuredAmps = getDouble("measuredAmps", inp);
// 	double const flowRate = getDouble("flowRate", inp);
// 	double const inletPressure = getDouble("inletPressure", inp);
// 	double const outletPressure = getDouble("outletPressure", inp);
// 	double const compressibilityFactor = getDouble("compressibilityFactor", inp);
// 	Fan::FieldDataModified fanFieldData = {measuredVoltage, measuredAmps, flowRate, inletPressure,
// 	                                                 outletPressure, compressibilityFactor};

// 	Motor::LineFrequency const lineFrequency = GetEnumVal<Motor::LineFrequency>("lineFrequency", inp);
// 	double const motorRatedPower = getDouble("motorRatedPower", inp);
// 	double const motorRpm = getDouble("motorRpm", inp);
// 	Motor::EfficiencyClass const efficiencyClass = GetEnumVal<Motor::EfficiencyClass>("efficiencyClass", inp);
// 	double const specifiedEfficiency = getDouble("specifiedEfficiency", inp);
// 	double const motorRatedVoltage = getDouble("motorRatedVoltage", inp);
// 	double const fullLoadAmps = getDouble("fullLoadAmps", inp);
// 	double const sizeMargin = getDouble("sizeMargin", inp);

// 	Motor motor = {lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin};

// 	FanResult result = {input, motor, getDouble("operatingHours", inp), getDouble("unitCost", inp)};

// 	auto const output = getBool("isSpecified", inp) ? result.calculateOptimal(fanFieldData, getDouble("userInputFanEfficiency", inp) / 100)
// 	                                                : result.calculateOptimal(fanFieldData, GetEnumVal<OptimalFanEfficiency::FanType>("fanType", inp));

// 	setR("fanEfficiency", output.fanEfficiency * 100);
// 	setR("motorRatedPower", output.motorRatedPower);
// 	setR("motorShaftPower", output.motorShaftPower);
// 	setR("fanShaftPower", output.fanShaftPower);
// 	setR("motorEfficiency", output.motorEfficiency * 100);
// 	setR("motorPowerFactor", output.motorPowerFactor * 100);
// 	setR("motorCurrent", output.motorCurrent);
// 	setR("motorPower", output.motorPower);
// 	setR("annualEnergy", output.annualEnergy);
// 	setR("annualCost", output.annualCost);
// 	setR("estimatedFLA", output.estimatedFLA);
// 	setR("fanEnergyIndex", output.fanEnergyIndex);
// 	info.GetReturnValue().Set(r);
// }

NAN_METHOD(getBaseGasDensityRelativeHumidity)
{
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = getDouble("dryBulbTemp", inp);
		const double staticPressure = getDouble("staticPressure", inp);
		const double barometricPressure = getDouble("barometricPressure", inp);
		const double relativeHumidity = getDouble("relativeHumidity", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = getDouble("specificGravity", inp);

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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = getDouble("dryBulbTemp", inp);
		const double staticPressure = getDouble("staticPressure", inp);
		const double barometricPressure = getDouble("barometricPressure", inp);
		const double dewPoint = getDouble("dewPoint", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = getDouble("specificGravity", inp);

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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	try
	{
		//NAN data init
		const double dryBulbTemp = getDouble("dryBulbTemp", inp);
		const double staticPressure = getDouble("staticPressure", inp);
		const double barometricPressure = getDouble("barometricPressure", inp);
		const double wetBulbTemp = getDouble("wetBulbTemp", inp);
		BaseGasDensity::GasType gasType = getGasType(inp);
		BaseGasDensity::InputType inputType = getInputType(inp);
		const double specificGravity = getDouble("specificGravity", inp);
		const double specificHeatGas = getDouble("specificHeatGas", inp);

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
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Object> baseGasDensityV8 = Nan::To<Object>(Nan::To<Object>(inp).ToLocalChecked()->Get(context, Nan::New<String>("BaseGasDensity").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();
	const double dryBulbTemp = getDouble("dryBulbTemp", baseGasDensityV8);
	const double staticPressure = getDouble("staticPressure", baseGasDensityV8);
	const double barometricPressure = getDouble("barometricPressure", baseGasDensityV8);
	const double gasDensity = getDouble("gasDensity", baseGasDensityV8);
	const BaseGasDensity::GasType gasType = getGasType(baseGasDensityV8);

	//Create C++ obj and return
	BaseGasDensity baseGasDensity(dryBulbTemp, staticPressure, barometricPressure, gasDensity, gasType);
	return baseGasDensity;
}

FanShaftPower getFanShaftPower()
{
	//NAN data init
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Object> fanShaftPowerV8 = Nan::To<Object>(Nan::To<Object>(inp).ToLocalChecked()->Get(context, Nan::New<String>("FanShaftPower").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();
	const double motorShaftPower = getDouble("motorShaftPower", fanShaftPowerV8);
	const double efficiencyMotor = getDouble("efficiencyMotor", fanShaftPowerV8);
	const double efficiencyVFD = getDouble("efficiencyVFD", fanShaftPowerV8);
	const double efficiencyBelt = getDouble("efficiencyBelt", fanShaftPowerV8);
	const double sumSEF = getDouble("sumSEF", fanShaftPowerV8);

	//Create C++ obj and return
	FanShaftPower fanShaftPower(motorShaftPower, efficiencyMotor, efficiencyVFD, efficiencyBelt, sumSEF);
	return fanShaftPower;
}

NAN_METHOD(getVelocityPressureData)
{
	//NAN init data
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	TraversePlane const travPlane = constructTraverse(Nan::To<Object>(inp).ToLocalChecked());

	//Calculation procedure
	double pv3 = travPlane.getPv3Value();
	double percent75Rule = travPlane.get75percentRule();
	percent75Rule = Conversion(percent75Rule).fractionToPercent();

	//NAN construct return obj
	setR("pv3", pv3);
	setR("percent75Rule", percent75Rule);

	//NAN return obj
	info.GetReturnValue().Set(r);
}

NAN_METHOD(getPlaneResults)
{
	Local<Object> rv = Nan::New<Object>();
	inp = Nan::To<Object>(info[0]).ToLocalChecked();

	try
	{
		//NAN fetching PlaneData data
		PlaneData planeData = getPlaneData();
		BaseGasDensity baseGasDensity = getBaseGasDensity();

		//assign output and perform C++ calculation
		PlaneData::NodeBinding::Output const output = PlaneData::NodeBinding::calculate(planeData, baseGasDensity);

		//iterate through traverse planes and build data array to be injected in to return object
		Local<Array> addlTravPlanes = Nan::New<v8::Array>(output.addlTravPlanes.size());

		std::size_t index = 0;

		auto const setData = [&rv, &addlTravPlanes, &index](const PlaneData::NodeBinding::Data &data, std::string const &name,
															bool isArray = false, bool isStaticPressure = false, const double staticPressure = 0) {
			//NAN assigning data to array of child-objects
			r = Nan::New<Object>();
			setR("gasDensity", data.gasDensity);
			setR("gasVolumeFlowRate", data.gasVolumeFlowRate);
			setR("gasVelocity", data.gasVelocity);
			setR("gasVelocityPressure", data.gasVelocityPressure);
			setR("gasTotalPressure", data.gasTotalPressure);
			if (isStaticPressure)
			{
				setR("staticPressure", staticPressure);
			}

			if (isArray)
			{
				Nan::Set(addlTravPlanes, index, r);
			}
			else
			{
				Nan::Set(rv, Nan::New<String>(name).ToLocalChecked(), r);
			}
		};

		for (PlaneData::NodeBinding::Data const &data : output.addlTravPlanes)
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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	try
	{
		//NAN init data
		FanRatedInfo fanRatedInfo = getFanRatedInfo();
		PlaneData planeData = getPlaneData();
		BaseGasDensity baseGasDensity = getBaseGasDensity();
		FanShaftPower fanShaftPower = getFanShaftPower();

		//Calculation procedure
		Fan203::Output const rv = Fan203(fanRatedInfo, planeData, baseGasDensity, fanShaftPower).calculate();

		//NAN return resutls
		setR("fanEfficiencyTotalPressure", rv.fanEfficiencyTotalPressure);
		setR("fanEfficiencyStaticPressure", rv.fanEfficiencyStaticPressure);
		setR("fanEfficiencyStaticPressureRise", rv.fanEfficiencyStaticPressureRise);
		setR("flow", rv.asTested.flow);
		setR("pressureTotal", rv.asTested.pressureTotal);
		setR("pressureStatic", rv.asTested.pressureStatic);
		setR("staticPressureRise", rv.asTested.staticPressureRise);
		setR("power", rv.asTested.power);
		setR("kpc", rv.asTested.kpc);
		setR("flowCorrected", rv.converted.flow);
		setR("pressureTotalCorrected", rv.converted.pressureTotal);
		setR("pressureStaticCorrected", rv.converted.pressureStatic);
		setR("staticPressureRiseCorrected", rv.converted.staticPressureRise);
		setR("powerCorrected", rv.converted.power);
		setR("kpcCorrected", rv.converted.kpc);
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
	std::string const curveTypeStr = getString("curveType", inp);

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
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> const &arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, Nan::New<String>("BaseCurveData").ToLocalChecked()).ToLocalChecked();
	Local<Array> const &array = v8::Local<v8::Array>::Cast(arrayTmp);
	std::vector<FanCurveData::BaseCurve> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		Local<Value> const &innerArrayTmp = Nan::To<Object>(array->Get(context, i).ToLocalChecked()).ToLocalChecked();
		Local<Array> const &innerArray = Local<Array>::Cast(innerArrayTmp);
		curveData.emplace_back(FanCurveData::BaseCurve(Nan::To<double>(innerArray->Get(context, 0).ToLocalChecked()).FromJust(),
													   Nan::To<double>(innerArray->Get(context, 1).ToLocalChecked()).FromJust(),
													   Nan::To<double>(innerArray->Get(context, 2).ToLocalChecked()).FromJust()));
	}
	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
}

FanCurveData getFanRatedPointCurveData()
{
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> const &arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, Nan::New<String>("RatedPointCurveData").ToLocalChecked()).ToLocalChecked();
	Local<Array> const &array = v8::Local<v8::Array>::Cast(arrayTmp);
	std::vector<FanCurveData::RatedPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		Local<Value> const &innerArrayTmp = Nan::To<Object>(array->Get(context, i).ToLocalChecked()).ToLocalChecked();
		Local<Array> const &innerArray = Local<Array>::Cast(innerArrayTmp);
		curveData.emplace_back(FanCurveData::RatedPoint(Nan::To<double>(innerArray->Get(context, 0).ToLocalChecked()).FromJust(),
														Nan::To<double>(innerArray->Get(context, 1).ToLocalChecked()).FromJust(),
														Nan::To<double>(innerArray->Get(context, 2).ToLocalChecked()).FromJust(),
														Nan::To<double>(innerArray->Get(context, 3).ToLocalChecked()).FromJust(),
														Nan::To<double>(innerArray->Get(context, 4).ToLocalChecked()).FromJust(),
														Nan::To<double>(innerArray->Get(context, 5).ToLocalChecked()).FromJust()));
	}

	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
}

FanCurveData getFanBaseOperatingPointCurveData()
{
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> const &arrayTmp = Nan::To<Object>(inp).ToLocalChecked()->Get(context, Nan::New<String>("BaseOperatingPointCurveData").ToLocalChecked()).ToLocalChecked();
	Local<Array> const &array = v8::Local<v8::Array>::Cast(arrayTmp);
	std::vector<FanCurveData::BaseOperatingPoint> curveData;
	for (std::size_t i = 0; i < array->Length(); i++)
	{
		Local<Value> const &innerArrayTmp = Nan::To<Object>(array->Get(context, i).ToLocalChecked()).ToLocalChecked();
		Local<Array> const &innerArray = Local<Array>::Cast(innerArrayTmp);
		curveData.emplace_back(FanCurveData::BaseOperatingPoint(Nan::To<double>(innerArray->Get(context, 0).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 1).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 2).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 3).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 4).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 5).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 6).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 7).ToLocalChecked()).FromJust(),
																Nan::To<double>(innerArray->Get(context, 8).ToLocalChecked()).FromJust()));
	}
	FanCurveType fanCurveType = getFanCurveType();

	//construct C++ obj and return
	FanCurveData fanCurveData(fanCurveType, std::move(curveData));
	return fanCurveData;
}

void returnResultData(std::vector<ResultData> const &results)
{
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();

	std::size_t index = 0;
	Local<Array> outerArray = Nan::New<Array>(results.size());
	for (ResultData const &row : results)
	{
		Local<Array> array = Nan::New<Array>(4);
		Nan::Set(array, 0, Nan::New<Number>(row.flow));
		Nan::Set(array, 1, Nan::New<Number>(row.pressure));
		Nan::Set(array, 2, Nan::New<Number>(row.power));
		Nan::Set(array, 3, Nan::New<Number>(row.efficiency));

		Nan::Set(outerArray, index, array);
		index++;
	}
	Nan::Set(r, Nan::New<String>("ResultData").ToLocalChecked(), outerArray);
}

// fan performance curves
NAN_METHOD(fanCurve)
{
	//NAN init data
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	//fetch bool values to check if defined objects were supplied
	const bool baseCurveDataDefined = isDefined(inp, "BaseCurveData");
	const bool ratedPointCurveDataDefined = isDefined(inp, "RatedPointCurveData");

	//NAN data fetching
	const double density = getDouble("density", inp);
	const double densityCorrected = getDouble("densityCorrected", inp);
	const double speed = getDouble("speed", inp);
	const double speedCorrected = getDouble("speedCorrected", inp);
	const double pressureBarometric = getDouble("pressureBarometric", inp);
	const double pressureBarometricCorrected = getDouble("pressureBarometricCorrected", inp);
	const double pt1Factor = getDouble("pt1Factor", inp);
	const double gamma = getDouble("gamma", inp);
	const double gammaCorrected = getDouble("gammaCorrected", inp);
	const double area1 = getDouble("area1", inp);
	const double area2 = getDouble("area2", inp);

	if (baseCurveDataDefined)
	{
		FanCurveData fanCurveData = getFanBaseCurveData();
		//Create C++ obj and calculate
		std::vector<ResultData> const rv = FanCurve(density, densityCorrected, speed,
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
		std::vector<ResultData> const rv = FanCurve(density, densityCorrected, speed,
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
		std::vector<ResultData> const rv = FanCurve(density, densityCorrected, speed,
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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	OptimalFanEfficiency::FanType const fanType = GetEnumVal<OptimalFanEfficiency::FanType>("fanType", inp);
	double const fanSpeed = getDouble("fanSpeed", inp);
	double const flowRate = getDouble("flowRate", inp);
	double const inletPressure = getDouble("inletPressure", inp);
	double const outletPressure = getDouble("outletPressure", inp);
	double const compressibility = getDouble("compressibility", inp);

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
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	const double moverShaftPower = getDouble("moverShaftPower", inp);
	const double inletPressure = getDouble("inletPressure", inp);
	const double outletPressure = getDouble("outletPressure", inp);
	const double barometricPressure = getDouble("barometricPressure", inp);
	const double flowRate = getDouble("flowRate", inp);
	const double specificHeatRatio = getDouble("specificHeatRatio", inp);

	//Create C++ obj and calculate
	double const compressibilityFactor = CompressibilityFactor(
											 moverShaftPower, inletPressure, outletPressure,
											 barometricPressure, flowRate, specificHeatRatio)
											 .calculate();

	//NAN returning single value
	info.GetReturnValue().Set(compressibilityFactor);
}
