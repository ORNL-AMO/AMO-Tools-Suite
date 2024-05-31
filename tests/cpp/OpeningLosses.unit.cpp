#include "catch.hpp"
#include <calculator/losses/OpeningLosses.h>

TEST_CASE( "Calculate Heat Loss for opening Losses", "[Heat Loss]" ) {
    // Circular
    REQUIRE( OpeningLosses(0.95, 12.0, 9.0, 1.33, 75.0, 1600.0, 100.0, 0.70).getHeatLoss() == Approx( 16038.269976979091 ) );
    // Quadrilateral
    REQUIRE( OpeningLosses(0.95, 48.0, 15.0, 9.0, 1.67, 75.0, 1600.0, 20.0, 0.64).getHeatLoss() == Approx( 18670.2258869289 ) );

}

TEST_CASE( "Calculate viewFactor for Opening Losses", "[Heat Loss][viewFactor]" ) {
    auto opening = OpeningLosses();
	// Circular view factor calculations
    CHECK(opening.calculateViewFactor(3, 5) == Approx(0.624519890259));
    CHECK(opening.calculateViewFactor(1, 5) == Approx(0.83499999996));
    CHECK(opening.calculateViewFactor(0, 5) == Approx(0.86));
    CHECK(opening.calculateViewFactor(10, 5) == Approx(0.35084375));
    CHECK(opening.calculateViewFactor(50, 5) == Approx(0.098254464286));
    CHECK(opening.calculateViewFactor(50, 9) == Approx(0.160395178571));
    CHECK(opening.calculateViewFactor(50, 19) == Approx(0.289271964286));

    // Rectangular view factor calculations
    CHECK(opening.calculateViewFactor(5, 5, 10) == Approx(0.60));
    CHECK(opening.calculateViewFactor(5, 10, 5) == Approx(0.60));
    CHECK(opening.calculateViewFactor(1, 10, 5) == Approx(0.88));
    CHECK(opening.calculateViewFactor(2, 10, 5) == Approx(0.786933593749));
    CHECK(opening.calculateViewFactor(27, 50, 55) == Approx(0.678646418065));
    CHECK(opening.calculateViewFactor(0.5, 3, 4) == Approx(0.876666666245));
    CHECK(opening.calculateViewFactor(14.05, 3, 3) == Approx(0.2044991347));
}
