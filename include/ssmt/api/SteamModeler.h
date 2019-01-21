#ifndef AMO_TOOLS_SUITE_STEAMMODELER_H
#define AMO_TOOLS_SUITE_STEAMMODELER_H

#include "SteamModelerInput.h"
#include "SteamModelerOutput.h"
#include <ssmt/domain/SteamModelCalculationsDomain.h>
#include <ssmt/domain/SteamModelerOutputFactory.h>
#include <ssmt/service/SteamModelRunner.h>

class SteamModeler {
public:
    SteamModelerOutput model(const SteamModelerInput &steamModelerInput);

    SteamModelerOutput
    model(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
          const BoilerInput &boilerInput, const TurbineInput &turbineInput, const OperationsInput &operationsInput);

private:
    SteamModelRunner steamModelRunner = SteamModelRunner();
    SteamModelerOutputFactory steamModelerOutputFactory = SteamModelerOutputFactory();

    SteamModelCalculationsDomain
    runModel(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
             const BoilerInput &boilerInput, const TurbineInput &turbineInput,
             const OperationsInput &operationsInput) const;

    SteamModelerOutput makeOutput(const SteamModelCalculationsDomain &steamModelCalculationsDomain) const;

    void logSection(const std::string &message) const;

    void logException(const std::exception &e, const std::string &message) const;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELER_H
