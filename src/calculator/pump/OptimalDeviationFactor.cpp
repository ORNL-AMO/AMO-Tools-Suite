/**
 * @brief Contains the definition of functions of OptimalDeviationFactor class.
 *      calculate(): Calculates the Optimal Deviation Factor
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/pump/OptimalDeviationFactor.h"

double OptimalDeviationFactor::calculate() {
    double pdCoeff[5] = {0.10805906,
                         18.077243,
                         0.78231304,
                         30.525232,
                         0.80684022};
    double positiveDeviationFactor =
            1 + (pdCoeff[0] + (pdCoeff[1] * exp(-pdCoeff[2] * log10(flowRate_))) +
                 pdCoeff[3] * exp(-pdCoeff[4] * log10(flowRate_))) / 100;
    return positiveDeviationFactor;
}
