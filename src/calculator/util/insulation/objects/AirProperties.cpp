#include "calculator/util/insulation/objects/AirProperties.h"
#include <cmath>

double AirProperties::getConductivity()
{
    return this->_conductivity;
}

double AirProperties::getViscosity()
{
    return this->_viscosity;
}

double AirProperties::getPrandtl()
{
    return this->_prandtl;
}

double AirProperties::getExpansionCoefficient()
{
    return this->_expansionCoefficient;
}

double AirProperties::getDensity()
{
    return this->_density;
}

double AirProperties::getKinViscosity()
{
    return this->_kinViscosity;
}

double AirProperties::getSpecificHeat()
{
    return this->_specificHeat;
}

double AirProperties::getAlpha()
{
    return this->_alpha;
}

double AirProperties::getReynolds()
{
    return this->_reynolds;
}

double AirProperties::getRayleigh()
{
    return this->_rayleigh;
}

double AirProperties::setConductivity(double conductivity)
{
    this->_conductivity = conductivity;
}

double AirProperties::setViscosity(double viscosity)
{
    this->_viscosity = viscosity;
}

double AirProperties::setPrandtl(double prandtl)
{
    this->_prandtl = prandtl;
}

double AirProperties::setExpansionCoefficient(double expansionCoefficient)
{
    this->_expansionCoefficient = expansionCoefficient;
}

double AirProperties::setDensity(double density)
{
    this->_desnity = density;
}

double AirProperties::setKinViscosity(double kinViscosity)
{
    this->_kinViscosity = kinViscosity
}

double AirProperties::setSpecificHeat(double specificHeat)
{
    this->_specificHeat = specificHeat;
}

double AirProperties::setAlpha(double alpha)
{
    this->_alpha = alpha;
}

double AirProperties::setReynolds(double reynolds)
{
    this->_reynolds = reynolds;
}

double AirProperties::setRayleigh(double rayleigh)
{
    this->_rayleigh = rayleigh;
}