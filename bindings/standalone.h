#ifndef AMO_TOOLS_SUITE_STANDALONE_H
#define AMO_TOOLS_SUITE_STANDALONE_H

#include "NanDataConverters.h"

#include <nan.h>
#include <node.h>
#include "calculator/util/CHP.h"
#include "calculator/util/CompressedAir.h"
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>


using namespace Nan;
using namespace v8;

std::vector<double> GetVector(const std::string &key, Local<Object> obj)
{
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();

	Local<Value> arrayTmp = Nan::Get(Nan::To<v8::Object>(obj).ToLocalChecked(), Nan::New<String>(key).ToLocalChecked()).ToLocalChecked();
    Local<Array> jsArray = v8::Local<v8::Array>::Cast(arrayTmp);
    std::vector<double> array;

    for (unsigned int i = 0; i < jsArray->Length(); i++)
    {
        v8::Local<v8::Value> jsElement = jsArray->Get(context, i).ToLocalChecked();
        double val = Nan::To<double>(jsElement).FromJust();
        array.push_back(val);
    }
    return array;
}

NAN_METHOD(CHPcalculator) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double annualOperatingHours = getDouble("annualOperatingHours");
	const double annualElectricityConsumption = getDouble("annualElectricityConsumption");
	const double annualThermalDemand = getDouble("annualThermalDemand");
	const double boilerThermalFuelCosts = getDouble("boilerThermalFuelCosts");
	const double avgElectricityCosts =  getDouble("avgElectricityCosts");
	const double boilerThermalFuelCostsCHPcase = getDouble("boilerThermalFuelCostsCHPcase");
	const double CHPfuelCosts =  getDouble("CHPfuelCosts");
	const double percentAvgkWhElectricCostAvoidedOrStandbyRate = getDouble("percentAvgkWhElectricCostAvoidedOrStandbyRate");
	const double displacedThermalEfficiency = getDouble("displacedThermalEfficiency");
	const double chpAvailability = getDouble("chpAvailability");
	const double thermalUtilization = getDouble("thermalUtilization");

	unsigned val = static_cast<unsigned>(getDouble("option"));
	CHP::Option option = static_cast<CHP::Option>(val);

	auto const chp = CHP(annualOperatingHours, annualElectricityConsumption, annualThermalDemand,
	                     boilerThermalFuelCosts, avgElectricityCosts, option, boilerThermalFuelCostsCHPcase,
	                     CHPfuelCosts, percentAvgkWhElectricCostAvoidedOrStandbyRate, displacedThermalEfficiency,
	                     chpAvailability, thermalUtilization);

	auto const & costInfo = chp.getCostInfo();

	setR("annualOperationSavings", costInfo.at("annualOperationSavings"));
	setR("totalInstalledCostsPayback", costInfo.at("totalInstalledCostsPayback"));
	setR("simplePayback", costInfo.at("simplePayback"));
	setR("fuelCosts", costInfo.at("fuelCosts"));
	setR("thermalCredit", costInfo.at("thermalCredit"));
	setR("incrementalOandM", costInfo.at("incrementalOandM"));
	setR("totalOperatingCosts", costInfo.at("totalOperatingCosts"));
	info.GetReturnValue().Set(r);
}

NAN_METHOD(usableAirCapacity) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	const double tankSize = getDouble("tankSize");
	const double airPressureIn = getDouble("airPressureIn");
	const double airPressureOut = getDouble("airPressureOut");
	info.GetReturnValue().Set(ReceiverTank::calculateUsableCapacity(tankSize, airPressureIn, airPressureOut));
}

NAN_METHOD(pneumaticAirRequirement) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	int val = getDouble("pistonType");
	auto const pistonType = (!val) ? PneumaticAirRequirement::PistonType::SingleActing : PneumaticAirRequirement::PistonType::DoubleActing;
	const double cylinderDiameter = getDouble("cylinderDiameter");
	const double cylinderStroke = getDouble("cylinderStroke");
	const double airPressure =  getDouble("airPressure");
	const double cyclesPerMinute = getDouble("cyclesPerMinute");
	

	PneumaticAirRequirement airRequirement;
	if (pistonType == PneumaticAirRequirement::PistonType::SingleActing) {
		airRequirement = PneumaticAirRequirement(pistonType, cylinderDiameter, cylinderStroke, airPressure, cyclesPerMinute);
	} else {
		const double pistonRodDiameter = getDouble("pistonRodDiameter");
		airRequirement = PneumaticAirRequirement(pistonType, cylinderDiameter, cylinderStroke, pistonRodDiameter, airPressure, cyclesPerMinute);
	}

	auto const output = airRequirement.calculate();
	setR("airRequirementPneumaticCylinder", output.airRequirementPneumaticCylinder);
	setR("volumeAirIntakePiston", output.volumeAirIntakePiston);
	setR("compressionRatio", output.compressionRatio);
	info.GetReturnValue().Set(r);
}

