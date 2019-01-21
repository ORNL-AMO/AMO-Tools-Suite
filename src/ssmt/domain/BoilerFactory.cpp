#include "ssmt/domain/BoilerFactory.h"

Boiler BoilerFactory::make(const HeaderInput &headerInput, const BoilerInput &boilerInput, double massFlow) const {
    double deaeratorPressure = boilerInput.getDeaeratorPressure();
    double combustionEfficiency = boilerInput.getCombustionEfficiency();
    double blowdownRate = boilerInput.getBlowdownRate();
    double steamPressure = headerInput.getHighPressureHeader().getPressure();
    SteamProperties::ThermodynamicQuantity quantityType = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
    double quantityValue = boilerInput.getSteamTemperature();

    return {deaeratorPressure, combustionEfficiency, blowdownRate, steamPressure, quantityType, quantityValue,
            massFlow};
}
