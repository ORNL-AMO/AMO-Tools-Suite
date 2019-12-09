#include "ssmt/domain/PrvWithoutDesuperheatingFactory.h"

PrvWithoutDesuperheating
PrvWithoutDesuperheatingFactory::make(const SteamSystemModelerTool::FluidProperties &remainingSteam,
                                      const double massFlow,
                                      const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure) const {
    double inletPressure = remainingSteam.pressure;
    SteamProperties::ThermodynamicQuantity quantityType = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double quantityValue = remainingSteam.specificEnthalpy;
    double inletMassFlow = massFlow;
    double outletPressure = headerNotHighestPressure->getPressure();

    return {inletPressure, quantityType, quantityValue, inletMassFlow, outletPressure};
}
