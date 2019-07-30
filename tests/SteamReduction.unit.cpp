#include <catch.hpp>
#include "calculator/util/SteamReduction.h"

TEST_CASE("Steam Reduction Flow Meter Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8760, 1, 5.5, 0, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamOtherMethodData(400000.0),
                            1)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(438000000.0));
    CHECK(testOutput.energyUse == Approx(385822.0922));
    CHECK(testOutput.energyCost == Approx(2122021.5071));
}

TEST_CASE("Steam Reduction Air Mass Flow - Measured", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8760, 1, 5.5, 1, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamOtherMethodData(400000.0),
                            1)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(698117.037));
    CHECK(testOutput.energyUse == Approx(614.950));
    CHECK(testOutput.energyCost == Approx(3382.225));
}

TEST_CASE("Steam Reduction Air Mass Flow - Nameplate", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8760, 1, 5.5, 1, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamOtherMethodData(400000.0),
                            1)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(558493.63));
    CHECK(testOutput.energyUse == Approx(491.96));
    CHECK(testOutput.energyCost == Approx(2705.78));
}

TEST_CASE("Steam Reduction Water Mass Flow - Nameplate", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8760, 1, 5.5, 2, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(8.0),
                                70.0, 100.0),
                            SteamOtherMethodData(400000.0),
                            1)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(1193362.457));
    CHECK(testOutput.energyUse == Approx(1051.2));
    CHECK(testOutput.energyCost == Approx(5781.6));
}

TEST_CASE("Steam Reduction Other Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8760, 0, 1.5, 3, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(8.0),
                                70.0, 100.0),
                            SteamOtherMethodData(400000.0),
                            1)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(454095303.357));
    CHECK(testOutput.energyUse == Approx(400000.0));
    CHECK(testOutput.energyCost == Approx(681.143));
}

TEST_CASE("Steam Reduction Multi Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        //flow meter method
        SteamReductionInput(8760, 1, 5.5, 0, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(40000.0),
                                75.0, 500.0),
                            SteamOtherMethodData(400000.0),
                            1),
        //water mass
        SteamReductionInput(8760, 1, 5.5, 2, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(8.0),
                                70.0, 100.0),
                            SteamOtherMethodData(400000.0),
                            1),
        //other method
        SteamReductionInput(8760, 0, 1.5, 3, 1.0, 0.790800732,
                            SteamFlowMeterMethodData(50000.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(50.0, 1000.0),
                                SteamMassFlowNameplateData(8.0),
                                70.0, 100.0),
                            SteamOtherMethodData(400000.0),
                            1)

    };

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(893288665.814));
    CHECK(testOutput.energyUse == Approx(786873.2922));
    CHECK(testOutput.energyCost == Approx(2128484.2501));
}