/**
 * @brief Contains the definition of functions of OptimalSpecificSpeed class.
 *      calculate(): Calculates the Optimal Specific Speed
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/pump/OptimalSpecificSpeed.h"

double OptimalSpecificSpeed::calculate() {
    double specificSpeed = rpm * sqrt(flowRate) / (pow((head / stageCount), 0.75));
    return specificSpeed;
}
