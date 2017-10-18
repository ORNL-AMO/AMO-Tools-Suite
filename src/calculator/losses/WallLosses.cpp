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
    const double boltzman = 0.1713 * std::pow(10, -8);
    const double sqrt_wv = 1 + (1.277 * windVelocity);
    const double hl_conv1 = conditionFactor * std::pow((1 / 24.0), 0.2);
    const double hl_conv2 = std::pow((1.0 / ((ambientTemperature  + surfaceTemperature) / 2.0)), 0.181);
    const double hl_conv3 = std::pow((surfaceTemperature - ambientTemperature), 0.266);
    const double hl_conv4 = std::sqrt(sqrt_wv);
    const double hl_conv = (hl_conv1 * hl_conv2 * hl_conv3 * hl_conv4) * surfaceArea * (surfaceTemperature - ambientTemperature);
    const double hl_rad1 = std::pow((surfaceTemperature + RAD_CONSTANT), 4.0);
    const double hl_rad2 = std::pow((ambientTemperature + RAD_CONSTANT), 4.0);
    const double hl_rad3 = hl_rad1 - hl_rad2;
    const double hl_rad = surfaceEmissivity * boltzman * hl_rad3 * surfaceArea;
	heatLoss = (hl_conv + hl_rad) * correctionFactor;
    return heatLoss;
}