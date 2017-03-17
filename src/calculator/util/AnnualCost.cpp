/**
 * @brief Contains the definition of functions of AnnualCost class.
 *      calculate(): Calculates the annual energy cost
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "calculator/util/AnnualCost.h"

/**
 * Calculate Annual energy cost.
 * Annual energy cost = MWh/year * 1000 * energy cost rate ($/kWh)
 * 1000 in above equation is not used in excel version of the tool.
 *
 * @return Annual Energy Cost
 */
double AnnualCost::calculate() {
    annualEnergyCost_ = annualEnergy_ * kwhRate_;
    return annualEnergyCost_;
}
