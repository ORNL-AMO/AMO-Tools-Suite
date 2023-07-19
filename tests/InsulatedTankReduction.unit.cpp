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
    double insulationConductivity = 0.0191;
    double jacketEmissivity = 0.9;
    double surfaceTemperature = 959.67;

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
        jacketEmissivity,
        surfaceTemperature);

    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();
    CHECK(output.getHeatLoss() == Approx(0.0444638799));
    CHECK(output.getAnnualHeatLoss() == Approx(43.278176));
}

TEST_CASE("Insulated Tank 2", "[InsulatedTankReduction][util]")
{
    int operatingHours = 8760;
    double tankHeight = 50;
    double tankDiameter = 1;
    double tankThickness = 0.25;
    double tankEmissivity = 0.3;
    double tankConductivity = 9.25;
    double tankTemperature = 759.67;
    double ambientTemperature = 539.67;
    double systemEfficiency = 0.9;
    double insulationThickness = 0.5;
    double insulationConductivity = 0.0231;
    double jacketEmissivity = 0.1;
    double surfaceTemperature = 759.67;

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
        jacketEmissivity,
        surfaceTemperature);

    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();
    CHECK(output.getHeatLoss() == Approx(0.030515));
    CHECK(output.getAnnualHeatLoss() == Approx(29.70135));
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
    double surfaceTemperature = 959.67;

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
        jacketEmissivity,
        surfaceTemperature);

    InsulatedTankCalculator calculator(input);
    InsulatedTankOutput output = calculator.calculate();
    CHECK(output.getHeatLoss() == Approx(1.1112001223));
    CHECK(output.getAnnualHeatLoss() == Approx(1081.568119));
}
