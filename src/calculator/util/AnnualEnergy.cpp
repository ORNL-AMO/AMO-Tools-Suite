/**
 * @brief Contains the definition of functions of AnnualEnergy class.
 *      calculate(): Calculates the annual energy
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "calculator/util/AnnualEnergy.h"

/**
 * Calculates annual energy
 * Annual energy, MWh/year = kWe * operating hours/1000
 * @return Annual Energy
 */
double AnnualEnergy::calculate() {
    annualEnergy = fieldPower * operatingHours / 1000;
    return annualEnergy;
}
