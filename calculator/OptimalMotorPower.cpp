//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalMotorPower.h"
#include "OptimalMotorCurrent.h"


#include <iostream>
using namespace std;

double OptimalMotorPower::calculate() {
    double tempLoadFraction_ = 0.01;
    while (true) {
        OptimalMotorCurrent optimalMotorCurrent(motorRatedPower_, motorRPM_, lineFrequency_, efficiencyClass_,
                                                specifiedEfficiency_, tempLoadFraction_, ratedVoltage_, fieldVoltage_,
                                                fullLoadAmps_);
        current = optimalMotorCurrent.calculate();

        MotorEfficiency motorEfficiency(motorRPM_, efficiencyClass_, specifiedEfficiency_, motorRatedPower_,
                                        tempLoadFraction_);
        eff = motorEfficiency.calculate();

        MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(fieldVoltage_, current, pf);
        power = motorPower.calculate();
        tempMsp = power * eff;
        cout << tempLoadFraction_ << ":" << current << ":" << eff << ":" <<pf << ":" << power << ":" << tempMsp << ":" << optimalMotorShaftPower_<< endl;
        if (tempMsp > optimalMotorShaftPower_ || tempLoadFraction_ > 1.5) {
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
    double measuredMspdiff_ = optimalMotorShaftPower_ - tempMsp2;
    double fractionalIndex_ = lf1 + ((measuredMspdiff_ / motorMspdiff_) / 100);
    cout << "pf1: " << lf1 << endl;
    cout << "pf2: " << lf2 << endl;
    /*
     * Linear Interpolation of values
     */
    double adjCurrent1 = (((fieldVoltage_ / ratedVoltage_) - 1) * (1 - (2 * lf1)) + 1) * current1;
    double adjCurrent2 = (((fieldVoltage_ / ratedVoltage_) - 1) * (1 - (2 * lf2)) + 1) * current2;
    current = adjCurrent1 + 100 * (fractionalIndex_ - lf1) * (adjCurrent2 - adjCurrent1);
    //current = current1 + 100 * (fractionalIndex_ - lf1) * (current2 - current1);
    eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
    power = powerE1 + 100 * (fractionalIndex_ - lf1) * (powerE2 - powerE1);
    pf = power / (current * fieldVoltage_ * sqrt(3) / 1000);

}
