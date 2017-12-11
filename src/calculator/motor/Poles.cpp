//
// Created by Mishra, Subhankar on 10/3/16.
//

#include <cmath>
#include "calculator/motor/Poles.h"

int Poles::calculate() {
    int poles = 0;
    if(lineFreq == Motor::LineFrequency::FREQ60) {
        if(motorRpm >= 3240 && motorRpm <= 3960) poles = 2;
        else if(motorRpm >= 1620 && motorRpm <= 1980) poles = 4;
        else if(motorRpm >= 1080 && motorRpm <= 1320) poles = 6;
        else if(motorRpm >= 810 && motorRpm <= 990) poles = 8;
        else if(motorRpm >= 648 && motorRpm <= 792) poles = 10;
        else if(motorRpm >= 540 && motorRpm <= 660) poles = 12;
    }
    else if (lineFreq == Motor::LineFrequency::FREQ50){
        if(motorRpm >= 2700 && motorRpm <= 3300) poles = 2;
        else if(motorRpm >= 1350 && motorRpm <= 1650) poles = 4;
        else if(motorRpm >= 900 && motorRpm <= 1100) poles = 6;
        else if(motorRpm >= 675 && motorRpm <= 825) poles = 8;
        else if(motorRpm >= 540 && motorRpm <= 660) poles = 10;
        else if(motorRpm >= 450 && motorRpm <= 550) poles = 12;
    }

    /*
     * Backup case when the Rpm does not fall within any range. Currently the equation for 60 Hz is used. 50 Hz equation
     * is not available at the time of implementing this.
     */

    if (poles == 0){
        if (motorRpm > 3600) {
            poles = 2;
        } else {
            if (floor(floor(7200 / motorRpm) / 2) * 2 > 12) {
                poles = 12;
            } else {
                poles = static_cast<int>(floor(floor(7200 / motorRpm) / 2) * 2);
            }
        }
    }

    return poles;
}
