#ifndef AMO_TOOLS_SUITE_RESTARTER_H
#define AMO_TOOLS_SUITE_RESTARTER_H

#include <memory>
#include <ssmt/Boiler.h>
#include <ssmt/Turbine.h>

//TODO rename to RestarterService?
class Restarter {
public:
    void restartIfNotEnoughSteam(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow,
                                 const Boiler &boiler) const;

    void restartIfNotEnoughSteam(const double additionalSteamNeeded, const Boiler &boiler) const;
};

#endif //AMO_TOOLS_SUITE_RESTARTER_H
