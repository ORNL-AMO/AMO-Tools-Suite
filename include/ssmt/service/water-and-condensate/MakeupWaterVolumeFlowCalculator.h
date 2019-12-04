#ifndef AMO_TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H
#define AMO_TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/domain/MakeupWaterVolumeFlowCalculationsDomain.h>

class MakeupWaterVolumeFlowCalculator {
public:
    MakeupWaterVolumeFlowCalculationsDomain
    calc(const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
         const OperationsInput &operationsInput) const;

private:
    double calcMakeupWaterVolumeFlow(const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow) const;

    double
    calcMakeupWaterVolumeFlowAnnual(const double makeupWaterVolumeFlow, const double operatingHoursPerYear) const;
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERVOLUMEFLOWCALCULATOR_H
