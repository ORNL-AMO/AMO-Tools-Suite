#include "ssmt/api/SteamModeler.h"

SteamModelerOutput SteamModeler::model(const SteamModelerInput &steamModelerInput) {
    //TODO run calculators

    //TODO populate output
    SteamModelerOutput steamModelerOutput = makeSteamModelerOutput();

    return steamModelerOutput;
}

//TODO Move to factory?
SteamModelerOutput SteamModeler::makeSteamModelerOutput() {
    SteamModelerOutput steamModelerOutput = SteamModelerOutput();


    return steamModelerOutput;
}
