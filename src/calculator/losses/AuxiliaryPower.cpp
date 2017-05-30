/**
 * @file
 * @brief Contains the implementation of the Auxiliary Power - Heat Use
 *
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/losses/AuxiliaryPower.h"

double AuxiliaryPower::getPowerUsed() const {
	return pow(motorPhase, 0.5) * supplyVoltage * avgCurrent * powerFactor * operatingTime / 1000.0;
}
