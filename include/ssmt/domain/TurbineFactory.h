#ifndef AMO_TOOLS_SUITE_TURBINEFACTORY_H
#define AMO_TOOLS_SUITE_TURBINEFACTORY_H

#include <ssmt/Header.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/api/HeaderInput.h>

class TurbineFactory {
public:
    Turbine make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const Turbine::TurbineProperty &turbineProperty,
                 const PressureTurbine &highToLowTurbine, const double massFlowOrPowerOut,
                 const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

    Turbine make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const CondensingTurbine &condensingTurbine) const;

    Turbine make(const Header &mediumPressureHeader, const Turbine::TurbineProperty &turbineProperty,
                 const PressureTurbine &mediumToLowTurbineInput, const double massFlowOrPowerOut,
                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

    Turbine makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                             const PressureTurbine &pressureTurbine, const double massFlow,
                             const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

    std::shared_ptr<Turbine>
    makePtrWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                        const PressureTurbine &pressureTurbine, double massFlow,
                        const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

    Turbine makeWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                             const PressureTurbine &pressureTurbine, const double powerOut,
                             const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

    std::shared_ptr<Turbine>
    makePtrWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                        const PressureTurbine &pressureTurbine, double massFlow,
                        const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

private:
    Turbine::TurbineProperty
    convertCondensingTurbineOperationToTurbineProperty(const CondensingTurbineOperation &operationType) const;
};

#endif //AMO_TOOLS_SUITE_TURBINEFACTORY_H
