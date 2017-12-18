#ifndef AMO_TOOLS_SUITE_STANDALONE_H
#define AMO_TOOLS_SUITE_STANDALONE_H

#include <nan.h>
#include <node.h>
#include "calculator/util/CHP.h"
#include "calculator/util/CompressedAir.h"
#include <string>


using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();

	auto rObj = inp->ToObject()->Get(getName);
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in standalone.h: " + nm + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

void SetR(std::string const & nm, double n) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	Local<Number> getNum = Nan::New<Number>(n);
	Nan::Set(r, getName, getNum);
}

NAN_METHOD(CHPcalculator) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	unsigned val = static_cast<unsigned>(Get("option"));
	CHP::Option option = static_cast<CHP::Option>(val);

	auto const chp = CHP(Get("annualOperatingHours"), Get("annualElectricityConsumption"), Get("annualThermalDemand"),
	                     Get("boilerThermalFuelCosts"), Get("avgElectricityCosts"), option, Get("boilerThermalFuelCostsCHPcase"),
	                     Get("CHPfuelCosts"), Get("percentAvgkWhElectricCostAvoidedOrStandbyRate"), Get("displacedThermalEfficiency"),
	                     Get("chpAvailability"), Get("thermalUtilization"));

	auto const & costInfo = chp.getCostInfo();

	SetR("annualOperationSavings", costInfo.at("annualOperationSavings"));
	SetR("totalInstalledCostsPayback", costInfo.at("totalInstalledCostsPayback"));
	SetR("simplePayback", costInfo.at("simplePayback"));
	SetR("fuelCosts", costInfo.at("fuelCosts"));
	SetR("thermalCredit", costInfo.at("thermalCredit"));
	SetR("incrementalOandM", costInfo.at("incrementalOandM"));
	SetR("totalOperatingCosts", costInfo.at("totalOperatingCosts"));
	info.GetReturnValue().Set(r);
}

NAN_METHOD(pneumaticAirRequirement) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

//	unsigned val = static_cast<unsigned>(Get("pistonType"));
//	PneumaticAirRequirement::PistonType pistonType = static_cast<PneumaticAirRequirement::PistonType>(val);

	int val = Get("pistonType");
	auto const pistonType = (!val) ? PneumaticAirRequirement::PistonType::SingleActing : PneumaticAirRequirement::PistonType::DoubleActing;

	PneumaticAirRequirement airRequirement;
	if (pistonType == PneumaticAirRequirement::PistonType::SingleActing) {
		airRequirement = PneumaticAirRequirement(pistonType, Get("cylinderDiameter"), Get("cylinderStroke"), Get("airPressure"), Get("cyclesPerMinute"));
	} else {
		airRequirement = PneumaticAirRequirement(pistonType, Get("cylinderDiameter"), Get("cylinderStroke"), Get("pistonRodDiameter"), Get("airPressure"), Get("cyclesPerMinute"));
	}

	auto const output = airRequirement.calculate();
	SetR("airRequirementPneumaticCylinder", output.airRequirementPneumaticCylinder);
	SetR("volumeAirIntakePiston", output.volumeAirIntakePiston);
	SetR("compressionRatio", output.compressionRatio);
	info.GetReturnValue().Set(r);
}

NAN_METHOD(receiverTank) {
	inp = info[0]->ToObject();

	ReceiverTank tank;
	ReceiverTank::Method method = static_cast<ReceiverTank::Method>(static_cast<unsigned>(Get("method")));

	if (method == ReceiverTank::Method::General) {
		tank = {ReceiverTank::Method::General, Get("airDemand"), Get("allowablePressureDrop"), Get("atmosphericPressure")};
	} else if (method == ReceiverTank::Method::DedicatedStorage) {
		tank = {ReceiverTank::Method::DedicatedStorage, Get("lengthOfDemand"), Get("airFlowRequirement"), Get("atmosphericPressure"), Get("initialTankPressure"), Get("finalTankPressure")};
	} else if (method == ReceiverTank::Method::BridgingCompressorReactionDelay) {
		tank = {ReceiverTank::Method::BridgingCompressorReactionDelay, Get("distanceToCompressorRoom"), Get("speedOfAir"), Get("atmosphericPressure"), Get("airDemand"), Get("allowablePressureDrop")};
	} else {
		tank = {ReceiverTank::Method::MeteredStorage, Get("lengthOfDemand"), Get("airFlowRequirement"), Get("atmosphericPressure"), Get("initialTankPressure"), Get("finalTankPressure"), Get("meteredControl")};
	}

	Local<Number> size = Nan::New(tank.calculateSize());
	info.GetReturnValue().Set(size);
}

#endif //AMO_TOOLS_SUITE_STANDALONE_H
