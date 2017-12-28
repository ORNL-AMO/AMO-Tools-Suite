/**
 * @brief Contains the definition of functions of OptimalMotorCurrent class.
 *      calculate(): Calculates the Optimal Motor Current
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <array>
#include "calculator/motor/OptimalMotorCurrent.h"
#include "calculator/util/CurveFitVal.h"
#include "calculator/motor/EstimateFLA.h"

double OptimalMotorCurrent::calculate() {

    EstimateFLA estimateFLA(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,specifiedEfficiency, ratedVoltage);
    const std::array<double, 6> plValues = estimateFLA.calculate();

    // Adjustment based on the measured Voltage/ Field Voltage
//    double temp_fullLoadAmps = plValues[4];
//    for (int i = 0; i < 6; i++) {
//        plValues[i] = plValues[i]*((((fieldVoltage/ratedVoltage)-1)*(1+(-2*(0.25*i))))+1);
//    }
    if (loadFactor < 0.251) {
        CurveFitVal cfv({0, .25, .50}, {plValues[0], plValues[1], plValues[2]}, 2, loadFactor);
        return cfv.calculate();
    } else if (loadFactor < 1.251) {
        CurveFitVal cfv({.25, .50, .75, 1.00, 1.25}, {plValues[1], plValues[2], plValues[3], plValues[4], plValues[5]}, 4, loadFactor);
        return cfv.calculate();
    }
    if (loadFactor > 1.5) {
        loadFactor = 1.5;
    }
    return CurveFitVal({.75, 1.00, 1.25}, {plValues[3], plValues[4], plValues[5]}, 2, loadFactor).calculate();
}
