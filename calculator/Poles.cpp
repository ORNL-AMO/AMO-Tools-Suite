//
// Created by Mishra, Subhankar on 10/3/16.
//

#include "Poles.h"

int Poles::calculate() {
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
    return poles_;
}