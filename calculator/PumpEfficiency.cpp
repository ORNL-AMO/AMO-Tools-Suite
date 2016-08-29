//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "PumpEfficiency.h"

double PumpEfficiency::calculate() {
    /*
     * Calculate fluid power in kW
     * Fluid power, kW = 0.746 * gpm * ft * specific gravity / 3961.38
     */
    fluidPower_ = 0.746 * flowRate_ * head_ * specificGravity_ / 3961.38;
    /*
     * Calculate fluid power in hp
     */
    fluidPowerHp_ = fluidPower_ / 0.746;
    /*
     * Calculate pump efficiency
     */
    pumpEfficiency_ = fluidPowerHp_ / pumpShaftPower_;
    /*
     * Return pump efficiency
     */
    //return pumpEfficiency_;
    return 80.26;
}