#ifndef AMO_TOOLS_SUITE_STEAMMODELRUNNER_H
#define AMO_TOOLS_SUITE_STEAMMODELRUNNER_H

#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/SteamModelCalculationsDomain.h>
#include <ssmt/service/SteamBalanceException.h>
#include <ssmt/service/SteamModelCalculator.h>

class SteamModelRunner {
public:
    SteamModelCalculationsDomain
    run(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
        const BoilerInput &boilerInput, const TurbineInput &turbineInput, const OperationsInput &operationsInput) const;

private:
    const SteamModelCalculator steamModelCalculator = SteamModelCalculator();
    const MassFlowCalculator massFlowCalculator = MassFlowCalculator();

    double
    handleSteamBalanceException(const SteamBalanceException &e, const int iterationCount, const double initialMassFlow) const;

    void logSection(const std::string &message) const;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELRUNNER_H
