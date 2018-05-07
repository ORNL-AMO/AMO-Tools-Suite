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
 * Calculates the fluid power for both Pump and Fan systems, depending on constructor input
 * @return Fluid power in kw
 */
double FluidPower::calculate() {
    if (isPump) {
        return 0.746 * flowRate * head * specificGravity / 3961.38;
    }
    return 0.746 * flowRate * (outletPressure - inletPressure) * compressibilityFactor / 6362;
}
