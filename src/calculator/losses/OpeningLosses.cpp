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
        area = (diameter * width) / 144;
    }

    const double hlRad = emissivity * stephenBoltzman * (std::pow(insideTemperature + 460, 4) -
                          std::pow(ambientTemperature + 460, 4)) * area;

    heatLoss = hlRad * viewFactor * percentTimeOpen / 100;
    return heatLoss;
}

double OpeningLosses::calculateViewFactor(OpeningLosses::OpeningShape const shape, const double thickness,
                                          const double diameter)
{
    if (shape != OpeningLosses::OpeningShape::CIRCULAR) throw std::runtime_error("OpeningShape must be circular");

    if (!diameter) return 0;
    const double thicknessRatio = (!thickness) ? 6.1 : diameter / thickness;
    if (thicknessRatio > 6) return viewFactorEquations[1](6);
    if (thicknessRatio < 0.1) return viewFactorEquations[0](0.1) * thicknessRatio / 0.1;
    if (thicknessRatio < 1) return viewFactorEquations[0](thicknessRatio);
    return viewFactorEquations[1](thicknessRatio);
}

double OpeningLosses::calculateViewFactor(OpeningLosses::OpeningShape const shape, const double thickness,
                                          const double length, const double height)
{
    if (shape != OpeningLosses::OpeningShape::RECTANGULAR) throw std::runtime_error("OpeningShape must be rectangular");

    double thicknessRatio, lateralDimensionRatio; //= (height > length) ? height / length : length / height;
	if (!length || !height) return 0;
	if (height > length) {
        lateralDimensionRatio = height / length;
        thicknessRatio = (!thickness) ? 6.1 : length / thickness;
    } else {
        lateralDimensionRatio = length / height;
        thicknessRatio = (!thickness) ? 6.1 : height / thickness;
    }




}
