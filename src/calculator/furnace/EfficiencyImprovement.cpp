/**
 * @file
 * @brief Contains the implementation of the efficiency improvement calculator for fuel fired furnace.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/EfficiencyImprovement.h"

double EfficiencyImprovement::getCurrentExcessAir() {
    this->currentExcessAir_ = (100 * 8.52381 * ((this->currentFlueGasOxygen_)/100))/(2 - 9.52381 *((this->currentFlueGasOxygen_)/100));
    return this->currentExcessAir_;
}

double EfficiencyImprovement::getNewExcessAir() {
    this->newExcessAir_ = (100 * 8.52381 * ((this->newFlueGasOxygen_)/100))/(2 - 9.52381 *((this->newFlueGasOxygen_)/100));
    return this->newExcessAir_;
}

double EfficiencyImprovement::getCurrentHeatInput() {
    this->currentHeatInput_ = 95 + (-0.025) * (this->currentFlueGasTemp_);
    return this->currentHeatInput_;
}

double EfficiencyImprovement::getNewHeatInput() {
    this->newHeatInput_ = 95 + (-0.025) * (this->newFlueGasTemp_);
    return this->newHeatInput_;
}

double EfficiencyImprovement::getCurrentAirSpecificHeat(){
    this->currentAirSpecificHeat_ = 0.017828518 + 0.000002556 * (this->currentCombustionAirTemp_);
    return this->currentAirSpecificHeat_;
}

double EfficiencyImprovement::getNewAirSpecificHeat(){
    this->newAirSpecificHeat_ = 0.017828518 + 0.000002556 * (this->newCombustionAirTemp_);
    return this->newAirSpecificHeat_;
}

double EfficiencyImprovement::getCurrentAirCorrection(){
    double currentExcessAir = getCurrentExcessAir();
    double currentAirSpecificHeat = getCurrentAirSpecificHeat();
    this->currentAirCorrection_ = -(-1.07891327 + currentAirSpecificHeat * (this->currentFlueGasTemp_) * (currentExcessAir/100));
    return this->currentAirCorrection_;
}

double EfficiencyImprovement::getNewAirCorrection(){
    double newExcessAir = getNewExcessAir();
    double newAirSpecificHeat = getNewAirSpecificHeat();
    this->newAirCorrection_ = -(-1.07891327 + newAirSpecificHeat * (this->newFlueGasTemp_) * (newExcessAir/100));
    return this->newAirCorrection_;
}

double EfficiencyImprovement::getCurrentCombustionAirCorrection() {
    double currentAirSpecificHeat = getCurrentAirSpecificHeat();
    double currentExcessAir = getCurrentExcessAir();
    this->currentCombustionAirCorrection_ = (-1.078913827 + currentAirSpecificHeat * (this->currentCombustionAirTemp_) * (1 + (currentExcessAir/100)));
    return this->currentCombustionAirCorrection_;
}

double EfficiencyImprovement::getNewCombustionAirCorrection() {
    double newAirSpecificHeat = getNewAirSpecificHeat();
    double newExcessAir = getNewExcessAir();
    this->newCombustionAirCorrection_ = (-1.078913827 + newAirSpecificHeat * (this->newCombustionAirTemp_) * (1 + (newExcessAir/100)));
    return this->newCombustionAirCorrection_;
}

double EfficiencyImprovement::getCurrentAvailableHeat(){
    double currentHeatInput = getCurrentHeatInput();
    double currentAirCorrection = getCurrentAirCorrection();
    double currentCombustionAirCorrection = getCurrentCombustionAirCorrection();
    this->currentAvailableHeat_ = currentHeatInput + currentAirCorrection + currentCombustionAirCorrection;
    return this->currentAvailableHeat_;
}

double EfficiencyImprovement::getNewAvailableHeat(){
    double newHeatInput = getNewHeatInput();
    double newAirCorrection = getNewAirCorrection();
    double newCombustionAirCorrection = getNewCombustionAirCorrection();
    this->newAvailableHeat_ = newHeatInput + newAirCorrection + newCombustionAirCorrection;
    return this->newAvailableHeat_;
}


double EfficiencyImprovement::getNewFuelSavings() {
    double newAvailableHeat = getNewAvailableHeat();
    double currentAvailableHeat = getCurrentAvailableHeat();
    this->newFuelSavings_ = ((newAvailableHeat - currentAvailableHeat) / newAvailableHeat) * 100;
    return this->newFuelSavings_;
}

double EfficiencyImprovement::getNewEnergyInput(){
    double newFuelSavings = getNewFuelSavings();
    this->newEnergyInput_ = (this->currentEnergyInput_) * (1 - newFuelSavings/100);
    return this->newEnergyInput_;
}