/**
 * @file
 * @brief Contains the implementation of the opening leakage losses calculations.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/losses/OpeningLosses.h"

double OpeningLosses::getHeatLoss() {
    const double pi = 3.141592653589793238463;
    const double stephenBoltzman = 0.1713 * pow(10, -8);
    double area;

    if ( openingShape_ == OpeningShape::CIRCULAR ) {
        const double d = diameter_ / 12;
        area = pi * (d / 2) * (d / 2);
    } else {
        area = (diameter_ * width_) / 144;
    }

    const double hlRad = emissivity_ * stephenBoltzman * (pow(insideTemperature_ + 460, 4) -
                          pow(ambientTemperature_ + 460, 4)) * area;

    heatLoss_ = hlRad * viewFactor_ * percentTimeOpen_ / 100;
    return heatLoss_;
}