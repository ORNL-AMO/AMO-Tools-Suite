#include <catch.hpp>
#include "calculator/util/CompressedAirLeakSurvey.h"

TEST_CASE("Compressed Air Leak Survey Estimate Method and Electricity", "[CompressedAirLeakSurvey][Util]")
{
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(8640, 1, 0.12, 0,
                                    EstimateMethodData(0.1),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(55.296));
    CHECK(testOutput.energyCost == Approx(6.63552));
    CHECK(testOutput.flowRate == Approx(0.1));
    CHECK(testOutput.compressedAirUse == Approx(51840));

    compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(3840, 1, 0.12, 0,
                                    EstimateMethodData(0.1),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.25, 0.16),
                                    1)};

    compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(15.36));
    CHECK(testOutput.energyCost == Approx(1.8432));
    CHECK(testOutput.flowRate == Approx(0.1));
    CHECK(testOutput.compressedAirUse == Approx(23040));

    compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(8760, 1, 0.12, 0,
                                    EstimateMethodData(100),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.25, 0.16),
                                    1)};

    compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(35040));
    CHECK(testOutput.energyCost == Approx(4204.8));
    CHECK(testOutput.flowRate == Approx(100));
    CHECK(testOutput.compressedAirUse == Approx(52560000));
}

TEST_CASE("Compressed Air Leak Survey Decibels Method and Electricity", "[CompressedAirLeakSurvey][Util]")
{
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(8640, 1, 0.12, 1,
                                    EstimateMethodData(0.1),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(790.17984));
    CHECK(testOutput.energyCost == Approx(94.8215808));
    CHECK(testOutput.flowRate == Approx(1.429));
    CHECK(testOutput.compressedAirUse == Approx(740793.6));
}

TEST_CASE("Compressed Air Leak Survey Bag Method and Electricity", "[CompressedAirLeakSurvey][Util]")
{
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(8640, 1, 0.12, 2,
                                    EstimateMethodData(0.1),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.40, 0.16),
                                    2)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(3769.9111));
    CHECK(testOutput.energyCost == Approx(452.3893));
    CHECK(testOutput.flowRate == Approx(6.8176923906));
    CHECK(testOutput.compressedAirUse == Approx(3534291.73528));
}

TEST_CASE("Compressed Air Leak Survey Orifice Method and Electricity", "[CompressedAirLeakSurvey][Util]")
{
    std::vector<CompressedAirLeakSurveyInput> compressedAirLeakSurveyInputVec = {
        CompressedAirLeakSurveyInput(8640, 1, 0.12, 3,
                                    EstimateMethodData(0.1),
                                    DecibelsMethodData(130, 25, 20, 150, 1.04, 1.2, 30, 125, 1.85, 1.65),
                                    BagMethodData(15, 10, 12),
                                    OrificeMethodData(250.0, 14.7, 1.0, 6.0, 6.2, 4),
                                    CompressorElectricityData(0.40, 0.16),
                                    1)};

    auto compressedAirLeakSurvey = CompressedAirLeakSurvey(compressedAirLeakSurveyInputVec);
    auto testOutput = compressedAirLeakSurvey.calculate();
    CHECK(testOutput.energyUse == Approx(1253583.3379004421));
    CHECK(testOutput.energyCost == Approx(150430.000548053));
    CHECK(testOutput.flowRate == Approx(2267.0416267007));
    CHECK(testOutput.compressedAirUse == Approx(1175234379));
}