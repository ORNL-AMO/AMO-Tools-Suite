/**
 * @file Implementation of Power Factor (PF) Calculations
 * @author Created by Omer Aziz (omerb).
 */

#include "electrical/PowerFactor.h"

PowerFactor::Output PowerFactor::calculate(const Mode mode, const double input1, const double input2, const double inputPowerFactor) {
    const double PI = 3.141592653589793238463;

    switch(mode) {
        case ApparentPower_RealPower:
            apparentPower = input1;
            realPower = input2;

            powerFactor = realPower / apparentPower;
            reactivePower = apparentPower * sin(acos(powerFactor));
            break;
        case ApparentPower_ReactivePower:
            apparentPower = input1;
            reactivePower = input2;

            powerFactor = cos(asin(reactivePower/apparentPower));
            realPower = apparentPower * powerFactor;
            break;
        case ApparentPower_PhaseAngle:
            apparentPower = input1;
            phaseAngle = input2 * PI / 180;

            powerFactor = cos(phaseAngle);
            realPower = apparentPower * powerFactor;
            reactivePower = apparentPower * sin(phaseAngle);
            break;
        case ApparentPower_PowerFactor:
            apparentPower = input1;
            powerFactor = input2;

            realPower = apparentPower * powerFactor;
            reactivePower = apparentPower * sin(acos(powerFactor));
            break;

        case RealPower_ReactivePower:
            realPower = input1;
            reactivePower = input2;

            powerFactor = cos(atan(reactivePower / realPower));
            apparentPower = realPower / powerFactor;
            break;
        case RealPower_PhaseAngle:
            realPower = input1;
            phaseAngle = input2 * PI / 180;

            powerFactor = cos(phaseAngle);
            reactivePower = realPower * tan(phaseAngle);
            apparentPower = realPower / powerFactor;
            break;
        case RealPower_PowerFactor:
            realPower = input1;
            powerFactor = input2;

            apparentPower = realPower / powerFactor;
            reactivePower = realPower * tan(acos(powerFactor));
            break;

        case ReactivePower_PhaseAngle:
            reactivePower = input1;
            phaseAngle = input2 * PI / 180;

            realPower = reactivePower / tan(phaseAngle);
            apparentPower = reactivePower / sin(phaseAngle);
            powerFactor = realPower / apparentPower;
            break;
        case ReactivePower_PowerFactor:
            reactivePower = input1;
            powerFactor = input2;

            apparentPower = reactivePower / sin(acos(powerFactor));
            realPower = apparentPower * powerFactor;
            break;
    }
    phaseAngle = acos(powerFactor) * 180 / PI;

    const double realDemand = realPower / inputPowerFactor;
    const double proposedReactivePower = realPower * tan(acos(inputPowerFactor));

    return {realPower, reactivePower, apparentPower, powerFactor, phaseAngle,
            realDemand, fabs(realDemand - apparentPower),
            proposedReactivePower, reactivePower - proposedReactivePower};
}
