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