#include "catch.hpp"
#include <calculator/WallLosses.h>

TEST_CASE( "Calculate Heat Loss for furnace walls", "[Heat Loss]" ) {

    REQUIRE( WallLosses(500.0, 80.0, 225.0, 10.0, 0.9, 1.394, 1.0).getHeatLoss() == Approx( 422982.18003245839 ) );

}