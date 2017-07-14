
/**
 * @file
 * @brief Contains the implementation of the humidity ratio calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/HumidityRatio.h"
#include <cmath>
//
//double HumidityRatio::getSaturationPressure() {
//    const double C1 = -5674.5359;
//    const double C2 = -0.51523058;
//    const double C3 = -0.009677843;
//    const double C4 = 0.00000062215701;
//    const double C5 = 2.0747825 * pow(10,-9);
//    const double C6 = -9.0484024 * pow(10,-13);
//    const double C7 = 4.1635019;
//    const double C8 = -5800.2206;
//    const double C9 = -5.516256;
//    const double C10 = -0.048640239;
//    const double C11 = 0.000041764768;
//    const double C12 = -0.000000014452093;
//    const double C13 = 6.5459673;
//    const double absoluteTempConversion = 459.67;
//    const double kelvinConversion = 0.555556;
//    double temperatureInKelvins = ((this->inputAirTemp_) + absoluteTempConversion) * kelvinConversion;
//
//    if ((this->inputAirTemp))
//    this->excessAir_ = (100 * 8.52381 * ((this->o2FlueGas_)/100)/(2 - 9.52381 * ((this->o2FlueGas_)/100)));
//    return this->excessAir_;
//}