#ifndef AMO_TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H
#define AMO_TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H

#include <memory>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/ProcessSteamUsageCalculationsDomain.h>

class ProcessSteamUsageModeler {
public:
    ProcessSteamUsageCalculationsDomain
    model(const double headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    ProcessSteamUsage
    calc(const HeaderWithHighestPressure &highPressureHeaderInput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

    ProcessSteamUsage
    calc(const std::shared_ptr<HeaderNotHighestPressure> &headerInput,
         const SteamSystemModelerTool::FluidProperties &headerOutput,
         const SteamSystemModelerTool::FluidProperties &pressureCondensate) const;
};

#endif //AMO_TOOLS_SUITE_PROCESSSTEAMUSAGEMODELER_H
