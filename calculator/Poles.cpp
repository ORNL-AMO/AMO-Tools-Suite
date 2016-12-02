//
// Created by Mishra, Subhankar on 10/3/16.
//

#include "Poles.h"
#include <cmath>

int Poles::calculate() {
    poles_ =0;
    if(lineFreq_ == Motor::LineFrequency::FREQ60) {
        if(motorRpm_ >= 3240 && motorRpm_ <= 3960) poles_ = 2;
        else if(motorRpm_ >= 1620 && motorRpm_ <= 1980) poles_ = 4;
        else if(motorRpm_ >= 1080 && motorRpm_ <= 1320) poles_ = 6;
        else if(motorRpm_ >= 810 && motorRpm_ <= 990) poles_ = 8;
        else if(motorRpm_ >= 648 && motorRpm_ <= 792) poles_ = 10;
        else if(motorRpm_ >= 540 && motorRpm_ <= 660) poles_ = 12;
    }
    else if (lineFreq_ == Motor::LineFrequency::FREQ50){
        if(motorRpm_ >= 2700 && motorRpm_ <= 3300) poles_ = 2;
        else if(motorRpm_ >= 1350 && motorRpm_ <= 1650) poles_ = 4;
        else if(motorRpm_ >= 900 && motorRpm_ <= 1100) poles_ = 6;
        else if(motorRpm_ >= 675 && motorRpm_ <= 825) poles_ = 8;
        else if(motorRpm_ >= 540 && motorRpm_ <= 660) poles_ = 10;
        else if(motorRpm_ >= 450 && motorRpm_ <= 550) poles_ = 12;
    }

    /*
     * Backup case when the Rpm does not fall within any range. Currently the equation for 60 Hz is used. 50 Hz equation
     * is not available at the time of implementing this.
     */

    if (poles_ == 0){
        if (motorRpm_ > 3600) {
            poles_ = 2;
        } else {
            if (floor(floor(7200 / motorRpm_) / 2) * 2 > 12) {
                poles_ = 12;
            } else {
                poles_ = static_cast<int>(floor(floor(7200 / motorRpm_) / 2) * 2);
            }
        }
    }

    return poles_;
}
