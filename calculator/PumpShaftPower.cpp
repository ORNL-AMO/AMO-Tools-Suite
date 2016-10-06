//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "PumpShaftPower.h"

double PumpShaftPower::calculate() {
    /*
     * 2a	If a belt drive is specified, calculate the pump shaft power
     * 2b	If direct drive, motor shaft power = pump shaft power
     */
    if (drive_ == Pump::Drive::DIRECT_DRIVE) {
        pumpShaftPower_ = motorShaftPower_;
    } else {
        // Belt Drive scenario
        double BLM = motorShaftPower_ * ((0.68759 * exp((motorShaftPower_ / 0.746) * (-0.019791)) +
                                          3.7558 * exp((motorShaftPower_ / 0.746) * (-0.21507)) + 3.9963) / 100);
        // motorShaftPower_ is already in hp , so make BLM in hp
        BLM = BLM / 0.746;
        double motorSheavePowerRatio = motorShaftPower_ / (motorShaftPower_ - BLM);
        pumpShaftPower_ = motorShaftPower_ - BLM;
    }
    return pumpShaftPower_;
}