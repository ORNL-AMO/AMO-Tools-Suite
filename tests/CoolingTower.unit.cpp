#include <catch.hpp>
#include "chillers/CoolingTower.h"
#include <tuple>

TEST_CASE("Cooling Tower Makeup Water Calculator", "[CoolingTower][Chillers]")
{
    auto const test = [](const std::tuple<double, double, int, double, int, double, int, double> &input,
                         const std::tuple<double, double, double> &ExpectedOutput)
    {
        double flowRate = std::get<0>(input);
        double coolingLoad = std::get<1>(input);
        int operationalHours = std::get<2>(input);
        double lossCorrectionFactor = std::get<3>(input);

        int baselineCyclesOfConcentration = std::get<4>(input);
        double baselineDriftLossFactor = std::get<5>(input);

        int modificationCyclesOfConcentration = std::get<6>(input);
        double modificationDriftLossFactor = std::get<7>(input);

        CoolingTowerOperatingConditionsData operatingConditionsData(flowRate, coolingLoad, operationalHours, lossCorrectionFactor);
        CoolingTowerWaterConservationData waterConservationBaselineData(baselineCyclesOfConcentration, baselineDriftLossFactor);
        CoolingTowerWaterConservationData waterConservationModificationData(modificationCyclesOfConcentration, modificationDriftLossFactor);

        CoolingTowerMakeupWaterCalculator coolingTowerMakeupWaterCalculator(operatingConditionsData, waterConservationBaselineData, waterConservationModificationData);
        CoolingTowerMakeupWaterCalculator::Output results = coolingTowerMakeupWaterCalculator.calculate();

        CHECK(results.wcBaseline == std::get<0>(ExpectedOutput));
        CHECK(results.wcModification == std::get<1>(ExpectedOutput));
        CHECK(results.waterSavings == std::get<2>(ExpectedOutput));
    };

    //Test 1

    double flowRate = 2500;
    double coolingLoad = 10.00;
    int operationalHours = 1000;
    double lossCorrectionFactor = 1.00;

    int baselineCyclesOfConcentration = 3;
    double baselineDriftLossFactor = 0.002;

    int modificationCyclesOfConcentration = 3;
    double modificationDriftLossFactor = 0.0001;

    std::tuple<double, double, int, double, int, double, int, double> input1;
    input1 = std::make_tuple(flowRate, coolingLoad, operationalHours, lossCorrectionFactor, baselineCyclesOfConcentration,
                             baselineDriftLossFactor, modificationCyclesOfConcentration, modificationDriftLossFactor);

    std::tuple<double, double, double> expectedOutput1;
    expectedOutput1 = std::make_tuple(2100000.0, 1815000.0, 285000.0);

    test(input1, expectedOutput1);

    //Test 2

    flowRate = 2500;
    coolingLoad = 5.00;
    operationalHours = 2000;
    lossCorrectionFactor = 1.00;

    baselineCyclesOfConcentration = 3;
    baselineDriftLossFactor = 0.002;

    modificationCyclesOfConcentration = 3;
    modificationDriftLossFactor = 0.0001;

    std::tuple<double, double, int, double, int, double, int, double> input2;
    input2 = std::make_tuple(flowRate, coolingLoad, operationalHours, lossCorrectionFactor, baselineCyclesOfConcentration,
                             baselineDriftLossFactor, modificationCyclesOfConcentration, modificationDriftLossFactor);

    std::tuple<double, double, double> expectedOutput2;
    expectedOutput2 = std::make_tuple(2400000.0, 1830000.0, 570000.0);

    test(input2, expectedOutput2);

    //Test 3

    flowRate = 2500;
    coolingLoad = 2.00;
    operationalHours = 3000;
    lossCorrectionFactor = 1.00;

    baselineCyclesOfConcentration = 3;
    baselineDriftLossFactor = 0.002;

    modificationCyclesOfConcentration = 3;
    modificationDriftLossFactor = 0.0001;

    std::tuple<double, double, int, double, int, double, int, double> input3;
    input3 = std::make_tuple(flowRate, coolingLoad, operationalHours, lossCorrectionFactor, baselineCyclesOfConcentration,
                             baselineDriftLossFactor, modificationCyclesOfConcentration, modificationDriftLossFactor);
                             
    std::tuple<double, double, double> expectedOutput3;
    expectedOutput3 = std::make_tuple(1980000.0, 1125000.0, 855000.0);

    test(input3, expectedOutput3);
}


