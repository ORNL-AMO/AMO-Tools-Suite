/**
 * @file
 * @brief Contains the implementation of the flue gas loss calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/losses/FlueGas.h"

double FlueGas::getHeatLoss() {
//    double t_furnace = this->specificGravity_ * ( 520.0 / (460.0 + this->leakageTemperature_));
//    double cfh = 1655.0 * 0.8052 * (this->openingArea_ * 144.0) * pow((this->furnaceDraft_ / t_furnace), 0.5);
//    double scfh = cfh * ( 520.0 / ( 460.0 + this->leakageTemperature_));
//    double specific_heat_gasses_avg_temperature = (this->leakageTemperature_ + 60.0) / 2.0;
    return 2850767;
}