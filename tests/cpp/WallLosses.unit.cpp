#include "catch.hpp"
#include <calculator/losses/WallLosses.h>

TEST_CASE( "Calculate Heat Loss for furnace walls", "[Heat Loss]" ) {
    REQUIRE( WallLosses(500.0, 80.0, 225.0, 10.0, 0.9, 1.394, 1.0).getHeatLoss() == Approx( 404627.551342992 ) );
}