#ifndef AMO_TOOLS_SUITE_STEAMUSECALCULATOR_H
#define AMO_TOOLS_SUITE_STEAMUSECALCULATOR_H

#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>

class SteamUseCalculator {
public:
    double calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                const double deaeratorInletSteamMassFlow, const CondensingTurbine &condensingTurbineInput,
                const std::shared_ptr<Turbine> &condensingTurbine) const;

private:
    double calcProcessSteamUsage(const int headerCountInput,
                                 const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;
};

#endif //AMO_TOOLS_SUITE_STEAMUSECALCULATOR_H
