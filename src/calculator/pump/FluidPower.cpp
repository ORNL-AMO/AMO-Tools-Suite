/**
 * @brief Contains the definition of functions of FluidPower class.
 *      calculate(): Calculates the fluid power
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/FluidPower.h"

/**
 * Calculates the fluid power
 * @return Fluid power in kw
 */
double FluidPower::calculate() {
    return 0.746 * flowRate * head * specificGravity / 3961.38;
}
