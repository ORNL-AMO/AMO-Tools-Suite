#include "catch.hpp"
#include <calculator/pump/HeadTool.h>

TEST_CASE( "Calculate Pump Head with suction tank elevation and discharge pressure", "[What is this?]" ) {
	REQUIRE( HeadToolSuctionTank(1, 454.2, 355.6, 729.9, 0, 1, 254, 854.9, 0, 1).calculate() == Approx(7) );
}
