#include "calculator/util/insulation/services/ReynoldsNumber.h"

double ReynoldsNumber::calculate()
{
    return this->_diameter * this->_windVelocity / this->_kinematicViscosity;
}