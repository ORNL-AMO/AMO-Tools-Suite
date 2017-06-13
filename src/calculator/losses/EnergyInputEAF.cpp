/**
 * @file
 * @brief Contains the implementation of the energy input EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/EnergyInputEAF.h"

double EnergyInputEAF::getNaturalGasHeat() {
    this->naturalGasHeat_ = (this->naturalGasFlow_)*0.00102;
    return this->naturalGasHeat_;
}

double EnergyInputEAF::getCoalHeatContent(){
    this->coalHeatContent_ = (this->coalHeatingValue_)*(this->coalCarbonInjection_)/1000000;
    return this->coalHeatContent_;

}

double EnergyInputEAF::getElectrodeHeatContent(){
    this->electrodeHeatContent_ = (this->electrodeUse_)*(this->electrodeHeatingValue_)/1000000;
    return this->electrodeHeatContent_;
}

double EnergyInputEAF::getTotalChemicalEnergyInput(){
    double coalHeatContent = getCoalHeatContent();
    double electrodeHeatContent = getElectrodeHeatContent();
    this->totalChemicalEnergyInput_ = (this->naturalGasHeatInput_) + coalHeatContent + electrodeHeatContent + (this->otherFuels_);
    return this->totalChemicalEnergyInput_;

}

double EnergyInputEAF::getKwhCycle(){
    double totalChemicalEnergyInput = getTotalChemicalEnergyInput();
    this->kwhCycle_ = totalChemicalEnergyInput*(293.0832356);
    return this->kwhCycle_;

}

double EnergyInputEAF::getHeatDelivered(){
    double naturalGasHeat = getNaturalGasHeat();
    double coalHeatContent = getCoalHeatContent();
    double electrodeHeatContent = getElectrodeHeatContent();
    this->heatDelivered_ = naturalGasHeat + coalHeatContent + electrodeHeatContent + (this->otherFuels_);
    return this->heatDelivered_;
}

double EnergyInputEAF::getTotalKwhPerCycle(){
    double kwhCycle = getKwhCycle();
    this->totalKwhPerCycle_ = kwhCycle + (this->electricityInput_);
    return this->totalKwhPerCycle_;

}