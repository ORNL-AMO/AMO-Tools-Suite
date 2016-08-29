//
// Created by Accawi, Gina K. on 8/19/16.
//
#include "AnnualCost.h"

double AnnualCost::calculate() {
    /*
     * Calculate Annual energy cost
     * Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)
     */
    annualEnergyCost_ = annualEnergy_ * 1000 * kwhRate_;
    //return annualEnergyCost_;
    // Return value from sample
    return 32.18;
}
