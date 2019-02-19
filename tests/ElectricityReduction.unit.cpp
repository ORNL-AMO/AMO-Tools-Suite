#include <catch.hpp>
#include "calculator/util/ElectricityReduction.h"

TEST_CASE("Electricity Reduction Power Meter Method Test", "[ElectricityReduction][util]") {
    
    std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(24, 30, 12, 0.12, 2, 
            MultimeterData(3, 800, 40, 0.85), 
            NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50), 
            OtherMethodData(432000), 2)
    };

    auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
    auto testOutput = electricityReduction.calculate();

    // auto controlOutput = ElectricityReduction::Output(1728000,207360, 0, 0);
    // auto testOutput = electricityReduction.getOutput();
    CHECK(testOutput.energyUse == Approx(1728000));
    // CHECK(testOutput.energyUse == Approx(controlOutput.energyUse));
    CHECK(testOutput.energyCost == Approx(207360));
}