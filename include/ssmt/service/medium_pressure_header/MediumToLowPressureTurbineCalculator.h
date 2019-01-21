#ifndef AMO_TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H
#define AMO_TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include "ssmt/domain/TurbineFactory.h"
#include <ssmt/service/Restarter.h>
#include <ssmt/service/SteamReducer.h>
#include "ssmt/service/TurbineCalculator.h"

class MediumToLowPressureTurbineCalculatorOutput {
public:
    std::shared_ptr<Turbine> mediumToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
};

class MediumToLowPressureTurbineCalculator {
public:
    MediumToLowPressureTurbineCalculatorOutput
    calc(const PressureTurbine &highToLowTurbineInput, const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const PressureTurbine &mediumToLowTurbineInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

private:
    const Restarter restarter = Restarter();
    const SteamReducer steamReducer = SteamReducer();

    const TurbineCalculator turbineCalculator = TurbineCalculator();
    const TurbineFactory turbineFactory = TurbineFactory();

    MediumToLowPressureTurbineCalculatorOutput
    calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const PressureTurbine &mediumToLowTurbineInput,
         const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcFlowRange(const double availableMassFlow, const PressureTurbine &mediumToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcPowerRange(const double availableMassFlow,
                   const PressureTurbine &mediumToLowTurbineInput,
                   const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const Boiler &boiler,
                   const PressureTurbine &highToLowTurbineInput,
                   const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcPowerGeneration(const double availableMassFlow,
                        const PressureTurbine &mediumToLowTurbineInput,
                        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const Boiler &boiler,
                        const PressureTurbine &highToLowTurbineInput,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcSteamFlow(const double availableMassFlow,
                  const PressureTurbine &mediumToLowTurbineInput,
                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                  const Boiler &boiler,
                  const PressureTurbine &highToLowTurbineInput,
                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

    MediumToLowPressureTurbineCalculatorOutput
    calcBalanceHeader(const double availableMassFlow,
                      const PressureTurbine &mediumToLowTurbineInput,
                      const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine) const;

    double calcAvailableMassFlow(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                 const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const;

    std::shared_ptr<Turbine>
    checkSteamBalance(const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const PressureTurbine &highToLowTurbineInput,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
                      const std::shared_ptr<Turbine> &mediumToLowPressureTurbine, const double availableMassFlow) const;
};

#endif //AMO_TOOLS_SUITE_MEDIUMTOLOWPRESSURETURBINECALCULATOR_H
