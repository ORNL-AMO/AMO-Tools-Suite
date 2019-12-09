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

	const double annualOperatingHours = Get("annualOperatingHours");
	const double annualElectricityConsumption = Get("annualElectricityConsumption");
	const double annualThermalDemand = Get("annualThermalDemand");
	const double boilerThermalFuelCosts = Get("boilerThermalFuelCosts");
	const double avgElectricityCosts =  Get("avgElectricityCosts");
	const double boilerThermalFuelCostsCHPcase = Get("boilerThermalFuelCostsCHPcase");
	const double CHPfuelCosts =  Get("CHPfuelCosts");
	const double percentAvgkWhElectricCostAvoidedOrStandbyRate = Get("percentAvgkWhElectricCostAvoidedOrStandbyRate");
	const double displacedThermalEfficiency = Get("displacedThermalEfficiency");
	const double chpAvailability = Get("chpAvailability");
	const double thermalUtilization = Get("thermalUtilization");

	unsigned val = static_cast<unsigned>(Get("option"));
	CHP::Option option = static_cast<CHP::Option>(val);

	auto const chp = CHP(annualOperatingHours, annualElectricityConsumption, annualThermalDemand,
	                     boilerThermalFuelCosts, avgElectricityCosts, option, boilerThermalFuelCostsCHPcase,
	                     CHPfuelCosts, percentAvgkWhElectricCostAvoidedOrStandbyRate, displacedThermalEfficiency,
	                     chpAvailability, thermalUtilization);

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

NAN_METHOD(usableAirCapacity) {
	inp = info[0]->ToObject();
	
	const double tankSize = Get("tankSize");
	const double airPressureIn = Get("airPressureIn");
	const double airPressureOut = Get("airPressureOut");

	info.GetReturnValue().Set(ReceiverTank::calculateUsableCapacity(tankSize, airPressureIn, airPressureOut));
}

NAN_METHOD(pneumaticAirRequirement) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	int val = Get("pistonType");
	auto const pistonType = (!val) ? PneumaticAirRequirement::PistonType::SingleActing : PneumaticAirRequirement::PistonType::DoubleActing;
	const double cylinderDiameter = Get("cylinderDiameter");
	const double cylinderStroke = Get("cylinderStroke");
	const double airPressure =  Get("airPressure");
	const double cyclesPerMinute = Get("cyclesPerMinute");
	const double pistonRodDiameter = Get("pistonRodDiameter");	

	PneumaticAirRequirement airRequirement;
	if (pistonType == PneumaticAirRequirement::PistonType::SingleActing) {
		airRequirement = PneumaticAirRequirement(pistonType, cylinderDiameter, cylinderStroke, airPressure, cyclesPerMinute);
	} else {
		airRequirement = PneumaticAirRequirement(pistonType, cylinderDiameter, cylinderStroke, pistonRodDiameter, airPressure, cyclesPerMinute);
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

	const double airDemand = Get("airDemand");
	const double allowablePressureDrop = Get("allowablePressureDrop");
	const double atmosphericPressure = Get("atmosphericPressure");
	const double lengthOfDemand =  Get("lengthOfDemand");
	const double airFlowRequirement = Get("airFlowRequirement");
	const double initialTankPressure = Get("initialTankPressure");
	const double finalTankPressure = Get("finalTankPressure");
	const double distanceToCompressorRoom = Get("distanceToCompressorRoom");
	const double speedOfAir = Get("speedOfAir");
	const double meteredControl = Get("meteredControl");

	if (method == ReceiverTank::Method::General) {
		tank = {ReceiverTank::Method::General, airDemand, allowablePressureDrop, atmosphericPressure};
	} else if (method == ReceiverTank::Method::DedicatedStorage) {
		tank = {ReceiverTank::Method::DedicatedStorage, lengthOfDemand, airFlowRequirement, atmosphericPressure, initialTankPressure, finalTankPressure};
	} else if (method == ReceiverTank::Method::BridgingCompressorReactionDelay) {
		tank = {ReceiverTank::Method::BridgingCompressorReactionDelay, distanceToCompressorRoom, speedOfAir, atmosphericPressure, airDemand, allowablePressureDrop};
	} else {
		tank = {ReceiverTank::Method::MeteredStorage, lengthOfDemand, airFlowRequirement, atmosphericPressure, initialTankPressure, finalTankPressure, meteredControl};
	}

	Local<Number> size = Nan::New(tank.calculateSize());
	info.GetReturnValue().Set(size);
}

NAN_METHOD(operatingCost) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	const double motorBhp = Get("motorBhp");
	const double bhpUnloaded =  Get("bhpUnloaded");
	const double annualOperatingHours = Get("annualOperatingHours");
	const double runTimeLoaded = Get("runTimeLoaded");
	const double efficiencyLoaded = Get("efficiencyLoaded");
	const double efficiencyUnloaded = Get("efficiencyUnloaded");
	const double costOfElectricity = Get("costOfElectricity");

	auto output = Compressor::OperatingCost(motorBhp, bhpUnloaded, annualOperatingHours,
	                                        runTimeLoaded, efficiencyLoaded, efficiencyUnloaded,
	                                        costOfElectricity).calculate();

	SetR("runTimeUnloaded", output.runTimeUnloaded);
	SetR("costForLoaded", output.costForLoaded);
	SetR("costForUnloaded", output.costForUnloaded);
	SetR("totalAnnualCost", output.totalAnnualCost);
	info.GetReturnValue().Set(r);
}

