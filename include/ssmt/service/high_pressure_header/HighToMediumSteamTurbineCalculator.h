#ifndef AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H

#include <memory>
#include <ssmt/Boiler.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HighToMediumSteamTurbineCalculationsDomain.h>
#include <ssmt/domain/TurbineFactory.h>
#include <ssmt/service/RestarterService.h>
#include <ssmt/service/SteamBalanceException.h>
#include <ssmt/service/SteamReducer.h>
#include <ssmt/service/medium_pressure_header/SteamBalanceCheckerService.h>

class HighToMediumSteamTurbineCalculator {
public:
    HighToMediumSteamTurbineCalculationsDomain
    calc(const int headerCountInput, const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const HeaderWithHighestPressure &highPressureHeaderInput, const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<Turbine> &condensingTurbine, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal, const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

private:
    TurbineFactory turbineFactory = TurbineFactory();
    SteamBalanceCheckerService steamBalanceCheckerService = SteamBalanceCheckerService();

    HighToMediumSteamTurbineCalculationsDomain
    calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal, const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcFlowRange(const double availableMassFlow,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const PressureTurbine &highToMediumTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcPowerRange(const double availableMassFlow,
                   const PressureTurbine &highToLowTurbineInput,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                   const PressureTurbine &highToMediumTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcPowerGeneration(const double availableMassFlow,
                        const PressureTurbine &highToLowTurbineInput,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                        const PressureTurbine &highToMediumTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcSteamFlow(const double availableMassFlow,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                  const PressureTurbine &highToMediumTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcBalanceHeader(const double availableMassFlow,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                      const PressureTurbine &highToMediumTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

    double calcAvailableMassFlow(const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const CondensingTurbine &condensingTurbineInput,
                                 const std::shared_ptr<Turbine> &condensingTurbine,
                                 const PressureTurbine &highToLowTurbineInput,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbine) const;
};

#endif //AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATOR_H
