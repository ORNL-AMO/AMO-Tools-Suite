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

TEST_CASE( "ReceiverTank - Useable Air Capacity", "[CompressedAir][ReceiverTank][UseableAirCapacity]") {
	CHECK(ReceiverTank::calculateUsableCapacity(660, 110, 100) == Approx(60.0240096038));
	CHECK(ReceiverTank::calculateUsableCapacity(760, 110, 100) == Approx(69.1185565135));
	CHECK(ReceiverTank::calculateUsableCapacity(760, 150, 100) == Approx(345.5927825676));
	CHECK(ReceiverTank::calculateUsableCapacity(760, 150, 130) == Approx(138.237113027));
}

TEST_CASE( "ReceiverTank - Size Calculation", "[CompressedAir][ReceiverTank][SizeCalculation]") {
	CHECK(ReceiverTank(ReceiverTank::Method::General, 150, 3, 14.7).calculateSize() == Approx(5497.8));
	CHECK(ReceiverTank(ReceiverTank::Method::General, 190, 3, 14.7).calculateSize() == Approx(6963.88));
	CHECK(ReceiverTank(ReceiverTank::Method::General, 190, 8, 14.7).calculateSize() == Approx(2611.455));
	CHECK(ReceiverTank(ReceiverTank::Method::General, 190, 8, 12.7).calculateSize() == Approx(2256.155));

	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 0.5, 100, 14.7, 110, 100).calculateSize() == Approx(549.78));
	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 1.5, 100, 14.7, 110, 100).calculateSize() == Approx(1649.34));
	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 1.5, 120, 14.7, 110, 100).calculateSize() == Approx(1979.208));
	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 1.5, 120, 11.7, 110, 100).calculateSize() == Approx(1575.288));
	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 1.5, 120, 11.7, 150, 100).calculateSize() == Approx(315.0576));
	CHECK(ReceiverTank(ReceiverTank::Method::DedicatedStorage, 1.5, 120, 11.7, 150, 120).calculateSize() == Approx(525.096));

	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 0.5, 900, 14.7, 100, 70, 45).calculateSize() == Approx(1566.873));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 900, 14.7, 100, 70, 45).calculateSize() == Approx(4700.619));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 800, 14.7, 100, 70, 45).calculateSize() == Approx(4150.839));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 800, 11.7, 100, 70, 45).calculateSize() == Approx(3303.729));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 800, 11.7, 120, 70, 45).calculateSize() == Approx(1982.2374));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 800, 11.7, 120, 90, 45).calculateSize() == Approx(3303.729));
	CHECK(ReceiverTank(ReceiverTank::Method::MeteredStorage, 1.5, 800, 11.7, 120, 90, 75).calculateSize() == Approx(3172.455));

	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1000, 250, 14.7, 600, 2).calculateSize() == Approx(2199.12));
	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1200, 250, 14.7, 600, 2).calculateSize() == Approx(2638.944));
	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1200, 350, 14.7, 600, 2).calculateSize() == Approx(1884.96));
	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1200, 350, 11.7, 600, 2).calculateSize() == Approx(1500.2742857143));
	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1200, 350, 11.7, 800, 2).calculateSize() == Approx(2000.3657142857));
	CHECK(ReceiverTank(ReceiverTank::Method::BridgingCompressorReactionDelay, 1200, 350, 11.7, 800, 19).calculateSize() == Approx(210.56481203));
}

TEST_CASE( "Compressor Operating Cost", "[CompressedAir][OperatingCost]") {
	std::size_t unitTestNumber = 1;
	auto const compare = [&unitTestNumber](Compressor::OperatingCost::Output actual, Compressor::OperatingCost::Output expected) {
		INFO("Unit test number " + std::to_string(unitTestNumber));
		CHECK(expected.runTimeUnloaded == Approx(actual.runTimeUnloaded));
		CHECK(expected.costForLoaded == Approx(actual.costForLoaded));
		CHECK(expected.costForUnloaded == Approx(actual.costForUnloaded));
		CHECK(expected.totalAnnualCost == Approx(actual.totalAnnualCost));
		unitTestNumber++;
	};

	compare(Compressor::OperatingCost(215, 25, 6800, 85, 95, 90, 0.05).calculate(), {15, 48792.3263157895, 2272.1916666667, 51064.5179824561});
	compare(Compressor::OperatingCost(255, 25, 6800, 85, 95, 90, 0.05).calculate(), {15, 57869.9684210526, 2694.925, 60564.893421});
	compare(Compressor::OperatingCost(255, 35, 6800, 85, 95, 90, 0.05).calculate(), {15, 57869.9684210526, 3772.895, 61642.8634210526});
	compare(Compressor::OperatingCost(255, 35, 6000, 85, 95, 90, 0.05).calculate(), {15, 51061.7368421053, 3329.025, 54390.7618421053});
	compare(Compressor::OperatingCost(255, 35, 6000, 89, 93, 90, 0.05).calculate(), {11, 54614.419354838, 2441.285, 57055.704354838});
	compare(Compressor::OperatingCost(255, 35, 6000, 89, 93, 90, 0.09).calculate(), {11, 98305.9548387097, 4394.313, 102700.2678387097});
}









