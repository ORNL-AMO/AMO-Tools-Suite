#include <cmath>
#include "calculator/motor/Poles.h"

int Poles::calculate() {
    if(lineFreq == Motor::LineFrequency::FREQ60) {
        if (motorRpm >= 3240 && motorRpm <= 3600) return 2;
        else if (motorRpm >= 1620 && motorRpm <= 1800) return 4;
        else if (motorRpm >= 1080 && motorRpm <= 1200) return 6;
        else if (motorRpm >= 810 && motorRpm <= 900) return 8;
        else if (motorRpm >= 648 && motorRpm <= 720) return 10;
        else if (motorRpm >= 540 && motorRpm <= 600) return 12;
    } else if (lineFreq == Motor::LineFrequency::FREQ50) {
        if (motorRpm >= 2700 && motorRpm <= 3000) return 2;
        else if (motorRpm >= 1350 && motorRpm <= 1500) return 4;
        else if (motorRpm >= 900 && motorRpm <= 1000) return 6;
        else if (motorRpm >= 675 && motorRpm <= 750) return 8;
        else if (motorRpm >= 540 && motorRpm <= 600) return 10;
        else if (motorRpm >= 450 && motorRpm <= 500) return 12;
    }

    // Backup case when the Rpm does not fall within any range. Currently the equation for 60 Hz is used. 50 Hz equation
    // is not available at the time of implementing this.
    if (motorRpm > 3600) return 2;

	auto const poles = static_cast<int>(std::floor(std::floor(7200 / motorRpm) / 2) * 2);
    return (poles > 12) ? 12 : poles;
}
