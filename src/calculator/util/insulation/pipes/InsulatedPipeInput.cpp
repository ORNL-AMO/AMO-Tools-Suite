#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include <cmath>

int InsulatedPipeInput::getOperatingHours()
{
    return this->_operatingHours;
}

double InsulatedPipeInput::getLength()
{
    return this->_length;
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

double InsulatedPipeInput::getNaturalGasSystemEfficiency()
{
    return this->_naturalGasSystemEfficiency;
}

double InsulatedPipeInput::getInsulationThickness()
{
    return this->_insulationThickness;
}

double InsulatedPipeInput::getPipeEmissivity()
{
    return this->_pipeEmissivity;
}

double InsulatedPipeInput::getInsulationEmissivity()
{
    return this->_insulationEmissivity;
}

double InsulatedPipeInput::getJacketEmissivity()
{
    return this->_jacketEmissivity;
}

const double[] getPipeMaterialCoefficients()
{
    return this->_pipeMaterialCoefficients;
}

const double[] getInsulationMaterialCoefficients()
{
    return this->_insulationMaterialCoefficients;
}

AirProperties InsulatedPipeInput::getAirProperties()
{
    return this->_airProperties;
}

double InsulatedPipeInput::lookupAirProperty(int property, int n)
{
    return this->_airProperties[property][n];
}

double InsulatedPipeInput::lookupPipeProperty(int x, int y)
{
    return this->_pipeProperties[x][y];
}

double InsulatedPipeInput::lookupInsulationProperty(int x, int y)
{
    return this->_insulationProperties[x][y];
}

/*
    air properties array [x][y]
    x = material in this order
    [specificHeat_air, viscosity, kinematic viscosity, thermCond, Alpha, Prandtl]
    y = order of equation (T^0, T^1, T^2, etc.)
*/
const double InsulatedPipeInput::_airProperties[][] = {

    {3.03724e-13, -1.1132e-9, 1.44382e-6, -0.000565339, 1.07223839},     // specificHeat
    {-1.586e-10, 5.115e-7, -7.246e-4, 7.978e-1, -1.850},                 // viscosity
    {2.25852e-11, -8.32093e-8, 0.000172673, 0.01063728, -0.76108359},    // kinViscosity
    {3.17176E-11, -5.90229E-08, 4.58531E-06, 0.088867888, 0.520072239},  // thermCond
    {1.35569E-10, -3.80588E-07, 0.000446483, -0.035935528, 2.254489164}, // Alpha
    {-2.08438E-13, -1.72787E-11, 8.00624E-07, -0.000694606, 0.845781218} // Prandtl

};

/*
    pipe properties array [x][y]
    x = material in this order
    [carbon steel, copper, stainless steel]
    y = order of equation (T^0, T^1, T^2, etc.)
*/
// const double InsulatedPipeInput::_pipeProperties[][] = {
//     {7.9e1, 4.48114e2, 1.05921e1},
//     {-5.10833e-2, -2.28992e-1, 1.28270e-1},
//     {3.67044e-19, 2.90813e-4, -1.93992e-4},
//     {2.08333e-9, -1.66247e-7, 1.06090e-7},
//     {0, 0, 0},
// };

// /*
//     insulation properties array [x][y]
//     x = material in this order
//     [calcium silicate, fiber glass, mineral fiber, glass and resin, cellular glass, polystyrene, polyolefin, flexible aerogel]
//     y = order of equation (T^0, T^1, T^2, etc.)
// */
// const double InsulatedPipeInput::_insulationProperties[][] = {
//     {0.07333604, 0.006729488, 1.131348303, 0.467788289, 0.314093419, -15.8404154, 108.4294544, 0.008307081},
//     {-0.000224881, 0, -0.011562712, 0.005220797, -0.003524638, 0.210773437, -1.446699957, 6.54415e-5},
//     {7.36555e-7, 8.6328e-7, 4.44951e-5, -2.02956e-5, 1.59039e-5, -0.001050362, 0.007230837, -1.17653e-7},
//     {-7.46414e-10, -2.02822e-9, -7.42824e-8, 3.45583e-8, -3.02553e-8, 2.32707e-6, -1.60433e-5, 1.04141e-10},
//     {3.15711e-13, 1.57526e-12, 4.61278e-11, -2.11005e-11, 2.15612e-11, -1.93278e-9, 1.33333e-8, 7.57576e-14},
// };

// /*
//     emissivity lookup
//     list of default jacket materials and corresponding emissivities
// */
// const double InsulatedPipeInput::_jacketMaterials[] = {
//     0,    // _None
//     0.9,  // All Service Jacket
//     0.5,  // Aluminum Paint
//     0.04, // Aluminum, new, bright
//     0.1,  // Aluminum, oxidized
//     0.9,  // Canvas
//     0.9,  // Colored Mastics
//     0.6,  // Copper, pure
//     0.1,  // Galvanized Steel
//     0.8,  // Iron
//     0.8,  // Painted Metal
//     0.9,  // PVC Jacketing
//     0.9,  // Roofing felt and black mastics
//     0.3,  // Stainless Steel, dull
//     0.13, // Stainless Steel, new
//     0.8   // Steel
// };

// /*
//     emissivity lookup
//     list of default pipe base materials and corresponding emissivities
// */
// const double InsulatedPipeInput::_pipeBaseMaterials[] = {
//     0.8000, // Carbon Steel
//     0.6000, // Copper
//     0.3000  // Stainless Steel
// };