/**
 * @file
 * @brief Contains the implementation of the boiler calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/Boiler.h"

std::unordered_map <std::string, double> Boiler::getSteamProperties() const {
    return steamProperties_;
}

std::unordered_map <std::string, double> Boiler::getBlowdownProperties() const {
    return blowdownProperties_;
}

std::unordered_map <std::string, double> Boiler::getFeedwaterProperties() {
    return feedwaterProperties_;
}

double Boiler::getBoilerEnergy(){
    return this->boilerEnergy_;
}

double Boiler::getFuelEnergy() {
    return this->fuelEnergy_;
}