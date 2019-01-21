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

    Turbine makeIdeal(const SteamSystemModelerTool::FluidProperties &headerProperties,
                      const Turbine::TurbineProperty &turbineProperty, const PressureTurbine &highToLowTurbine,
                      const double massFlowOrPowerOut,
                      const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const;

    Turbine make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const Turbine::TurbineProperty &turbineProperty, const PressureTurbine &highToLowTurbine,
                 const double massFlowOrPowerOut,
                 const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure,
                 const double isentropicEfficiency) const;

    Turbine
    make(const SteamSystemModelerTool::FluidProperties &headerProperties, const CondensingTurbine &condensingTurbine,
         const bool isCalcIdeal) const;

    Turbine
    make(const SteamSystemModelerTool::FluidProperties &headerProperties, const CondensingTurbine &condensingTurbine,
         const double isentropicEfficiency) const;

    Turbine makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                             const PressureTurbine &pressureTurbine, const double massFlow,
                             const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure,
                             const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    makePtrWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                        const PressureTurbine &pressureTurbine, double massFlow,
                        const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure,
                        const bool isCalcIdeal) const;

    Turbine makeWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                             const PressureTurbine &pressureTurbine, const double powerOut,
                             const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure,
                             const bool isCalcIdeal) const;

    std::shared_ptr<Turbine>
    makePtrWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                        const PressureTurbine &pressureTurbine, const double massFlow,
                        const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure,
                        const bool isCalcIdeal) const;

private:
    Turbine make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const CondensingTurbine &condensingTurbine) const;

    Turbine makeIdeal(const SteamSystemModelerTool::FluidProperties &headerProperties,
                      const CondensingTurbine &condensingTurbine) const;

    Turbine::TurbineProperty
    convertCondensingTurbineOperationToTurbineProperty(const CondensingTurbineOperation &operationType) const;
};

#endif //AMO_TOOLS_SUITE_TURBINEFACTORY_H
