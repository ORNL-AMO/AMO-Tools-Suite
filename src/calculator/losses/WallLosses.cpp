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
    double boltzman = 0.1713 * pow(10, -8);
    double d = 24.0;
    double d1 = 1/d;
    double sqrt_wv = 1 + (1.227 * this->windVelocity_);
    double hl_conv1 = this->conditionFactor_ * pow(d1, 0.2);
    double hl_conv2 = pow((1.0 / ((this->ambientTemperature_  + this->surfaceTemperature_) / 2.0)), 0.181);
    double hl_conv3 = pow((this->surfaceTemperature_ - this->ambientTemperature_), 0.266);
    double hl_conv4 = sqrt(sqrt_wv);
    double hl_conv = (hl_conv1 * hl_conv2 * hl_conv3 * hl_conv4) * this->surfaceArea_ * (this->surfaceTemperature_ - this->ambientTemperature_);
    double hl_rad1 = pow((this->surfaceTemperature_ + RAD_CONSTANT), 4.0);
    double hl_rad2 = pow((this->ambientTemperature_ + RAD_CONSTANT), 4.0);
    double hl_rad3 = hl_rad1 - hl_rad2;
    double hl_rad = this->surfaceEmissivity_ * boltzman * hl_rad3 * this->surfaceArea_;
    return hl_conv + hl_rad;
}