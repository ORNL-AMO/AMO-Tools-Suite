//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorPowerFactor.h"
#include "MotorEfficiency.h"

double MotorPowerFactor::calculate() {
    double motorPowerFactor_ = 0.0;

    if (loadFactor_ == 0.0 || std::abs(loadFactor_ - 0.0) < 0.001) {
        /*
         * When the loadFactor is 0
         *  The powerFactor is calculated from the Motor KW loss and Motor kW Input development.
         *  MotorKWloss (0) = 0.8 * MotorKWloss (25)
         *  MotorKWInput (0) = MotorKWloss (0)
         *  motorkVA (0) = 460 * sqrt(3) * motorCurrent_ (0)/1000;
         *  MotorPowerFactor (0) = motorKwInput (0) / motorkVA (0);
         */
        MotorEfficiency motorEfficiency(lineFrequency_, motorRpm_, efficiencyClass_, specifiedEfficiency_,
                                        motorRatedPower_, 0.25);
        motorEfficiency.calculate();
        motorKwInput = motorEfficiency.getKWloss0();
        motorkVA = 460 * sqrt(3) * motorCurrent_ / 1000;
        motorPowerFactor_ = motorKwInput / motorkVA;
    } else {
        /*
         *  Make sure the loadfactor comes not in %.
         *  pf (X) = [(X/100) * rated hp * 0.746] / [Amps (X) * Eff (X) * Rated Voltage * Square root (3) / 1000]
         */
        motorPowerFactor_ = (loadFactor_ * motorRatedPower_ * 0.746) /
                            (motorCurrent_ * motorEfficiency_ * ratedVoltage_ * sqrt(3) / 1000);
    }
    return motorPowerFactor_;

}