NAN_METHOD(receiverTank) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();

	ReceiverTank tank;
	ReceiverTank::Method method = static_cast<ReceiverTank::Method>(static_cast<unsigned>(getDouble("method")));

	
	if (method == ReceiverTank::Method::General) {

		const double airDemand = getDouble("airDemand");
		const double allowablePressureDrop = getDouble("allowablePressureDrop");
		const double atmosphericPressure = getDouble("atmosphericPressure");

		tank = {ReceiverTank::Method::General, airDemand, allowablePressureDrop, atmosphericPressure};

	} else if (method == ReceiverTank::Method::DedicatedStorage) {

		const double finalTankPressure = getDouble("finalTankPressure");
		const double initialTankPressure = getDouble("initialTankPressure");
		const double lengthOfDemand =  getDouble("lengthOfDemand");
		const double airFlowRequirement = getDouble("airFlowRequirement");
		const double atmosphericPressure = getDouble("atmosphericPressure");

		tank = {ReceiverTank::Method::DedicatedStorage, lengthOfDemand, airFlowRequirement, atmosphericPressure, initialTankPressure, finalTankPressure};

	} else if (method == ReceiverTank::Method::BridgingCompressorReactionDelay) {

		const double speedOfAir = getDouble("speedOfAir");
		const double distanceToCompressorRoom = getDouble("distanceToCompressorRoom");
		const double atmosphericPressure = getDouble("atmosphericPressure");
		const double airDemand = getDouble("airDemand");
		const double allowablePressureDrop = getDouble("allowablePressureDrop");

		tank = {ReceiverTank::Method::BridgingCompressorReactionDelay, distanceToCompressorRoom, speedOfAir, atmosphericPressure, airDemand, allowablePressureDrop};

	} else {
		const double lengthOfDemand =  getDouble("lengthOfDemand");
		const double airFlowRequirement = getDouble("airFlowRequirement");
		const double atmosphericPressure = getDouble("atmosphericPressure");
		const double initialTankPressure = getDouble("initialTankPressure");
		const double finalTankPressure = getDouble("finalTankPressure");
		const double meteredControl = getDouble("meteredControl");
		
		tank = {ReceiverTank::Method::MeteredStorage, lengthOfDemand, airFlowRequirement, atmosphericPressure, initialTankPressure, finalTankPressure, meteredControl};
	}
	Local<Number> size = Nan::New(tank.calculateSize());
	info.GetReturnValue().Set(size);
}

NAN_METHOD(operatingCost) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double motorBhp = getDouble("motorBhp");
	const double bhpUnloaded =  getDouble("bhpUnloaded");
	const double annualOperatingHours = getDouble("annualOperatingHours");
	const double runTimeLoaded = getDouble("runTimeLoaded");
	const double efficiencyLoaded = getDouble("efficiencyLoaded");
	const double efficiencyUnloaded = getDouble("efficiencyUnloaded");
	const double costOfElectricity = getDouble("costOfElectricity");

	auto output = Compressor::OperatingCost(motorBhp, bhpUnloaded, annualOperatingHours,
	                                        runTimeLoaded, efficiencyLoaded, efficiencyUnloaded,
	                                        costOfElectricity).calculate();

	setR("runTimeUnloaded", output.runTimeUnloaded);
	setR("costForLoaded", output.costForLoaded);
	setR("costForUnloaded", output.costForUnloaded);
	setR("totalAnnualCost", output.totalAnnualCost);
	info.GetReturnValue().Set(r);
}

