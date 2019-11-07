
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"

double InsulatedPipeOutput::getHeatLength()
{
    return this->_heatLength;
} 

double InsulatedPipeOutput::getAnnualHeatLoss()
{
    return this->_annualHeatLoss;
}

void InsulatedPipeOutput::setHeatLength(double heatLength)
{
    this->_heatLength = heatLength;
}

void InsulatedPipeOutput::setAnnualHeatLoss(double annualHeatLoss)
{
    this->_annualHeatLoss = annualHeatLoss;
}