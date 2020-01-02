#ifndef AMO_TOOLS_SUITE_DEAERATORMODELER_H
#define AMO_TOOLS_SUITE_DEAERATORMODELER_H

#include <ssmt/Boiler.h>
#include <ssmt/PRV.h>
#include <ssmt/domain/DeaeratorFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h>

class DeaeratorModeler {
public:
    Deaerator
    model(const int headerCountInput, const BoilerInput &boilerInput, const Boiler &boiler,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
          const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain) const;

private:
    DeaeratorFactory deaeratorFactory = DeaeratorFactory();

    double getFeedwaterMassFlow(const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;

    double calcFeedwaterMassFlow(const int headerCountInput, const Boiler &boiler,
                                 const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                 const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    Deaerator makeDeaerator(const int headerCountInput, const BoilerInput &boilerInput,
                            const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
                            const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain,
                            const double feedwaterMassFlow) const;
};

#endif //AMO_TOOLS_SUITE_DEAERATORMODELER_H
