/**
 * @brief Contains the definition of functions of MotorCurrent class.
 *      calculate(): Calculates the motor current for a given value of load factor.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <array>
#include "calculator/motor/MotorCurrent.h"
#include "calculator/util/CurveFitVal.h"
#include "calculator/motor/EstimateFLA.h"

/**
 * Calculates the motor current for a given value of load factor.
 * Given the load% calculate the Amps.
 * Pick the 0,25,50% motor current values and do a 2nd order polynomial fit.
 * Use the fit coefficients to populate, in 1% load intervals, the current range from 0 to 25% load
 *
 * Pick the 25,50,75,100,and 125% motor current values and do a 4th order polynomial fit.
 * Use the fit coefficients to popluate, in 1% load intervals, from 26 to 125% load
 *
 * Pick the 75, 100, and 125% motor current values and do a 2nd order polynomial fit.
 * Use the fit coefficients to populate, in 1% load intervals, the current range from 126 to 150% load
 * @return motor current
 */
double MotorCurrent::calculate() {
    if (loadFactor > 1.5) loadFactor = 1.5;

    EstimateFLA estimateFLA(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency,
                            ratedVoltage);
    std::array<double, 6> plValues = estimateFLA.calculate();
    estimatedFLA = estimateFLA.getEstimatedFLA();

    // Adjustment based on the rated voltage and Adjustment based on the specified FLA
	auto const tempFLA = plValues[4];
    for (auto & val : plValues) {
        val *= 460 / ratedVoltage;
        val *= fullLoadAmps / tempFLA;
    }

    if (loadFactor <= 0.25 || std::abs(loadFactor - 0.25) < 0.001) {
        motorCurrent = CurveFitVal({0, 0.25, 0.5}, {plValues[0], plValues[1], plValues[2]}, 2, loadFactor).calculate();
    } else if (loadFactor > 0.25 && (loadFactor <= 1.25 || std::abs(loadFactor - 1.25) < 0.001)) {
        CurveFitVal cfv({0.25, 0.5, 0.75, 1, 1.25}, {plValues[1], plValues[2], plValues[3], plValues[4], plValues[5]}, 4, loadFactor);
        motorCurrent = cfv.calculate();
    } else if (loadFactor > 1.25 && (loadFactor <= 1.50 || std::abs(loadFactor - 1.50) < 0.001)) {
        CurveFitVal cfv({.75, 1.00, 1.25}, {plValues[3], plValues[4], plValues[5]}, 2, loadFactor);
        motorCurrent = cfv.calculate();
    }
    return motorCurrent;

}
