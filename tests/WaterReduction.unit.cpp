#include <iostream>
#include <catch.hpp>
#include "calculator/util/WaterReduction.h"

TEST_CASE("Water Reduction Metered Flow Data", "[WaterReduction][util]")
{
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput(8640, 0.005, 0,
                            MeteredFlowMethodData(100),
                            VolumeMeterMethodData(5942, 4235, 15),
                            BucketMethodData(10, 20),
                            WaterOtherMethodData(15000), 1)};

    auto waterReduction = WaterReduction(waterReductionInputVec);
    auto testOutput = waterReduction.calculate();

    CHECK(testOutput.waterUse == Approx(51840000.0));
    CHECK(testOutput.waterCost == Approx(259200.0));
}

TEST_CASE("Water Reduction VolumeMeterData", "[WaterReduction][util]")
{
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput(8640, 0.005, 1,
                            MeteredFlowMethodData(100),
                            VolumeMeterMethodData(5942, 4235, 15),
                            BucketMethodData(10, 20),
                            WaterOtherMethodData(15000), 1)};

    auto waterReduction = WaterReduction(waterReductionInputVec);
    auto testOutput = waterReduction.calculate();

    CHECK(testOutput.waterUse == Approx(58993920.0));
    CHECK(testOutput.waterCost == Approx(294969.6));
}

TEST_CASE("Water Reduction BucketMethodData", "[WaterReduction][util]")
{
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput(8640, 0.005, 2,
                            MeteredFlowMethodData(100),
                            VolumeMeterMethodData(5942, 4235, 15),
                            BucketMethodData(10, 20),
                            WaterOtherMethodData(15000), 1)
    };

    auto waterReduction = WaterReduction(waterReductionInputVec);
    auto testOutput = waterReduction.calculate();

    CHECK(testOutput.waterUse == Approx(15552000.0));
    CHECK(testOutput.waterCost == Approx(77760.0));
}

TEST_CASE("Water Reduction WaterOtherMethodData", "[WaterReduction][util]")
{
    std::vector<WaterReductionInput> waterReductionInputVec = {
        WaterReductionInput(8640, 0.005, 3,
                            MeteredFlowMethodData(100),
                            VolumeMeterMethodData(5942, 4235, 15),
                            BucketMethodData(10, 20),
                            WaterOtherMethodData(15000), 1)};

    auto waterReduction = WaterReduction(waterReductionInputVec);
    auto testOutput = waterReduction.calculate();

    CHECK(testOutput.waterUse == Approx(15000.0));
    CHECK(testOutput.waterCost == Approx(75.0));
}