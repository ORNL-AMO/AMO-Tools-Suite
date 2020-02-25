#ifndef AMO_TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H
#define AMO_TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H

#include "LowPressureCondensateCalculator.h"
#include "LowPressureFlashedSteamIntoHeaderCalculator.h"
#include "LowPressureHeaderCalculator.h"
#include "LowPressurePrvCalculator.h"
#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/Header.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FlashTankFactory.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/domain/HeatLossFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/PrvWithDesuperheatingFactory.h>
#include <ssmt/domain/PrvWithoutDesuperheatingFactory.h>

class LowPressureHeaderModeler {
public:
    std::shared_ptr<LowPressureHeaderCalculationsDomain>
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToLowTurbineInput, const PressureTurbine &mediumToLowTurbineInput,
          const CondensingTurbine &condensingTurbineInput, const BoilerInput &boilerInput, const Boiler &boiler,
          const std::shared_ptr<FlashTank> &blowdownFlashTank,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const LowPressureCondensateCalculator lowPressureCondensateCalculator = LowPressureCondensateCalculator();
    const LowPressureHeaderCalculator lowPressureHeaderCalculator = LowPressureHeaderCalculator();
    const LowPressurePrvCalculator lowPressurePrvCalculator = LowPressurePrvCalculator();
    const LowPressureFlashedSteamIntoHeaderCalculator lowPressureFlashedSteamIntoHeaderCalculator = LowPressureFlashedSteamIntoHeaderCalculator();
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREHEADERMODELER_H
