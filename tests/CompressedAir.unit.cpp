#include <catch.hpp>
#include "calculator/util/CompressedAir.h"

TEST_CASE( "PneumaticAirRequirement", "[CompressedAir][PneumaticAirRequirement]") {
	std::size_t unitTestNumber = 1;
	auto const compare = [&unitTestNumber](PneumaticAirRequirement::Output actual, PneumaticAirRequirement::Output expected) {
		INFO("Unit test number " + std::to_string(unitTestNumber));
		CHECK(expected.volumeAirIntakeSingleActingPiston == Approx(actual.volumeAirIntakeSingleActingPiston));
		CHECK(expected.volumeAirIntakeDoubleActingPiston == Approx(actual.volumeAirIntakeDoubleActingPiston));
		CHECK(expected.compressionRatio == Approx(actual.compressionRatio));
		CHECK(expected.airRequirementSingleActingPneumaticCylinder == Approx(actual.airRequirementSingleActingPneumaticCylinder));
		CHECK(expected.airRequirementDoubleActingPneumaticCylinder == Approx(actual.airRequirementDoubleActingPneumaticCylinder));
		unitTestNumber++;
	};

	compare(PneumaticAirRequirement(1.5, 6, 0.375, 100, 60).calculate(), PneumaticAirRequirement::Output(0.36796875, 0.7129394531, 7.8027210884, 2.8711575255, 5.5628677057));
	compare(PneumaticAirRequirement(3.5, 6, 0.375, 100, 60).calculate(), PneumaticAirRequirement::Output(2.0033854167, 3.9837727865, 7.8027210884, 15.6318576389, 31.0842679324));
	compare(PneumaticAirRequirement(1.5, 9, 0.375, 100, 60).calculate(), PneumaticAirRequirement::Output(0.551953125, 1.069409179, 7.8027210884, 4.30673628832, 8.3443015585));
	compare(PneumaticAirRequirement(1.5, 6, 0.575, 100, 60).calculate(), PneumaticAirRequirement::Output(0.36796875, 0.6818665365, 7.8027210884, 2.8711575255, 5.3204144035));
	compare(PneumaticAirRequirement(1.5, 6, 0.575, 140, 90).calculate(), PneumaticAirRequirement::Output(0.551953125, 1.0227998047, 10.5238095238, 5.8086495536, 10.7637503255));
}