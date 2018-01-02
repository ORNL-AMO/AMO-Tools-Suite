#ifndef AMO_TOOLS_SUITE_ATMOSPHERESPECIFICHEATDATA_H
#define AMO_TOOLS_SUITE_ATMOSPHERESPECIFICHEATDATA_H

class Atmosphere;

std::vector<Atmosphere> SQLite::get_default_atmosphere_specific_heat() {
    return {
            {"Nitrogen", 0.0185},
            {"Hydrogen", 0.0182},
            {"Exothermic Gas", 0.0185},
            {"Endothermic Gas", 0.0185},
            {"Air", 0.0184},
            {"Water Vapor", 0.0212},
    };
}

#endif //AMO_TOOLS_SUITE_ATMOSPHERESPECIFICHEATDATA_H
