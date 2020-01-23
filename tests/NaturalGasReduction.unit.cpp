#include <catch.hpp>
#include "calculator/util/NaturalGasReduction.h"

TEST_CASE("Natural Gas Reduction Flow Meter Method", "[NaturalGasReduction][Util]")
{

    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(8640, 0.12, 0,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(true,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(10000),
                                                 120,
                                                 200,
                                                 100),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   100),
                                 2)};

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(88992000.00));
    CHECK(testOutput.energyCost == Approx(10679040.00));
    CHECK(testOutput.heatFlow == Approx(0));
    CHECK(testOutput.totalFlow == Approx(10.0));
}

TEST_CASE("Natural Gas Reduction Air Mass Flow Nameplate", "[NaturalGasReduction][Util]")
{
    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(8640, 0.12, 1,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(true,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2)};

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(44.78976));
    CHECK(testOutput.energyCost == Approx(5.37477));
    CHECK(testOutput.heatFlow == Approx(0.002592));
    CHECK(testOutput.totalFlow == Approx(60));
}

TEST_CASE("Natural Gas Reduction Air Mass Flow Measured", "[NaturalGasReduction][Util]")
{
    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(8640, 0.12, 1,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2)};

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(14929.92));
    CHECK(testOutput.energyCost == Approx(1791.5904));
    CHECK(testOutput.heatFlow == Approx(0.864));
    CHECK(testOutput.totalFlow == Approx(20000));
}

TEST_CASE("Natural Gas Reduction Water Mass Flow", "[NaturalGasReduction][Util]")
{
    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(8640, 0.12, 2,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2)};

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(276480));
    CHECK(testOutput.energyCost == Approx(33177.6));
    CHECK(testOutput.heatFlow == Approx(16));
    CHECK(testOutput.totalFlow == Approx(800));
}

TEST_CASE("Natural Gas Reduction Other/Off Sheet", "[NaturalGasReduction][Util]")
{
    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(8640, 0.12, 3,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(2000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2)};

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(2000));
    CHECK(testOutput.energyCost == Approx(240));
    CHECK(testOutput.heatFlow == Approx(0));
    CHECK(testOutput.totalFlow == Approx(0));
}

TEST_CASE("Natural Gas Reduction All Methods", "[NaturalGasReduction][Util]")
{
    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        //flow meter method
        NaturalGasReductionInput(8640, 0.12, 0,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(true,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(10000),
                                                 120,
                                                 200,
                                                 100),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   100),
                                 2),
        //air mass flow nameplate
        NaturalGasReductionInput(8640, 0.12, 1,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(true,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2),
        //air mass flow measured
        NaturalGasReductionInput(8640, 0.12, 1,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2),
        //water mass flow method
        NaturalGasReductionInput(8640, 0.12, 2,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(200000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2),
        //other/offsheet method
        NaturalGasReductionInput(8640, 0.12, 3,
                                 FlowMeterMethodData(5),
                                 NaturalGasOtherMethodData(2000),
                                 AirMassFlowData(false,
                                                 AirMassFlowMeasuredData(50, 200),
                                                 AirMassFlowNameplateData(30),
                                                 120,
                                                 200,
                                                 1),
                                 WaterMassFlowData(400,
                                                   120,
                                                   200,
                                                   1),
                                 2),

    };

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(89285454.70976));
    CHECK(testOutput.energyCost == Approx(10714254.56517));
    CHECK(testOutput.heatFlow == Approx(16.866592));
    CHECK(testOutput.totalFlow == Approx(20870));
}