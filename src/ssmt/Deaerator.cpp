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
    this->inletWaterProperties_ = sp.calculate();
    return this->inletWaterProperties_;
}

std::unordered_map <std::string, double> Deaerator::getInletSteamProperties() {
    SteamProperties sp = SteamProperties(this->steamPressure_, this->steamQuantityType_, this->steamQuantityValue_);
    this->inletSteamProperties_ = sp.calculate();
    return this->inletSteamProperties_;
}

std::unordered_map <std::string, double> Deaerator::getFeedwaterProperties() {
    SaturatedTemperature temp = SaturatedTemperature(this->deaeratorPressure_);
    SaturatedProperties sp = SaturatedProperties(this->deaeratorPressure_, temp.calculate());
    std::unordered_map <std::string, double> satProp = sp.calculate();
    this->feedwaterProperties_["temperature"] = satProp["temperature"];
    this->feedwaterProperties_["pressure"] = satProp["pressure"];
    this->feedwaterProperties_["specificEnthalpy"] = satProp["liquidSpecificEnthalpy"];
    this->feedwaterProperties_["specificEntropy"] = satProp["liquidSpecificEntropy"];
    this->feedwaterProperties_["quality"] = 0;
    return this->feedwaterProperties_;
}

std::unordered_map <std::string, double> Deaerator::getVentedSteamProperties() {
    SaturatedTemperature temp = SaturatedTemperature(this->deaeratorPressure_);
    SaturatedProperties sp = SaturatedProperties(this->deaeratorPressure_, temp.calculate());
    std::unordered_map <std::string, double> satProp = sp.calculate();
    ventedSteamProperties_["temperature"] = satProp["temperature"];
    ventedSteamProperties_["pressure"] = satProp["pressure"];
    ventedSteamProperties_["specificEnthalpy"] = satProp["gasSpecificEnthalpy"];
    ventedSteamProperties_["specificEntropy"] = satProp["gasSpecificEntropy"];
    ventedSteamProperties_["quality"] = 1;
    return this->ventedSteamProperties_;
}

double Deaerator::getFeedwaterEnergyFlow() {
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    this->feedwaterEnergyFlow_ = feedwaterProps["specificEnthalpy"] * this->feedwaterMassFlow_;
    return feedwaterEnergyFlow_ / 1000;
}

double Deaerator::getVentedSteamMassFlow() {
    this->ventedSteamMassFlow_ = (this->ventRate_ / 100) * this->feedwaterMassFlow_;
    return ventedSteamMassFlow_;
}

double Deaerator::getVentedSteamEnergyFlow() {
    std::unordered_map <std::string, double> ventedSteamProps = getVentedSteamProperties();
    this->ventedSteamEnergyFlow_ = ventedSteamProps["specificEnthalpy"] * getVentedSteamMassFlow();
    return ventedSteamEnergyFlow_ / 1000;
}

double Deaerator::getTotalDAMassFlow() {
    this->totalDAMassFlow_ = getVentedSteamMassFlow() + this->feedwaterMassFlow_;
    return totalDAMassFlow_;
}

double Deaerator::getTotalOutletEnergyFlow() {
    std::unordered_map <std::string, double> feedwaterProps = getFeedwaterProperties();
    std::unordered_map <std::string, double> ventedSteamProps = getVentedSteamProperties();
    this->totalOutletEnergyFlow_ = (feedwaterProps["specificEnthalpy"] * this->feedwaterMassFlow_) + (ventedSteamProps["specificEnthalpy"] * getVentedSteamMassFlow());
    return totalOutletEnergyFlow_ / 1000;
}

double Deaerator::getMinEnergyFlow() {
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->minEnergyFlow_ = inletWaterProps["specificEnthalpy"]* getTotalDAMassFlow();
    return minEnergyFlow_ / 1000;
}

double Deaerator::getNeededEnergyFlow() {
    this->neededEnergyFlow_ = getTotalOutletEnergyFlow() - getMinEnergyFlow();
    return neededEnergyFlow_;
}

double Deaerator::getInletSteamMassFlow() {
    std::unordered_map <std::string, double> inletSteamProps = getInletSteamProperties();
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->inletSteamMassFlow_ = getNeededEnergyFlow()/(inletSteamProps["specificEnthalpy"] - inletWaterProps["specificEnthalpy"]);
    return inletSteamMassFlow_ * 1000;
}

double Deaerator::getInletSteamEnergyFlow() {
    std::unordered_map <std::string, double> inletSteamProps = getInletSteamProperties();
    this->inletSteamEnergyFlow_ = inletSteamProps["specificEnthalpy"] * getInletSteamMassFlow();
    return inletSteamEnergyFlow_ / 1000;
}

double Deaerator::getInletWaterMassFlow() {
    this->inletWaterMassFlow_ = getTotalDAMassFlow() - getInletSteamMassFlow();
    return inletWaterMassFlow_;
}

double Deaerator::getInletWaterEnergyFlow() {
    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
    this->inletWaterEnergyFlow_ = inletWaterProps["specificEnthalpy"] * getInletWaterMassFlow();
    return inletWaterEnergyFlow_ / 1000;
}