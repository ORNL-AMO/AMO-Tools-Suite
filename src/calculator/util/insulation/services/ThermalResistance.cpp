#include "calculator/util/insulation/services/ThermalResistance.h"
#include <cmath>

double ThermalResistance::calculate()
{
    return this->_diameterA * std::log(this->_diameterB / this->_diameterC) / (2 * this->_thermalConductivity);
}