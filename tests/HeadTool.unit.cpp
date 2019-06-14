#include "catch.hpp"
#include <calculator/pump/HeadTool.h>

TEST_CASE( "Calculate Pump Head with and without suction tanks", "[HeadToolCalculations]" ) {
	const double flowRate = 2000;
	auto res = HeadToolSuctionTank(1, flowRate, 17.9, 115, 0, 1, 10, 124, 0, 1).calculate();

	CHECK(res.pumpHead == Approx(22.9728655518));
	CHECK(res.pressureHead == Approx(20.7972269883));
	CHECK(res.elevationHead == Approx(0.0));
	CHECK(res.velocityHeadDifferential == Approx(1.0372994353));
	CHECK(res.suctionHead == Approx(0.1010396929));
	CHECK(res.dischargeHead == Approx(1.0372994353));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 0, 1, 10, 124, 0, 1).calculate().pumpHead ==
	        Approx(46.080895538862784));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 10, 124, 0, 1).calculate().pumpHead ==
	        Approx(41.080895538862784));

	res = HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 0.5, 10, 124, 0, 1).calculate();
	CHECK(res.pumpHead == Approx(41.0303756924));
	CHECK(res.pressureHead == Approx(43.9052569754));
	CHECK(res.elevationHead == Approx(-5.0));
	CHECK(res.velocityHeadDifferential == Approx(1.0372994353));
	CHECK(res.suctionHead == Approx(0.0505198464));
	CHECK(res.dischargeHead == Approx(1.0372994353));

	res = HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 124, 0, 1).calculate();
	CHECK(res.pumpHead == Approx(39.416093976));
	CHECK(res.pressureHead == Approx(43.9052569754));
	CHECK(res.elevationHead == Approx(-5.0));
	CHECK(res.velocityHeadDifferential == Approx(0.2048986539));
	CHECK(res.suctionHead == Approx(0.1010396929));
	CHECK(res.dischargeHead == Approx(0.2048986539));

	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 124, 0, 1).calculate().pumpHead ==
	        Approx(39.41609397604601));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 135, 0, 1).calculate().pumpHead ==
	        Approx(64.83492696179103));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 135, 4, 0.1).calculate().pumpHead ==
	        Approx(68.6505181732944));


	res = HeadTool(1, flowRate, 17.9, 5, 5, 1, 15, 50, 1, 1 ).calculate();
	CHECK(res.pumpHead == Approx(100.3959322495));
	CHECK(res.pressureHead == Approx(103.9861349417));
	CHECK(res.elevationHead == Approx(-4.0));
	CHECK(res.velocityHeadDifferential == Approx(0.103858961));
	CHECK(res.suctionHead == Approx(0.1010396929));
	CHECK(res.dischargeHead == Approx(0.2048986539));

	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 5, 1, 15, 50, 1, 1 ).calculate().pumpHead == Approx(88.84191725593406) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 1, 15, 50, 1, 1 ).calculate().pumpHead == Approx(78.84191725593406) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 15, 50, 1, 1 ).calculate().pumpHead == Approx(78.75098153232594) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 50, 1, 1 ).calculate().pumpHead == Approx(78.34278499528914) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 1, 1 ).calculate().pumpHead == Approx(9.018695034166301) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 10, 1 ).calculate().pumpHead == Approx(18.0186950341663) );

	res = HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 10, 0.9 ).calculate();
	CHECK(res.pumpHead == Approx(18.0186149956));
	CHECK(res.pressureHead == Approx(23.108029987));
	CHECK(res.elevationHead == Approx(-5.0));
	CHECK(res.velocityHeadDifferential == Approx(-0.1002393075));
	CHECK(res.suctionHead == Approx(0.0101039693));
	CHECK(res.dischargeHead == Approx(0.0007203468));
}
