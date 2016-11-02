//
// Created by Accawi, Gina K. on 8/19/16.
//
#include "AnnualCost.h"

double AnnualCost::calculate() {
    /*
     * Calculate Annual energy cost
     * Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)
     * 1000 in above equation is not used in excel.
     */
    annualEnergyCost_ = annualEnergy_ * kwhRate_;
    return annualEnergyCost_;
}
