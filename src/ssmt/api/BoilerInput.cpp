#include "ssmt/api/BoilerInput.h"

BoilerInput::BoilerInput(double fuelType, double fuel, double combustionEfficiency, double blowdownRate,
                         bool blowdownFlashed, bool preheatMakeupWater, double steamTemperature,
                         double deaeratorVentRate, double deaeratorPressure, double approachTemperature)
        : fuelType(fuelType), fuel(fuel), combustionEfficiency(combustionEfficiency), blowdownRate(blowdownRate),
          blowdownFlashed(blowdownFlashed), preheatMakeupWater(preheatMakeupWater), steamTemperature(steamTemperature),
          deaeratorVentRate(deaeratorVentRate), deaeratorPressure(deaeratorPressure),
          approachTemperature(approachTemperature) {
}

std::ostream &operator<<(std::ostream &stream, const BoilerInput &bi) {
    return stream << "BoilerInput: "
                  << "fuelType=" << bi.fuelType
                  << ", fuel=" << bi.fuel
                  << ", combustionEfficiency=" << bi.combustionEfficiency
                  << ", blowdownRate=" << bi.blowdownRate
                  << ", blowdownFlashed=" << bi.blowdownFlashed
                  << ", preheatMakeupWater=" << bi.preheatMakeupWater
                  << ", steamTemperature=" << bi.steamTemperature
                  << ", deaeratorVentRate=" << bi.deaeratorVentRate
                  << ", deaeratorPressure=" << bi.deaeratorPressure
                  << ", approachTemperature=" << bi.approachTemperature;
}

double BoilerInput::getFuelType() const {
    return fuelType;
}

double BoilerInput::getFuel() const {
    return fuel;
}

double BoilerInput::getCombustionEfficiency() const {
    return combustionEfficiency;
}

double BoilerInput::getBlowdownRate() const {
    return blowdownRate;
}

bool BoilerInput::isBlowdownFlashed() const {
    return blowdownFlashed;
}

bool BoilerInput::isPreheatMakeupWater() const {
    return preheatMakeupWater;
}

double BoilerInput::getSteamTemperature() const {
    return steamTemperature;
}

double BoilerInput::getDeaeratorVentRate() const {
    return deaeratorVentRate;
}

double BoilerInput::getDeaeratorPressure() const {
    return deaeratorPressure;
}

double BoilerInput::getApproachTemperature() const {
    return approachTemperature;
}
