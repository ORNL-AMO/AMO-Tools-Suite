/**
 * @brief Contains the definition of functions of OptimalPumpEfficiency class.
 *      calculate(): Calculates the pump efficiency after correction
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalPumpEfficiency.h"

using namespace std;

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
    OptimalDeviationFactor optimalDeviationFactor(flowRate_);
    double positiveDeviationFactor = optimalDeviationFactor.calculate();
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
