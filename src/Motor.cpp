//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "Motor.h"
#include <cmath>

int Motor::getMotorRpm() {
    return static_cast<int>(std::round(motorRpm_));
}
