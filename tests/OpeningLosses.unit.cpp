#include "catch.hpp"
#include <calculator/losses/OpeningLosses.h>

TEST_CASE( "Calculate Heat Loss for opening Losses", "[Heat Loss]" ) {
    // Circular
    REQUIRE( OpeningLosses(0.95, 12.0, 9.0, 1.33, 75.0, 1600.0, 100.0, 0.70).getHeatLoss() == Approx( 16038.269976979091 ) );
    // Quadrilateral
    REQUIRE( OpeningLosses(0.95, 48.0, 15.0, 9.0, 1.67, 75.0, 1600.0, 20.0, 0.64).getHeatLoss() == Approx( 18670.2258869289 ) );

}

TEST_CASE( "Calculate viewFactor for opening Losses", "[Heat Loss][viewFactor]" ) {
    auto opening = OpeningLosses();
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 3, 5) == Approx(62.4519890259));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 1, 5) == Approx(83.499999996));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 0, 5) == Approx(86));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 10, 5) == Approx(35.084375));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 50, 5) == Approx(9.8254464286));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 50, 9) == Approx(16.0395178571));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::CIRCULAR, 50, 19) == Approx(28.9271964286));


    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 5, 5, 10) == Approx(60));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 5, 10, 5) == Approx(60));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 1, 10, 5) == Approx(88));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 2, 10, 5) == Approx(78.6933593749));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 27, 50, 55) == Approx(67.8646418065));
    REQUIRE(opening.calculateViewFactor(OpeningLosses::OpeningShape::RECTANGULAR, 0.5, 3, 4) == Approx(87.6666666245));
}
