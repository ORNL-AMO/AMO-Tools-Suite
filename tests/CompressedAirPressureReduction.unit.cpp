#include <catch.hpp>
#include "calculator/util/CompressedAirPressureReduction.h"

TEST_CASE("Compressed Air Pressure Reduction Baseline", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 150, NULL, NULL, NULL)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == Approx(4320000.0));
    CHECK(testOutput.energyCost == Approx(21600.0));
}

TEST_CASE("Compressed Air Pressure Reduction Modification", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(false, 8760, 0.005, 200, 100, 90, 14.7, 100)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == Approx(1650714.710542));
    CHECK(testOutput.energyCost == Approx(8253.57355271));
}

TEST_CASE("Compressed Air Pressure Reduction Baseline List", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 150, NULL, NULL, NULL),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 250, 150, NULL, NULL, NULL),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 500, 120, 120, NULL, NULL),
        CompressedAirPressureReductionInput(true, 8640, 0.005, 450, 170, 100, NULL, NULL)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();
    CHECK(testOutput.energyUse == 14688000.0);
    CHECK(testOutput.energyCost == 73440.0);
}

TEST_CASE("Compressed Air Pressure Reduction Modification List", "[CompressedAirPressureReduction][Util]")
{
    std::vector<CompressedAirPressureReductionInput> compressedAirPressureReductionInputVec = {
        CompressedAirPressureReductionInput(false, 8760, 0.005, 200, 100, 90, 14.7, 100),
        CompressedAirPressureReductionInput(false, 8760, 0.005, 200, 100, 90, 14.7, 100)};

    auto compressedAirPressureReduction = CompressedAirPressureReduction(compressedAirPressureReductionInputVec);
    auto testOutput = compressedAirPressureReduction.calculate();

    CHECK(testOutput.energyUse == Approx(3301429.421084));
    CHECK(testOutput.energyCost == Approx(16507.14710542));
}