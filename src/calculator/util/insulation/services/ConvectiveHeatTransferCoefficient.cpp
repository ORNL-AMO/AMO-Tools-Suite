#include "calculator/util/insulation/services/ConvectiveHeatTransferCoefficient.h"

double ConvectiveHeatTransferCoefficient::calculate()
{
    return this->_nusselt * this->_airConductivity / this->_diameter;
}