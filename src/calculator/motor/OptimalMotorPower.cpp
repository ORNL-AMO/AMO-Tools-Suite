/**
 * @brief Contains the definition of functions of OptimalMotorPower class.
 *      calculate(): Calculates the Optimal Motor Power
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/motor/OptimalMotorPower.h"
#include "calculator/motor/OptimalMotorCurrent.h"
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/motor/MotorPower.h"

double OptimalMotorPower::calculate() {
    double tempLoadFraction_ = 0.00;
    double mspkW = 0.0;
    while (true) {
        OptimalMotorCurrent optimalMotorCurrent(motorRatedPower_, motorRPM_, lineFrequency_, optimalEfficiencyClass_,
                                                specifiedEfficiency_, tempLoadFraction_, ratedVoltage_, fieldVoltage_,
                                                fullLoadAmps_);
        current = optimalMotorCurrent.calculate();
        //Adjustment to current based on measured Voltage
        current = current * ((((fieldVoltage_ / ratedVoltage_) - 1) * (1 + (-2 * tempLoadFraction_))) + 1);
        MotorEfficiency motorEfficiency(lineFrequency_, motorRPM_, optimalEfficiencyClass_, specifiedEfficiency_,
                                        motorRatedPower_,
                                        tempLoadFraction_);
        eff = motorEfficiency.calculate();
        //Similar to motorpowerfactor in existing case instead of ratedVoltage
        MotorPowerFactor motorPowerFactor(lineFrequency_,motorRPM_, efficiencyClass_, specifiedEfficiency_,  motorRatedPower_, tempLoadFraction_, current, eff, fieldVoltage_);
        pf = motorPowerFactor.calculate();

        MotorPower motorPower(fieldVoltage_, current, pf);
        power = motorPower.calculate();
        tempMsp = power * eff;
        // Converting to KW for matching purpose.
        //cout << tempLoadFraction << ":" << current << ":" << eff <<":" << pf << ":" << power << ":" << endl;
        mspkW = optimalMotorShaftPower_ * 0.746;

        if (tempMsp > mspkW || tempLoadFraction_ > 1.5) {
            powerE2 = power;
            lf2 = tempLoadFraction_;
            eff2 = eff;
            pf2 = pf;
            current2 = current;
            tempMsp2 = tempMsp;
            break;
        } else {
            powerE1 = power;
            lf1 = tempLoadFraction_;
            eff1 = eff;
            pf1 = pf;
            current1 = current;
            tempMsp1 = tempMsp;
            tempLoadFraction_ += 0.01;
        }
    }
    /*
     * Calculate Fractional Index
     */

    double motorMspdiff_ = tempMsp2 - tempMsp1;
    double measuredMspdiff_ = mspkW - tempMsp1;
    double fractionalIndex_ = lf1 + ((measuredMspdiff_ / motorMspdiff_) / 100);
    /*
     * Linear Interpolation of values
     */
    //double adjCurrent1 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf1)) + 1) * current1;
    //double adjCurrent2 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf2)) + 1) * current2;
    //current = adjCurrent1 + 100 * (fractionalIndex_ - lf1) * (adjCurrent2 - adjCurrent1);
    current = current1 + 100 * (fractionalIndex_ - lf1) * (current2 - current1);
    eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
    power = powerE1 + 100 * (fractionalIndex_ - lf1) * (powerE2 - powerE1);
    pf = power / (current * fieldVoltage_ * sqrt(3) / 1000);
    return 0;
}
