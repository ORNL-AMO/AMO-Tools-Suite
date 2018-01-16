#include <cmath>
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"

double OptimalSpecificSpeedCorrection::calculate() {
    const double notVTP[7][2] = {{14.884085,           6.5703317},
                           {-0.021342141,        -0.010048327},
                           {0.0000121172,        0.0000061475098},
                           {-0.0000000031885957, -0.0000000019659725},
                           {1.4907927E-13,       3.5079978E-13},
                           {1.2855352E-16,       -3.2272033E-17},
                           {-2.3798184E-20,      1.1881188E-21}};

    const double VTP[7][2] = {{14.788539,           4.0559384},
                        {-0.022490348,        -0.0026632249},
                        {0.000017226359,      0.0000006761157},
                        {-0.0000000075690542, -0.000000000087766773},
                        {1.8893534E-12,       6.5103425E-15},
                        {-2.4834106E-16,      -2.5380141E-19},
                        {1.3345507E-20,       4.007753E-24}};
    // Specific Speed comes as input.
    // double specificSpeed = rpm * sqrt(flowRate) / (pow((head / stageCount), 0.75));

    //double speedCorrection = 0;
    if (style == Pump::Style::VERTICAL_TURBINE) {
        std::size_t index = (specificSpeed < 4550) ? 0 : 1;
        return std::fmax((VTP[0][index] + (VTP[1][index] * specificSpeed) +
                          (VTP[2][index] * pow(specificSpeed, 2)) +
                          (VTP[3][index] * pow(specificSpeed, 3)) +
                          (VTP[4][index] * pow(specificSpeed, 4)) +
                          (VTP[5][index] * pow(specificSpeed, 5)) +
                          (VTP[6][index] * pow(specificSpeed, 6))), 0) / 100;
    }

    std::size_t index = (specificSpeed < 2530) ? 0 : 1;
    return std::fmax((notVTP[0][index] + (notVTP[1][index] * specificSpeed) +
                      (notVTP[2][index] * pow(specificSpeed, 2)) +
                      (notVTP[3][index] * pow(specificSpeed, 3)) +
                      (notVTP[4][index] * pow(specificSpeed, 4)) +
                      (notVTP[5][index] * pow(specificSpeed, 5)) +
                      (notVTP[6][index] * pow(specificSpeed, 6))), 0) / 100;
}
