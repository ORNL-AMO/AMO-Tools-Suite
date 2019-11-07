#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include <cmath>

int InsulatedPipeInput::getOperatingHours()
{
    return this->_operatingHours;
}

double InsulatedPipeInput::getPipeLength()
{
    return this->_pipeLength;
}

double InsulatedPipeInput::getPipeDiameter()
{
    return this->_pipeDiameter;
}

double InsulatedPipeInput::getPipeThickness()
{
    return this->_pipeThickness;
}

double InsulatedPipeInput::getPipeTemperature()
{
    return this->_pipeTemperature;
}

double InsulatedPipeInput::getAmbientTemperature()
{
    return this->_ambientTemperature;
}

double InsulatedPipeInput::getWindVelocity()
{
    return this->_windVelocity;
}

double InsulatedPipeInput::getSystemEfficiency()
{
    return this->_systemEfficiency;
}

double InsulatedPipeInput::getInsulationThickness()
{
    return this->_insulationThickness;
}

double InsulatedPipeInput::getPipeEmissivity()
{
    return this->_pipeEmissivity;
}

double InsulatedPipeInput::getJacketEmissivity()
{
    return this->_jacketEmissivity;
}

std::vector<double> InsulatedPipeInput::getPipeMaterialCoefficients()
{
    return this->_pipeMaterialCoefficients;
}

std::vector<double> InsulatedPipeInput::getInsulationMaterialCoefficients()
{
    return this->_insulationMaterialCoefficients;
}