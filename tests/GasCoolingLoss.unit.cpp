#include "catch.hpp"
#include <calculator/GasCoolingLosses.h>

TEST_CASE( "Calculate Heat Loss for gas cooling Losses Air", "[Heat Loss][Air][Gas]") {
    CHECK(GasCoolingLosses(2500.0, 80.0, 280.0, 0.02).getHeatLoss() == Approx(600000.0));
}