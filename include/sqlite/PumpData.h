//
// Created by zf9 on 7/17/18.
//

#ifndef AMO_TOOLS_SUITE_PUMPDATA_H
#define AMO_TOOLS_SUITE_PUMPDATA_H

#include <vector>
#include "SQLite.h"

class PumpData;

std::vector<PumpData> SQLite::get_default_pump_data() {
    return {
            {                                                                                                                                                                                         94.3, 91.6, 78, 73.6, 63.3, 41.5, 147.4, 294.8, 206.4, 63.5, 25.7, 362.5, 92.9, 115.2, 2000
            }
    };
}

#endif //AMO_TOOLS_SUITE_PUMPDATA_H
