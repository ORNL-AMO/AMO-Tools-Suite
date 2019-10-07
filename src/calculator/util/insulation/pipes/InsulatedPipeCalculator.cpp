#include "calculator/util/insulation/pipes/InsulatedPipeCalculator.h"
#include "calculator/util/insulation/objects/AirProperties.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/*
    Steps:
        1) Check if there is insulation
*/
InsulatedPipeOutput InsulatedPipeCalculator::calculate()
{
    InsulatedPipeInput input = this->_insulatedPipeInput;
    InsulatedPipeOutput output;

    sanatizeInput(input);

    // 1) if -1, then no insulation was provided
    if (input.getInsulationEmissivity() == -1)
    {
        output = calculateNoInsulation(input);
    }
    else
    {
        output = calculateInsulation(input);
    }

    return output;
}

//check if emissivity values are out of expected range and throw error
void sanatizeInput(InsulatedPipeInput input)
{
    if (input.getPipeEmissivity() < 0.0 || input.getPipeEmissivity() > 1.0)
    {
        throw "ERROR : pipe emissivity out of acceptable range";
    }
    if ((input.getInsulationEmissivity() < 0.0 || input.getInsulationEmissivity() > 1.0) && input.getInsulationEmissivity() != -1)
    {
        throw "ERROR : insulation emissivity out of acceptable range";
    }
    if (input.getJacketEmissivity() < 0.0 || input.getJacketEmissivity() > 1.0)
    {
        throw "ERROR : jacket emissivity out of acceptable range";
    }
}

InsulatedPipeOutput calculateInsulation(InsulatedPipeInput input)
{
    double innerPipeDiameter;
    double outerInsulationDiameter;
    double surfaceTemperature;
    double interfaceTemperature;
    double heatLength;
    double annualHeatLoss;
    innerPipeDiameter = input.getPipeDiameter() - input.getPipeThickness();
    outerInsulationDiameter = input.getPipeDiameter() + (2.0 * input.getInsulationThickness());
    surfaceTemperature = input.getAmbientTemperature() + 1.0;
    interfaceTemperature = input.getPipeTemperature() - 1.0;

    heatLength = insulationRecursive(input, innerPipeDiameter, outerInsulationDiameter, surfaceTemperature, interfaceTemperature, 0, 0, 0);
    annualHeatLoss = heatLength * input.getLength() * input.getOperatingHours() / input.getNaturalGasSystemEfficiency();
    return InsulatedPipeOutput(annualHeatLoss);
}

double insulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature()) / 2.0;
    //step 1: establish air properties
    AirProperties airProperties = calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double insReynolds = ReynoldsNumber(insulationOuterDiameter, input.getWindVelocity(), airProperties.getKinViscosity()).calculate();
    double insRayleigh = RayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(), insulationOuterDiameter, airProperties.getKinViscosity(), airProperties.getAlpha()).calculate();
    double insHeatRadiation = RadiativeHeatTransferCoefficient(input.getJacketEmissivity(), surfaceTemperature, input.getAmbientTemperature()).calculate();
    double insNusseltForced = NusseltNumber(insReynolds, airProperties.getPrandtl()).calculateForcedConvection();
    double insConvectionForced = ConvectiveHeatTransferCoefficient(insNusseltForced, airProperties.getPrandtl()).calculate();
    double insNusseltFree = NusseltNumber(insRayleigh, airProperties.getPrandtl()).calculateFreeConvection();
    double insConvectionFree = ConvectiveHeatTransferCoefficient(insNusseltFree, airProperties.getConductivity(), insulationOuterDiameter).calculate();
    double insNusseltCombined = NusseltNumber(insNusseltForced, insNusseltFree).calculate();
    double insConvectionCombined = ConvectiveHeatTransferCoefficient(insNusseltCombined, airProperties.getConductivity(), insulationOuterDiameter);
    double insHeatAir = insHeatRadiation + insConvectionCombined;

    //step 3: pipe resistance
    double kPipe = propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = ThermalResistance(insulationOuterDiameter, input.getPipeDiameter(), innerPipeDiameter, kPipe).calculate();

    //step 4: insulation resistance
    double insulationTemperature = (surfaceTemperature + interfaceTemperature) / 2.0;
    double kInsulation = propertyFit(input.getInsulationMaterialCoefficients(), insulationTemperature);
    double insulationResistance = ThermalResistance(insulationOuterDiameter, input.getPipeDiameter(), innerPipeDiameter, kInsulation).calculate();

    //step 5: overall resistance
    double overallResistance = insulationResistance + pipeResistance + (1.0 / insHeatAir);
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 6: rewriting interfaceTemp & surfaceTemp
    interfaceTemperature = input.getPipeTemperature() - heatFlow * pipeResistance;
    surfaceTemperature = interfaceTemperature - heatFlow * insulationResistance;
    double heatLengthNew = heatFlow * M_PI * insulationOuterDiameter;

    if (std::abs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR: No Insulation - recursion limit exceeded";
    }
    else
    {
        return insulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i++);
    }
}

InsulatedPipeOutput calculateNoInsulation(InsulatedPipeInput input)
{
    double innerPipeDiameter;
    double insulationOuterDiameter;
    double surfaceTemperature;
    double interfaceTemperature;
    double heatLength;
    double annualHeatLoss;
    innerPipeDiameter = input.getPipeDiameter() - input.getPipeThickness();
    insulationOuterDiameter = input.getPipeDiameter() + (2.0 * input.getInsulationThickness());
    surfaceTemperature = input.getAmbientTemperature() + 1.0;
    interfaceTemperature = input.getPipeTemperature() - 1.0;

    //start iteration
    heatLength = noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, 0.0, 0);
    annualHeatLoss = heatLength * input.getLength() * input.getOperatingHours() / input.getNaturalGasSystemEfficiency();
    return InsulatedPipeOutput(annualHeatLoss);
}

double noInsulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature) / 2.0;
    //step 1: establish air properties
    AirProperties airProperties = calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double bareReynolds = ReynoldsNumber(input.getPipeDiameter(), input.getWindVelocity(), airProperties.getKinViscosity()).calculate();
    double bareRayleigh = RayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(), input.getPipeDiameter(), airProperties.getKinViscosity(), airProperties.getAlpha()).calculate();
    double bareRadiativeHeatTransferCoefficient = RadiativeHeatTransferCoefficient(input.getPipeEmissivity(), surfaceTemperature, input.getAmbientTemperature()).calculate();
    double bareNusseltForced = NusseltNumber(bareReynolds, airProperties.getPrandtl()).calculateForcedConvection();
    double bareConvectionForced = ConvectiveHeatTransferCoefficient(bareNusseltForced, airProperties.getConductivity(), input.getPipeDiameter).calculate();
    double bareNusseltFree = NusseltNumber(bareRayleigh, airProperties.getPrandtl()).calculateFreeConvection();
    double bareConvectionFree = ConvectiveHeatTransferCoefficient(bareNusseltFree, airProperties.getConductivity(), input.getPipeDiameter()).calculate();
    double bareNusseltCombined = NusseltNumber(bareNusseltForced, bareNusseltFree).calculate();
    double bareConvection = ConvectiveHeatTransferCoefficient(bareNusseltCombined, airProperties.getConductivity(), input.getPipeDiameter()).calculate();
    double bareHeatTransferAir = bareRadiativeHeatTransferCoefficient + bareConvection;

    //step 3: pipe resistance
    double kPipe = propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = ThermalResistance(input.getPipeDiameter(), input.getPipeDiameter(), innerPipeDiameter, kPipe);

    //step 4: overall resistance
    double overallResistance = pipeResistance + 1 / bareHeatTransferAir;
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 5: rewriting interfaceTemperature && surfaceTemperature;
    interfaceTemperature = input.getPipeTemperature() - heatFlow * pipeResistance;
    surfaceTemperature = interfaceTemperature - (heatFlow * insulationResistance);
    double heatLengthNew = heatFlow * M_PI * input.getPipeDiameter();

    if (std::abs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR: No Insulation - recursion limit exceeded";
    }
    else
    {
        return noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i++);
    }
}

AirProperties calculateAirProperties(double temp)
{
    AirProperties airProperties = new AirProperties();
    double airConductivity = propertyFit(this->_airProperties[3], temp) / 10e3;
    double airViscosity = propertyFit(this->_airProperties[1], temp) / 10e7;
    double airPrandtl = propertyFit(this->_airProperties[5], temp);
    double airExpansionCoefficient = 1.0 / temp;
    double airDensity = 29.0 / 0.0820575 / temp;
    double airKinViscosity = propertyFit(this->_airProperties[2], temp) / 10e6;
    double airSpecificHeat = propertyFit(this->_airProperties[0], temp);
    double airAlpha = propertyFit(this->_airProperties[4], temp) / 10e6;
    airProperties.setConductivity(airConductivity);
    airProperties.setViscosity(airViscosity);
    airProperties.setPrandtl(airPrandtl);
    airProperties.setExpansionCoefficient(airExpansionCoefficient);
    airProperties.setDensity(airDensity);
    airProperties.setKinViscosity(airKinViscosity);
    airProperties.setSpecificHeat(airSpecificHeat);
    airProperties.setAlpha(airAlpha);
    return airProperties;
}

double calculateAirProperty(int property, double temp)
{
    double coefficients[5] = {
        lookupAirProperty(property, 0),
        lookupAirProperty(property, 1),
        lookupAirProperty(property, 2),
        lookupAirProperty(property, 3),
        lookupAirProperty(property, 4)};
    return propertyFit(coefficients, temp);
}

double propertyFit(double coefficients[5], double temp)
{
    double property;
    double order4 = coefficients[4] * std::pow(temp, 4);
    double order3 = coefficients[3] * std::pow(temp, 3);
    double order2 = coefficients[2] * std::pow(temp, 2);
    double order1 = coefficients[1] * temp;
    double order0 = coefficients[0];
    property = order4 + order3 + order2 + order1 + order0;
    return property;
}

double lookupAirProperty(int property, int n)
{
    return this->_airProperties[property][n];
}

const double InsulatedPipeCalculator::_airProperties[][] = {

    {3.03724e-13, -1.1132e-9, 1.44382e-6, -0.000565339, 1.07223839},     // specificHeat
    {-1.586e-10, 5.115e-7, -7.246e-4, 7.978e-1, -1.850},                 // viscosity
    {2.25852e-11, -8.32093e-8, 0.000172673, 0.01063728, -0.76108359},    // kinViscosity
    {3.17176E-11, -5.90229E-08, 4.58531E-06, 0.088867888, 0.520072239},  // thermCond
    {1.35569E-10, -3.80588E-07, 0.000446483, -0.035935528, 2.254489164}, // Alpha
    {-2.08438E-13, -1.72787E-11, 8.00624E-07, -0.000694606, 0.845781218} // Prandtl

};