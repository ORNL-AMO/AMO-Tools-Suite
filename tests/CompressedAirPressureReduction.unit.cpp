#include <catch.hpp>
#include "calculator/util/CompressedAirPressureReduction.h"

TEST_CASE("Compressed Air Pressure Reduction Baseline", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 150, NULL)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == Approx(4320000.0));
    CHECK(testOutput.energyCost == Approx(21600.0));
}

TEST_CASE("Compressed Air Pressure Reduction Modification", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(false, 8640, 0.005, 500, 150, 100)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == Approx(3240000.0));
    CHECK(testOutput.energyCost == Approx(16200.0));
}

TEST_CASE("Compressed Air Pressure Reduction Baseline List", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 150, NULL),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 250, 150, NULL),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 120, 120),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 450, 170, 100)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == 14688000.0);
    CHECK(testOutput.energyCost == 73440.0);
}

TEST_CASE("Compressed Air Pressure Reduction Modification List", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(false, 8640, 0.005, 500, 150, 50),
        CompressedAirPressureReductionInput(false, 8640, 0.005, 250, 150, 89)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();

    CHECK(testOutput.energyUse == Approx(3661200.0));
    CHECK(testOutput.energyCost == Approx(18306.0));
}