#include "ssmt/service/EnergyFlowCalculator.h"

double EnergyFlowCalculator::calc(const double massFlow, const Boiler &boiler) const {
    const SteamSystemModelerTool::FluidProperties &blowdownProperties = boiler.getBlowdownProperties();
    const double specificEnthalpy = blowdownProperties.specificEnthalpy;
    return calc(massFlow, specificEnthalpy);
}

double EnergyFlowCalculator::calc(const double massFlow,
                                  const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput) const {
    const double specificEnthalpy = steamPropertiesOutput.specificEnthalpy;
    return calc(massFlow, specificEnthalpy);
}

double EnergyFlowCalculator::calc(const double massFlow, const double specificEnthalpy) const {
    return massFlow * specificEnthalpy;
}
