#include "calculator/util/insulation/services/RadiativeHeatTransferCoefficient.h"
#include <cmath>

double RadiativeHeatTransferCoefficient::calculate()
{
    const c = 0.00000005670373;
    return c * this->_emissivity * (std::pow(this->_surfaceTemperature, 4) - std::pow(this->_ambientTemperature, 4)) / (this->_surfaceTemperature - this->_ambientTemperature);
}