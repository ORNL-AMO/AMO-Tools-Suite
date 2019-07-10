#include <catch.hpp>
#include "calculator/util/ElectricityReduction.h"


TEST_CASE("Electricity Reduction Multimeter Reading - 3 Phases", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(8640, 0.12, 0,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(407045.796185));
CHECK(testOutput
.energyCost == Approx(48845.495542));
CHECK(testOutput
.power == Approx(47.111781));
}

TEST_CASE("Electricity Reduction Multimeter Reading - 1 Phase", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(8640, 0.12, 0,
                                  MultimeterData(1, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(235008));
CHECK(testOutput
.energyCost == Approx(28200.96));
}

TEST_CASE("Electricity Reduction Nameplate Data", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(8640, 0.12, 1,
                                  MultimeterData(1, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(6950.9206));
CHECK(testOutput
.energyCost == Approx(834.11047));
}

TEST_CASE("Electricity Reduction Power Meter Method Test", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(8640, 0.12, 2,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 2)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(864000));
CHECK(testOutput
.energyCost == Approx(103680));
}

TEST_CASE("Electricity Reduction Other Method Test", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        ElectricityReductionInput(8640, 0.12, 3,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 2)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(432000));
CHECK(testOutput
.energyCost == Approx(51840));
}


TEST_CASE("Electricity Reduction Combination", "[ElectricityReduction][util]") {

std::vector<ElectricityReductionInput> electricityReductionInputVec = {
        // multimeter method - 3 phase
        ElectricityReductionInput(8640, 0.12, 0,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1),
        // multimeter method - 1 phase
        ElectricityReductionInput(8640, 0.12, 0,
                                  MultimeterData(1, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1),
        // nameplate data
        ElectricityReductionInput(8640, 0.12, 1,
                                  MultimeterData(1, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 1),
        // power meter method
        ElectricityReductionInput(8640, 0.12, 2,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 2),
        // other method
        ElectricityReductionInput(8640, 0.12, 3,
                                  MultimeterData(3, 800, 40, 0.85),
                                  NameplateData(100, 0, 55, 60, 100, 1), PowerMeterData(50),
                                  OtherMethodData(432000), 2)
};

auto electricityReduction = ElectricityReduction(electricityReductionInputVec);
auto testOutput = electricityReduction.calculate();

CHECK(testOutput
.energyUse == Approx(1945004.716785));
CHECK(testOutput
.energyCost == Approx(233400.566012));
}