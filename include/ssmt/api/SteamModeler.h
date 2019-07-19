#ifndef AMO_TOOLS_SUITE_STEAMMODELER_H
#define AMO_TOOLS_SUITE_STEAMMODELER_H

#include "SteamModelerInput.h"
#include "SteamModelerOutput.h"

/**
 * The entry-point into the Steam Modeler.
 * Use one of the model methods to initiate the system balancing.
 */
class SteamModeler {
public:
    /**
     * Entry into the Steam Modeler using a SteamModelerInput object.
     * @param steamModelerInput The object containing the Steam Modeler data for processing.
     * @return The Steam Modeler processing results.
     */
    SteamModelerOutput model(const SteamModelerInput &steamModelerInput);

private:
    SteamModelerOutput makeSteamModelerOutput();
};

#endif //AMO_TOOLS_SUITE_STEAMMODELER_H
