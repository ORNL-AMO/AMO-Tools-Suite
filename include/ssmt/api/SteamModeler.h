#ifndef AMO_TOOLS_SUITE_STEAMMODELER_H
#define AMO_TOOLS_SUITE_STEAMMODELER_H

#include "SteamModelerInput.h"
#include "SteamModelerOutput.h"
#include <ssmt/domain/SteamModelCalculationsDomain.h>
#include <ssmt/domain/SteamModelerOutputFactory.h>
#include <ssmt/service/SteamModelRunner.h>

/**
 * The entry-point into the Steam Modeler.
 * Use one of the model methods to initiate the system balancing.
 */
class SteamModeler {
public:
    /**
     * Entry into the Steam Modeler using a SteamModelerInput object.
     * @param steamModelerInput The object containing the Steam Modeler data for processing.
     * @return The Steam Modeler processing results.
     */
    SteamModelerOutput model(const SteamModelerInput &steamModelerInput);

    /**
     * Entry into the Steam Modeler using individual data objects.
     * @param isBaselineCalc true if this is the baseline calc run.
     * @param baselinePowerDemand Amount of the baseline power demand.
     * @param headerInput All of the headers input data.
     * @param boilerInput The boiler input data.
     * @param turbineInput All of the turbines input data.
     * @param operationsInput The operational input data.
     * @return The Steam Modeler processing results.
     */
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

    void logInputData(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
                      const BoilerInput &boilerInput, const TurbineInput &turbineInput,
                      const OperationsInput &operationsInput);
};

#endif //AMO_TOOLS_SUITE_STEAMMODELER_H
