#include "catch.hpp"
#include <calculator/pump/HeadTool.h>

TEST_CASE( "Calculate Pump Head with and without suction tanks", "[HeadToolCalculations]" ) {
	const double flowRate = 454.24941359535023; // this is the default flow rate when 454.2 is entered in the electron app
	REQUIRE(HeadToolSuctionTank(1, flowRate, 455.6, 792.9, 0, 1, 254, 854.9, 0, 1).calculate() ==
	        Approx(6.9867498670003165));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 255.6, 792.9, 0, 1, 254, 854.9, 0, 1).calculate() ==
	        Approx(7.264536476019559));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 255.6, 692.9, 0, 1, 254, 854.9, 0, 1).calculate() ==
	        Approx(17.464309816021647));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 255.6, 692.9, 2, 1, 254, 854.9, 0, 1).calculate() ==
	        Approx(15.464309816021645));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 255.6, 692.9, 2, 1, 254, 854.9, 3, 1).calculate() ==
	        Approx(18.464309816021647));
	REQUIRE(HeadToolSuctionTank(1, flowRate, 255.6, 692.9, 2, 1, 254, 954.9, 3, 1).calculate() ==
	        Approx(28.664083156023732));

	REQUIRE( HeadTool(1, flowRate, 355.6, 34.5, 0, 1, 254, 854.9, 0, 1 ).calculate() == Approx(84.3112869348736) );
	REQUIRE( HeadTool(1, flowRate, 355.6, 34.5, 5, 1, 254, 854.9, 0, 1 ).calculate() == Approx(79.3112869348736) );
	REQUIRE( HeadTool(1, flowRate, 355.6, 34.5, 5, 1, 254, 554.9, 0, 1 ).calculate() == Approx(48.711966914867354) );
	REQUIRE( HeadTool(1, flowRate, 355.6, 34.5, 5, 1, 254, 554.9, 3, 1 ).calculate() == Approx(51.711966914867354) );
}
