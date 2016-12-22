#include "catch.hpp"
#include <calculator/OpeningLosses.h>

TEST_CASE( "Calculate Heat Loss for opening Losses", "[Heat Loss]" ) {

    REQUIRE( OpeningLosses(12.0, 9.0, 1.33, 75.0, 1600.0, 100.0, 0.70, OpeningLosses::OpeningShape::CIRCULAR).getHeatLoss() == Approx( 16038.0 ) );

}