NAN_METHOD(airSystemCapacity) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	std::vector<double> receiverCapacitiesGallons = GetVector("receiverCapacities", inp);
	const double oneHalf =  getDouble("oneHalf");
	const double threeFourths = getDouble("threeFourths");
	const double one = getDouble("one");
	const double oneAndOneFourth = getDouble("oneAndOneFourth");
	const double oneAndOneHalf = getDouble("oneAndOneHalf");
	const double two = getDouble("two");
	const double twoAndOneHalf = getDouble("twoAndOneHalf");
	const double three = getDouble("three");
	const double threeAndOneHalf = getDouble("threeAndOneHalf");
	const double four = getDouble("four");
	const double five = getDouble("five");
	const double six = getDouble("six");

	Compressor::AirSystemCapacity::Output output = Compressor::AirSystemCapacity
			(
					{
							oneHalf, threeFourths, one, oneAndOneFourth,
							oneAndOneHalf, two, twoAndOneHalf, three,
							threeAndOneHalf, four, five, six
					},
					std::move(receiverCapacitiesGallons)
			).calculate();

	setR("totalPipeVolume", output.totalPipeVolume);
	setR("totalReceiverVolume", output.totalReceiverVol);
	setR("totalCapacityOfCompressedAirSystem", output.totalCapacityOfCompressedAirSystem);

	v8::Local<v8::Array> receiverCapacities = Nan::New<v8::Array>(output.receiverCapacities.size());
	for (std::size_t i = 0; i < output.receiverCapacities.size(); i++) {
		Nan::Set(receiverCapacities, i, Nan::New<Number>(output.receiverCapacities[i]));
	}
	Nan::Set(r, Nan::New<String>("receiverCapacities").ToLocalChecked(), receiverCapacities);

	setR("oneHalf", output.pipeLengths.oneHalf);
	setR("threeFourths", output.pipeLengths.threeFourths);
	setR("one", output.pipeLengths.one);
	setR("oneAndOneFourth", output.pipeLengths.oneAndOneFourth);
	setR("oneAndOneHalf", output.pipeLengths.oneAndOneHalf);
	setR("two", output.pipeLengths.two);
	setR("twoAndOneHalf", output.pipeLengths.twoAndOneHalf);
	setR("three", output.pipeLengths.three);
	setR("threeAndOneHalf", output.pipeLengths.threeAndOneHalf);
	setR("four", output.pipeLengths.four);
	setR("five", output.pipeLengths.five);
	setR("six", output.pipeLengths.six);
	info.GetReturnValue().Set(r);
}

NAN_METHOD(airVelocity) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double airFlow = getDouble("airFlow");
	const double pipePressure = getDouble("pipePressure");
	const double atmosphericPressure = getDouble("atmosphericPressure");

	Compressor::PipeData output = Compressor::AirVelocity(airFlow, pipePressure, atmosphericPressure).calculate();

	setR("oneHalf", output.oneHalf);
	setR("threeFourths", output.threeFourths);
	setR("one", output.one);
	setR("oneAndOneFourth", output.oneAndOneFourth);
	setR("oneAndOneHalf", output.oneAndOneHalf);
	setR("two", output.two);
	setR("twoAndOneHalf", output.twoAndOneHalf);
	setR("three", output.three);
	setR("threeAndOneHalf", output.threeAndOneHalf);
	setR("four", output.four);
	setR("five", output.five);
	setR("six", output.six);

	info.GetReturnValue().Set(r);
}

NAN_METHOD(pipeSizing) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
	
	const double airFlow = getDouble("airFlow");
	const double airlinePressure = getDouble("airlinePressure");
	const double designVelocity = getDouble("designVelocity");
	const double atmosphericPressure = getDouble("atmosphericPressure");

	auto output = Compressor::PipeSizing(airFlow, airlinePressure, designVelocity, atmosphericPressure).calculate();

	setR("crossSectionalArea", output.crossSectionalArea);
	setR("pipeDiameter", output.pipeDiameter);

	info.GetReturnValue().Set(r);
}

NAN_METHOD(pneumaticValve) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();

	Local<Value> flowRate = inp->Get(context, Nan::New<String>("flowRate").ToLocalChecked()).ToLocalChecked();
	const double inletPressure = getDouble("inletPressure");
	const double outletPressure = getDouble("outletPressure");
	if (flowRate->IsUndefined()) {
		double output = Compressor::PneumaticValve(inletPressure, outletPressure).calculate();
		setR("flowRate", output);
	} else {
		const double flowRateInput = getDouble("flowRate");
		double output = Compressor::PneumaticValve(inletPressure, outletPressure, flowRateInput).calculate();
		setR("flowCoefficient", output);
	}

	info.GetReturnValue().Set(r);
}

NAN_METHOD(bagMethod) {
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double operatingTime = getDouble("operatingTime");
	const double bagFillTime = getDouble("bagFillTime");
	const double heightOfBag = getDouble("heightOfBag");
	const double diameterOfBag = getDouble("diameterOfBag");
	const double numberOfUnits = getDouble("numberOfUnits");

	auto output = BagMethod(operatingTime, bagFillTime, heightOfBag, diameterOfBag, numberOfUnits).calculate();
	setR("flowRate", output.flowRate);
	setR("annualConsumption", output.annualConsumption);

	info.GetReturnValue().Set(r);
}


#endif //AMO_TOOLS_SUITE_STANDALONE_H
