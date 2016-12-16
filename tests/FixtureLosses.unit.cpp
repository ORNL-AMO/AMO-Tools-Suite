#include "catch.hpp"
#include <calculator/FixtureLosses.h>

TEST_CASE( "Calculate Total Heat for Fixture Losses", "[Total Heat][Fixture][Solid]") {
    CHECK( FixtureLosses(0.122, 1250.0, 300.0, 1800.0, 1.0).getTotalHeat() == Approx(228750.0));
}