#include <iostream>
#include <catch.hpp>
#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include "calculator/util/insulation/pipes/InsulatedPipeCalculator.h"
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"
#include "calculator/util/insulation/objects/AirProperties.h"

TEST_CASE("Insulated Pipe", "[InsulatedPipeReduction][util]")
{
    int operatingHours = 8640;
    double length = 15.24;
    double diameter = .025399;
    double pipeThickness = 0.0033782;
    double pipeTemperature = 422.039;
    double ambientTemperature = 299.817;
    double windVelocity = 0.89408;
    double ngSystemEfficiency = 0.9;
    double pipeMaterialCoefficients[] = {0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1};
    double insulationMaterialCoefficients[] = {1.57526E-12, -2.02822E-09, 8.6328E-07, 0, 0.006729488};
    double insulationThickness = 0.0762;
    double pipeEmissivity = 0.8000;
    double jacketEmissivity = 0.1;
    double pipeBaseMaterialEmissivity = 0.8000;

    InsulatedPipeInput input(
        operatingHours,
        length,
        diameter,
        pipeThickness,
        pipeTemperature,
        ambientTemperature,
        windVelocity,
        ngSystemEfficiency,
        insulationThickness,
        pipeMaterialCoefficients,
        insulationMaterialCoefficients,
        pipeEmissivity,
        jacketEmissivity,
        pipeBaseMaterialEmissivity);

    InsulatedPipeCalculator calculator(input);
    InsulatedPipeOutput output = calculator.calculate();

    CHECK(output.getAnnualHeatLoss() == Approx(19.3862753));
}