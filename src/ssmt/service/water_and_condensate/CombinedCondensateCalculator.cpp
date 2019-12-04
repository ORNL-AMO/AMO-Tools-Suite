#include "ssmt/service/water_and_condensate/CombinedCondensateCalculator.h"

Header
CombinedCondensateCalculator::calc(const int headerCountInput,
                                   const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                   const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                   const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const {
    return headerFactory.make(headerCountInput, highPressureHeaderCalculationsDomain,
                              mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain);
}
