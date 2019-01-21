#ifndef AMO_TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H
#define AMO_TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H

#include <ssmt/api/SteamModelerOutput.h>
#include <ssmt/domain/SteamModelCalculationsDomain.h>
#include <ssmt/service/SteamModelCalculator.h>

class SteamModelerOutputFactory {
public:
    SteamModelerOutput make(const SteamModelCalculationsDomain &domain) const;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUTPUTFACTORY_H
