/**
 * @brief Contains the definition of functions of AnnualEnergy class.
 *      calculate(): Calculates the annual energy
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "calculator/AnnualEnergy.h"

/**
 * Calculates annual energy
 * Annual energy, MWh/year = kWe * 8760 hrs/year * operating fraction/1000
 * @return Annual Energy
 */
double AnnualEnergy::calculate() {
    annualEnergy_ = fieldPower_ * 8760 * operatingFraction_ / 1000;
    return annualEnergy_;
}
