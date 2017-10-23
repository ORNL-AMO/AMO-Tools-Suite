/**
 * @file
 * @brief Contains the implementation of the O2 enrichment calculator for fuel fired furnace.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/O2Enrichment.h"

double O2Enrichment::getExcessAir() {
    excessAir = (100 * 8.52381 * ((o2FlueGas)/100)/(2 - 9.52381 * ((o2FlueGas)/100)));
    return excessAir;
}

double O2Enrichment::getExcessAirEnriched() {
    excessAirEnriched = (100 * 8.52381 * ((o2FlueGasEnriched)/100)/(2 - 9.52381 * ((o2FlueGasEnriched)/100)));
    return excessAirEnriched;
}

double O2Enrichment::getHeatInput() {
    heatInput = 95 + (-0.025) * (flueGasTemp);
    return heatInput;
}

double O2Enrichment::getHeatInputEnriched() {
    heatInputEnriched = 95 + (-0.025) * (flueGasTempEnriched);
    return heatInputEnriched;
}

double O2Enrichment::getAirSpecificHeat() {
    airSpecificHeat = 0.017828518 + 0.000002556 * (combAirTemp);
    return airSpecificHeat;
}

double O2Enrichment::getEnrichedAirSpecificHeat() {
    enrichedAirSpecificHeat = 0.017828518 + 0.000002556 * (combAirTempEnriched);
    return enrichedAirSpecificHeat;
}

double O2Enrichment::getAirCorrection() {
    double airSpecificHeat = getAirSpecificHeat();
    double excessAir = getExcessAir();
    airCorrection = -(-1.07891327 + airSpecificHeat * (flueGasTemp)) * (excessAir/100);
    return airCorrection;
}

double O2Enrichment::getEnrichedAirCorrection() {
    double enrichedAirSpecificHeat = getEnrichedAirSpecificHeat();
    double excessAirEnriched = getExcessAirEnriched();
    enrichedAirCorrection = -(-1.07891327 + enrichedAirSpecificHeat * (flueGasTempEnriched)) * (excessAirEnriched/100);
    return enrichedAirCorrection;
}

double O2Enrichment::getCombustionAirCorrection() {
    double airSpecificHeat = getAirSpecificHeat();
    double excessAir = getExcessAir();
    combustionAirCorrection = (-1.078913827 + airSpecificHeat * (combAirTemp)) * (1 + excessAir/100);
    return combustionAirCorrection;
}

double O2Enrichment::getCombustionAirCorrectionEnriched() {
    double enrichedAirSpecificHeat = getEnrichedAirSpecificHeat();
    double excessAirEnriched = getExcessAirEnriched();
    combustionAirCorrectionEnriched = (-1.078913827 + enrichedAirSpecificHeat * (combAirTempEnriched)) * (1 + excessAirEnriched/100);
    return combustionAirCorrectionEnriched;
}

double O2Enrichment::getStdAvailableHeat() {
    double heatInput = getHeatInput();
    double airCorrection = getAirCorrection();
    double combustionAirCorrection = getCombustionAirCorrection();
    stdAvailableHeat = heatInput + airCorrection + combustionAirCorrection;
    return stdAvailableHeat;
}

double O2Enrichment::getStdAvailableHeatEnriched() {
    double heatInputEnriched = getHeatInputEnriched();
    double enrichedAirCorrection = getEnrichedAirCorrection();
    double combustionAirCorrectionEnriched = getCombustionAirCorrectionEnriched();
    stdAvailableHeatEnriched = heatInputEnriched + enrichedAirCorrection + combustionAirCorrectionEnriched;
    return stdAvailableHeatEnriched;
}

double O2Enrichment::getAvailableHeat() {
    double stdAvailableHeat = getStdAvailableHeat();
    availableHeat = stdAvailableHeat + 100 * (9.38 * ((o2CombAir)/100 - 0.21)/((o2CombAir)/100) * 0.02 * (((flueGasTemp) - 60)/980));
    return availableHeat;
}

double O2Enrichment::getAvailableHeatEnriched() {
    double stdAvailableHeatEnriched = getStdAvailableHeatEnriched();
    availableHeatEnriched = stdAvailableHeatEnriched + 100 * (9.38 * ((o2CombAirEnriched)/100 - 0.21)/((o2CombAirEnriched)/100) * 0.02 * (((flueGasTempEnriched) - 60)/980));
    return availableHeatEnriched;
}

double O2Enrichment::getFuelConsumptionEnriched() {
    double stdAvailableHeat = getStdAvailableHeat();
    double availableHeatEnriched = getAvailableHeatEnriched();
    fuelConsumptionEnriched = (fuelConsumption) * (stdAvailableHeat/availableHeatEnriched);
    return fuelConsumptionEnriched;
}

double O2Enrichment::getFuelSavingsEnriched() {
    double fuelConsumptionEnriched = getFuelConsumptionEnriched();
    fuelSavingsEnriched = (((fuelConsumption) - fuelConsumptionEnriched)/ (fuelConsumption)) * 100;
    return fuelSavingsEnriched;
}