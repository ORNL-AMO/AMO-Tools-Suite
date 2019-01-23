#ifndef AMO_TOOLS_SUITE_STEAMMODELER_H
#define AMO_TOOLS_SUITE_STEAMMODELER_H

#include "SteamModelerInput.h"
#include "SteamModelerOutput.h"

class SteamModeler {
public:
    SteamModelerOutput model(const SteamModelerInput &steamModelerInput);

private:
    SteamModelerOutput makeSteamModelerOutput();
};

#endif //AMO_TOOLS_SUITE_STEAMMODELER_H
