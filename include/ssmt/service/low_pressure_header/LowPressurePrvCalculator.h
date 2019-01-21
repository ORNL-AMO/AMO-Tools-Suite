#ifndef AMO_TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H
#define AMO_TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H

#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/PrvWithDesuperheatingFactory.h>
#include <ssmt/domain/PrvWithoutDesuperheatingFactory.h>

class LowPressurePrvCalculator {
public:
    std::shared_ptr<PrvWithoutDesuperheating>
    calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
         const PressureTurbine &highToLowTurbineInput,
         const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const PressureTurbine &mediumToLowTurbineInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const ;

private:
    const PrvWithDesuperheatingFactory prvWithDesuperheatingFactory = PrvWithDesuperheatingFactory();
    const PrvWithoutDesuperheatingFactory prvWithoutDesuperheatingFactory = PrvWithoutDesuperheatingFactory();

    double calcPrvMassFlow(const int headerCountInput,
                           const HeaderWithHighestPressure &highPressureHeaderInput,
                           const SteamSystemModelerTool::FluidProperties &highPressureHeader,
                           const PressureTurbine &highToLowTurbineInput,
                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                           const CondensingTurbine &condensingTurbineInput,
                           const std::shared_ptr<Turbine> &condensingTurbine,
                           const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                           const PressureTurbine &mediumToLowTurbineInput,
                           const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREPRVCALCULATOR_H
