#ifndef AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
#define AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/TurbineFactory.h>

class CondensingTurbineCalculator {
public:
    const std::shared_ptr<Turbine> calc(const CondensingTurbine &condensingTurbineInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;
private:
    TurbineFactory turbineFactory = TurbineFactory();
};

#endif //AMO_TOOLS_SUITE_CONDENSINGTURBINECALCULATOR_H
