/**
 * @file
 * @brief Contains the implementation of the energy input - exhaust gas loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/EnergyInputExhaustGasLosses.h"

double  AvailableHeat::getHeat() {
    this->heat_ = 95 + (-0.025) * (this->exhaustGasTemp_);
    return this->heat_;
}

double AvailableHeat::getSpecificHeatAir(){
    this->specificHeatAir_ = 0.017828518 + 0.000002556 * (this->combustionAirTemp_);
    return this->specificHeatAir_;
}

double AvailableHeat::getAirCorrection(){
    double specificHeatAir = getSpecificHeatAir();
    this->airCorrection_ = -((-1.078913827 + specificHeatAir * (this->exhaustGasTemp_)) * ((this->excessAir_)/100));
    return this->airCorrection_;
}

double AvailableHeat::getCombustionAirCorrection() {
    double specificHeatAir = getSpecificHeatAir();
    this->combustionAirCorrection_ = (-1.078913827 + specificHeatAir * (this->combustionAirTemp_)) * (1 + (this->excessAir_)/100);
    return this->combustionAirCorrection_;
}

double AvailableHeat::getAvailableHeat(){
    double heat = getHeat();
    double airCorrection = getAirCorrection();
    double combustionAirCorrection = getCombustionAirCorrection();
    this->availableHeat_ = heat + airCorrection + combustionAirCorrection;
    return this->availableHeat_;
}
