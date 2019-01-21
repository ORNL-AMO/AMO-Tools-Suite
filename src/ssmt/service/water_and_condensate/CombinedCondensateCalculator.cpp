#include "ssmt/service/water_and_condensate/CombinedCondensateCalculator.h"

Header
CombinedCondensateCalculator::calc(const int headerCountInput,
                                   const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                   const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                   const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const {
    const double lowHeaderPressure =
            determineLowHeaderPressure(headerCountInput, highPressureHeaderCalculationsDomain,
                                       lowPressureHeaderCalculationsDomain);

    const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank =
            selectHighPressureCondensateFlashTank(mediumPressureHeaderCalculationsDomain,
                                                  lowPressureHeaderCalculationsDomain);

    return headerFactory.make(headerCountInput, lowHeaderPressure, highPressureCondensateFlashTank,
                              highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
                              lowPressureHeaderCalculationsDomain);
}

/** Pressure from lowest pressure condensate. */
double
CombinedCondensateCalculator::determineLowHeaderPressure(const int headerCountInput,
                                                         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                                         const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const {
    double pressure = 0;

    if (headerCountInput == 1) {
        const SteamSystemModelerTool::FluidProperties &highPressureCondensate =
                highPressureHeaderCalculationsDomain.highPressureCondensate;
        pressure = highPressureCondensate.pressure;
    } else {
        const SteamSystemModelerTool::FluidProperties &lowPressureCondensate =
                lowPressureHeaderCalculationsDomain->lowPressureCondensate;
        pressure = lowPressureCondensate.pressure;
    }

    return pressure;
}

/** @return selected one, possibly null. */
std::shared_ptr<FlashTank>
CombinedCondensateCalculator::selectHighPressureCondensateFlashTank(
        const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
        const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const {
    std::shared_ptr<FlashTank> flashTank = nullptr;

    if (lowPressureHeaderCalculationsDomain == nullptr) {
        if (mediumPressureHeaderCalculationsDomain != nullptr) {
            flashTank = mediumPressureHeaderCalculationsDomain->highPressureCondensateFlashTank;
        }
    } else {
        const LowPressureFlashedSteamIntoHeaderCalculatorDomain &lowPressureFlashedSteamIntoHeaderCalculatorDomain =
                lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
        flashTank = lowPressureFlashedSteamIntoHeaderCalculatorDomain.highPressureCondensateFlashTank;
    }

    return flashTank;
}
