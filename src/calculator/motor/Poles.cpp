#include <cmath>
#include "calculator/motor/Poles.h"

int Poles::calculate() {
    if(lineFreq == Motor::LineFrequency::FREQ60) {
        if (motorRpm >= 3240 && motorRpm <= 3960) return 2;
        else if (motorRpm >= 1620 && motorRpm <= 1980) return 4;
        else if (motorRpm >= 1080 && motorRpm <= 1320) return 6;
        else if (motorRpm >= 810 && motorRpm <= 990) return 8;
        else if (motorRpm >= 648 && motorRpm <= 792) return 10;
        else if (motorRpm >= 540 && motorRpm <= 660) return 12;
    } else if (lineFreq == Motor::LineFrequency::FREQ50) {
        if (motorRpm >= 2700 && motorRpm <= 3300) return 2;
        else if (motorRpm >= 1350 && motorRpm <= 1650) return 4;
        else if (motorRpm >= 900 && motorRpm <= 1100) return 6;
        else if (motorRpm >= 675 && motorRpm <= 825) return 8;
        else if (motorRpm >= 540 && motorRpm <= 660) return 10;
        else if (motorRpm >= 450 && motorRpm <= 550) return 12;
    }

    // Backup case when the Rpm does not fall within any range. Currently the equation for 60 Hz is used. 50 Hz equation
    // is not available at the time of implementing this.
    if (motorRpm > 3600) return 2;

	auto const poles = static_cast<int>(std::floor(std::floor(7200 / motorRpm) / 2) * 2);
    return (poles > 12) ? 12 : poles;
}
