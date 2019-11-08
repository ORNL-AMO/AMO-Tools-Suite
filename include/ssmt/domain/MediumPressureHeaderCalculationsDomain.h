#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <iostream>
#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>

class MediumPressureHeaderCalculationsDomain {
public:
    std::shared_ptr<PrvWithoutDesuperheating> highToMediumPressurePrv;
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank;
    HeatLoss mediumPressureHeaderHeatLoss;
    SteamSystemModelerTool::FluidProperties mediumPressureHeaderOutput;
    SteamSystemModelerTool::FluidProperties mediumPressureCondensate;
    std::shared_ptr<Turbine> mediumToLowPressureTurbine;
    std::shared_ptr<Turbine> mediumToLowPressureTurbineIdeal;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;

    friend std::ostream &operator<<(std::ostream &stream, const MediumPressureHeaderCalculationsDomain &domain) {
        const std::shared_ptr<PrvWithoutDesuperheating> &prvWithoutPtr = domain.highToMediumPressurePrv;

        stream << "MediumPressureHeaderCalculationsDomain[";

        if (prvWithoutPtr->isWithDesuperheating()) {
            std::shared_ptr<PrvWithDesuperheating> prvWithPtr =
                    std::static_pointer_cast<PrvWithDesuperheating>(prvWithoutPtr);
            stream << "highToMediumPressurePrv=" << prvWithPtr;
        } else {
            stream << "highToMediumPressurePrv=" << prvWithoutPtr;
        }

        stream << ", highPressureCondensateFlashTank=" << domain.highPressureCondensateFlashTank
               << ", mediumPressureHeaderHeatLoss=" << domain.mediumPressureHeaderHeatLoss
               << ", mediumPressureHeaderOutput=" << domain.mediumPressureHeaderOutput
               << ", mediumPressureCondensate=" << domain.mediumPressureCondensate
               << ", mediumToLowPressureTurbine=" << domain.mediumToLowPressureTurbine
               << ", mediumToLowPressureTurbineIdeal=" << domain.mediumToLowPressureTurbineIdeal
               << ", highToLowPressureTurbineUpdated=" << domain.highToLowPressureTurbineUpdated
               << ", highToLowPressureTurbineIdealUpdated=" << domain.highToLowPressureTurbineIdealUpdated
               << "]";

        return stream;
    }

    friend std::ostream &
    operator<<(std::ostream &stream, const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &domain) {
        if (domain == nullptr) {
            stream << "MediumPressureHeaderCalculationsDomain[nullptr]";
        } else {
            stream << *domain;
        }
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H
