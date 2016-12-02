//
// Created by Mishra, Subhankar on 10/21/16.
//

#ifndef AMO_LIBRARY_OPTIMALSPECIFICSPEEDCORRECTION_H
#define AMO_LIBRARY_OPTIMALSPECIFICSPEEDCORRECTION_H

#include "../Pump.h"

class OptimalSpecificSpeedCorrection {
public:
    OptimalSpecificSpeedCorrection(
        Pump::Style style,
        double specificSpeed
    ):
        specificSpeed_(specificSpeed),
        style_(style)
    {};

    double calculate();
private:
    double specificSpeed_;
    Pump::Style style_;

    double specificSpeedCorrection_ = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALSPECIFICSPEEDCORRECTION_H
