#include "catch.hpp"
#include <calculator/losses/OpeningLosses.h>

TEST_CASE( "Calculate Heat Loss for opening Losses", "[Heat Loss]" ) {
    // Circular
    REQUIRE( OpeningLosses(0.95, 12.0, 9.0, 1.33, 75.0, 1600.0, 100.0, 0.70).getHeatLoss() == Approx( 16038.269976979091 ) );
    // Quadrilateral
    REQUIRE( OpeningLosses(0.95, 48.0, 15.0, 9.0, 1.67, 75.0, 1600.0, 20.0, 0.64).getHeatLoss() == Approx( 18670.2258869289 ) );

}