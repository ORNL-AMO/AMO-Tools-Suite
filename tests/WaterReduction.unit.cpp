#include <catch.hpp>
#include "calculator/util/WaterReduction.h"

TEST_CASE("Water Reduction MeteredFlowData", "[WaterReduction][util]")
{
        std::vector<WaterReductionInput> waterReductionInputVec = {
            WaterReductionInput(8640, 0.005, 0,
                                MeteredFlowData(100),
                                VolumeMeterData(5942, 4235, 15),
                                BucketMethodData(10, 20),
                                WaterOtherMethodData(15000), 1)};
        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        CHECK(testOutput
                  .waterUse == Approx(51840));
        CHECK(testOutput
                  .waterUse == Approx(51840));
        CHECK(testOutput
                  .waterCost == Approx(259.2));
}

TEST_CASE("Water Reduction VolumeMeterData", "[WaterReduction][util]")
{
        std::vector<WaterReductionInput> waterReductionInputVec = {
            WaterReductionInput(8640, 0.005, 1,
                                MeteredFlowData(100),
                                VolumeMeterData(5942, 4235, 15),
                                BucketMethodData(10, 20),
                                WaterOtherMethodData(15000), 1)};
        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        CHECK(testOutput
                  .waterUse == Approx(58993));
        CHECK(testOutput
                  .waterUse == Approx(58993));
        CHECK(testOutput
                  .waterCost == Approx(294.965));
}

TEST_CASE("Water Reduction BucketMethodData", "[WaterReduction][util]")
{
        std::vector<WaterReductionInput> waterReductionInputVec = {
            WaterReductionInput(8640, 0.005, 2,
                                MeteredFlowData(100),
                                VolumeMeterData(5942, 4235, 15),
                                BucketMethodData(10, 20),
                                WaterOtherMethodData(15000), 1)};
        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        CHECK(testOutput
                  .waterUse == Approx(15552));
        CHECK(testOutput
                  .waterUse == Approx(15552));
        CHECK(testOutput
                  .waterCost == Approx(77.76));
}

TEST_CASE("Water Reduction WaterOtherMethodData", "[WaterReduction][util]")
{
        std::vector<WaterReductionInput> waterReductionInputVec = {
            WaterReductionInput(8640, 0.005, 3,
                                MeteredFlowData(100),
                                VolumeMeterData(5942, 4235, 15),
                                BucketMethodData(10, 20),
                                WaterOtherMethodData(15000), 1)};
        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        auto waterReduction = WaterReduction(waterReductionInputVec);
        auto testOutput = waterReduction.calculate();

        CHECK(testOutput
                  .waterUse == Approx(15000));
        CHECK(testOutput
                  .waterUse == Approx(15000));
        CHECK(testOutput
                  .waterCost == Approx(75));
}