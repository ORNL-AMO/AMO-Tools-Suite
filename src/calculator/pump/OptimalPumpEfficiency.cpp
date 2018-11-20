/**
 * @brief Contains the definition of functions of OptimalPumpEfficiency class.
 *      calculate(): Calculates the pump efficiency after correction
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/pump/OptimalPumpEfficiency.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalSpecificSpeed.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/OptimalDeviationFactor.h"

double OptimalPumpEfficiency::calculate() {

    OptimalPrePumpEff optimalPrePumpEff(style, flowRate);
    prePumpEfficiency = optimalPrePumpEff.calculate();
    /*
     * You may have individual functions for each also.
     */
    /*
     * Viscosity Correction Factor
     */
    double parameterB = 26.6 * (std::pow(kinematicViscosity, 0.5) * std::pow(head, 0.0625))
                        / (std::pow(flowRate, 0.375) * std::pow(rpm, 0.25));
    double viscosityCorrectionFactor = std::fmin(1, (std::pow(parameterB, -(0.0547 * std::pow(parameterB, 0.69)))));
    /*
     * Speed Correction
     */
    OptimalSpecificSpeed optimalSpecificSpeed(rpm,flowRate, head, stageCount);
    double specificSpeed = optimalSpecificSpeed.calculate();
    OptimalSpecificSpeedCorrection optimalSpecificSpeedCorrection(style, specificSpeed);
    double speedCorrection = optimalSpecificSpeedCorrection.calculate();
    /*
     * positiveDeviationFactor
     */
    OptimalDeviationFactor optimalDeviationFactor(flowRate);
    double positiveDeviationFactor = optimalDeviationFactor.calculate();
    /*
     * Optimal Efficiency
     */
    prePumpEfficiency = prePumpEfficiency / 100;
    optimalEfficiency = (prePumpEfficiency * viscosityCorrectionFactor - speedCorrection) * positiveDeviationFactor;
    return optimalEfficiency;
}
