/**
 * @file
 * @brief Contains the implementation of the opening leakage losses calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <stdexcept>
#include "calculator/losses/OpeningLosses.h"

double OpeningLosses::getHeatLoss() {
    const double pi = 3.141592653589793238463;
    const double stephenBoltzman = 0.1713 * std::pow(10, -8);
    double area;

    if ( openingShape == OpeningShape::CIRCULAR ) {
        const double d = diameter / 12;
        area = pi * (d / 2) * (d / 2);
    } else {
        area = (length * width) / 144;
    }

    const double hlRad = emissivity * stephenBoltzman * (std::pow(insideTemperature + 460, 4) -
                          std::pow(ambientTemperature + 460, 4)) * area;

    heatLoss = hlRad * viewFactor * percentTimeOpen / 100;
    return heatLoss;
}

double OpeningLosses::calculateViewFactor(const double thickness, const double diameter)
{
    if (!diameter) return 0;
    const double thicknessRatio = (!thickness) ? 6 : diameter / thickness;
    if (thicknessRatio >= 6) return viewFactorEquations[1](6);
    if (thicknessRatio < 0.1) return viewFactorEquations[0](0.1) * thicknessRatio / 0.1;
    if (thicknessRatio < 1) return viewFactorEquations[0](thicknessRatio);
    return viewFactorEquations[1](thicknessRatio);
}

double OpeningLosses::calculateViewFactor(const double thickness, const double length, const double height)
{
    double thicknessRatio, lateralDimensionRatio;
	if (!length || !height) return 0;
	if (height > length) {
        lateralDimensionRatio = height / length;
        thicknessRatio = (!thickness) ? 6 : length / thickness;
    } else {
        lateralDimensionRatio = length / height;
        thicknessRatio = (!thickness) ? 6 : height / thickness;
    }

    if (thicknessRatio >= 6) {
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorEquations[3](6) + (viewFactorEquations[5](6) - viewFactorEquations[3](6)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorEquations[5](6) + (viewFactorEquations[7](6) - viewFactorEquations[5](6)) * (lateralDimensionRatio - 2) / 8;
        }
        return viewFactorEquations[7](6);
    } else if (thicknessRatio < 1) {
        auto const tr = (thicknessRatio < 0.1) ? 0.1 : thicknessRatio;
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorEquations[2](tr) + (viewFactorEquations[4](tr) - viewFactorEquations[2](tr)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorEquations[4](tr) + (viewFactorEquations[6](tr) - viewFactorEquations[4](tr)) * (lateralDimensionRatio - 2) / 8;
        }
        return viewFactorEquations[6](tr) * thicknessRatio / tr;
    } else {
        if (lateralDimensionRatio >= 1 && lateralDimensionRatio < 2) {
            return viewFactorEquations[3](thicknessRatio) + (viewFactorEquations[5](thicknessRatio) - viewFactorEquations[3](thicknessRatio)) * (lateralDimensionRatio - 1);
        }
        if (lateralDimensionRatio >= 2 && lateralDimensionRatio < 10) {
            return viewFactorEquations[5](thicknessRatio) + (viewFactorEquations[7](thicknessRatio) - viewFactorEquations[5](thicknessRatio)) * (lateralDimensionRatio - 2) / 8;
        }
        return viewFactorEquations[7](thicknessRatio);
    }
}
