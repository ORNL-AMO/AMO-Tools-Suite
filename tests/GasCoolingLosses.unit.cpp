#include "catch.hpp"
#include <calculator/losses/GasCoolingLosses.h>

TEST_CASE( "Calculate Heat Loss for gas cooling Losses Air", "[Heat Loss]" ) {

    REQUIRE(GasCoolingLosses(2500.0, 80.0, 280.0, 0.02, 1.0).getHeatLoss() == Approx(600000.0 ) );
    REQUIRE(GasCoolingLosses(600, 80.0, 350.0, 0.02, 1.0).getHeatLoss() == Approx(194400.0 ) );

}