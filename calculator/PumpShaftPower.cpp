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
        // Calculate using the sheet
    }
    return pumpShaftPower_;
}