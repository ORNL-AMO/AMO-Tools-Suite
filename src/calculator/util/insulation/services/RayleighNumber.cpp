#include "calculator/util/insulation/services/RayleighNumber.h"
#include <cmath>

double RayleighNumber::calculate()
{
    return 9.81 * this->_expCoefficient * std::abs(this->_surfaceTemperature - this->_ambientTemperature) * std::pow(this->_diameter, 3) / (this->_kinematicViscosity * this->_alpha);
}