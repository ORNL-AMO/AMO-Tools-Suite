#include "calculator/util/insulation/tanks/InsulatedTankCalculator.h"
#include "calculator/util/insulation/objects/AirProperties.h"
#include <cmath>
#include <vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

InsulatedTankOutput InsulatedTankCalculator::calculate()
{
    InsulatedTankInput input = this->_insulatedTankInput;
    this->validateInput(input);

    // if -1 or 0, then no insulation was provided
    if (this->_insulatedTankInput.getInsulationThickness() == -1 || this->_insulatedTankInput.getInsulationThickness() == 0)
    {
        return InsulatedTankCalculator::calculateNoInsulation(input);
    }
    else
    {
        return InsulatedTankCalculator::calculateInsulation(input);
    }
}

void InsulatedTankCalculator::validateInput(InsulatedTankInput input)
{
    if (input.getTankEmissivity() < 0.0 || input.getTankEmissivity() > 1.0)
    {
        throw "ERROR : Tank - tank emissivity out of acceptable range";
    }
    if (input.getJacketEmissivity() < 0.0 || input.getJacketEmissivity() > 1.0)
    {
        throw "ERROR : Tank - jacket emissivity out of acceptable range";
    }
    if (input.getTankMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Tank - expected exactly 5 tank material coefficients, received " + input.getTankMaterialCoefficients().size();
    }
    if (input.getInsulationMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Tank - expected exactly 5 insulation material coefficients, received " + input.getInsulationMaterialCoefficients().size();
    }
}

InsulatedTankInput InsulatedTankCalculator::calculateInsulation(InsulatedTankInput input)
{
    double thermalDiffusivity;
    double thermalExpansionCoefficient;
    double naturalConvectionCoefficient;
    double airRayleigh;
    double innerTankRadius;
    double outerTankRadius;
    double outerInsulationRadius;
    double tankArea;
    double insulationOverallCoefficient;
    AirProperties airProperties = InsulatedTankCalculator::calculateAirProperties(input.getAmbientTemperature());
    thermalDiffusivity = airProperties.getConductivity() / (airProperties.getDensity() * airProperties.getSpecificHeat());
    thermalExpansionCoefficient = 1.0 / input.getAmbientTemperature();
    airRayleigh = (32.174 * thermalExpansionCoefficient * (input.getTankTemperature() - input.getAmbientTemperature()) * std::pow(airProperties.getSpecificHeat(), 3)) / (airProperties.getKinViscosity() * thermalDiffusivity);
    naturalConvectionCoefficient = 0.125 * std::pow(airRayleigh, 1/3) * airProperties.getConductivity() / airProperties.getSpecificHeat();
    innerTankRadius = input.getTankDiameter() / 2.0;
    outerTankRadius = innerTankRadius + input.getTankThickness();
    outerInsulationRadius = outerTankRadius + input.getTankThickness();
    tankArea = input.getTankDiameter() * input.getTankHeight() * M_PI;


    




}

AirProperties InsulatedTankCalculator::calculateAirProperties(double temp)
{
    double airSpecificHeat = calculateAirProperty(0, temp);
    double airDensity = calculateAirProperty(1, temp) * 1e-2;
    double airKinViscosity = calculateAirProperty(2, temp) * 1e-4 / 3600;
    double airConductivity = calculateAirProperty(3, temp);
    // double 
}

double InsulatedTankCalculator::calculateAirProperty(int property, double temp)
{
    std::vector<double> coefficients = {
        InsulatedTankCalculator::lookupAirPropertyCoefficient(property, 0),
        InsulatedTankCalculator::lookupAirPropertyCoefficient(property, 1),
        InsulatedTankCalculator::lookupAirPropertyCoefficient(property, 2),
        InsulatedTankCalculator::lookupAirPropertyCoefficient(property, 3),
        InsulatedTankCalculator::lookupAirPropertyCoefficient(property, 4)};
    return this->propertyFit(coefficients, temp);
}

double InsulatedTankCalculator::propertyFit(std::vector<double> coefficients, double temp)
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

double InsulatedTankCalculator::lookupAirPropertyCoefficient(int property, int n)
{
    return this->_airPropertiesArray[property][n];
}

const double *InsulatedTankCalculator::lookupAirProperty(int property)
{
    return this->_airPropertiesArray[property];
}