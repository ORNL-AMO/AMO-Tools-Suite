//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"
#include "MotorEfficiency.h"
#include "MotorPower.h"
#include "MotorCurrent.h"
#include "MotorPowerFactor.h"

double MotorShaftPower::calculate() {
    tempLoadFraction_ = 0.01;
    while (true) {
        MotorCurrent motorCurrent(motorRatedPower_, motorRPM_, Motor::EfficiencyClass::ENERGY_EFFICIENT,
                                  tempLoadFraction_);
        current = motorCurrent.calculate();
        MotorEfficiency motorEfficiency(motorRPM_, Motor::EfficiencyClass::ENERGY_EFFICIENT, motorRatedPower_,
                                        motorMeasuredPower_, tempLoadFraction_);
        eff = motorEfficiency.calculate();
        MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(460, current, pf);
        power = motorPower.calculate();
        if (power > 80 || tempLoadFraction_ > 1.5) {
            powerE2 = power;
            lf2 = tempLoadFraction_;
            eff2 = eff;
            pf2 = pf;
            break;
        } else {
            powerE1 = power;
            lf1 = tempLoadFraction_;
            eff1 = eff;
            pf1 = pf;
            tempLoadFraction_ += 0.01;
        }
    }
    double motorPowerdiff_ = powerE2 - powerE1;
    double measuredMotorPowerdiff_ = motorMeasuredPower_ - powerE1;
    double fractionalIndex_ = lf1 + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    eff = eff1 + 100*(fractionalIndex_-lf1)*(eff2-eff1);
    pf = pf1 + 100*(fractionalIndex_-lf1)*(pf2-pf1);
    double motorShaftPower_ = motorMeasuredPower_ * eff;
    return motorShaftPower_;
}

double MotorShaftPower::calculateCurrent() {
    return current;
}

double MotorShaftPower::calculateEfficiency() {
    return eff;
}

double MotorShaftPower::calculatePowerFactor() {
    return pf;
}

double MotorShaftPower::calculateElectricPower() {
    return power;
}
