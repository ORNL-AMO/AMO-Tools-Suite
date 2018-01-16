/**
 * @file
 * @brief Contains the implementation of the O2 enrichment calculator for fuel fired furnace.
 *
 * @author Autumn Ferree (ferreeak) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/O2Enrichment.h"

void O2Enrichment::calculate() {
    excessAir = 8.52381 * o2FlueGas / (2 - 9.52381 * o2FlueGas);
    excessAirEnriched = 8.52381 * o2FlueGasEnriched / (2 - 9.52381 * o2FlueGasEnriched);
    heatInput = 95 + (-0.025) * flueGasTemp;
    heatInputEnriched = 95 + (-0.025) * flueGasTempEnriched;
    airSpecificHeat = 0.017828518 + 0.000002556 * combAirTemp;
    enrichedAirSpecificHeat = 0.017828518 + 0.000002556 * combAirTempEnriched;
    airCorrection = -(-1.07891327 + airSpecificHeat * flueGasTemp) * excessAir;
    enrichedAirCorrection = -(-1.07891327 + enrichedAirSpecificHeat * flueGasTempEnriched) * excessAirEnriched;
    combustionAirCorrection = (-1.078913827 + airSpecificHeat * combAirTemp) * (1 + excessAir);
    combustionAirCorrectionEnriched = (-1.078913827 + enrichedAirSpecificHeat * combAirTempEnriched) * (1 + excessAirEnriched);
    stdAvailableHeat = heatInput + airCorrection + combustionAirCorrection;
    stdAvailableHeatEnriched = heatInputEnriched + enrichedAirCorrection + combustionAirCorrectionEnriched;
    availableHeat = stdAvailableHeat + 100 * (9.38 * (o2CombAir - 0.21) / o2CombAir * 0.02 * ((flueGasTemp - 60) / 980));
    availableHeatEnriched = stdAvailableHeatEnriched + 100 * (9.38 * (o2CombAirEnriched - 0.21) / o2CombAirEnriched * 0.02 * ((flueGasTempEnriched - 60) / 980));
    fuelConsumptionEnriched = fuelConsumption * (stdAvailableHeat / availableHeatEnriched);
    fuelSavingsEnriched = ((fuelConsumption - fuelConsumptionEnriched)/ fuelConsumption) * 100;
}
