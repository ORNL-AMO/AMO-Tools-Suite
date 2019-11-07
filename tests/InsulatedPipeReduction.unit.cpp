#include <iostream>
#include <vector>
#include <catch.hpp>
#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include "calculator/util/insulation/pipes/InsulatedPipeCalculator.h"
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"
#include "calculator/util/insulation/objects/AirProperties.h"

TEST_CASE("Insulated Pipe", "[InsulatedPipeReduction][util]")
{
    int operatingHours = 8640;        //hrs
    double pipeLength = 15.24;            //m
    double pipeDiameter = .025399;    //m
    double pipeThickness = 0.0033782; //m
    double pipeTemperature = 422.039;
    double ambientTemperature = 299.817;
    double windVelocity = 0.89408;
    double systemEfficiency = 0.9;
    double insulationThickness = 0.0762;
    double pipeEmissivity = 0.8000;
    double jacketEmissivity = 0.1;
    std::vector<double> pipeMaterialCoefficients = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    std::vector<double> insulationMaterialCoefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeInput input(
        operatingHours,
        pipeLength,
        pipeDiameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        systemEfficiency,
        insulationThickness,
        pipeEmissivity,
        jacketEmissivity,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients);

    InsulatedPipeCalculator calculator(input);
    InsulatedPipeOutput output = calculator.calculate();
    CHECK(output.getHeatLength() == Approx(19.3858771378));
    CHECK(output.getAnnualHeatLoss() == Approx(2836231.3687633672));
}

TEST_CASE("Non-Insulated Pipe", "[InsulatedPipeReduction][util]")
{
    int operatingHours = 8640;        //hrs
    double pipeLength = 15.24;            //m
    double diameter = .025399;        //m
    double pipeThickness = 0.0033782; //m
    double pipeTemperature = 422.039;
    double ambientTemperature = 299.817;
    double windVelocity = 0.89408;
    double systemEfficiency = 0.9;
    double insulationThickness = 0;
    double pipeEmissivity = 0.8000;
    double jacketEmissivity = 0.1;
    std::vector<double> pipeMaterialCoefficients = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    std::vector<double> insulationMaterialCoefficients = {1.57526e-12, -2.02822e-09, 8.6328e-07, 0, 0.006729488};

    InsulatedPipeInput input(
        operatingHours,
        pipeLength,
        diameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        systemEfficiency,
        insulationThickness,
        pipeEmissivity,
        jacketEmissivity,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients);

    InsulatedPipeCalculator calculator(input);
    InsulatedPipeOutput output = calculator.calculate();
    CHECK(output.getHeatLength() == Approx(278.8984025085));
    CHECK(output.getAnnualHeatLoss() == Approx(40803938.64));
}