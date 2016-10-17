//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpEfficiency.h"

double OptimalPumpEfficiency::calculate() {

    OptimalPrePumpEff optimalPrePumpEff(style_, achievableEfficiency_, flowRate_);
    pumpEfficiency = optimalPrePumpEff.calculate();
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
    double pdCoeff[5] = {0.10805906,
                         18.077243,
                         0.78231304,
                         30.525232,
                         0.80684022};
    double positiveDeviationFactor =
            1 + (pdCoeff[0] + (pdCoeff[1] * exp(-pdCoeff[2] * log10(flowRate_))) +
                 pdCoeff[3] * exp(-pdCoeff[4] * log10(flowRate_))) / 100;
    /*
     * Optimal Efficiency
     */
    pumpEfficiency = pumpEfficiency/100;
    optimalEfficiency_ = (pumpEfficiency * viscosityCorrectionFactor - speedCorrection) * positiveDeviationFactor;
    if(style_ == Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY){
        optimalEfficiency_ = achievableEfficiency_;
    }
    return optimalEfficiency_;
}
