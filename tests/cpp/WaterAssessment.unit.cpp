#include "catch.hpp"
#include "calculator/losses/WaterAssessment.h"

TEST_CASE("Calculate ProcessWaterUse", "[ProcessWaterUse]") {
    auto output = WaterAssessment().calculateProcessWaterUse(1000, 700, 50, 0.2);
    CHECK(output.recirculatedWater == Approx(200));
    CHECK(output.incomingWater == Approx(800));
    CHECK(output.wasteDischargedAndRecycledOther == Approx(50));
}

TEST_CASE("Calculate CoolingTowerLoss", "[CoolingTowerLoss]") {
    auto output = WaterAssessment().calculateCoolingTowerLoss(2000, 5, 0.2, 0.2, 10, 5, 15);
    CHECK(output.grossWaterUse == Approx(360000));
    CHECK(output.evaporationLoss == Approx(72000));
    CHECK(output.cycleOfConcentration == Approx(3));
    CHECK(output.makeupWater == Approx(108000));
    CHECK(output.blowdownLoss == Approx(36000));
}

TEST_CASE("Calculate BoilerWaterLosses", "[BoilerWaterLosses]") {
    auto output = WaterAssessment().calculateBoilerWaterLosses(2000, 5, 0.2, 0.2, 2.5, 5, 15);
    CHECK(output.cycleOfConcentration == Approx(6));
    CHECK(output.grossWaterUse == Approx(57.6));
    CHECK(output.makeupWater == Approx(28.8));
    CHECK(output.steamLoss == Approx(19.2));
    CHECK(output.blowdownLoss == Approx(9.6));
    CHECK(output.condensateReturn == Approx(28.8));
    CHECK(output.rateOfRecirculation == Approx(0.5));
}

TEST_CASE("Calculate KitchenRestroomGrossWaterUse", "[KitchenRestroomGrossWaterUse]") {
    CHECK(WaterAssessment().calculateKitchenRestroomGrossWaterUse(50, 260, 3) == Approx(39000));
}

TEST_CASE("Calculate LandscapingGrossWaterUse", "[LandscapingGrossWaterUse]") {
    CHECK(WaterAssessment().calculateLandscapingGrossWaterUse(50, 60) == Approx(3000));
}

TEST_CASE("Calculate HeatEnergyInDischarge", "[HeatEnergyInDischarge]") {
    CHECK(WaterAssessment().calculateHeatEnergyInDischarge(50, 60, 0.8, 200) == Approx(0.01335));
}

TEST_CASE("Calculate AddedMotorEnergyUse", "[AddedMotorEnergyUse]") {
    CHECK(WaterAssessment().calculateAddedMotorEnergyUse(50, 2000, 100, 0.8, 0.75) == Approx(10666666.66666));
}
