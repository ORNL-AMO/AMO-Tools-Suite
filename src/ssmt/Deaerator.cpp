/**
 * @file
 * @brief Contains the implementation of the deaerator calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/Deaerator.h"

std::unordered_map <std::string, double> Deaerator::getInletWaterProperties() {
    SteamProperties sp = SteamProperties(this->waterPressure_, this->waterQuantityType_, this->waterQuantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletWaterProperties_ = steamProperties;
    return this->inletWaterProperties_;
}

std::unordered_map <std::string, double> Deaerator::getInletSteamProperties() {
    SteamProperties sp = SteamProperties(this->steamPressure_, this->steamQuantityType_, this->steamQuantityValue_);
    std::unordered_map <std::string, double> steamProperties = sp.calculate();
    this->inletSteamProperties_ = steamProperties;
    return this->inletSteamProperties_;
}

std::unordered_map <std::string, double> Deaerator::getFeedwaterProperties() {
    SaturatedTemperature temp = SaturatedTemperature(this->deaeratorPressure_);
    SaturatedProperties sp = SaturatedProperties(this->deaeratorPressure_, temp.calculate());
    std::unordered_map <std::string, double> satProp = sp.calculate();
    std::unordered_map <std::string, double> props;
    props["temperature"] = satProp["temperature"];
    props["pressure"] = satProp["pressure"];
    props["specificEnthalpy"] = satProp["liquidSpecificEnthalpy"];
    props["specificEntropy"] = satProp["liquidSpecificEntropy"];
    props["quality"] = 0;
    this->feedwaterProperties_ = props;
    return this->feedwaterProperties_;
}

std::unordered_map <std::string, double> Deaerator::getVentedSteamProperties() {
    SaturatedTemperature temp = SaturatedTemperature(this->deaeratorPressure_);
    SaturatedProperties sp = SaturatedProperties(this->deaeratorPressure_, temp.calculate());
    std::unordered_map <std::string, double> satProp = sp.calculate();
    std::unordered_map <std::string, double> props;
    props["temperature"] = satProp["temperature"];
    props["pressure"] = satProp["pressure"];
    props["specificEnthalpy"] = satProp["gasSpecificEnthalpy"];
    props["specificEntropy"] = satProp["gasSpecificEntropy"];
    props["quality"] = 1;
    this->ventedSteamProperties_ = props;
    return this->ventedSteamProperties_;
}

double Deaerator::getFeedwaterEnergyFlow(){
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    this->feedwaterEnergyFlow_ = feedwaterProps["specificEnthalpy"] * this->feedwaterMassFlow_;
    return feedwaterEnergyFlow_/1000;
}

double Deaerator::getVentedSteamMassFlow(){
    this->ventedSteamMassFlow_ = this->ventRate_ * this->feedwaterMassFlow_;
    return ventedSteamMassFlow_;
}

double Deaerator::getTotalDAMassFlow(){
    this->totalDAMassFlow_ = getInletSteamMassFlow() + this->feedwaterMassFlow_;
    return totalDAMassFlow_;
}

double Deaerator::getTotalOutletEnergyFlow(){
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    std::unordered_map <std::string, double> ventedSteamProps = getVentedSteamProperties();
    this->totalDAMassFlow_ = (feedwaterProps["specificEnthalpy"] * this->feedwaterMassFlow_) + (ventedSteamProps["specificEnthalpy"] * getVentedSteamMassFlow());
    return totalDAMassFlow_;
}

double Deaerator::getMinEnergyFlow(){
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->minEnergyFlow_ = inletWaterProps["specificEnthalpy"] * getTotalDAMassFlow();
    return minEnergyFlow_;
}

double Deaerator::getNeededEnergyFlow(){
    this->neededEnergyFlow_ = getTotalOutletEnergyFlow() - getMinEnergyFlow();
    return neededEnergyFlow_;
}

double Deaerator::getInletSteamMassFlow(){
    std::unordered_map <std::string, double> inletSteamProps = getInletSteamProperties();
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->inletSteamMassFlow_ = getNeededEnergyFlow()/(inletSteamProps["specificEnthalpy"] - inletWaterProps["specificEnthalpy"]);
    return inletSteamMassFlow_;
}

double Deaerator::getInletSteamEnergyFlow(){
    std::unordered_map <std::string, double> inletSteamProps = getInletSteamProperties();
    this->inletSteamEnergyFlow_ = inletSteamProps["specificEnthalpy"] * getInletSteamMassFlow();
    return inletSteamEnergyFlow_/1000;
}

double Deaerator::getInletWaterMassFlow(){
    this->inletWaterMassFlow_ = getTotalDAMassFlow() - getInletSteamMassFlow();
    return inletWaterMassFlow_;
}

double Deaerator::getInletWaterEnergyFlow(){
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->inletWaterEnergyFlow_ = inletWaterProps["specificEnthalpy"] * getInletWaterMassFlow();
    return inletWaterEnergyFlow_/1000;
}