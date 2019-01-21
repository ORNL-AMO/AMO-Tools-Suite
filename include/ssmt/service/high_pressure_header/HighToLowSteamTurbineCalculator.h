#ifndef AMO_TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/TurbineFactory.h>
#include <ssmt/service/Restarter.h>
#include <ssmt/service/SteamBalanceException.h>

class HighToLowSteamTurbineCalculator {
public:
    std::shared_ptr<Turbine> calc(const int headerCountInput, const PressureTurbine &highToLowTurbineInput,
                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                  const HeaderWithHighestPressure &highPressureHeaderInput,
                                  const CondensingTurbine &condensingTurbineInput,
                                  const std::shared_ptr<Turbine> &condensingTurbine,
                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                  const Boiler &boiler) const;

private:
    Restarter restarter = Restarter();
    TurbineFactory turbineFactory = TurbineFactory();

    std::shared_ptr<Turbine>
    calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const Boiler &boiler) const;

    std::shared_ptr<Turbine>
    calcFlowRange(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    std::shared_ptr<Turbine>
    calcPowerRange(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler) const;

    std::shared_ptr<Turbine>
    calcPowerGeneration(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler) const;

    std::shared_ptr<Turbine>
    calcSteamFlow(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    std::shared_ptr<Turbine>
    calcBalanceHeader(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

    double calcAvailableMassFlow(const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const CondensingTurbine &condensingTurbineInput,
                                 const std::shared_ptr<Turbine> &condensingTurbine) const;

    void checkSteamBalanceWithMassFlow(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow,
                                       const Boiler &boiler) const;
};

#endif //AMO_TOOLS_SUITE_HIGHTOLOWSTEAMTURBINECALCULATOR_H
