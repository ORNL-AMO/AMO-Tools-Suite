#ifndef AMO_TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/service/EnergyFlowCalculator.h>
#include <ssmt/service/MassFlowCalculator.h>

class HighPressureCondensateCalculator {
public:
    const SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Boiler &boiler) const;

private:
    const EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSURECONDENSATECALCULATOR_H
