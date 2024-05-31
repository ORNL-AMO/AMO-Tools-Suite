#include "catch.hpp"
#include "ssmt/api/BoilerInput.h"

TEST_CASE("boilerInputConstructor", "[boiler input constructor]") {
    auto actual = BoilerInput(1, 1, 1, 1, true, true, 1, 1, 1, 1);
    CHECK(actual.getFuelType() == 1);
    CHECK(actual.getFuel() == 1);
    CHECK(actual.getCombustionEfficiency() == 1);
    CHECK(actual.getBlowdownRate() == 1);
    CHECK(actual.isBlowdownFlashed());
    CHECK(actual.isPreheatMakeupWater());
    CHECK(actual.getSteamTemperature() == 1);
    CHECK(actual.getDeaeratorVentRate() == 1);
    CHECK(actual.getDeaeratorPressure() == 1);
    CHECK(actual.getApproachTemperature() == 1);
}
