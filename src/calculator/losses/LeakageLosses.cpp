/**
 * @file
 * @brief Contains the implementation of the gas leakage losses calculations.
 *
 * @author Gina Accawi (accawigk), Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/losses/LeakageLosses.h"

double LeakageLosses::getExfiltratedGasesHeatContent() {
    const double tFurnace = specificGravity_ * ( 520.0 / ( 460 + leakageGasTemperature_ ) );
    const double specificHeatGassesAvgTemp = (leakageGasTemperature_ + 60.0) / 2.0;
    const double cfh = 1655 * 0.8052 * ( openingArea_ * 10.764 * 144 ) * pow( draftPressure_ / tFurnace, 0.5 );
    const double scfh = cfh * pow( 520.0 / ( 460.0 + leakageGasTemperature_ ), 0.5 );
    exfiltratedGasesHeatContent_ = cfh * specificHeatGassesAvgTemp * (leakageGasTemperature_ - ambientTemperature_);

    return exfiltratedGasesHeatContent_;
}