/**
 * @brief Contains the definition of functions of OptimalPumpShaftPower class.
 *      calculate(): Calculates the Optimal Pump ShaftPower
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/OptimalPumpShaftPower.h"

double OptimalPumpShaftPower::calculate() {
    if (isPump) {
        const double fluidPower = FluidPower(specificGravity, flowRate, head).calculate();
        return (fluidPower / efficiency) / 0.746;
    }
    const double fluidPower = FluidPower(flowRate, inletPressure, outletPressure, compressibilityFactor).calculate();
    return (fluidPower / efficiency) / 0.746;
}
