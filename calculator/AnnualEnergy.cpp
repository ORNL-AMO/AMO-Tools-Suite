/**
 * @file
 * @brief Calculates the Annual Energy
 *
 * This contains the prototypes for the PSAT results structure
 * including getters and setters for the important fields. Primary
 * importance are methods for calculating the existing and optimal results.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "AnnualEnergy.h"

double AnnualEnergy::calculate() {
    /*
     * Calculate annual energy
     * Annual energy, MWh/year = kWe * 8760 hrs/year * operating fraction/1000
     */
    annualEnergy_ = fieldPower_ * 8760 * operatingFraction_ / 1000;
    return annualEnergy_;
}
