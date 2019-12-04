#ifndef AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include "LowPressureFlashedSteamIntoHeaderCalculatorDomain.h"

class LowPressureHeaderCalculationsDomain {
public:
    std::shared_ptr<PrvWithoutDesuperheating> lowPressurePrv;
    SteamSystemModelerTool::FluidProperties lowPressureHeaderOutput;
    HeatLoss lowPressureHeaderHeatLoss;
    SteamSystemModelerTool::FluidProperties lowPressureCondensate;
    LowPressureFlashedSteamIntoHeaderCalculatorDomain lowPressureFlashedSteamIntoHeaderCalculatorDomain;

    friend std::ostream &operator<<(std::ostream &stream, const LowPressureHeaderCalculationsDomain &domain) {
        const std::shared_ptr<PrvWithoutDesuperheating> &prvWithoutPtr = domain.lowPressurePrv;

        stream << "LowPressureHeaderCalculationsDomain[";

        if (prvWithoutPtr->isWithDesuperheating()) {
            std::shared_ptr<PrvWithDesuperheating> prvWithPtr =
                    std::static_pointer_cast<PrvWithDesuperheating>(prvWithoutPtr);
            stream << "lowPressurePrv=" << prvWithPtr;
        } else {
            stream << "lowPressurePrv=" << prvWithoutPtr;
        }

        stream << ", lowPressureHeaderOutput=" << domain.lowPressureHeaderOutput
               << ", lowPressureHeaderHeatLoss=" << domain.lowPressureHeaderHeatLoss
               << ", lowPressureCondensate=" << domain.lowPressureCondensate
               << ", lowPressureFlashedSteamIntoHeaderCalculatorDomain="
               << domain.lowPressureFlashedSteamIntoHeaderCalculatorDomain
               << "]";

        return stream;
    }

    friend std::ostream &
    operator<<(std::ostream &stream, const std::shared_ptr<LowPressureHeaderCalculationsDomain> &domain) {
        if (domain == nullptr) {
            stream << "LowPressureHeaderCalculationsDomain[nullptr]";
        } else {
            stream << *domain;
        }
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H