NAN_METHOD(airSystemCapacity) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	Local<String> gallonsStr = Nan::New<String>("receiverCapacities").ToLocalChecked();
	auto array = inp->ToObject()->Get(gallonsStr);
	v8::Local<v8::Array> arr = v8::Local<v8::Array>::Cast(array);
	std::vector<double> receiverCapacitiesGallons(arr->Length());
	for (std::size_t i = 0; i < arr->Length(); i++) 
	{
		receiverCapacitiesGallons[i] = arr->Get(i)->NumberValue();
	}

	const double oneHalf =  Get("oneHalf");
	const double threeFourths = Get("threeFourths");
	const double one = Get("one");
	const double oneAndOneFourth = Get("oneAndOneFourth");
	const double oneAndOneHalf = Get("oneAndOneHalf");
	const double two = Get("two");
	const double twoAndOneHalf = Get("twoAndOneHalf");
	const double three = Get("three");
	const double threeAndOneHalf = Get("threeAndOneHalf");
	const double four = Get("four");
	const double five = Get("five");
	const double six = Get("six");

	auto output = Compressor::AirSystemCapacity
			(
					{
							oneHalf, threeFourths, one, oneAndOneFourth,
							oneAndOneHalf, two, twoAndOneHalf, three,
							threeAndOneHalf, four, five, six
					},
					std::move(receiverCapacitiesGallons)
			).calculate();

	SetR("totalPipeVolume", output.totalPipeVolume);
	SetR("totalReceiverVolume", output.totalReceiverVol);
	SetR("totalCapacityOfCompressedAirSystem", output.totalCapacityOfCompressedAirSystem);

	Handle<Array> receiverCapacities = Array::New(v8::Isolate::GetCurrent(), output.receiverCapacities.size());
	for (std::size_t i = 0; i < output.receiverCapacities.size(); i++) {
		receiverCapacities->Set(i, Nan::New<Number>(output.receiverCapacities[i]));
	}
	Nan::Set(r, Nan::New<String>("receiverCapacities").ToLocalChecked(), receiverCapacities);

	SetR("oneHalf", output.pipeLengths.oneHalf);
	SetR("threeFourths", output.pipeLengths.threeFourths);
	SetR("one", output.pipeLengths.one);
	SetR("oneAndOneFourth", output.pipeLengths.oneAndOneFourth);
	SetR("oneAndOneHalf", output.pipeLengths.oneAndOneHalf);
	SetR("two", output.pipeLengths.two);
	SetR("twoAndOneHalf", output.pipeLengths.twoAndOneHalf);
	SetR("three", output.pipeLengths.three);
	SetR("threeAndOneHalf", output.pipeLengths.threeAndOneHalf);
	SetR("four", output.pipeLengths.four);
	SetR("five", output.pipeLengths.five);
	SetR("six", output.pipeLengths.six);

	info.GetReturnValue().Set(r);
}

NAN_METHOD(airVelocity) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	const double airFlow = Get("airFlow");
	const double pipePressure = Get("pipePressure");
	const double atmosphericPressure = Get("atmosphericPressure");

	auto output = Compressor::AirVelocity(airFlow, pipePressure, atmosphericPressure).calculate();

	SetR("oneHalf", output.oneHalf);
	SetR("threeFourths", output.threeFourths);
	SetR("one", output.one);
	SetR("oneAndOneFourth", output.oneAndOneFourth);
	SetR("oneAndOneHalf", output.oneAndOneHalf);
	SetR("two", output.two);
	SetR("twoAndOneHalf", output.twoAndOneHalf);
	SetR("three", output.three);
	SetR("threeAndOneHalf", output.threeAndOneHalf);
	SetR("four", output.four);
	SetR("five", output.five);
	SetR("six", output.six);

	info.GetReturnValue().Set(r);
}

NAN_METHOD(pipeSizing) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	
	const double airFlow = Get("airFlow");
	const double airlinePressure = Get("airlinePressure");
	const double designVelocity = Get("designVelocity");
	const double atmosphericPressure = Get("atmosphericPressure");

	auto output = Compressor::PipeSizing(airFlow, airlinePressure, designVelocity, atmosphericPressure).calculate();

	SetR("crossSectionalArea", output.crossSectionalArea);
	SetR("pipeDiameter", output.pipeDiameter);

	info.GetReturnValue().Set(r);
}

NAN_METHOD(pneumaticValve) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();
	Local<String> flowRateStr = Nan::New<String>("flowRate").ToLocalChecked();

	const double inletPressure = Get("inletPressure");
	const double outletPressure = Get("outletPressure");
	const double flowRateInput = Get("flowRate");	

	auto flowRate = inp->ToObject()->Get(flowRateStr);
	if (flowRate->IsUndefined()) {
		auto output = Compressor::PneumaticValve(inletPressure, outletPressure).calculate();
		SetR("flowRate", output);
	} else {
		auto output = Compressor::PneumaticValve(inletPressure, outletPressure, flowRateInput).calculate();
		SetR("flowCoefficient", output);
	}

	info.GetReturnValue().Set(r);
}

NAN_METHOD(bagMethod) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	const double operatingTime = Get("operatingTime");
	const double bagFillTime = Get("bagFillTime");
	const double heightOfBag = Get("heightOfBag");
	const double diameterOfBag = Get("diameterOfBag");
	const double numberOfUnits = Get("numberOfUnits");

	auto output = BagMethod(operatingTime, bagFillTime, heightOfBag, diameterOfBag, numberOfUnits).calculate();
	SetR("flowRate", output.flowRate);
	SetR("annualConsumption", output.annualConsumption);

	info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_STANDALONE_H
