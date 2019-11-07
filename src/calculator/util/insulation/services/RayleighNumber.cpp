#include "calculator/util/insulation/services/RayleighNumber.h"
#include <cmath>

double RayleighNumber::calculate()
{
    double g = 9.81;
    double absTempDifference = std::fabs(this->_surfaceTemperature - this->_ambientTemperature);
    double diameterCubed = std::pow(this->_diameter, 3);
    double kinVisAlpha = this->_kinematicViscosity * this->_alpha;
    double coeff = g * this->_expCoefficient;
    double result = coeff * absTempDifference * diameterCubed / kinVisAlpha;
    return result;
}