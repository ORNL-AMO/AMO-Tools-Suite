//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpEfficiency.h"
#include "OptimalSpecificSpeed.h"
#include "OptimalSpecificSpeedCorrection.h"

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
    OptimalSpecificSpeed optimalSpecificSpeed(rpm_,flowRate_, head_, stageCount_);
    double specificSpeed = optimalSpecificSpeed.calculate();
    OptimalSpecificSpeedCorrection optimalSpecificSpeedCorrection(style_,specificSpeed);
    double speedCorrection = optimalSpecificSpeedCorrection.calculate();
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
