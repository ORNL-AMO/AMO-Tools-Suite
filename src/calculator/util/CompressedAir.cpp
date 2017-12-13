#include <cmath>
#include "calculator/util/CompressedAir.h"

PneumaticAirRequirement::PneumaticAirRequirement(const double cylinderDiameter, const double cylinderStroke,
                                                 const double pistonRodDiameter, const double airPressure,
                                                 const double cyclesPerMin)
		: cylinderDiameter(cylinderDiameter), cylinderStroke(cylinderStroke), pistonRodDiameter(pistonRodDiameter),
		  airPressure(airPressure), cyclesPerMin(cyclesPerMin)
{}

PneumaticAirRequirement::Output PneumaticAirRequirement::calculate() {
	auto const volumeAirIntakeSingle = (0.785 * std::pow(cylinderDiameter, 2) * cylinderStroke * cyclesPerMin) / 1728;
	auto const volumeAirIntakeDouble = (2 * 1728 * volumeAirIntakeSingle - (0.785 * std::pow(pistonRodDiameter, 2)
	                                                                        * cylinderStroke * cyclesPerMin)) / 1728;
	auto const compressionRatio = (airPressure + 14.7) / 14.7;
	auto const airRequirementSingleActingPneumaticCylinder = volumeAirIntakeSingle * compressionRatio;
	auto const airRequirementDoubleActingPneumaticCylinder = volumeAirIntakeDouble * compressionRatio;
	return {volumeAirIntakeSingle, volumeAirIntakeDouble, compressionRatio, airRequirementSingleActingPneumaticCylinder,
	        airRequirementDoubleActingPneumaticCylinder};
}