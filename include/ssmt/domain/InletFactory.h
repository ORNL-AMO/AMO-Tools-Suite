#ifndef AMO_TOOLS_SUITE_INLETFACTORY_H
#define AMO_TOOLS_SUITE_INLETFACTORY_H

#include <memory>
#include <vector>
#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/Header.h>
#include <ssmt/HeatExchanger.h>
#include <ssmt/PRV.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>

class InletFactory {
public:
    std::vector<Inlet> make(const Boiler &boiler) const;

    Inlet make(const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;

    Inlet make(const std::shared_ptr<Turbine> &turbine) const;

    Inlet make(const double pressure, const std::shared_ptr<Turbine> &turbine) const;

    Inlet makeFromOutletGas(const std::shared_ptr<FlashTank> &flashTank) const;

    Inlet makeFromOutletLiquid(const std::shared_ptr<FlashTank> &flashTank) const;

    Inlet makeWithEnthalpy(const SteamSystemModelerTool::FluidProperties &properties) const;

    Inlet makeWithTemperature(const std::shared_ptr<HeatExchanger::Output> &output) const;
};

#endif //AMO_TOOLS_SUITE_INLETFACTORY_H
