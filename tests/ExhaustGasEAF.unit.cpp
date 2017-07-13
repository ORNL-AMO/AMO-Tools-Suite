#include "catch.hpp"
#include <calculator/losses/ExhaustGasEAF.h>

TEST_CASE( "Calculate the CO Heating Value", "[CO Heating Value][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getCOHeatingValue() == Approx(32.1));
}

TEST_CASE( "Calculate the H2 Heating Value", "[H2 Heating Value][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getH2HeatingValue() == Approx(32.5));
}

TEST_CASE( "Calculate the Combustibles", "[Combustibles][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getCombustibles() == Approx(50));
}

TEST_CASE( "Calculate the Chemical Heat", "[Chemical Heat][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getChemicalHeat() == Approx(114.6));
}

TEST_CASE( "Calculate the Total VFR", "[Total VFR][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getTotalVfr() == Approx(7975.46));
}

TEST_CASE( "Calculate the Sensible Heat", "[Sensible Heat][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getSensibleHeat() == Approx(61.65));
}

TEST_CASE( "Calculate the Heat in Dust", "[Heat in Dust][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getHeatInDust() == Approx(3.425));
}

TEST_CASE( "Calculate the Total Heat Flue", "[Total Heat Flue][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getTotalHeatFlue() == Approx(179.675));
}

TEST_CASE( "Calculate the Total Heat Exhaust", "[Total Heat Exhaust][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getTotalHeatExhaust() == Approx(171958895.705521));
}

TEST_CASE( "Calculate the Total Kwh Per Cycle", "[Total Kwh Per Hour][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getTotalKwhPerCycle() == Approx(50398.3));
}

TEST_CASE( "Calculate the Chemical Heat Percent", "[Chemical Heat Percent][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getChemicalHeatPercent() == Approx(63.7818283010992));
}

TEST_CASE( "Calculate the Sensible Heat Percent", "[Sensible Heat Percent][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getSensibleHeatPercent() == Approx(34.3119521358007));
}

TEST_CASE( "Calculate the Other Heat Percent", "[Other Heat Percent][ExhaustGasEAF][EAF]") {
    CHECK( ExhaustGasEAF(2, 2800, 10, 10, 0, 5, 5, 50000, .005, 0).getOtherHeatPercent() == Approx(1.90621956310005));
}
