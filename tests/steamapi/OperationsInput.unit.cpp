#include "catch.hpp"
#include "ssmt/api/OperationsInput.h"

TEST_CASE("operationsInputConstructor", "[operations input constructor]") {
    auto actual = OperationsInput(1,1,1,1,1,1);
    CHECK(actual.getElectricityCosts() == 1);
    CHECK(actual.getFuelCosts() == 1);
    CHECK(actual.getMakeUpWaterCosts() == 1);
    CHECK(actual.getMakeUpWaterTemperature() == 1);
    CHECK(actual.getOperatingHoursPerYear() == 1);
    CHECK(actual.getSitePowerImport() == 1);
}
