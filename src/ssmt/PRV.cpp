/**
 * @file
 * @brief Contains the implementation of the PRV calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/PRV.h"

std::unordered_map <std::string, double> PrvWithoutDesuperheating::getInletProperties() {
    SteamProperties sp = SteamProperties(this->inletPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}

std::unordered_map <std::string, double> PrvWithoutDesuperheating::getOutletProperties() {
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    SteamProperties sp = SteamProperties(this->outletPressure_, SteamProperties::ThermodynamicQuantity::ENTHALPY, inletProps["specificEnthalpy"]);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}

double PrvWithoutDesuperheating::getInletEnergyFlow(){
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    this->inletEnergyFlow_ = inletProps["specificEnthalpy"] * this->inletMassFlow_;
    return inletEnergyFlow_/1000;
}

double PrvWithoutDesuperheating::getOutletMassFlow(){
    this->outletMassFlow_ = this->inletMassFlow_;
    return outletMassFlow_;
}

double PrvWithoutDesuperheating::getOutletEnergyFlow(){
    this->outletEnergyFlow_ = getInletEnergyFlow();
    return outletEnergyFlow_;
}


std::unordered_map <std::string, double> PrvWithDesuperheating::getInletProperties() {
    SteamProperties sp = SteamProperties(this->inletPressure_, this->quantityType_, this->quantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}

std::unordered_map <std::string, double> PrvWithDesuperheating::getFeedwaterProperties() {
    SteamProperties sp = SteamProperties(this->inletPressure_, SteamProperties::ThermodynamicQuantity::ENTHALPY, inletProps["specificEnthalpy"]);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}

std::unordered_map <std::string, double> PrvWithDesuperheating::getOutletProperties() {
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    SteamProperties sp = SteamProperties(this->outletPressure_, SteamProperties::ThermodynamicQuantity::ENTHALPY, inletProps["specificEnthalpy"]);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletProperties_ = steamProperties;
    return this->inletProperties_;
}


double PrvWithoutDesuperheating::getInletEnergyFlow(){
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    this->inletEnergyFlow_ = inletProps["specificEnthalpy"] * this->inletMassFlow_;
    return inletEnergyFlow_/1000;
}

double PrvWithoutDesuperheating::getOutletMassFlow(){
    this->outletMassFlow_ = this->inletMassFlow_;
    return outletMassFlow_;
}

double PrvWithoutDesuperheating::getOutletEnergyFlow(){
    this->outletEnergyFlow_ = getInletEnergyFlow();
    return outletEnergyFlow_;
}