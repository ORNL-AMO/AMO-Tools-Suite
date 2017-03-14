/**
 * @brief Contains the definition of functions of water cooling losses class.
 *
 * Calculates the heat loss due to water cooling.
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include <cmath>
#include "calculator/losses/WaterCoolingLosses.h"

double WaterCoolingLosses::getHeatLoss() {
    double avg_temp = (this->initialTemperature_ + this->outletTemperature_) / 2.0;
    double avg_temp_in_celcius = (avg_temp - 32.0) / 1.8;
    double water_density = 1000 * (1 - (avg_temp_in_celcius+288.9414)/(508929.2*(avg_temp_in_celcius+68.12963))* pow((avg_temp_in_celcius-3.9863), 2));
    double water_density_in_lb_gal = water_density * 0.0083454;
    heatLoss_ = this->flowRate_ * 60.0 * water_density_in_lb_gal * 1.0 * (this->outletTemperature_ - this->initialTemperature_) * this->correctionFactor_;
    return heatLoss_;
}