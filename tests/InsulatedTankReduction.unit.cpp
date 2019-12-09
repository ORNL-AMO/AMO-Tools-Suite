#include <iostream>
#include <vector>
#include <catch.hpp>
#include "calculator/util/insulation/tanks/InsulatedTankInput.h"
#include "calculator/util/insulation/tanks/InsulatedTankCalculator.h"
#include "calculator/util/insulation/tanks/InsulatedTankOutput.h"
#include "calculator/util/insulation/objects/AirProperties.h"

TEST_CASE("Insulated Tank", "[InsulatedTankReduction][util]")
{
    int operatingHours = 8760;
    double tankHeight = 10;
    double tankDiameter = 5;
    double tankThickness = 0.5;
    double tankEmissivity = 0.8;
    double tankConductivity = 46.2320;
    double tankTemperature = 959.67;
    double ambientTemperature = 529.67;
    double systemEfficiency = 0.9;
    double insulationThickness = 0.5;
    double insulationConductivity = 0.0190707;
    double jacketEmissivity = 0.9;

    InsulatedTankInput input(
        operatingHours,
        tankHeight,
        tankDiameter,
        tankThickness,
        tankEmissivity,
        tankConductivity,
        tankTemperature,
        ambientTemperature,
        systemEfficiency,
        insulationThickness,
        insulationConductivity,
        jacketEmissivity);

    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();
    CHECK(output.getHeatLoss() == Approx(0.0444151747));
    CHECK(output.getAnnualHeatLoss() == Approx(389.0769300822));
}


TEST_CASE("No Insulation Tank", "[InsulatedTankReduction][util]")
{
    int operatingHours = 8760;
    double tankHeight = 10;
    double tankDiameter = 5;
    double tankThickness = 0.5;
    double tankEmissivity = 0.8;
    double tankConductivity = 46.2320;
    double tankTemperature = 959.67;
    double ambientTemperature = 529.67;
    double systemEfficiency = 0.9;
    double insulationThickness = 0;
    double insulationConductivity = 0;
    double jacketEmissivity = 0.9;

    InsulatedTankInput input(
        operatingHours,
        tankHeight,
        tankDiameter,
        tankThickness,
        tankEmissivity,
        tankConductivity,
        tankTemperature,
        ambientTemperature,
        systemEfficiency,
        insulationThickness,
        insulationConductivity,
        jacketEmissivity);

    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();
    CHECK(output.getHeatLoss() == Approx(1.1112001223));
    CHECK(output.getAnnualHeatLoss() == Approx(9734.11));
}
