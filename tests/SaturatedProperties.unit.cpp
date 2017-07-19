#include "catch.hpp"
#include <ssmt/SaturatedProperties.h>

TEST_CASE( "Calculate the Saturated Temperature from Pressure", "[Saturated Temperature][ssmt][Calculator]") {
    CHECK( SaturatedTemperature(22).calculate() == Approx(262.0551525336));
}

TEST_CASE( "Calculate the Saturated Pressure from Temperature", "[Saturated Pressure][ssmt][Calculator]") {
    CHECK( SaturatedPressure(500).calculate() == Approx(665.8313710097));
}

TEST_CASE( "Calculate the Saturated Gas Specific Enthalpy", "[Gas Enthalpy][ssmt][Calculator]") {
    CHECK( SaturatedProperties(500, 470).getGasEnthalpy() == Approx(1204.9));
}