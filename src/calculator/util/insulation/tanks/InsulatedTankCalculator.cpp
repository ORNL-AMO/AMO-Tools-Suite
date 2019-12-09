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
}

InsulatedTankOutput InsulatedTankCalculator::calculateInsulation(InsulatedTankInput input)
{
    double thermalDiffusivity;
    double thermalExpansionCoefficient;
    double airRayleigh;
    double naturalConvectionCoefficient;
    double innerTankRadius;
    double outerTankRadius;
    double outerInsulationRadius;
    double tankArea;
    double insulationOverallCoefficient;
    double insulationConvCondHeatLoss;
    double insulationRadiativeHeatLoss;
    double insulationHeatLoss;
    double annualHeatLoss;
    AirProperties airProperties = InsulatedTankCalculator::calculateAirProperties(input.getAmbientTemperature());
    thermalDiffusivity = airProperties.getConductivity() / (airProperties.getDensity() * airProperties.getSpecificHeat());
    thermalExpansionCoefficient = 1.0 / input.getAmbientTemperature();
    airRayleigh = (32.174 * thermalExpansionCoefficient * (input.getTankTemperature() - input.getAmbientTemperature()) * std::pow(input.getTankDiameter(), 3)) / (airProperties.getKinViscosity() * thermalDiffusivity);
    airProperties.setRayleigh(airRayleigh);
    naturalConvectionCoefficient = 0.125 * std::pow(airProperties.getRayleigh(), 1.0 / 3.0) * airProperties.getConductivity() / input.getTankDiameter();
    innerTankRadius = input.getTankDiameter() / 2.0;
    outerTankRadius = innerTankRadius + input.getTankThickness();
    outerInsulationRadius = outerTankRadius + input.getTankThickness();
    tankArea = input.getTankDiameter() * input.getTankHeight() * M_PI;
    insulationOverallCoefficient = 1.0 / (innerTankRadius / outerInsulationRadius * 1.0 / naturalConvectionCoefficient + innerTankRadius / input.getInsulationConductivity() * std::log(outerInsulationRadius / outerTankRadius) + innerTankRadius / input.getTankConductivity() * std::log(outerTankRadius / innerTankRadius) + 1.0 / 10.0);
    insulationConvCondHeatLoss = insulationOverallCoefficient * tankArea * (input.getTankTemperature() - input.getAmbientTemperature()) / 1e5;
    insulationRadiativeHeatLoss = 0.1713e-8 * input.getJacketEmissivity() * (std::pow(input.getTankTemperature(), 4) - std::pow(input.getAmbientTemperature(), 4)) / 1e5;
    insulationHeatLoss = insulationConvCondHeatLoss + insulationRadiativeHeatLoss;
    annualHeatLoss = insulationHeatLoss * (double)input.getOperatingHours();
    return InsulatedTankOutput(insulationHeatLoss, annualHeatLoss);
}

InsulatedTankOutput InsulatedTankCalculator::calculateNoInsulation(InsulatedTankInput input)
{
    double thermalDiffusivity;
    double thermalExpansionCoefficient;
    double airRayleigh;
    double naturalConvectionCoefficient;
    double innerTankRadius;
    double outerTankRadius;
    double tankArea;
    double bareOverallCoefficient;
    double bareConvCondHeatLoss;
    double bareRadiativeHeatLoss;
    double bareHeatLoss;
    double annualHeatLoss;
    AirProperties airProperties = InsulatedTankCalculator::calculateAirProperties(input.getAmbientTemperature());
    thermalDiffusivity = airProperties.getConductivity() / (airProperties.getDensity() * airProperties.getSpecificHeat());
    thermalExpansionCoefficient = 1.0 / input.getAmbientTemperature();
    airRayleigh = (32.174 * thermalExpansionCoefficient * (input.getTankTemperature() - input.getAmbientTemperature()) * std::pow(input.getTankDiameter(), 3)) / (airProperties.getKinViscosity() * thermalDiffusivity);
    airProperties.setRayleigh(airRayleigh);
    naturalConvectionCoefficient = 0.125 * std::pow(airProperties.getRayleigh(), 1.0 / 3.0) * airProperties.getConductivity() / input.getTankDiameter();
    innerTankRadius = input.getTankDiameter() / 2.0;
    outerTankRadius = innerTankRadius + input.getTankThickness();
    tankArea = input.getTankDiameter() * input.getTankHeight() * M_PI;
    bareOverallCoefficient = 1.0 / (innerTankRadius / outerTankRadius * 1.0 / naturalConvectionCoefficient + innerTankRadius / input.getTankConductivity() * std::log(outerTankRadius / innerTankRadius) + 1.0 / 10.0);
    bareConvCondHeatLoss = bareOverallCoefficient * tankArea * (input.getTankTemperature() - input.getAmbientTemperature()) / 1e5;
    bareRadiativeHeatLoss = 0.1713e-8 * input.getTankEmissivity() * (std::pow(input.getTankTemperature(), 4) - std::pow(input.getAmbientTemperature(), 4)) / 1e5;
    bareHeatLoss = bareConvCondHeatLoss + bareRadiativeHeatLoss;
    annualHeatLoss = bareHeatLoss * (double)input.getOperatingHours();
    return InsulatedTankOutput(bareHeatLoss, annualHeatLoss);
}

AirProperties InsulatedTankCalculator::calculateAirProperties(double temp)
{
    double airConductivity = calculateAirProperty(3, temp);
    double viscosity = 0;
    double prandtl = 0;
    double expansionCoefficient = 0;
    double airDensity = calculateAirProperty(1, temp) * 1e-2;
    double airKinViscosity = calculateAirProperty(2, temp) * 1e-4 / 3600.0;
    double airSpecificHeat = calculateAirProperty(0, temp);
    double alpha = 0;
    double reynolds = 0;
    double rayleigh = 0;
    return AirProperties(airConductivity, viscosity, prandtl, expansionCoefficient, airDensity, airKinViscosity, airSpecificHeat, alpha, reynolds, rayleigh);
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