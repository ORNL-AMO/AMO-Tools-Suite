/**
 * @file
 * @brief Contains the implementation of the electric arc furnace EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/ElectricArcFurnaceEAF.h"

double ElectricArcFurnaceEAF::getNaturalGasHeat() {
    this->naturalGasHeat_ = (this->naturalGasFlow_)*0.00102;
    return this->naturalGasHeat_;
}

double ElectricArcFurnaceEAF::getCoalHeatContent(){
    this->coalHeatContent_ = (this->coalHeatingValue_)*(this->coalCarbonInjection_)/1000000;
    return this->coalHeatContent_;

}

double ElectricArcFurnaceEAF::getElectrodeHeatContent(){
    this->electrodeHeatContent_ = (this->electrodeUse_)*(this->electrodeHeatingValue_)/1000000;
    return this->electrodeHeatContent_;
}

double ElectricArcFurnaceEAF::getTotalChemicalEnergyInput(){
    double coalHeatContent = getCoalHeatContent();
    double electrodeHeatContent = getElectrodeHeatContent();
    this->totalChemicalEnergyInput_ = (this->naturalGasHeatInput_) + coalHeatContent + electrodeHeatContent + (this->otherFuels_);
    return this->totalChemicalEnergyInput_;

}

double ElectricArcFurnaceEAF::getKwhCycle(){
    double totalChemicalEnergyInput = getTotalChemicalEnergyInput();
    this->kwhCycle_ = totalChemicalEnergyInput*(293.0832356);
    return this->kwhCycle_;

}

double ElectricArcFurnaceEAF::getHeatDelivered(){
    double naturalGasHeat = getNaturalGasHeat();
    double coalHeatContent = getCoalHeatContent();
    double electrodeHeatContent = getElectrodeHeatContent();
    this->heatDelivered_ = naturalGasHeat + coalHeatContent + electrodeHeatContent + (this->otherFuels_);
    return this->heatDelivered_;
}

double ElectricArcFurnaceEAF::getTotalKwhPerCycle(){
    double kwhCycle = getKwhCycle();
    this->totalKwhPerCycle_ = kwhCycle + (this->electricityInput_);
    return this->totalKwhPerCycle_;

}