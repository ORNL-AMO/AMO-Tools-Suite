#include <catch.hpp>
#include "calculator/util/CompressedAirReduction.h"

TEST_CASE("Compressed Air Reduction Flow Meter Method", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 0, 0.12, 0,
                                    CompressedAirFlowMeterMethodData(200),
                                    BagMethodData(10, 5, 30),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(1.428, 1.38233),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.consumption == Approx(103680000));
    CHECK(testOutput.flowRate == Approx(200.0));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.energyUse == Approx(0.0));
    CHECK(testOutput.energyCost == Approx(12441600.0));
}

TEST_CASE("Compressed Air Reduction Flow Meter Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 0,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(10, 5, 30),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.8, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(221184000.0));
    CHECK(testOutput.energyCost == Approx(26542080.0));
    CHECK(testOutput.flowRate == Approx(200000.0));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.consumption == Approx(103680000000.0));
}

TEST_CASE("Compressed Air Reduction Bag Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 1,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.40, 0.16),
                                    2)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(3769.9111));
    CHECK(testOutput.energyCost == Approx(452.3893));
    CHECK(testOutput.flowRate == Approx(3.408846));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.consumption == Approx(3534291.73528));
}

TEST_CASE("Compressed Air Reduction Pressure Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 2,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(983.443));
    CHECK(testOutput.energyCost == Approx(118.013254));
    CHECK(testOutput.flowRate == Approx(1.778508));
    CHECK(testOutput.singleNozzleFlowRate == Approx(1.778508));
    CHECK(testOutput.consumption == Approx(921978.5471999));
}

TEST_CASE("Compressed Air Reduction Pressure Method Multiple Nozzles", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 2,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(2, 4, 50),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.40, 0.16),
                                    3)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.flowRate == Approx(363.9248));
    CHECK(testOutput.singleNozzleFlowRate == Approx(90.9812));
    CHECK(testOutput.consumption == Approx(188658616.32));
    CHECK(testOutput.energyUse == Approx(201235.857408));
    CHECK(testOutput.energyCost == Approx(24148.3028896));
}

TEST_CASE("Compressed Air Reduction Other Method", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 3,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(2, 4, 50),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.consumption == Approx(200000.00));
    CHECK(testOutput.energyUse == Approx(213.3333));
    CHECK(testOutput.energyCost == Approx(25.6));
}

TEST_CASE("Compressed Air Reduction Orifice Method and Electricity", "[CompressedAirReduction][Util]")
{
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec = {
        CompressedAirReductionInput(8640, 1, 0.12, 4,
                                    CompressedAirFlowMeterMethodData(200000),
                                    BagMethodData(15, 10, 12),
                                    PressureMethodData(0, 1, 80),
                                    CompressedAirOtherMethodData(200000),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    EstimateMethodData(0.1),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirReduction = CompressedAirReduction(compressedAirReductionInputVec);
    auto testOutput = compressedAirReduction.calculate();
    CHECK(testOutput.energyUse == Approx(1253583.3379004421));
    CHECK(testOutput.energyCost == Approx(150430.000548053));
    CHECK(testOutput.flowRate == Approx(2267.0416267007));
    CHECK(testOutput.singleNozzleFlowRate == Approx(0.0));
    CHECK(testOutput.consumption == Approx(1175234379));
}