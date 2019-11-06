#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H

#include <memory>
#include "HighToMediumPrvCalculator.h"
#include "MediumPressureCondensateCalculator.h"
#include "MediumPressureHeaderCalculator.h"
#include "MediumToLowPressureTurbineCalculator.h"
#include <ssmt/Boiler.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/service/high_pressure_header/HighPressureHeaderModeler.h>
#include <ssmt/service/medium_pressure_header/ReducedSteamException.h>
#include <ssmt/service/medium_pressure_header/UnableToBalanceException.h>

class MediumPressureHeaderModeler {
public:
    std::shared_ptr<MediumPressureHeaderCalculationsDomain>
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
          const PressureTurbine &mediumToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
          const Boiler &boiler, HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const HighPressureHeaderModeler highPressureHeaderModeler = HighPressureHeaderModeler();
    const HighToMediumPrvCalculator highToMediumPrvCalculator = HighToMediumPrvCalculator();
    const MediumPressureCondensateCalculator mediumPressureCondensateCalculator = MediumPressureCondensateCalculator();
    const MediumPressureHeaderCalculator mediumPressureHeaderCalculator = MediumPressureHeaderCalculator();
    const MediumToLowPressureTurbineCalculator mediumToLowPressureTurbineCalculator =
            MediumToLowPressureTurbineCalculator();

    std::shared_ptr<MediumPressureHeaderCalculationsDomain>
    modelIteration(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                   const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
                   const PressureTurbine &mediumToLowTurbineInput, const CondensingTurbine &condensingTurbineInput,
                   const Boiler &boiler,
                   const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERMODELER_H
