#ifndef AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/Turbine.h>

class HighToMediumSteamTurbineCalculationsDomain {
public:
    std::shared_ptr<Turbine> highToMediumPressureTurbine;
    std::shared_ptr<Turbine> highToMediumPressureTurbineIdeal;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;

    friend std::ostream &operator<<(std::ostream &stream, const HighToMediumSteamTurbineCalculationsDomain &domain) {
        stream << "Turbine["
               << "highToMediumPressureTurbine=" << domain.highToMediumPressureTurbine
               << ", highToMediumPressureTurbineIdeal=" << domain.highToMediumPressureTurbineIdeal
               << ", highToLowPressureTurbineUpdated=" << domain.highToLowPressureTurbineUpdated
               << ", highToLowPressureTurbineIdealUpdated=" << domain.highToLowPressureTurbineIdealUpdated
               << "]";
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_HIGHTOMEDIUMSTEAMTURBINECALCULATIONSDOMAIN_H
