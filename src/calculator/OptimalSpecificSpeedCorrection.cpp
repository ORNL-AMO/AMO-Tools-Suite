//
// Created by Mishra, Subhankar on 10/21/16.
//

#include <cmath>
#include "calculator/OptimalSpecificSpeedCorrection.h"

double OptimalSpecificSpeedCorrection::calculate() {
    double notVTP[7][2] = {{14.884085,           6.5703317},
                           {-0.021342141,        -0.010048327},
                           {0.0000121172,        0.0000061475098},
                           {-0.0000000031885957, -0.0000000019659725},
                           {1.4907927E-13,       3.5079978E-13},
                           {1.2855352E-16,       -3.2272033E-17},
                           {-2.3798184E-20,      1.1881188E-21}};

    double VTP[7][2] = {{14.788539,           4.0559384},
                        {-0.022490348,        -0.0026632249},
                        {0.000017226359,      0.0000006761157},
                        {-0.0000000075690542, -0.000000000087766773},
                        {1.8893534E-12,       6.5103425E-15},
                        {-2.4834106E-16,      -2.5380141E-19},
                        {1.3345507E-20,       4.007753E-24}};
    // Specific Speed comes as input.
    // double specificSpeed = rpm_ * sqrt(flowRate_) / (pow((head_ / stageCount_), 0.75));

    //double speedCorrection = 0;
    int speedCoeffChooser = 0;
    if (style_ == Pump::Style::VERTICAL_TURBINE) {
        if (specificSpeed_ < 4550)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        specificSpeedCorrection_ = std::fmax((VTP[0][speedCoeffChooser] + (VTP[1][speedCoeffChooser] * specificSpeed_) +
                                     (VTP[2][speedCoeffChooser] * pow(specificSpeed_, 2)) +
                                     (VTP[3][speedCoeffChooser] * pow(specificSpeed_, 3)) +
                                     (VTP[4][speedCoeffChooser] * pow(specificSpeed_, 4)) +
                                     (VTP[5][speedCoeffChooser] * pow(specificSpeed_, 5)) +
                                     (VTP[6][speedCoeffChooser] * pow(specificSpeed_, 6))), 0) / 100;
    } else {
        if (specificSpeed_ < 2530)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        specificSpeedCorrection_ = std::fmax((notVTP[0][speedCoeffChooser] + (notVTP[1][speedCoeffChooser] * specificSpeed_) +
                                     (notVTP[2][speedCoeffChooser] * pow(specificSpeed_, 2)) +
                                     (notVTP[3][speedCoeffChooser] * pow(specificSpeed_, 3)) +
                                     (notVTP[4][speedCoeffChooser] * pow(specificSpeed_, 4)) +
                                     (notVTP[5][speedCoeffChooser] * pow(specificSpeed_, 5)) +
                                     (notVTP[6][speedCoeffChooser] * pow(specificSpeed_, 6))), 0) / 100;
    }
    return specificSpeedCorrection_;
}
