#include "catch.hpp"
#include <calculator/pump/HeadTool.h>

TEST_CASE( "Calculate Pump Head with and without suction tanks", "[HeadToolCalculations]" ) {
	const double flowRate = 2000;
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 115, 0, 1, 10, 124, 0, 1).calculate()["pumpHead"] ==
	        Approx(22.972865551821844));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 0, 1, 10, 124, 0, 1).calculate()["pumpHead"] ==
	        Approx(46.080895538862784));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 10, 124, 0, 1).calculate()["pumpHead"] ==
	        Approx(41.080895538862784));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 0.5, 10, 124, 0, 1).calculate()["pumpHead"] ==
	        Approx(41.03037569241383));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 124, 0, 1).calculate()["pumpHead"] ==
	        Approx(39.41609397604601));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 135, 0, 1).calculate()["pumpHead"] ==
	        Approx(64.83492696179103));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 17.9, 105, 5, 1, 15, 135, 4, 0.1).calculate()["pumpHead"] ==
	        Approx(68.6505181732944));


	REQUIRE( HeadTool(1, flowRate, 17.9, 5, 5, 1, 15, 50, 1, 1 ).calculate()["pumpHead"] == Approx(100.39593224945455) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 5, 1, 15, 50, 1, 1 ).calculate()["pumpHead"] == Approx(88.84191725593406) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 1, 15, 50, 1, 1 ).calculate()["pumpHead"] == Approx(78.84191725593406) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 15, 50, 1, 1 ).calculate()["pumpHead"] == Approx(78.75098153232594) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 50, 1, 1 ).calculate()["pumpHead"] == Approx(78.34278499528914) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 1, 1 ).calculate()["pumpHead"] == Approx(9.018695034166301) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 10, 1 ).calculate()["pumpHead"] == Approx(18.0186950341663) );
	REQUIRE( HeadTool(1, flowRate, 17.9, 10, 15, 0.1, 60, 20, 10, 0.9 ).calculate()["pumpHead"] == Approx(18.018614995629626) );
}
