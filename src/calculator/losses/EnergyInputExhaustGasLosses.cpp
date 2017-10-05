/**
 * @file
 * @brief Contains the implementation of the energy input - exhaust gas loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/EnergyInputExhaustGasLosses.h"


AvailableHeat::AvailableHeat(const double excessAir, const double combustionAirTemp, const double exhaustGasTemp)
		:  excessAir(excessAir / 100), heat(95 - 0.025 * exhaustGasTemp),
		   specificHeatAir(0.017828518 + 0.000002556 * combustionAirTemp),
		   airCorrection(-((-1.078913827 + specificHeatAir * exhaustGasTemp) * this->excessAir)),
		   combustionAirCorrection((-1.078913827 + specificHeatAir * combustionAirTemp) * (1 + this->excessAir)),
		   availableHeat(heat + airCorrection + combustionAirCorrection)
{}

EnergyInputExhaustGasLosses::EnergyInputExhaustGasLosses(const double totalHeatInput, const double electricalPowerInput,
                            const double availableHeat, const double otherLosses)
		: heatDelivered(totalHeatInput * availableHeat / 100),
		  exhaustGasLosses(this->heatDelivered * (100 - availableHeat) / availableHeat)
{}
