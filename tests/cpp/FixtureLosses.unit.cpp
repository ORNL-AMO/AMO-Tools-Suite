#include "catch.hpp"
#include <calculator/losses/FixtureLosses.h>

TEST_CASE( "Calculate Heat Loss for Fixture Losses", "[Heat Loss][Fixture][Solid]") {
    CHECK(FixtureLosses(0.122, 1250.0, 300.0, 1800.0, 1.0).getHeatLoss() == Approx(228750.0));
}