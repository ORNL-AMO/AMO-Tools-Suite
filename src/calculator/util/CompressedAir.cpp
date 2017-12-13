#include <cmath>
#include <stdexcept>
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

double ReceiverTank::calculateUsableCapacity(const double tankSize, const double airPressureIn,
                                             const double airPressureOut)
{
	return (tankSize / 7.48) * (airPressureIn - airPressureOut) / 14.7;
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