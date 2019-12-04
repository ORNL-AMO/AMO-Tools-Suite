
#include "calculator/util/insulation/tanks/InsulatedTankOutput.h"

double InsulatedTankOutput::getHeatLoss()
{
    return this->_heatLoss;
} 

double InsulatedTankOutput::getAnnualHeatLoss()
{
    return this->_annualHeatLoss;
}

void InsulatedTankOutput::setHeatLoss(double heatLoss)
{
    this->_heatLoss = heatLoss;
}

void InsulatedTankOutput::setAnnualHeatLoss(double annualHeatLoss)
{
    this->_annualHeatLoss = annualHeatLoss;
}