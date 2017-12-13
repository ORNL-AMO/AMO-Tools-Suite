#include <catch.hpp>
#include "calculator/util/CompressedAir.h"

TEST_CASE( "PneumaticAirRequirement", "[CompressedAir][PneumaticAirRequirement]") {
	std::size_t unitTestNumber = 1;
	auto const compare = [&unitTestNumber](PneumaticAirRequirement::Output actual, PneumaticAirRequirement::Output expected) {
		INFO("Unit test number " + std::to_string(unitTestNumber));
		CHECK(expected.volumeAirIntakePiston == Approx(actual.volumeAirIntakePiston));
		CHECK(expected.compressionRatio == Approx(actual.compressionRatio));
		CHECK(expected.airRequirementPneumaticCylinder == Approx(actual.airRequirementPneumaticCylinder));
		unitTestNumber++;
	};

	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::SingleActing, 1.5, 6, 100, 60).calculate(), {0.36796875, 7.8027210884, 2.8711575255});
	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType ::DoubleActing, 1.5, 6, 0.375, 100, 60).calculate(), {0.7129394531, 7.8027210884, 5.5628677057});

	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::SingleActing, 3.5, 6, 100, 60).calculate(), {2.0033854167, 7.8027210884, 15.6318576389});
	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::DoubleActing, 3.5, 6, 0.375, 100, 60).calculate(), {3.9837727865, 7.8027210884, 31.0842679324});

	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::SingleActing, 1.5, 9, 100, 60).calculate(), {0.551953125, 7.8027210884, 4.30673628832});
	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::DoubleActing, 1.5, 9, 0.375, 100, 60).calculate(), {1.069409179, 7.8027210884, 8.3443015585});

	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::SingleActing, 1.5, 6, 100, 60).calculate(), {0.36796875, 7.8027210884, 2.8711575255});
	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::DoubleActing, 1.5, 6, 0.575, 100, 60).calculate(), {0.6818665365, 7.8027210884, 5.3204144035});

	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::SingleActing, 1.5, 6, 140, 90).calculate(), {0.551953125, 10.5238095238, 5.8086495536});
	compare(PneumaticAirRequirement(PneumaticAirRequirement::PistonType::DoubleActing, 1.5, 6, 0.575, 140, 90).calculate(), {1.0227998047, 10.5238095238, 10.7637503255});
}