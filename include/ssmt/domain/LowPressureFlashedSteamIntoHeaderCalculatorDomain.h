#ifndef AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATORDOMAIN_H
#define AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATORDOMAIN_H

#include <memory>
#include <ssmt/FlashTank.h>

class LowPressureFlashedSteamIntoHeaderCalculatorDomain {
public:
    std::shared_ptr<FlashTank> mediumPressureCondensateFlashTank;

    /** The original one or updated with high and medium pressure mix.*/
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank;

    friend std::ostream &operator<<(std::ostream &stream, const LowPressureFlashedSteamIntoHeaderCalculatorDomain &domain) {
        stream << "LowPressureFlashedSteamIntoHeaderCalculatorDomain["
               << "mediumPressureCondensateFlashTank=" << domain.mediumPressureCondensateFlashTank
               << ", highPressureCondensateFlashTank=" << domain.highPressureCondensateFlashTank
               << "]";

        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATORDOMAIN_H
