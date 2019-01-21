#include "ssmt/domain/PrvWithDesuperheatingFactory.h"

PrvWithDesuperheating
PrvWithDesuperheatingFactory::make(const SteamSystemModelerTool::FluidProperties &remainingSteam, const double massFlow,
                                   const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure,
                                   const SteamSystemModelerTool::FluidProperties &feedwater) const {
    double inletPressure = remainingSteam.pressure;
    SteamProperties::ThermodynamicQuantity quantityType = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double quantityValue = remainingSteam.specificEnthalpy;
    double inletMassFlow = massFlow;
    double outletPressure = headerNotHighestPressure->getPressure();
    double feedwaterPressure = feedwater.pressure;
    SteamProperties::ThermodynamicQuantity feedwaterQuantityType = SteamProperties::ThermodynamicQuantity::QUALITY;
    double feedwaterQuantityValue = 0;
    double desuperheatingTemp = headerNotHighestPressure->getDesuperheatSteamTemperature();

    return {inletPressure, quantityType, quantityValue, inletMassFlow, outletPressure, feedwaterPressure,
            feedwaterQuantityType, feedwaterQuantityValue, desuperheatingTemp};
}
