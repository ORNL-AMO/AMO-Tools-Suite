//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorCurrent.h"

double MotorCurrent::calculate() {


    /*
     * Given the load% calculate the Amps.
     * Pick the 0,25,50% motor current values and do a 2nd order polynomial fit.
     * Use the fit coefficients to populate, in 1% load intervals, the current range from 0 to 25% load
     *
     * Pick the 25,50,75,100,and 125% motor current values and do a 4th order polynomial fit.
     * Use the fit coefficients to popluate, in 1% load intervals, from 26 to 125% load
     *
     * Pick the 75, 100, and 125% motor current values and do a 2nd order polynomial fit.
     * Use the fit coefficients to populate, in 1% load intervals, the current range from 126 to 150% load
     *
     */
    EstimateFLA estimateFLA(motorRatedPower_, motorRPM_, lineFrequency_, efficiencyClass_,specifiedEfficiency_, ratedVoltage_ );
    std::vector<double> plValues = estimateFLA.calculate();
    estimatedFLA_ = estimateFLA.getEstimatedFLA();

    // Adjustment based on the rated voltage.
    for (int i = 0; i < 6; i++) {
        plValues[i] = plValues[i] * 460 / ratedVoltage_;

    }

    // Adjustment based on the specified FLA
    double temp_fullLoadAmps = plValues[4];
    for (int i = 0; i < 6; i++) {
        plValues[i] = plValues[i]*fullLoadAmps_/temp_fullLoadAmps;
    }
    if (loadFactor_ < 0.25 || loadFactor_ == 0.25 || std::abs(loadFactor_- 0.25) < 0.001) {
            double xCoord_[3] = {0, .25, .50};
            double yCoord_[3] = {plValues[0], plValues[1], plValues[2]};
            CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor_);
            motorCurrent_ = cfv.calculate();

        } else if (loadFactor_ > 0.25 && (loadFactor_ < 1.25 || loadFactor_ == 1.25 || std::abs(loadFactor_- 1.25) < 0.001 )) {
            double xCoord_[5] = {.25, .50, .75, 1.00, 1.25};
            double yCoord_[5] = {plValues[1], plValues[2], plValues[3], plValues[4], plValues[5]};
            CurveFitVal cfv(5, xCoord_, yCoord_, 4, loadFactor_);
            motorCurrent_ = cfv.calculate();
    } else if (loadFactor_ > 1.25 && (loadFactor_ < 1.50 || loadFactor_ == 1.50 || std::abs(loadFactor_- 1.50) < 0.001)) {
        double xCoord_[3] = {.75, 1.00, 1.25};
        double yCoord_[3] = {plValues[3], plValues[4], plValues[5]};
        CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor_);
        motorCurrent_ = cfv.calculate();
    }
    return motorCurrent_;
    //return 125.857;
}
