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
    if (loadFactor_ > 1.5) loadFactor_ = 1.5;

    EstimateFLA estimateFLA(motorRatedPower_, motorRPM_, lineFrequency_, efficiencyClass_,specifiedEfficiency_, ratedVoltage_ );
    const std::array<double, 6> plValues = estimateFLA.calculate();

    /* Adjustment based on the measured Voltage/ Field Voltage
    double temp_fullLoadAmps = plValues[4];
    for (int i = 0; i < 6; i++) {
        plValues[i] = plValues[i]*((((fieldVoltage/ratedVoltage)-1)*(1+(-2*(0.25*i))))+1);
    }*/
    if (loadFactor_ < 0.25) {
        double xCoord_[3] = {0, .25, .50};
        double yCoord_[3] = {plValues[0], plValues[1], plValues[2]};
        CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor_);
        motorCurrent_ = cfv.calculate();
    } else if (loadFactor_ > 0.25 && loadFactor_ <= 1.25) {
        double xCoord_[5] = {.25, .50, .75, 1.00, 1.25};
        double yCoord_[5] = {plValues[1], plValues[2], plValues[3], plValues[4], plValues[5]};
        CurveFitVal cfv(5, xCoord_, yCoord_, 4, loadFactor_);
        motorCurrent_ = cfv.calculate();
    } else if (loadFactor_ > 1.25 && loadFactor_ <= 1.50) {
        double xCoord_[3] = {.75, 1.00, 1.25};
        double yCoord_[3] = {plValues[3], plValues[4], plValues[5]};
        CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor_);
        motorCurrent_ = cfv.calculate();
    }
    return motorCurrent_;
}
