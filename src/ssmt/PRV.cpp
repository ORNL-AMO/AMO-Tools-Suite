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
    SteamProperties sp(this->inletPressure_, this->quantityType_, this->quantityValue_);
    this->inletProperties_ = sp.calculate();
    return this->inletProperties_;
}

std::unordered_map <std::string, double> PrvWithoutDesuperheating::getOutletProperties() {
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    SteamProperties sp(this->outletPressure_, SteamProperties::ThermodynamicQuantity::ENTHALPY, inletProps["specificEnthalpy"]);
    this->inletProperties_ = sp.calculate();
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
    SteamProperties sp(this->inletPressure_, this->quantityType_, this->quantityValue_);
    this->inletProperties_ = sp.calculate();
    return this->inletProperties_;
}

std::unordered_map <std::string, double> PrvWithDesuperheating::getFeedwaterProperties() {
    SteamProperties sp(this->feedwaterPressure_, this->feedwaterQuantityType_, this->feedwaterQuantityValue_);
    this->feedwaterProperties_ = sp.calculate();
    return this->feedwaterProperties_;
}

std::unordered_map <std::string, double> PrvWithDesuperheating::getOutletProperties() {
    SteamProperties sp(this->outletPressure_, SteamProperties::ThermodynamicQuantity::TEMPERATURE, this->desuperheatingTemp_);
    this->outletProperties_ = sp.calculate();
    return this->outletProperties_;
}

double PrvWithDesuperheating::getInletEnergyFlow(){
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    this->inletEnergyFlow_ = inletProps["specificEnthalpy"] * this->inletMassFlow_;
    return inletEnergyFlow_/1000;
}

double PrvWithDesuperheating::getFeedwaterMassFlow(){
    std::unordered_map <std::string, double> outletProps = getOutletProperties();
    std::unordered_map <std::string, double> inletProps = getInletProperties();
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    this->feedwaterMassFlow_ = this->inletMassFlow_ * (inletProps["specificEnthalpy"] - outletProps["specificEnthalpy"]) / (outletProps["specificEnthalpy"] - feedwaterProps["specificEnthalpy"]);
    return feedwaterMassFlow_;
}

double PrvWithDesuperheating::getFeedwaterEnergyFlow(){
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    this->outletEnergyFlow_ = getFeedwaterMassFlow() * feedwaterProps["specificEnthalpy"];
    return outletEnergyFlow_/1000;
}

double PrvWithDesuperheating::getOutletMassFlow(){
    this->outletMassFlow_ =  this->inletMassFlow_ + getFeedwaterMassFlow();
    return outletMassFlow_;
}

double PrvWithDesuperheating::getOutletEnergyFlow(){
    std::unordered_map <std::string, double> outletProps = getOutletProperties();
    this->outletEnergyFlow_ = getOutletMassFlow() * outletProps["specificEnthalpy"];
    return outletEnergyFlow_/1000;
}