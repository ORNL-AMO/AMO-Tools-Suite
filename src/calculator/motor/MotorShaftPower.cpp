#include <cmath>
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPower.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorPowerFactor.h"

MotorShaftPower::Output MotorShaftPower::calculate() {
    double powerFactor, efficiency, current, power, estimatedFLA;

    if (loadEstimationMethod == Motor::LoadEstimationMethod::POWER) {
        double tempLoadFraction = 0.01;
	    double powerE1 = 0, powerE2 = 0, lf1 = 0, lf2 = 0, eff1 = 0, eff2 = 0, pf1 = 0, pf2 = 0;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage);
            current = motorCurrent.calculateCurrent(fullLoadAmps);
            MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
            efficiency = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
            MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                              motorRatedPower, tempLoadFraction, current, efficiency, ratedVoltage);
            powerFactor = motorPowerFactor.calculate();
            MotorPower motorPower(ratedVoltage, current, powerFactor);
            power = motorPower.calculate();
            if (power > fieldPower || tempLoadFraction > 1.5) {
                powerE2 = power;
                lf2 = tempLoadFraction;
                eff2 = efficiency;
                pf2 = powerFactor;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                powerE1 = power;
                lf1 = tempLoadFraction;
                eff1 = efficiency;
                pf1 = powerFactor;
                tempLoadFraction += 0.01;
            }
        }

        const double motorPowerdiff = powerE2 - powerE1;
        const double measuredMotorPowerdiff = fieldPower - powerE1;
        const double fractionalIndex = lf1 + ((measuredMotorPowerdiff / motorPowerdiff) / 100);
        efficiency = eff1 + 100 * (fractionalIndex - lf1) * (eff2 - eff1);
        const double adjpf1 = pf1 / ((((fieldVoltage / ratedVoltage - 1) * (-2 * lf1 + 1)) + 1) *
                                     (fieldVoltage / ratedVoltage));
        const double adjpf2 = pf2 / ((((fieldVoltage / ratedVoltage - 1) * (-2 * lf2 + 1)) + 1) *
                                     (fieldVoltage / ratedVoltage));
        powerFactor = adjpf1 + 100 * (fractionalIndex - lf1) * (adjpf2 - adjpf1);

        /**
         * Adjust powerFactor based on specified FLA
         * This does not happen in the Excel sheet during the final calculations.
         * powerFactor = powerFactor / (fullLoadAmps_/estimatedFLA);
        */
        current = fieldPower / (fieldVoltage * std::sqrt(3) * powerFactor / 1000);
        /// Output in hp
        auto const motorShaftPower = (fieldPower * efficiency) / 0.746;
        /// Electric power is same as Field value when load estimation method is POWER
        power = fieldPower;
        return {motorShaftPower, current, powerFactor, efficiency, power, estimatedFLA, fractionalIndex};
    } else { /// When the load estimation method is Current.
        double tempLoadFraction = 0.00;
        double powerE1, powerE2, lf1, lf2, eff1, eff2, current1, current2;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage);
            current = motorCurrent.calculateCurrent(fullLoadAmps);
            if (current > fieldCurrent || tempLoadFraction > 1.5) {
                MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
                efficiency = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
                MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                                  motorRatedPower, tempLoadFraction, current, efficiency, ratedVoltage);
                powerFactor = motorPowerFactor.calculate();
                MotorPower motorPower(ratedVoltage, current, powerFactor);
                power = motorPower.calculate();
                current2 = current;
                powerE2 = power;
                lf2 = tempLoadFraction;
                eff2 = efficiency;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            }
            tempLoadFraction += 0.01;
        }
        /// Dropping load fraction by 0.01
        tempLoadFraction -= 0.01;
        MotorCurrent motorCurrent1(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency,
                                   tempLoadFraction, ratedVoltage);
        current = motorCurrent1.calculateCurrent(fullLoadAmps);
        MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
        efficiency = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
        powerFactor = MotorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                       motorRatedPower, tempLoadFraction, current, efficiency, ratedVoltage).calculate();
        MotorPower motorPower(ratedVoltage, current, powerFactor);
        power = motorPower.calculate();
        current1 = current;
        powerE1 = power;
        lf1 = tempLoadFraction;
        eff1 = efficiency;

        /// Adjust powerFactor based on specified FLA
//        powerFactor = powerFactor / (fullLoadAmps / estimatedFLA);

        /// Adjust current
        const double adjCurrent1 = ((fieldVoltage / ratedVoltage - 1) * (1 - 2 * lf1) + 1) * current1;
        const double adjCurrent2 = ((fieldVoltage / ratedVoltage - 1) * (1 - 2 * lf2) + 1) * current2;
        const double currentDiff = adjCurrent2 - adjCurrent1;
        const double measuredCurrentDiff = fieldCurrent - adjCurrent1;
        const double fractionalIndex = lf1 + (measuredCurrentDiff / currentDiff) / 100;

        current = fieldCurrent;
        efficiency = eff1 + 100 * (fractionalIndex - lf1) * (eff2 - eff1);
        power = powerE1 + 100 * (fractionalIndex - lf1) * (powerE2 - powerE1);

        powerFactor = power / (current * fieldVoltage * std::sqrt(3) / 1000);
        /// Output in hp
        double const motorShaftPower = (power * efficiency) / 0.746;
        return {motorShaftPower, current, powerFactor, efficiency, power, estimatedFLA, fractionalIndex};
    }
}
