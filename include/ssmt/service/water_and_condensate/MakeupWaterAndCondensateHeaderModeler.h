#ifndef AMO_TOOLS_SUITE_WATERANDCONDENSATEMODELER_H
#define AMO_TOOLS_SUITE_WATERANDCONDENSATEMODELER_H

#include "CombinedCondensateCalculator.h"
#include "MakeupWaterCalculator.h"
#include "MakeupWaterMassFlowCalculator.h"
#include "ReturnCondensateCalculator.h"
#include "HeatExchangerCalculator.h"
#include "MakeupWaterAndCondensateHeaderCalculator.h"
#include "MakeupWaterAndCondensateHeaderModeler.h"
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/domain/FlashTankFactory.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/service/water-and-condensate/MakeupWaterVolumeFlowCalculator.h>

class MakeupWaterAndCondensateHeaderModeler {
public:
    MakeupWaterAndCondensateHeaderCalculationsDomain
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
              const BoilerInput &boilerInput, const OperationsInput &operationsInput,
              const CondensingTurbine &condensingTurbineInput, const Boiler &boiler,
              const std::shared_ptr<FlashTank> &blowdownFlashTank,
              const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
              const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
              const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    CombinedCondensateCalculator combinedCondensateCalculator = CombinedCondensateCalculator();
    FlashTankFactory flashTankFactory = FlashTankFactory();
    FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    HeaderFactory headerFactory = HeaderFactory();
    HeatExchangerCalculator heatExchangerCalculator = HeatExchangerCalculator();
    MakeupWaterCalculator makeupWaterCalculator = MakeupWaterCalculator();
    MakeupWaterAndCondensateHeaderCalculator makeupWaterAndCondensateHeaderCalculator = MakeupWaterAndCondensateHeaderCalculator();
    MakeupWaterMassFlowCalculator makeupWaterMassFlowCalculator = MakeupWaterMassFlowCalculator();
    MakeupWaterVolumeFlowCalculator makeupWaterVolumeFlowCalculator = MakeupWaterVolumeFlowCalculator();
    ReturnCondensateCalculator returnCondensateCalculator = ReturnCondensateCalculator();
};

#endif //AMO_TOOLS_SUITE_WATERANDCONDENSATEMODELER_H
