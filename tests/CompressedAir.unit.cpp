#include <catch.hpp>
#include "calculator/util/CompressedAir.h"

TEST_CASE( "PneumaticAirRequirement", "[CompressedAir][PneumaticAirRequirement]") {
	std::size_t unitTestNumber = 1;
	auto const compare = [&unitTestNumber](PneumaticAirRequirement::Output const & actual,
	                                       PneumaticAirRequirement::Output const & expected)
	{
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
	auto const compare = [&unitTestNumber](Compressor::OperatingCost::Output const & actual,
	                                       Compressor::OperatingCost::Output const & expected)
	{
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


TEST_CASE( "Compressor Air System Capacity", "[CompressedAir][AirSystemCapacity]") {
	auto output = Compressor::AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 0, 300, 0, 1000, 0, 0}, {400, 500, 660, 1060}).calculate();
	CHECK(output.totalPipeVolume == Approx(138.63));
	CHECK(output.totalReceiverVol == Approx(350.2673796791));
	CHECK(output.totalCapacityOfCompressedAirSystem == Approx(488.897379679));

	auto output2 = Compressor::AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0}, {400, 500, 660, 1060}).calculate();
	CHECK(output2.totalPipeVolume == Approx(155.28));
	CHECK(output2.totalReceiverVol == Approx(350.2673796791));
	CHECK(output2.totalCapacityOfCompressedAirSystem == Approx(505.5473796791));

	auto output3 = Compressor::AirSystemCapacity({3000, 2000, 1000, 200, 100, 500, 500, 300, 0, 1000, 0, 0}, {600, 1500, 660, 1060}).calculate();
	CHECK(output3.totalPipeVolume == Approx(155.28));
	CHECK(output3.totalReceiverVol == Approx(510.6951871658));
	CHECK(output3.totalCapacityOfCompressedAirSystem == Approx(665.9751871658));
	CHECK(output3.pipeLengths.threeFourths == Approx(7.4));
	CHECK(output3.pipeLengths.two == Approx(11.65));
	CHECK(output3.pipeLengths.four == Approx(88.4));
	CHECK(output3.receiverCapacities.at(0) == Approx(80.2139037433));
	CHECK(output3.receiverCapacities.at(1) == Approx(200.5347593583));
	CHECK(output3.receiverCapacities.at(3) == Approx(141.7112299465));
}

TEST_CASE( "Compressor Air Velocity", "[CompressedAir][AirVelocity]") {
	std::size_t unitTestNumber = 1;
	auto const compare = [&unitTestNumber](Compressor::PipeData const & results, std::vector<double> const & expected)
	{
		CHECK(expected.at(0) == Approx(results.oneHalf));
		CHECK(expected.at(1) == Approx(results.threeFourths));
		CHECK(expected.at(2) == Approx(results.one));
		CHECK(expected.at(3) == Approx(results.oneAndOneFourth));
		CHECK(expected.at(4) == Approx(results.oneAndOneHalf));
		CHECK(expected.at(5) == Approx(results.two));
		CHECK(expected.at(6) == Approx(results.twoAndOneHalf));
		CHECK(expected.at(7) == Approx(results.three));
//		CHECK(expected.at(8) == Approx(results.threeAndOneHalf));
		CHECK(expected.at(9) == Approx(results.four));
//		CHECK(expected.at(10) == Approx(results.five));
		CHECK(expected.at(11) == Approx(results.six));
		unitTestNumber++;
	};

	auto const threeAndOneHalf = 0, five = 0;
	compare(Compressor::AirVelocity(1800, 100, 14.7).calculate(), {1845.5100261552, 1044.628316691, 643.7825672634, 369.102005231, 271.3985332581, 164.7776809, 115.585179, 74.9192162174, threeAndOneHalf, 43.4919880476, five, 19.164174726});
	compare(Compressor::AirVelocity(1300, 80, 14.7).calculate(), {1614.361140443, 913.789324779, 563.149235038, 322.872228, 237.406050, 144.139387539, 101.108213388, 65.53563493, threeAndOneHalf, 38.044645886, five, 16.763874771});
}






