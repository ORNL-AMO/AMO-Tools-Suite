#include "catch.hpp"
#include <calculator/losses/ExhaustGasEAF.h>

TEST_CASE( "Calculate the Total Heat Exhaust", "[Total Heat Exhaust][ExhaustGasEAF][EAF]") {
//    CHECK( ExhaustGasEAF(2800, 10, 10, 0, 5, 5, 50000, .005).getTotalHeatExhaust() == Approx(171958895.705521));

    CHECK( ExhaustGasEAF(2800, 12, 10, 3, 8000, 0.001).getTotalHeatExhaust() == Approx(12553119.02));
    CHECK( ExhaustGasEAF(2800, 8, 6, 3, 6500, 0.001).getTotalHeatExhaust() == Approx(8591939.26));
}
