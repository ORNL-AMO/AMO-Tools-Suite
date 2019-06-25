/**
 * @brief Contains the definition of functions of OptimalMotorPower class.
 *      calculate(): Calculates the Optimal Motor Power
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <calculator/motor/MotorCurrent.h>
#include <calculator/motor/Poles.h>
#include "calculator/motor/OptimalMotorPower.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/motor/MotorPower.h"


OptimalMotorPower::Output OptimalMotorPower::calculate() {
    double tempLoadFraction = 0.00;
    double mspkW;
    double tempMsp = 0, tempMsp1 = 0, tempMsp2 = 0, powerE1 = 0, powerE2 = 0;
    double eff1 = 0, eff2 = 0, lf = 0, current1 = 0, current2 = 0;

    double power, efficiency, current, powerFactor;

    while (true) {
        MotorCurrent optimalMotorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                         specifiedEfficiency, tempLoadFraction, ratedVoltage);
        current = optimalMotorCurrent.calculateOptimalCurrent();
        //Adjustment to current based on measured Voltage
        current = current * ((((fieldVoltage / ratedVoltage) - 1) * (1 + (-2 * tempLoadFraction))) + 1);
        MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
        efficiency = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
        //Similar to motorpowerfactor in existing case instead of ratedVoltage
        MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                          motorRatedPower, tempLoadFraction, current, efficiency, fieldVoltage);
        powerFactor = motorPowerFactor.calculate();

        power = MotorPower(fieldVoltage, current, powerFactor).calculate();
        tempMsp = power * efficiency;
        // Converting to KW for matching purpose.
        mspkW = optimalMotorShaftPower * 0.746;

        if (tempMsp > mspkW || tempLoadFraction > 1.5) {
            powerE2 = power;
            eff2 = efficiency;
            current2 = current;
            tempMsp2 = tempMsp;
            break;
        } else {
            powerE1 = power;
            lf = tempLoadFraction;
            eff1 = efficiency;
            current1 = current;
            tempMsp1 = tempMsp;
            tempLoadFraction += 0.01;
        }
    }

    // Calculate Fractional Index
    const double motorMspdiff = tempMsp2 - tempMsp1;
    const double measuredMspdiff = mspkW - tempMsp1;
    const double fractionalIndex = lf + ((measuredMspdiff / motorMspdiff) / 100);

    // Linear Interpolation of values
    //double adjCurrent1 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf)) + 1) * current1;
    //double adjCurrent2 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf2)) + 1) * current2;
    //current = adjCurrent1 + 100 * (fractionalIndex - lf) * (adjCurrent2 - adjCurrent1);
    // current = current1 + 100 * (fractionalIndex - lf) * (current2 - current1);
    current = (current1 + 100 * (fractionalIndex - lf) * (current2 - current1)) * 460 / ratedVoltage;
    efficiency = eff1 + 100 * (fractionalIndex - lf) * (eff2 - eff1);
    power = powerE1 + 100 * (fractionalIndex - lf) * (powerE2 - powerE1);
    powerFactor = power / (current * fieldVoltage * std::sqrt(3) / 1000);

    return {power, efficiency, current, powerFactor, fractionalIndex};
}
