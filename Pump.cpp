//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "Pump.h"
#include <cmath>

int Pump::getRpm() {
    return static_cast<int>(std::round(rpm_));
}
