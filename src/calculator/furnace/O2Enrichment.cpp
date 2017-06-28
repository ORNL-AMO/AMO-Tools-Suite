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
    this->excessAir_ = (100 * 8.52381 * ((this->o2FlueGas_)/100)/(2 - 9.52381 * ((this->o2FlueGas_)/100)));
    return this->excessAir_;
}

double O2Enrichment::getExcessAirEnriched() {
    this->excessAirEnriched_ = (100 * 8.52381 * ((this->o2FlueGasEnriched_)/100)/(2 - 9.52381 * ((this->o2FlueGasEnriched_)/100)));
    return this->excessAirEnriched_;
}

double O2Enrichment::getHeatInput() {
    this->heatInput_ = 95 + (-0.025) * (this->flueGasTemp_);
    return this->heatInput_;
}

double O2Enrichment::getHeatInputEnriched() {
    this->heatInputEnriched_ = 95 + (-0.025) * (this->flueGasTempEnriched_);
    return this->heatInputEnriched_;
}

double O2Enrichment::getAirSpecificHeat() {
    this->airSpecificHeat_ = 0.017828518 + 0.000002556 * (this->combAirTemp_);
    return this->airSpecificHeat_;
}

double O2Enrichment::getEnrichedAirSpecificHeat() {
    this->enrichedAirSpecificHeat_ = 0.017828518 + 0.000002556 * (this->combAirTempEnriched_);
    return this->enrichedAirSpecificHeat_;
}

double O2Enrichment::getAirCorrection() {
    double airSpecificHeat = getAirSpecificHeat();
    double excessAir = getExcessAir();
    this->airCorrection_ = -(-1.07891327 + airSpecificHeat * (this->flueGasTemp_)) * (excessAir/100);
    return this->airCorrection_;
}

double O2Enrichment::getEnrichedAirCorrection() {
    double enrichedAirSpecificHeat = getEnrichedAirSpecificHeat();
    double excessAirEnriched = getExcessAirEnriched();
    this->enrichedAirCorrection_ = -(-1.07891327 + enrichedAirSpecificHeat * (this->flueGasTempEnriched_)) * (excessAirEnriched/100);
    return this->enrichedAirCorrection_;
}

double O2Enrichment::getCombustionAirCorrection() {
    double airSpecificHeat = getAirSpecificHeat();
    double excessAir = getExcessAir();
    this->combustionAirCorrection_ = (-1.078913827 + airSpecificHeat * (this->combAirTemp_)) * (1 + excessAir/100);
    return this->combustionAirCorrection_;
}

double O2Enrichment::getCombustionAirCorrectionEnriched() {
    double enrichedAirSpecificHeat = getEnrichedAirSpecificHeat();
    double excessAirEnriched = getExcessAirEnriched();
    this->combustionAirCorrectionEnriched_ = (-1.078913827 + enrichedAirSpecificHeat * (this->combAirTempEnriched_)) * (1 + excessAirEnriched/100);
    return this->combustionAirCorrectionEnriched_;
}

double O2Enrichment::getStdAvailableHeat() {
    double heatInput = getHeatInput();
    double airCorrection = getAirCorrection();
    double combustionAirCorrection = getCombustionAirCorrection();
    this->stdAvailableHeat_ = heatInput + airCorrection + combustionAirCorrection;
    return this->stdAvailableHeat_;
}

double O2Enrichment::getStdAvailableHeatEnriched() {
    double heatInputEnriched = getHeatInputEnriched();
    double enrichedAirCorrection = getEnrichedAirCorrection();
    double combustionAirCorrectionEnriched = getCombustionAirCorrectionEnriched();
    this->stdAvailableHeatEnriched_ = heatInputEnriched + enrichedAirCorrection + combustionAirCorrectionEnriched;
    return this->stdAvailableHeatEnriched_;
}

double O2Enrichment::getAvailableHeat() {
    double stdAvailableHeat = getStdAvailableHeat();
    this->availableHeat_ = stdAvailableHeat + 100 * (9.38 * ((this->o2CombAir_)/100 - 0.21)/((this->o2CombAir_)/100) * 0.02 * (((this->flueGasTemp_) - 60)/980));
    return this->availableHeat_;
}

double O2Enrichment::getAvailableHeatEnriched() {
    double stdAvailableHeatEnriched = getStdAvailableHeatEnriched();
    this->availableHeatEnriched_ = stdAvailableHeatEnriched + 100 * (9.38 * ((this->o2CombAirEnriched_)/100 - 0.21)/((this->o2CombAirEnriched_)/100) * 0.02 * (((this->flueGasTempEnriched_) - 60)/980));
    return this->availableHeatEnriched_;
}

double O2Enrichment::getFuelConsumptionEnriched() {
    double stdAvailableHeat = getStdAvailableHeat();
    double availableHeatEnriched = getAvailableHeatEnriched();
    this->fuelConsumptionEnriched_ = (this->fuelConsumption_) * (stdAvailableHeat/availableHeatEnriched);
    return this->fuelConsumptionEnriched_;
}

double O2Enrichment::getFuelSavingsEnriched() {
    double fuelConsumptionEnriched = getFuelConsumptionEnriched();
    this->fuelSavingsEnriched_ = (((this->fuelConsumption_) - fuelConsumptionEnriched)/ (this->fuelConsumption_)) * 100;
    return this->fuelSavingsEnriched_;
}