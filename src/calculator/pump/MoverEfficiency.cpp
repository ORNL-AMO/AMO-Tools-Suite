#include "calculator/pump/MoverEfficiency.h"

double MoverEfficiency::calculate() {
	if (isPump) {
		double const fluidPower = FluidPower(specificGravity, flowRate, head).calculate();
		double const fluidPowerHp = fluidPower / 0.746; // convert to hp
		return fluidPowerHp / moverShaftPower;
	}

	double const fluidPower = FluidPower(flowRate, inletPressure, outletPressure, compressibilityFactor).calculate();
	double const fluidPowerHp = fluidPower / 0.746; // convert to hp
	return fluidPowerHp / moverShaftPower;
}
