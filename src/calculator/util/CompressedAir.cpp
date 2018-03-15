#include "calculator/util/CompressedAir.h"

PneumaticAirRequirement::PneumaticAirRequirement(const PistonType pistonType, const double cylinderDiameter,
                                                 const double cylinderStroke, const double pistonRodDiameter,
                                                 const double airPressure, const double cyclesPerMin)
		: pistonType(pistonType), cylinderDiameter(cylinderDiameter), cylinderStroke(cylinderStroke),
		  pistonRodDiameter(pistonRodDiameter), airPressure(airPressure), cyclesPerMin(cyclesPerMin)
{
	if (pistonType != PistonType::DoubleActing) {
		throw std::runtime_error("You must have a DoubleActing piston type to use piston rod diameter");
	}
}

PneumaticAirRequirement::PneumaticAirRequirement(const PistonType pistonType, const double cylinderDiameter,
                                                 const double cylinderStroke, const double airPressure,
                                                 const double cyclesPerMin)
		: pistonType(pistonType), cylinderDiameter(cylinderDiameter), cylinderStroke(cylinderStroke),
		  airPressure(airPressure), cyclesPerMin(cyclesPerMin)
{
	if (pistonType != PistonType::SingleActing) {
		throw std::runtime_error("You must have a SingleActing piston type if you do not use piston rod diameter");
	}
}

PneumaticAirRequirement::Output PneumaticAirRequirement::calculate() {
	auto const volumeAirIntakeSingle = (0.785 * std::pow(cylinderDiameter, 2) * cylinderStroke * cyclesPerMin) / 1728;
	auto const compressionRatio = (airPressure + 14.7) / 14.7;

	if (pistonType == PneumaticAirRequirement::PistonType::SingleActing) {
		return {volumeAirIntakeSingle, compressionRatio, volumeAirIntakeSingle * compressionRatio};
	}
	auto const volumeAirIntakeDouble = (2 * 1728 * volumeAirIntakeSingle - (0.785 * std::pow(pistonRodDiameter, 2)
	                                                                        * cylinderStroke * cyclesPerMin)) / 1728;
	return {volumeAirIntakeDouble, compressionRatio, volumeAirIntakeDouble * compressionRatio};
}

ReceiverTank::ReceiverTank(const Method method, const double airDemand, const double allowablePressureDrop,
                           const double atmosphericPressure)
		: method(method), airDemand(airDemand), allowablePressureDrop(allowablePressureDrop),
		  atmosphericPressure(atmosphericPressure)
{
	if (method != ReceiverTank::Method::General) {
		throw std::runtime_error("Calculation method must be set to General to use this constructor");
	}
}

ReceiverTank::ReceiverTank(Method method, double lengthOfDemandOrDistanceToCompressorRoom, double airFlowRequirementOrSpeedOfAir, double atmosphericPressure,
                           double initialTankPressureOrAirDemand, double finalTankPressureOrAllowablePressureDrop)
		: method(method), atmosphericPressure(atmosphericPressure),
		  lengthOfDemandOrDistanceToCompressorRoom(lengthOfDemandOrDistanceToCompressorRoom),
		  airFlowRequirementOrSpeedOfAir(airFlowRequirementOrSpeedOfAir),
		  initialTankPressureOrAirDemand(initialTankPressureOrAirDemand),
		  finalTankPressureOrAllowablePressureDrop(finalTankPressureOrAllowablePressureDrop)
{
	if (method != ReceiverTank::Method::DedicatedStorage && method != ReceiverTank::Method::BridgingCompressorReactionDelay) {
		throw std::runtime_error("Calculation method must be set to DedicatedStorage or BridgingCompressorReactionDelay to use this constructor");
	}
}

ReceiverTank::ReceiverTank(Method method, double lengthOfDemand, double airFlowRequirement, double atmosphericPressure,
                           double initialTankPressure, double finalTankPressure, double meteredFlowControl)
		: method(method), atmosphericPressure(atmosphericPressure), lengthOfDemandOrDistanceToCompressorRoom(lengthOfDemand),
		  airFlowRequirementOrSpeedOfAir(airFlowRequirement), initialTankPressureOrAirDemand(initialTankPressure),
		  finalTankPressureOrAllowablePressureDrop(finalTankPressure), meteredFlowControl(meteredFlowControl)
{
	if (method != ReceiverTank::Method::MeteredStorage) {
		throw std::runtime_error("Calculation method must be set to MeteredStorage to use this constructor");
	}
}

double ReceiverTank::calculateSize() {
	if (method == ReceiverTank::Method::General) {
		return airDemand * (atmosphericPressure / allowablePressureDrop) * 7.48;
	} else if (method == ReceiverTank::Method::DedicatedStorage) {
		return 7.48 * (lengthOfDemandOrDistanceToCompressorRoom * airFlowRequirementOrSpeedOfAir * atmosphericPressure)
		       / (initialTankPressureOrAirDemand - finalTankPressureOrAllowablePressureDrop);
	} else if (method == ReceiverTank::Method::MeteredStorage) {
		return (7.48 * lengthOfDemandOrDistanceToCompressorRoom * (airFlowRequirementOrSpeedOfAir - meteredFlowControl) * atmosphericPressure)
		       / (initialTankPressureOrAirDemand - finalTankPressureOrAllowablePressureDrop);
	}
	// method must be BridgingCompressorReactionDelay
	return (lengthOfDemandOrDistanceToCompressorRoom / airFlowRequirementOrSpeedOfAir) * (initialTankPressureOrAirDemand / 60)
	       * (atmosphericPressure / finalTankPressureOrAllowablePressureDrop) * 7.48;
}