TEST_CASE("Cooling Tower Basin Heater Energy Consumption Calculator", "[CoolingTower][Chillers]")
{
    auto res = CoolingTower::BasinHeaterEnergyConsumption(1201.67, 40, -10, 45, 28, 9.21, 1, 40, 39);
    CHECK(res.baselinePower == Approx(3.0743));
    CHECK(res.baselineEnergy == Approx(3.0743));
    CHECK(res.modPower == Approx(2.761));
    CHECK(res.modEnergy == Approx(2.761));
    CHECK(res.savingsEnergy == Approx(0.31327));
}

TEST_CASE("Cooling Tower Fan Energy Consumption Calculator", "[CoolingTower][Chillers]")
{
    auto res = CoolingTower::FanEnergyConsumption(59.5119, 81.6495, 87.98386, 76, 1,
                                             CoolingTower::FanControlSpeedType::One, CoolingTower::FanControlSpeedType::Two);
    CHECK(res.baselinePower == Approx(55.15));
    CHECK(res.baselineEnergy == Approx(41.142));
    CHECK(res.modPower == Approx(50.503));
    CHECK(res.modEnergy == Approx(37.675));
    CHECK(res.savingsEnergy == Approx(3.4665));

    res = CoolingTower::FanEnergyConsumption(59.5119, 81.6495, 87.98386, 76, 1,
                                             CoolingTower::FanControlSpeedType::One, CoolingTower::FanControlSpeedType::Variable);
    CHECK(res.baselinePower == Approx(55.15));
    CHECK(res.baselineEnergy == Approx(41.142));
    CHECK(res.modPower == Approx(44.79));
    CHECK(res.modEnergy == Approx(33.413));
    CHECK(res.savingsEnergy == Approx(7.7288));
}

