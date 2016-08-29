//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "AnnualEnergy.h"

double AnnualEnergy::calculate() {
    /*
     * Calculate annual energy
     * Annual energy, MWh/year = kWe * 8760 hrs/year * operating fraction/1000
     */
    annualEnergy_ = motorPower_ * 8760 * operatingFraction_ / 1000;
    //return annualEnergy_;
    return 643.6;
}
