#ifndef AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
#define AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/TurbineFactory.h>

class CondensingTurbineCalculator {
public:
    const std::shared_ptr<Turbine> calc(const CondensingTurbine &condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                        const bool isCalcIdeal) const;

private:
    TurbineFactory turbineFactory = TurbineFactory();

    const std::shared_ptr<Turbine> make(const CondensingTurbine &condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                        const bool isCalcIdeal) const;
};

#endif //AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
