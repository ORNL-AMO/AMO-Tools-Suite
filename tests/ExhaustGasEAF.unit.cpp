#include "catch.hpp"
#include <calculator/losses/ExhaustGasEAF.h>

TEST_CASE( "Calculate the Total Heat Exhaust", "[Total Heat Exhaust][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2800, 10, 10, 0, 5, 5, 50000, .005).getTotalHeatExhaust() == Approx(171958895.705521));
}
