#include <catch.hpp>
#include "calculator/util/SteamReduction.h"

TEST_CASE("Steam Reduction Flow Meter Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8000, 1, 5.5, 0, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamOffsheetMethodData(13000000),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(10000000.0));
    CHECK(testOutput.energyUse == Approx(38671503020.03));
    CHECK(testOutput.energyCost == Approx(212693266610.1651));
}

TEST_CASE("Steam Reduction Air Mass Flow - Measured", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8000, 1, 5.5, 1, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(1.0, 100.0),
                                SteamMassFlowNameplateData(4000.0),
                                25.0, 425.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamOffsheetMethodData(13000000),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(9982.3376));
    CHECK(testOutput.energyUse == Approx(38603200.0));
    CHECK(testOutput.energyCost == Approx(212317600.0));
}

TEST_CASE("Steam Reduction Air Mass Flow - Nameplate", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8000, 1, 5.5, 1, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1.0, 100.0),
                                SteamMassFlowNameplateData(4000.0),
                                25.0, 425.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamOffsheetMethodData(13000000),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(399293.5054));
    CHECK(testOutput.energyUse == Approx(1544127999.9999));
    CHECK(testOutput.energyCost == Approx(8492703999.9999));
}

TEST_CASE("Steam Reduction Water Mass Flow - Nameplate", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8000, 1, 5.5, 2, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(1),
                                25.0, 225.0),
                            SteamOffsheetMethodData(13000000),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(173112830.1340));
    CHECK(testOutput.energyUse == Approx(669453333333.3332));
    CHECK(testOutput.energyCost == Approx(3681993333333.3330));
}

TEST_CASE("Steam Reduction Offsheet Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        SteamReductionInput(8000, 0, 5.5, 3, 0.8, 3.5,
                            SteamFlowMeterMethodData(5000),
                            SteamMassFlowMethodData(
                                    false,
                                    SteamMassFlowMeasuredData(1, 100),
                                    SteamMassFlowNameplateData(40000.0),
                                    25, 425),
                            SteamMassFlowMethodData(
                                    true,
                                    SteamMassFlowMeasuredData(1, 100),
                                    SteamMassFlowNameplateData(40000.0),
                                    25, 425),
                            SteamOffsheetMethodData(13000000),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)};

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx(3361.6485));
    CHECK(testOutput.energyUse == Approx(13000000.0));
    CHECK(testOutput.energyCost == Approx(18489.0667));
}

TEST_CASE("Steam Reduction Multi Method", "[SteamReduction][Util]")
{
    std::vector<SteamReductionInput> steamReductionInputVec = {
        //flow meter method
        SteamReductionInput(8000, 1, 5.5, 0, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                false,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(40000.0),
                                25, 425),
                            SteamOffsheetMethodData(13000000 ),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15),
        //water mass
        SteamReductionInput(8000, 1, 5.5, 2, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(100.0, 5.0),
                                SteamMassFlowNameplateData(400.0),
                                70.0, 200.0),
                            SteamMassFlowMethodData(
                                true,
                                SteamMassFlowMeasuredData(1, 100),
                                SteamMassFlowNameplateData(1),
                                25.0, 225.0),
                            SteamOffsheetMethodData(13000000 ),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15),
        //Offsheet method
        SteamReductionInput(8000, 0, 5.5, 3, 0.8, 3.5,
                            SteamFlowMeterMethodData(1000),
                            SteamMassFlowMethodData(
                                    false,
                                    SteamMassFlowMeasuredData(1, 100),
                                    SteamMassFlowNameplateData(40000.0),
                                    25, 425),
                            SteamMassFlowMethodData(
                                    true,
                                    SteamMassFlowMeasuredData(1, 100),
                                    SteamMassFlowNameplateData(40000.0),
                                    25, 425),
                            SteamOffsheetMethodData(13000000 ),
                            1, 0.75, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 560, 283.15)

    };

    auto steamReduction = SteamReduction(steamReductionInputVec);
    auto testOutput = steamReduction.calculate();
    CHECK(testOutput.steamUse == Approx( 183116191.7825));
    CHECK(testOutput.energyUse == Approx(708137836353.3633));
    CHECK(testOutput.energyCost == Approx(3894686618432.565));
}
