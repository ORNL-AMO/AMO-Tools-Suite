#ifndef AMO_TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H
#define AMO_TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H

#include <ssmt/Boiler.h>
#include <ssmt/Header.h>
#include <ssmt/HeatLoss.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/service/EnergyFlowCalculator.h>
#include <ssmt/service/MassFlowCalculator.h>

class FluidPropertiesFactory {
public:
    SteamSystemModelerTool::FluidProperties make(const Header &header) const;

    SteamSystemModelerTool::FluidProperties make(const SteamSystemModelerTool::FluidProperties &properties) const;

    SteamSystemModelerTool::FluidProperties make(const HeatLoss &heatLoss) const;

    SteamSystemModelerTool::FluidProperties
    makeWithSpecificVolume(const HeatLoss &heatLoss, const double specificVolume) const;

    SteamSystemModelerTool::FluidProperties
    makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                     const double massFlow) const;

    SteamSystemModelerTool::FluidProperties
    makeWithVentedSteamAmount(const SteamSystemModelerTool::FluidProperties &makeupWater,
                              const double ventedSteamAmount) const;

    SteamSystemModelerTool::FluidProperties makeFromBlowdown(const Boiler &boiler) const;

    SteamSystemModelerTool::FluidProperties
    makeFromBlowdown(const Boiler &boiler, const double massFlow, const double energyFlow) const;

    SteamSystemModelerTool::FluidProperties
    make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const;

    SteamSystemModelerTool::FluidProperties
    make(const HeaderWithHighestPressure &highPressureHeaderInput, const Header &combinedCondensateHeader) const;

private:
    EnergyFlowCalculator energyFlowCalculator = EnergyFlowCalculator();
    MassFlowCalculator massFlowCalculator = MassFlowCalculator();

    SteamSystemModelerTool::SteamPropertiesOutput
    calcLowPressureCondensateSteamOutput(
            const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const;
};

#endif //AMO_TOOLS_SUITE_FLUIDPROPERTIESFACTORY_H
