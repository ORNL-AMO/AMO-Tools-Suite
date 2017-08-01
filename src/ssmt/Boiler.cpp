/**
 * @file
 * @brief Contains the implementation of the boiler calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/Boiler.h"

std::unordered_map <std::string, double> Boiler::getSteamProperties() {
    SteamProperties sp = SteamProperties(this->steamPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->steamProperties_ = steamProperties;
    return this->steamProperties_;
}

std::unordered_map <std::string, double> Boiler::getBlowdownProperties() {
    SteamProperties sp = SteamProperties(this->steamPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->blowdownProperties_ = steamProperties;
    return this->blowdownProperties_;
}

std::unordered_map <std::string, double> Boiler::getFeedwaterProperties() {
    SteamProperties sp = SteamProperties(this->deaeratorPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->feedwaterProperties_ = steamProperties;
    return this->feedwaterProperties_;
}

double Boiler::getSteamEnergyFlow() {
    std::unordered_map <std::string, double> steamProperties = getSteamProperties();
    this->steamEnergyFlow_ = steamProperties["specificEnthalpy"] * this->steamMassFlow_;
    return this->steamEnergyFlow_
}

double Boiler::getFeedwaterMassFlow() {
    this->feedwaterMassFlow_ = getSteamMassFlow() / (1 - this->blowdownRate_/100);
    return this->feedwaterMassFlow_;
}

double Boiler::getFeedwaterEnergyFlow(){
    std::unordered_map <std::string, double> feedwaterProperties = getFeedwaterProperties();
    this->feedwaterEnergyFlow_ = feedwaterProperties["specificEnthalpy"] * getFeedwaterMassFlow();
    return this->feedwaterEnergyFlow_;
}

double Boiler::getBlowdownMassFlow() {
    this->blowdownMassFlow_ = getFeedwaterMassFlow() * (this->blowdownRate_/100);
    return this->blowdownMassFlow_;
}

double Boiler::getBlowdownEnergyFlow() {
    std::unordered_map <std::string, double> blowdownProperties = getBlowdownProperties();
    this->blowdownEnergyFlow_ = blowdownProperties["specificEnthalpy"] * getBlowdownMassFlow();
    return this->blowdownEnergyFlow_;
}

double Boiler::getBoilerEnergy(){
    this->boilerEnergy_ = getSteamEnergyFlow() + getBlowdownEnergyFlow() + getFeedwaterMassFlow();
    return this->boilerEnergy_;
}

double Boiler::getFuelEnergy() {
    this->fuelEnergy_ = getBoilerEnergy()/(this->combustionEfficiency_/100);
    return this->fuelEnergy_;
}