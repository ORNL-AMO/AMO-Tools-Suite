/**
 * @brief Contains the definition of functions of MotorEfficiency class.
 *      calculate(): Calculates the motor efficiency given a load factor and other parameters.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/util/CurveFitVal.h"
#include "calculator/motor/MotorEfficiency25.h"

double MotorEfficiency::calculate() {

    if (efficiencyClass == Motor::EfficiencyClass::ENERGY_EFFICIENT) {
        MotorEfficiency25 motorEfficiency25(efficiencyClass, motorRatedPower, motorRpm, lineFrequency);
        motorEfficiency = motorEfficiency25.calculate();

    } else if (efficiencyClass == Motor::EfficiencyClass::STANDARD) {
        MotorEfficiency25 motorEfficiency25(efficiencyClass, motorRatedPower, motorRpm, lineFrequency);
        motorEfficiency = motorEfficiency25.calculate();
    } else if (efficiencyClass == Motor::EfficiencyClass::SPECIFIED) {
        /**
         * For specified efficiency, you have to first choose the nominal efficiency.
         */
        MotorEfficiency25 eeMotorEfficiency(Motor::EfficiencyClass::ENERGY_EFFICIENT, motorRatedPower, motorRpm,
                                            lineFrequency);
        std::vector<double> motorEfficiencyE_ = eeMotorEfficiency.calculate();
        motorEfficiency = eeMotorEfficiency.calculate();
        MotorEfficiency25 seMotorEfficiency(Motor::EfficiencyClass::STANDARD, motorRatedPower, motorRpm,
                                            lineFrequency);
        std::vector<double> motorEfficiencyS_ = seMotorEfficiency.calculate();


        if (fabs(motorEfficiencyE_[3] - specifiedEfficiency) > fabs(motorEfficiencyS_[3] - specifiedEfficiency)) {
            //SE chosen
            double C = specifiedEfficiency / motorEfficiencyS_[3];
            for (std::size_t i = 0; i < 5; ++i) {
                motorEfficiency[i] = motorEfficiencyS_[i] * C;
            }
        } else { // EE chosen
            specifiedEfficiency = specifiedEfficiency / 100;
            double C = specifiedEfficiency / motorEfficiencyE_[3];


            for (std::size_t i = 0; i < 5; ++i) {
                motorEfficiency[i] = motorEfficiencyE_[i] * C;

            }
        }
    }

    /**
     * Calculating the 1% interval values based on the load factor
     * 0 - 25
     * 1. Using the 0% and 25% kW loss values, develop a linear table of loss by 1% load
     * Equation: kWloss (X) = kWloss (0) + X * (kWloss(25) - kWloss(0))/25      where X = 0,1,2,3…..25
     * 2. Assemble an array of shaft power from 0 to 25
     * Equation: kW shaft (X) = rated hp *0.746 * (X / 100)
     * Assemble an array of kWe (input electric power
     * Equation: kWe(X) = kWloss(x) + kWshaft(X)
     * Calculate efficiency
     * Equation: Eff(X) = kW shaft (X) / kWe (X)
     */

    /**
     * Setting up kWloss0 and kWloss25
     * Make sure motoEfficiency is in decimal rather %.
     * E.g.: 0.92 is correct, 92 is wrong.
     */
    double kWloss25 = ((1 / motorEfficiency[0]) - 1) * motorRatedPower * 0.746 * 0.25;
    kWloss0 = 0.8 * kWloss25;

    if (loadFactor > 1.5) loadFactor = 1.5;

    if (loadFactor < 0.25 || loadFactor == 0.25 || std::abs(loadFactor - 0.25) < 0.001) {
        double kWloss_ = kWloss0 + loadFactor * 100 * (kWloss25 - kWloss0) / 25;
        double kWshaft_ = motorRatedPower * 0.746 * (loadFactor); // Make sure motorRatedPower is in hp
        double kWe_ = kWloss_ + kWshaft_; // Input electric power
        motorEff = kWshaft_ / kWe_; //Final efficiency calculation
    }
        /**
         * 26 - 125
         * Fitting tabular, 25% interval, motor efficiency data to assemble an overall curve with 1% interval data from 26 to 150%
         * 25% load interval efficiency values come from "Adjusting 25 percent arrays for specified efficiency"
         * Pick the 25,50,75,100,and 125% motor efficiency values and do a 4th order polynomial fit.
         * Use the fit coefficients to popluate, in 1% load intervals, from 26 to 125% load
         */

    else if ((loadFactor < 1.25 || loadFactor == 1.25 || std::abs(loadFactor - 1.25) < 0.001) &&
             loadFactor > 0.25) {
        double xCoord_[5] = {.25, .50, .75, 1.00, 1.25};
        double yCoord_[5] = {motorEfficiency[0], motorEfficiency[1], motorEfficiency[2], motorEfficiency[3],
                             motorEfficiency[4]};
        CurveFitVal cfv(5, xCoord_, yCoord_, 4, loadFactor);
        motorEff = cfv.calculate();
    }
        /**
         * 126 - 150
         * Pick the 75, 100, and 125% motor efficiency values and do a 2nd order polynomial fit
         * Use the fit coefficients to populate, in 1% load intervals, the current range from 126 to 150% load
         */
    else if ((loadFactor < 1.50 || loadFactor == 1.50 || std::abs(loadFactor - 1.50) < 0.001) &&
             loadFactor > 1.25) {
        double xCoord_[3] = {.75, 1.00, 1.25};
        double yCoord_[3] = {motorEfficiency[2], motorEfficiency[3], motorEfficiency[4]};
        CurveFitVal cfv(3, xCoord_, yCoord_, 2, loadFactor);
        motorEff = cfv.calculate();
    }

    return motorEff;
}
