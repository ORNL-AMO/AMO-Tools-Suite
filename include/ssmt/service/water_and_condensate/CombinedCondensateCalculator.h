#ifndef AMO_TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H
#define AMO_TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H

#include <ssmt/Header.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>

class CombinedCondensateCalculator {
public:
    Header calc(const int headerCountInput,
                const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    const HeaderFactory headerFactory = HeaderFactory();

    double determineLowHeaderPressure(const int headerCountInput,
                                      const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                      const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    std::shared_ptr<FlashTank>
    selectHighPressureCondensateFlashTank(
            const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;
};

#endif //AMO_TOOLS_SUITE_COMBINEDCONDENSATECALCULATOR_H