TEST_CASE("Chiller Efficiency Capacity Power Energy Consumption Calculator", "[CoolingTower][Chillers]")
{
    auto res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Centrifugal, ChillerEfficiency::Water, ChillerEfficiency::NoVFD,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.5522));
    CHECK(res.baselineActualCapacity == Approx(995.5464));
    CHECK(res.modActualEfficiency == Approx(0.526177));
    CHECK(res.modActualCapacity == Approx(1033.1179));
    CHECK(res.baselinePower == Approx(549.74));
    CHECK(res.baselineEnergy == Approx(549.74));
    CHECK(res.modPower == Approx(543.6029));
    CHECK(res.modEnergy == Approx(543.6029));
    CHECK(res.savingsEnergy == Approx(6.13717));

    res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Centrifugal, ChillerEfficiency::Water, ChillerEfficiency::VFD,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.50594));
    CHECK(res.baselineActualCapacity == Approx(1017.8465));
    CHECK(res.baselinePower == Approx(514.97077));
    CHECK(res.baselineEnergy == Approx(514.97077));
    CHECK(res.modActualEfficiency == Approx(0.477184));
    CHECK(res.modActualCapacity == Approx(1038.26662));
    CHECK(res.modPower == Approx(495.444));
    CHECK(res.modEnergy == Approx(495.444));
    CHECK(res.savingsEnergy == Approx(19.5266));

    res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Centrifugal, ChillerEfficiency::Water, ChillerEfficiency::MagneticBearing,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.5335));
    CHECK(res.baselineActualCapacity == Approx(985.4549));
    CHECK(res.baselinePower == Approx(525.74132));
    CHECK(res.baselineEnergy == Approx(525.74132));
    CHECK(res.modActualEfficiency == Approx(0.486282));
    CHECK(res.modActualCapacity == Approx(1047.968));
    CHECK(res.modPower == Approx(509.608));
    CHECK(res.modEnergy == Approx(509.608));
    CHECK(res.savingsEnergy == Approx(16.13328));

    res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Screw, ChillerEfficiency::Water, ChillerEfficiency::NoVFD,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.5899));
    CHECK(res.baselineActualCapacity == Approx(963.087556));
    CHECK(res.baselinePower == Approx(568.13317));
    CHECK(res.baselineEnergy == Approx(568.13317));
    CHECK(res.modActualEfficiency == Approx(0.56246));
    CHECK(res.modActualCapacity == Approx(1000.57839));
    CHECK(res.modPower == Approx(562.7885));
    CHECK(res.modEnergy == Approx(562.7885));
    CHECK(res.savingsEnergy == Approx(5.34465));

    res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Screw, ChillerEfficiency::Air, ChillerEfficiency::NoVFD,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.47777));
    CHECK(res.baselineActualCapacity == Approx(1050.0458));
    CHECK(res.baselinePower == Approx(501.67899));
    CHECK(res.baselineEnergy == Approx(501.67899));
    CHECK(res.modActualEfficiency == Approx(0.4604));
    CHECK(res.modActualCapacity == Approx(1081.77855));
    CHECK(res.modPower == Approx(498.0641));
    CHECK(res.modEnergy == Approx(498.0641));
    CHECK(res.savingsEnergy == Approx(3.61489));

    res = ChillerEfficiency::ChillerCapacityEfficiency(
            ChillerEfficiency::Centrifugal, ChillerEfficiency::Air, ChillerEfficiency::NoVFD,
            1000, 0.676, 1.00, 1.00, 2000.00, 10,
            42, 82.12, 43, 82.12);
    CHECK(res.baselineActualEfficiency == Approx(0.442926));
    CHECK(res.baselineActualCapacity == Approx(1130.92));
    CHECK(res.baselinePower == Approx(500.91377));
    CHECK(res.modActualEfficiency == Approx(0.4285));
    CHECK(res.modActualCapacity == Approx(1168.492));
    CHECK(res.baselineEnergy == Approx(500.91377));
    CHECK(res.modPower == Approx(500.7157));
    CHECK(res.modEnergy == Approx(500.7157));
    CHECK(res.savingsEnergy == Approx(0.19807));
}

TEST_CASE("Chiller Efficiency Chiller Staging Efficiency Calculator", "[CoolingTower][Chillers]")
{
    const std::vector<double> baselineLoadList {300,300,300};
    const std::vector<double> modLoadList {450,450,0};
    auto res = ChillerEfficiency::ChillerStagingEfficiency(
            ChillerEfficiency::Centrifugal, ChillerEfficiency::Water, ChillerEfficiency::VFD,
            1000, 0.676, 1.00, 1.00, 42, 82.12,
            std::vector<double> {300,300,300},
            std::vector<double> {450,450,0});

    CHECK(res.baselineTotalPower == Approx(820.5017));
    CHECK(res.baselineTotalEnergy == Approx(820.5017));
    CHECK(res.modTotalPower == Approx(603.9089));
    CHECK(res.modTotalEnergy == Approx(603.9089));
    CHECK(res.savingsEnergy == Approx(216.5928));

    CHECK(res.baselinePowerList[0] == Approx(273.501));
    CHECK(res.baselinePowerList[1] == Approx(273.501));
    CHECK(res.baselinePowerList[2] == Approx(273.501));

    CHECK(res.modPowerList[0] == Approx(301.954));
    CHECK(res.modPowerList[1] == Approx(301.954));
    CHECK(res.modPowerList[2] == Approx(0));
}
