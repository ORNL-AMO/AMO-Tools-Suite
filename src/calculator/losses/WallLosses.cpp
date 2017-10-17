/**
 * @file
 * @brief Contains the implementation of the wall leakage losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include <cmath>
#include "calculator/losses/WallLosses.h"

double WallLosses::getHeatLoss() {
    const double boltzman = 0.1713 * pow(10, -8);
    const double d1 = 1 / 24.0;
    double sqrt_wv = 1 + (1.227 * windVelocity);
    double hl_conv1 = conditionFactor * std::pow(d1, 0.2);
    double hl_conv2 = std::pow((1.0 / ((ambientTemperature  + surfaceTemperature) / 2.0)), 0.181);
    double hl_conv3 = std::pow((surfaceTemperature - ambientTemperature), 0.266);
    double hl_conv4 = std::sqrt(sqrt_wv);
    double hl_conv = (hl_conv1 * hl_conv2 * hl_conv3 * hl_conv4) * surfaceArea * (surfaceTemperature - ambientTemperature);
    double hl_rad1 = std::pow((surfaceTemperature + RAD_CONSTANT), 4.0);
    double hl_rad2 = std::pow((ambientTemperature + RAD_CONSTANT), 4.0);
    double hl_rad3 = hl_rad1 - hl_rad2;
    double hl_rad = surfaceEmissivity * boltzman * hl_rad3 * surfaceArea;
	heatLoss = (hl_conv + hl_rad) * correctionFactor;
    return heatLoss;
}