#ifndef AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/Turbine.h>

class HighToMediumSteamTurbineCalculationsDomain {
public:
    std::shared_ptr<Turbine> highToMediumPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
};

#endif //AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H
