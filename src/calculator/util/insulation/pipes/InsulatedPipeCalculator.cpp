#include "calculator/util/insulation/pipes/InsulatedPipeCalculator.h"
#include "calculator/util/insulation/objects/AirProperties.h"
#include <cmath>
#include <vector>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

InsulatedPipeOutput InsulatedPipeCalculator::calculate()
{
    InsulatedPipeInput input = this->_insulatedPipeInput;
    this->validateInput(input);

    // if -1, then no insulation was provided
    if (this->_insulatedPipeInput.getInsulationThickness() == -1 || this->_insulatedPipeInput.getInsulationThickness() == 0)
    {
        return InsulatedPipeCalculator::calculateNoInsulation(input);
    }
    else
    {
        return InsulatedPipeCalculator::calculateInsulation(input);
    }
}

//check if emissivity values are out of expected range and throw error
void InsulatedPipeCalculator::validateInput(InsulatedPipeInput input)
{
    if (input.getPipeEmissivity() < 0.0 || input.getPipeEmissivity() > 1.0)
    {
        throw "ERROR : Pipe - pipe emissivity out of acceptable range";
    }
    if (input.getJacketEmissivity() < 0.0 || input.getJacketEmissivity() > 1.0)
    {
        throw "ERROR : Pipe - jacket emissivity out of acceptable range";
    }
    if (input.getPipeMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Pipe - expected exactly 5 pipe material coefficients, received " + std::to_string(input.getPipeMaterialCoefficients().size());
    }
    if (input.getInsulationMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Pipe - expected exactly 5 insulation material coefficients, received " + std::to_string(input.getInsulationMaterialCoefficients().size());
    }
}

InsulatedPipeOutput InsulatedPipeCalculator::calculateInsulation(InsulatedPipeInput input)
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

    //start iteration
    heatLength = InsulatedPipeCalculator::insulationRecursive(input, innerPipeDiameter, outerInsulationDiameter, surfaceTemperature, interfaceTemperature, 0, 0);
    annualHeatLoss = heatLength * input.getPipeLength() * input.getOperatingHours() / input.getSystemEfficiency();
    return InsulatedPipeOutput(heatLength, annualHeatLoss);
}

double InsulatedPipeCalculator::insulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature()) / 2.0;

    //step 1: establish air properties
    AirProperties airProperties = InsulatedPipeCalculator::calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double insReynolds = ReynoldsNumber(insulationOuterDiameter, input.getWindVelocity(), airProperties.getKinViscosity()).calculate();
    double insRayleigh = RayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(), insulationOuterDiameter, airProperties.getKinViscosity(), airProperties.getAlpha()).calculate();
    double insHeatRadiation = RadiativeHeatTransferCoefficient(input.getJacketEmissivity(), surfaceTemperature, input.getAmbientTemperature()).calculate();
    double insNusseltForced = NusseltNumber(insReynolds, airProperties.getPrandtl()).calculateForcedConvection();
    double insNusseltFree = NusseltNumber(insRayleigh, airProperties.getPrandtl()).calculateFreeConvection();
    double insNusseltCombined = NusseltNumber(insNusseltForced, insNusseltFree).calculate();
    double insConvectionCombined = ConvectiveHeatTransferCoefficient(insNusseltCombined, airProperties.getConductivity(), insulationOuterDiameter).calculate();
    double insHeatAir = insHeatRadiation + insConvectionCombined;

    //step 3: pipe resistance
    double kPipe = this->propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = ThermalResistance(insulationOuterDiameter, input.getPipeDiameter(), innerPipeDiameter, kPipe).calculate();

    //step 4: insulation resistance
    double insulationTemperature = (surfaceTemperature + interfaceTemperature) / 2.0;
    double kInsulation = this->propertyFit(input.getInsulationMaterialCoefficients(), insulationTemperature);
    double insulationResistance = ThermalResistance(insulationOuterDiameter, insulationOuterDiameter, input.getPipeDiameter(), kInsulation).calculate();

    //step 5: overall resistance
    double overallResistance = insulationResistance + pipeResistance + (1.0 / insHeatAir);
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 6: rewriting interfaceTemp & surfaceTemp
    interfaceTemperature = input.getPipeTemperature() - (heatFlow * pipeResistance);
    surfaceTemperature = interfaceTemperature - (heatFlow * insulationResistance);
    double heatLengthNew = heatFlow * M_PI * insulationOuterDiameter;

    if (std::fabs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR : Pipe, Insulation - recursion limit exceeded";
    }
    else
    {
        i = i + 1;
        return InsulatedPipeCalculator::insulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i);
    }
}

InsulatedPipeOutput InsulatedPipeCalculator::calculateNoInsulation(InsulatedPipeInput input)
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
    heatLength = InsulatedPipeCalculator::noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, 0.0, 0);
    annualHeatLoss = heatLength * input.getPipeLength() * input.getOperatingHours() / input.getSystemEfficiency();
    return InsulatedPipeOutput(heatLength, annualHeatLoss);
}

