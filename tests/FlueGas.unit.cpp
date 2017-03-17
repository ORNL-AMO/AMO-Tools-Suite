#include "catch.hpp"
#include <calculator/losses/FlueGas.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {

    REQUIRE(FlueGas(0.1, 3.0, 1600.0, 80.0, 0.8, 1.02, 10.0).getHeatLoss() == Approx(2850767.0 ) );

}