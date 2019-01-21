#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H

#include "HighToMediumPrvCalculator.h"
#include "MediumPressureCondensateCalculator.h"
#include "MediumPressureHeaderCalculator.h"
#include "MediumToLowPressureTurbineCalculator.h"
#include "MediumPressureHeatLossCalculator.h"
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>

class MediumPressureHeaderModeler {
public:
    std::shared_ptr<MediumPressureHeaderCalculationsDomain>
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
          const PressureTurbine &mediumToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
          const Boiler &boiler, const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HighToMediumPrvCalculator highToMediumPrvCalculator = HighToMediumPrvCalculator();
    const MediumPressureCondensateCalculator mediumPressureCondensateCalculator = MediumPressureCondensateCalculator();
    const MediumPressureHeatLossCalculator mediumPressureHeatLossCalculator = MediumPressureHeatLossCalculator();
    const MediumPressureHeaderCalculator mediumPressureHeaderCalculator = MediumPressureHeaderCalculator();
    const MediumToLowPressureTurbineCalculator mediumToLowPressureTurbineCalculator =
            MediumToLowPressureTurbineCalculator();
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
