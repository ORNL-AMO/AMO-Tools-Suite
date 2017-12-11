#include "calculator/pump/PumpEfficiency.h"

double PumpEfficiency::calculate() {
    /**
     * Calculate fluid power in kW
     * Fluid power, kW = 0.746 * gpm * ft * specific gravity / 3961.38
     */
    auto const fluidPower = FluidPower(specificGravity,flowRate,head).calculate();
    /**
     * Calculate fluid power in hp
     */
    auto const fluidPowerHp = fluidPower / 0.746;

    /**
     * Calculate pump efficiency
     */
    return fluidPowerHp / pumpShaftPower;
}
