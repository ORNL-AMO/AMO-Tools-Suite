/**
 * @file
 * @brief Contains the implementation of the atmosphere total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/Atmosphere.h"

double Atmosphere::getTotalHeat() {
    // return the total net heat for the example case
    totalHeat = flowRate * specificHeat * (outletTemperature - inletTemperature) * correctionFactor;
    return totalHeat;
}
