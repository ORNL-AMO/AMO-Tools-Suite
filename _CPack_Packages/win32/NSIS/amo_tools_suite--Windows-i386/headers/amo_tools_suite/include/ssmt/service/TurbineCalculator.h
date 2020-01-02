#ifndef AMO_TOOLS_SUITE_TURBINCALCULATOR_H
#define AMO_TOOLS_SUITE_TURBINCALCULATOR_H

#include <ssmt/Header.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/TurbineFactory.h>

class TurbineCalculator {
public:
    Turbine calc(const SteamSystemModelerTool::FluidProperties &headerProperties,
                 const HeaderWithHighestPressure &highPressureHeaderInput, const int headerCountInput,
                 const double connectedHeaderProcessSteamUsage,
                 const std::shared_ptr<HeaderNotHighestPressure> &headerWithNotHighPressure,
                 const PressureTurbine &pressureTurbine) const;

    Turbine calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                 const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                 const PressureTurbine &mediumToLowTurbineInput,
                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const TurbineFactory turbineFactory = TurbineFactory();

    Turbine::TurbineProperty determineTurbineProperty(const PressureTurbine &pressureTurbine) const;

    double calcMassFlowOrPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                  const HeaderWithHighestPressure &highPressureHeaderInput, const int headerCountInput,
                                  const double connectedHeaderProcessSteamUsage) const;

    double adjustMassFlowOrPowerOut(const double massFlowOrPowerOut, const PressureTurbine &pressureTurbine) const;

    double calcMassFlowOrPowerOut(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                  const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const;
};

#endif //AMO_TOOLS_SUITE_TURBINCALCULATOR_H
