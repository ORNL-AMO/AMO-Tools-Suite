#ifndef AMO_LIBRARY_INSULATEDPIPECALCULATOR_H
#define AMO_LIBRARY_INSULATEDPIPECALCULATOR_H

#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"
#include "calculator/util/insulation/objects/AirProperties.h"
#include "calculator/util/insulation/services/ConvectiveHeatTransferCoefficient.h"
#include "calculator/util/insulation/services/NusseltNumber.h"
#include "calculator/util/insulation/services/RadiativeHeatTransferCoefficient.h"
#include "calculator/util/insulation/services/RayleighNumber.h"
#include "calculator/util/insulation/services/ReynoldsNumber.h"
#include "calculator/util/insulation/services/ThermalResistance.h"

class InsulatedPipeCalculator
{
public:
    InsulatedPipeCalculator();
    InsulatedPipeCalculator(InsulatedPipeInput insulatedPipeInput) : _insulatedPipeInput(insulatedPipeInput) {}

    InsulatedPipeOutput calculate();
    AirProperties calculateAirProperties(double temp);
    InsulatedPipeOutput calculateNoInsulation(InsulatedPipeInput input);
    InsulatedPipeOutput calculateInsulation(InsulatedPipeInput input);
    double insulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i);
    double noInsulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i);
    double calculateAirProperty(int property, double temp);
    double lookupAirPropertyCoefficient(int property, int n);
    const double *lookupAirProperty(int property);

private:
    void validateInput(InsulatedPipeInput input);
    double propertyFit(std::vector<double> coefficients, double temp);

    InsulatedPipeInput _insulatedPipeInput;
    const double _airPropertiesArray[6][5] = {
        {3.03724e-13, -1.1132e-9, 1.44382e-6, -0.000565339, 1.07223839},     // specificHeat
        {-1.586e-10, 5.115e-7, -7.246e-4, 7.978e-1, -1.850},                 // viscosity
        {2.25852e-11, -8.32093e-8, 0.000172673, 0.01063728, -0.76108359},    // kinViscosity
        {3.17176E-11, -5.90229E-08, 4.58531E-06, 0.088867888, 0.520072239},  // thermCond
        {1.35569E-10, -3.80588E-07, 0.000446483, -0.035935528, 2.254489164}, // Alpha
        {-2.08438E-13, -1.72787E-11, 8.00624E-07, -0.000694606, 0.845781218} // Prandtl
    };
};

#endif