#ifndef AMO_TOOLS_SUITE_ENERGYFLOWCALCULATOR_H
#define AMO_TOOLS_SUITE_ENERGYFLOWCALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/SteamSystemModelerTool.h>

class EnergyFlowCalculator {
public:
    double calc(const double massFlow, const Boiler &boiler) const;

    double
    calc(const double massFlow, const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput) const;

    double calc(const double massFlow, const double specificEnthalpy) const;
};

#endif //AMO_TOOLS_SUITE_ENERGYFLOWCALCULATOR_H
