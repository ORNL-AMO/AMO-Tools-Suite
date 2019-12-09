#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include "ssmt/service/EnergyFlowCalculator.h"
#include "ssmt/service/MassFlowCalculator.h"

class MediumPressureCondensateCalculator {
public:
    const SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

private:
    const EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSURECONDENSATECALCULATOR_H
