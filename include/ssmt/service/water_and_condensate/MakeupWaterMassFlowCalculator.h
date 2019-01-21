#ifndef AMO_TOOLS_SUITE_MAKEUPWATERMASSFLOWCALCULATOR_H
#define AMO_TOOLS_SUITE_MAKEUPWATERMASSFLOWCALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/PRV.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>

class MakeupWaterMassFlowCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const CondensingTurbine &condensingTurbineInput, const BoilerInput &boilerInput, const Boiler &boiler,
         const SteamSystemModelerTool::FluidProperties &returnCondensate,
         const SteamSystemModelerTool::SteamPropertiesOutput &makeupWaterOutput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
         const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    double
    calcInletHeaderFlow(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                        const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                        const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double
    calcInletHeaderFlow(const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const HeaderWithHighestPressure &highPressureHeaderInput) const;

    double
    calcInletHeaderFlow(const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

    double
    calcMakeupWaterMassFlow(const int headerCountInput,
                            const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                            const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                            const CondensingTurbine &condensingTurbineInput, const BoilerInput &boilerInput,
                            const Boiler &boiler, const SteamSystemModelerTool::FluidProperties &returnCondensate,
                            const double inletHeaderFlow,
                            const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                            const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double calcMakeupWaterMassFlow(const BoilerInput &boilerInput, const Boiler &boiler) const;

    double
    addPrvFeedwaterMassFlowToMakeupWaterMassFlow(const std::shared_ptr<PrvWithoutDesuperheating> &prv,
                                                 double makeupWaterMassFlow) const;

    double getFeedwaterMassFlow(const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;

    double
    calcMakeupWaterEnergyFlow(double massFlow, const SteamSystemModelerTool::SteamPropertiesOutput &makeupWater) const;
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERMASSFLOWCALCULATOR_H
