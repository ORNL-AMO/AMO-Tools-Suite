/**
 * @file
 * @brief Contains the implementation of the heat loss calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/HeatLoss.h"

std::unordered_map <std::string, double> HeatLoss::getInletProperties() {
    SteamProperties sp = SteamProperties(this->inletPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}

double HeatLoss::getInletEnergyFlow(){
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    this->inletEnergyFlow_ = inletProps["specificEnthalpy"] * this->inletMassFlow_;
    return inletEnergyFlow_/1000;
}

double HeatLoss::getOutletMassFlow(){
    this->outletMassFlow_ = this->inletMassFlow_;
    return outletMassFlow_;
}

double HeatLoss::getOutletEnergyFlow(){
    this->outletEnergyFlow_ = getInletEnergyFlow() * (1 - this->percentHeatLoss_/100);
    return outletEnergyFlow_;
}

std::unordered_map <std::string, double> HeatLoss::getOutletProperties() {
    double outletEnthalpy = getOutletEnergyFlow()/getInletMassFlow();
    SteamProperties sp = SteamProperties(this->inletPressure_, SteamProperties::ThermodynamicQuantity::ENTHALPY, outletEnthalpy);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->outletProperties_ = steamProperties;
    return this->outletProperties_;
}

double HeatLoss::getHeatLoss(){
    this->heatLoss_ = getInletEnergyFlow() - getOutletEnergyFlow();
    return this->heatLoss_;
}