double InsulatedPipeCalculator::noInsulationRecursive(InsulatedPipeInput input, double innerPipeDiameter, double insulationOuterDiameter, double surfaceTemperature, double interfaceTemperature, double heatLength, int i)
{
    double filmTemperature;
    filmTemperature = (surfaceTemperature + input.getAmbientTemperature()) / 2.0;
    //step 1: establish air properties
    AirProperties airProperties = InsulatedPipeCalculator::calculateAirProperties(filmTemperature);

    //step 2: air film resistance
    double bareReynolds = ReynoldsNumber(input.getPipeDiameter(), input.getWindVelocity(), airProperties.getKinViscosity()).calculate();
    double bareRayleigh = RayleighNumber(airProperties.getExpansionCoefficient(), surfaceTemperature, input.getAmbientTemperature(), input.getPipeDiameter(), airProperties.getKinViscosity(), airProperties.getAlpha()).calculate();
    double bareRadiativeHeatTransferCoefficient = RadiativeHeatTransferCoefficient(input.getPipeEmissivity(), surfaceTemperature, input.getAmbientTemperature()).calculate();
    double bareNusseltForced = NusseltNumber(bareReynolds, airProperties.getPrandtl()).calculateForcedConvection();
    //double bareConvectionForced = ConvectiveHeatTransferCoefficient(bareNusseltForced, airProperties.getConductivity(), input.getPipeDiameter()).calculate();
    double bareNusseltFree = NusseltNumber(bareRayleigh, airProperties.getPrandtl()).calculateFreeConvection();
    //double bareConvectionFree = ConvectiveHeatTransferCoefficient(bareNusseltFree, airProperties.getConductivity(), input.getPipeDiameter()).calculate();
    double bareNusseltCombined = NusseltNumber(bareNusseltForced, bareNusseltFree).calculate();
    double bareConvection = ConvectiveHeatTransferCoefficient(bareNusseltCombined, airProperties.getConductivity(), input.getPipeDiameter()).calculate();
    double bareHeatTransferAir = bareRadiativeHeatTransferCoefficient + bareConvection;

    //step 3: pipe resistance
    double kPipe = this->propertyFit(input.getPipeMaterialCoefficients(), input.getPipeTemperature());
    double pipeResistance = ThermalResistance(input.getPipeDiameter(), input.getPipeDiameter(), innerPipeDiameter, kPipe).calculate();

    //step 4: overall resistance
    double overallResistance = pipeResistance + 1 / bareHeatTransferAir;
    double heatFlow = (input.getPipeTemperature() - input.getAmbientTemperature()) / overallResistance;

    //step 5: rewriting interfaceTemperature && surfaceTemperature;
    interfaceTemperature = input.getPipeTemperature() - heatFlow * pipeResistance;
    surfaceTemperature = interfaceTemperature - (heatFlow * 0);
    double heatLengthNew = heatFlow * M_PI * input.getPipeDiameter();

    if (std::fabs(heatLengthNew - heatLength) < 0.0001)
    {
        return (heatLength + heatLengthNew) / 2.0;
    }
    else if (i > 30)
    {
        throw "ERROR : Pipe, No Insulation - recursion limit exceeded";
    }
    else
    {
        return InsulatedPipeCalculator::noInsulationRecursive(input, innerPipeDiameter, insulationOuterDiameter, surfaceTemperature, interfaceTemperature, heatLengthNew, i++);
    }
}

AirProperties InsulatedPipeCalculator::calculateAirProperties(double temp)
{
    double airConductivity = this->calculateAirProperty(3, temp) / 1e3;
    double airViscosity = this->calculateAirProperty(1, temp) / 1e7;
    double airPrandtl = this->calculateAirProperty(5, temp);
    double airExpansionCoefficient = 1.0 / temp;
    double airDensity = 29.0 / 0.0820575 / temp;
    double airKinViscosity = this->calculateAirProperty(2, temp) / 1e6;
    double airSpecificHeat = this->calculateAirProperty(0, temp);
    double airAlpha = this->calculateAirProperty(4, temp) / 1e6;
    return AirProperties(airConductivity, airViscosity, airPrandtl, airExpansionCoefficient, airDensity, airKinViscosity, airSpecificHeat, airAlpha, 0, 0);
}

double InsulatedPipeCalculator::calculateAirProperty(int property, double temp)
{
    std::vector<double> coefficients = {
        InsulatedPipeCalculator::lookupAirPropertyCoefficient(property, 0),
        InsulatedPipeCalculator::lookupAirPropertyCoefficient(property, 1),
        InsulatedPipeCalculator::lookupAirPropertyCoefficient(property, 2),
        InsulatedPipeCalculator::lookupAirPropertyCoefficient(property, 3),
        InsulatedPipeCalculator::lookupAirPropertyCoefficient(property, 4)};
    return this->propertyFit(coefficients, temp);
}

double InsulatedPipeCalculator::propertyFit(std::vector<double> coefficients, double temp)
{
    double property;
    double order4 = coefficients.at(0) * std::pow(temp, 4);
    double order3 = coefficients.at(1) * std::pow(temp, 3);
    double order2 = coefficients.at(2) * std::pow(temp, 2);
    double order1 = coefficients.at(3) * temp;
    double order0 = coefficients.at(4);
    property = order4 + order3 + order2 + order1 + order0;
    return property;
}

double InsulatedPipeCalculator::lookupAirPropertyCoefficient(int property, int n)
{
    return this->_airPropertiesArray[property][n];
}

const double *InsulatedPipeCalculator::lookupAirProperty(int property)
{
    return this->_airPropertiesArray[property];
}