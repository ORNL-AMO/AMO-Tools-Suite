#include <ssmt/service/high_pressure_header/HighPressureHeaderCalculator.h>
#include <ssmt/Header.h>

SteamSystemModelerTool::FluidProperties
HighPressureHeaderCalculator::calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Boiler &boiler) const {
    std::cout << "HighPressureHeaderCalculator::calc: " << "calculating highPressureHeaderOutput" << std::endl;
    const double headerPressure = highPressureHeaderInput.getPressure();
    Header highPressureHeader = headerFactory.make(headerPressure, boiler);
    return fluidPropertiesFactory.make(highPressureHeader);
}
