//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpEfficiency.h"

double OptimalPumpEfficiency::calculate() {
    /*
     * Double Suction
     */
    double jcoeff[5][2] = {{90.190375,     91.0},
                           {-7.8068742,    -3.6664629},
                           {0.00033366482, 0.0001264433},
                           {-8.1364684,    -14.697275},
                           {0.0026659434,  0.00072855045}};
    /*
     * Vertical Turbine
     */
    double vcoeff[5][3] = {{87.456119,     89.899894,     90.124016},
                           {-9.3556039,    -5.9800814,    -1.7332611},
                           {0.00067139092, 0.00019480643, 0.00014953651},
                           {-9.4309496,    -7.0638099,    -3.3197451},
                           {0.0039344122,  0.0010440162,  0.00015232542}};

    double pumpEfficiency = 0.0;
    int range = 0;
    switch (style_) {
        case Pump::Style::DOUBLE_SUCTION:
            if (flowRate_ < 9000) {
                range = 0;
            } else {
                range = 1;
            }
            pumpEfficiency = (jcoeff[0][range] + (jcoeff[1][range] * exp(-jcoeff[2][range] * flowRate_) +
                                                  jcoeff[3][range] * exp(-jcoeff[4][range] * flowRate_)));
            break;
        case Pump::Style::VERTICAL_TURBINE:
            break;
        case Pump::Style::LARGE_END_SUCTION:
            break;
        case Pump::Style::END_SUCTION_ANSI_API:
            break;
        case Pump::Style::MULTISTAGE_BOILER_FEED:
            break;
        case Pump::Style::END_SUCTION_STOCK:
            break;
        case Pump::Style::API_DOUBLE_SUCTION:
            //same as Pump::Style::END_SUCTION_STOCK
            break;
        case Pump::Style::END_SUCTION_SEWAGE:
            break;
        case Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE:
            //same as Pump::Style::END_SUCTION_SEWAGE
            break;
        case Pump::Style::END_SUCTION_SLURRY:
            break;
        case Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY:
            break;
    }

    /*
     * You may have individual functions for each also.
     */
    /*
     * Viscosity Correction Factor
     */
    double parameterB =
            26.6 * (pow(kinematicViscosity_, 0.5) * pow(head_, 0.0625)) / (pow(flowRate_, 0.375) * pow(rpm_, 0.25));
    double viscosityCorrectionFactor = std::fmin(1, (pow(parameterB, -(0.0547 * pow(parameterB, 0.69)))));
    /*
     * Speed Correction
     */
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
    double specificSpeed = rpm_ * sqrt(flowRate_) / (pow((head_ / stageCount_), 0.75));
    double speedCorrection = 0;
    int speedCoeffChooser = 0;
    if (style_ == Pump::Style::VERTICAL_TURBINE) {
        if (specificSpeed < 4550)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        speedCorrection = std::fmax((VTP[0][speedCoeffChooser] + (VTP[1][speedCoeffChooser] * specificSpeed) +
                                     (VTP[2][speedCoeffChooser] * pow(specificSpeed, 2)) +
                                     (VTP[3][speedCoeffChooser] * pow(specificSpeed, 3)) +
                                     (VTP[4][speedCoeffChooser] * pow(specificSpeed, 4)) +
                                     (VTP[5][speedCoeffChooser] * pow(specificSpeed, 5)) +
                                     (VTP[6][speedCoeffChooser] * pow(specificSpeed, 6))), 0) / 100;
    } else {
        if (specificSpeed < 2530)
            speedCoeffChooser = 0;
        else
            speedCoeffChooser = 1;
        speedCorrection = std::fmax((notVTP[0][speedCoeffChooser] + (notVTP[1][speedCoeffChooser] * specificSpeed) +
                                     (notVTP[2][speedCoeffChooser] * pow(specificSpeed, 2)) +
                                     (notVTP[3][speedCoeffChooser] * pow(specificSpeed, 3)) +
                                     (notVTP[4][speedCoeffChooser] * pow(specificSpeed, 4)) +
                                     (notVTP[5][speedCoeffChooser] * pow(specificSpeed, 5)) +
                                     (notVTP[6][speedCoeffChooser] * pow(specificSpeed, 6))), 0) / 100;
    }

    /*
     * positiveDeviationFactor
     */
    double positiveDeviationFactor;
    optimalEfficiency_ = (pumpEfficiency * viscosityCorrectionFactor - speedCorrection) * positiveDeviationFactor;
    return optimalEfficiency_;
}
