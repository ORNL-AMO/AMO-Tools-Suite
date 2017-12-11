/**
 * @file
 * @brief Contains the implementation of the Exhaust Gas EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/ExhaustGasEAF.h"

double ExhaustGasEAF::getTotalHeatExhaust() {
    const double COheatingValue = CO * 321 / 100;
	const double H2heatingValue = H2 * 325 / 100;
    const double combustibles = combustibleGases * 1020 / 100;
    const double chemicalHeat = COheatingValue + H2heatingValue + combustibles;

    const double sensibleHeat = 0.0225 * (offGasTemp - 60);
	const double heatInDust = dustLoading * 0.25 * (offGasTemp - 60);
	const double totalHeatFlue = chemicalHeat + sensibleHeat + heatInDust;
    const double totalVfr = vfr * 520 / (460 + offGasTemp);
    return totalVfr * totalHeatFlue * 60;
}
