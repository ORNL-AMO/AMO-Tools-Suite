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
//    const double specificHeatGassesAvgTemp = (leakageGasTemperature_ + 60.0) / 2.0;

	const double cfh = 1655 * coefficient_ * ( openingArea_ * 144 ) * pow( draftPressure_ / specificGravity_, 0.5 );


    const double scfh = cfh * pow( 520.0 / ( 460.0 + leakageGasTemperature_ ), 0.5 );

	// TODO find out if the documentation means tFurnace (in the code here) or the input parameter T_furnace (leakageGasTemperature_ here)
	// TODO neither value produces the right numbers according to the documentation
//	const double calc = (ambientTemperature_ + tFurnace) / 2.0;
	const double calc = (ambientTemperature_ + leakageGasTemperature_) / 2.0;
	const double cpm = 0.2371 - (9 * pow(10, -6) * calc) + (7 * pow(10, -8) * pow(calc, 2)) - ((3 * pow(10, -11)) * pow(calc, 3));
	const double cpsv = 0.0793 * cpm;

//    exfiltratedGasesHeatContent_ = cfh * specificHeatGassesAvgTemp * (leakageGasTemperature_ - ambientTemperature_);
    exfiltratedGasesHeatContent_ = cpsv * scfh * (leakageGasTemperature_ - ambientTemperature_);

    return exfiltratedGasesHeatContent_;
}