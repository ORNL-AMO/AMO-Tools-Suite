#include "catch.hpp"
#include <calculator/losses/OpeningLosses.h>

TEST_CASE( "Calculate Heat Loss for opening Losses", "[Heat Loss]" ) {

    REQUIRE( OpeningLosses(12.0, 9.0, 1.33, 75.0, 1600.0, 100.0, 0.70, OpeningLosses::OpeningShape::CIRCULAR).getHeatLoss() == Approx( 16038.0 ) );
    REQUIRE( OpeningLosses(0.95, 48.0, 15.0, 9.0, 1.67, 75.0, 1600.0, 20.0, 0.64, OpeningLosses::OpeningShape::RECTANGULAR).getHeatLoss() == Approx( 18670.0 ) );

}