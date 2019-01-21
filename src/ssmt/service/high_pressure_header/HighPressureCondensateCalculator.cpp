#include "ssmt/service/high_pressure_header/HighPressureCondensateCalculator.h"

const SteamSystemModelerTool::FluidProperties
HighPressureCondensateCalculator::calc(const HeaderWithHighestPressure &highPressureHeaderInput,
                                       const Boiler &boiler) const {
    //has same properties as blowdown with updated mass and energy flows
    std::cout << "HighPressureCondensateCalculator::calc: " << "calculating highPressureCondensate" << std::endl;
    double massFlow = massFlowCalculator.calc(highPressureHeaderInput);
    double energyFlow = energyFlowCalculator.calc(massFlow, boiler);
    return fluidPropertiesFactory.makeFromBlowdown(boiler, massFlow, energyFlow);
}
