#include "catch.hpp"
#include <calculator/Atmosphere.h>

TEST_CASE( "Calculate Total Heat for Atmospheric Gas", "[Total Heat][Atmosphere][Gas]") {
    CHECK( Atmosphere(100.0, 1400.0, 1200.0, 1.0, 0.02).getTotalHeat() == Approx(0.0));
}
