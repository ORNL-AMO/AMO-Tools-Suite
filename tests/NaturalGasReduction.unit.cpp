#include <catch.hpp>
#include "calculator/util/NaturalGasReduction.h"

TEST_CASE("Natural Gas Reduction Flow Meter Method", "[NaturalGasReduction][Util]")
{

    std::vector<NaturalGasReductionInput> naturalGasReductionInputVec = {
        NaturalGasReductionInput(24, 30, 12, 0.12, 0,
                                 FlowMeterMethodData(200),
                                 OtherMethodData(200000),
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
                                 1)
    };

    auto naturalGasReduction = NaturalGasReduction(naturalGasReductionInputVec);
    auto testOutput = naturalGasReduction.calculate();

    CHECK(testOutput.energyUse == Approx(0));
    CHECK(testOutput.energyCost == Approx(0));
    CHECK(testOutput.totalFlow == Approx(0));
}