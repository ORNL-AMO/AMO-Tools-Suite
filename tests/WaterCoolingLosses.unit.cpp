#include "catch.hpp"
#include <calculator/losses/WaterCoolingLosses.h>

TEST_CASE( "Calculate Heat Loss for liquid cooling Losses Water", "[Heat Loss]" ) {

    REQUIRE(WaterCoolingLosses(100.0, 80.0, 120.0, 1.0).getHeatLoss() == Approx(1989032 ) );

}