Compressor::OperatingCost::OperatingCost(double motorBhp, double bhpUnloaded, double annualOperatingHours,
                                         double runTimeLoaded, double efficiencyLoaded, double efficiencyUnloaded,
                                         double costOfElectricity)
		: motorBhp(motorBhp), bhpUnloaded(bhpUnloaded), annualOperatingHours(annualOperatingHours),
		  runTimeLoaded(runTimeLoaded), efficiencyLoaded(efficiencyLoaded), efficiencyUnloaded(efficiencyUnloaded),
		  costOfElectricity(costOfElectricity)
{}

Compressor::OperatingCost::Output Compressor::OperatingCost::calculate() {
	auto const runTimeUnloaded = 100 - runTimeLoaded;
	auto const costForLoaded = (motorBhp * 0.746 * annualOperatingHours * costOfElectricity * (runTimeLoaded / 100))
	                           / (efficiencyLoaded / 100);
	auto const costForUnloaded = (motorBhp * 0.746 * annualOperatingHours * costOfElectricity * (bhpUnloaded / 100) * (runTimeUnloaded / 100))
	                           / (efficiencyUnloaded / 100);
	return {runTimeUnloaded, costForLoaded, costForUnloaded, costForLoaded + costForUnloaded};
}

Compressor::AirSystemCapacity::AirSystemCapacity(Compressor::PipeData pipeLengths,
                                                 std::vector<double> receivers)
		: pipeLengths(pipeLengths), receivers(std::move(receivers))
{}

Compressor::AirSystemCapacity::Output Compressor::AirSystemCapacity::calculate() {

	auto totalReceiverVol = 0.0;
	for (auto & gallons : receivers) {
		gallons /= 7.48;
		totalReceiverVol += gallons;
	}

	return {pipeLengths.totalPipeVolume, receivers, totalReceiverVol,
	        pipeLengths.totalPipeVolume + totalReceiverVol, pipeLengths};
}

Compressor::AirVelocity::AirVelocity(const double airFlow, const double pipePressure, const double atmosphericPressure)
		: airFlow(airFlow), pipePressure(pipePressure), atmosphericPressure(atmosphericPressure)
{}

Compressor::PipeData Compressor::AirVelocity::calculate() {
	auto const compressedAirVelocity = [this](const double traverseArea) {
		return (airFlow * atmosphericPressure / (pipePressure + atmosphericPressure)) * (144 / traverseArea) * (1.0 / 60);
	};

	return Compressor::PipeData(compressedAirVelocity);
}

Compressor::PipeSizing::PipeSizing(double airflow, double airlinePressure, double designVelocity,
                                   double atmosphericPressure)
		: airflow(airflow),  airlinePressure(airlinePressure),  designVelocity(designVelocity),
		  atmosphericPressure(atmosphericPressure)
{}

Compressor::PipeSizing::Output Compressor::PipeSizing::calculate() {
	auto const crossSectionalArea = (144 * airflow * atmosphericPressure) / (designVelocity * 60 * (airlinePressure + atmosphericPressure));
	return {crossSectionalArea, std::sqrt(crossSectionalArea / 0.78)};
}

Compressor::PneumaticValve::PneumaticValve(const double inletPressure, const double outletPressure)
		: inletPressure(inletPressure), outletPressure(outletPressure),
		  flowRate(0.6875 * std::sqrt(inletPressure - outletPressure) * std::sqrt(inletPressure + outletPressure)),
		  flowRateKnown(false)
{}

Compressor::PneumaticValve::PneumaticValve(const double inletPressure, const double outletPressure, const double flowRate)
		: inletPressure(inletPressure), outletPressure(outletPressure), flowRate(flowRate), flowRateKnown(true)
{}

double Compressor::PneumaticValve::calculate() {
	if (!flowRateKnown) {
		return flowRate;
	}
	return flowRate / (0.6875 * std::sqrt(inletPressure - outletPressure) * std::sqrt(inletPressure + outletPressure));
}

BagMethod::BagMethod(const double operatingTime, const double bagFillTime, const double heightOfBag,
                     const double diameterOfBag, const int numberOfUnits)
		: operatingTime(operatingTime), bagFillTime(bagFillTime),
		  heightOfBag(heightOfBag), diameterOfBag(diameterOfBag), numberOfUnits(numberOfUnits)
{}

BagMethod::Output BagMethod::calculate() {
	auto const flowRate = (0.0273 * std::pow(diameterOfBag, 2) * heightOfBag) / bagFillTime;
	return {flowRate, (flowRate * operatingTime * numberOfUnits * 60) / 1000 };
}
