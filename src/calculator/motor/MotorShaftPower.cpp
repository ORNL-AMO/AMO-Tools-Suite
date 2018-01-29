#include <cmath>
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPower.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorPowerFactor.h"

double MotorShaftPower::calculate() {
    /**
     * When the load estimation is power
     */
    if (loadEstimationMethod == FieldData::LoadEstimationMethod::POWER) {
        tempLoadFraction = 0.01;
	    double powerE1 = 0, powerE2 = 0, lf1 = 0, lf2 = 0, eff1 = 0, eff2 = 0, pf1 = 0, pf2 = 0;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage);
            current = motorCurrent.calculateCurrent(fullLoadAmps);
            MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
            eff = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
            MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                              motorRatedPower, tempLoadFraction, current, eff, ratedVoltage);
            pf = motorPowerFactor.calculate();
            MotorPower motorPower(ratedVoltage, current, pf);
            power = motorPower.calculate();
            if (power > fieldPower || tempLoadFraction > 1.5) {
                powerE2 = power;
                lf2 = tempLoadFraction;
                eff2 = eff;
                pf2 = pf;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                powerE1 = power;
                lf1 = tempLoadFraction;
                eff1 = eff;
                pf1 = pf;
                tempLoadFraction += 0.01;
            }
        }

        const double motorPowerdiff = powerE2 - powerE1;
        const double measuredMotorPowerdiff = fieldPower - powerE1;
        const double fractionalIndex = lf1 + ((measuredMotorPowerdiff / motorPowerdiff) / 100);
        eff = eff1 + 100 * (fractionalIndex - lf1) * (eff2 - eff1);
        const double adjpf1 = pf1 / ((((fieldVoltage / ratedVoltage - 1) * (-2 * lf1 + 1)) + 1) *
                                     (fieldVoltage / ratedVoltage));
        const double adjpf2 = pf2 / ((((fieldVoltage / ratedVoltage - 1) * (-2 * lf2 + 1)) + 1) *
                                     (fieldVoltage / ratedVoltage));
        pf = adjpf1 + 100 * (fractionalIndex - lf1) * (adjpf2 - adjpf1);

        /**
         * Adjust pf based on specified FLA
         * This does not happen in the Excel sheet during the final calculations.
         * pf = pf / (fullLoadAmps_/estimatedFLA);
        */
        /// Output current
        current = fieldPower / (fieldVoltage * std::sqrt(3) * pf / 1000);
        /// Output in kW
        motorShaftPower = fieldPower * eff;
        /// Output in hP
        motorShaftPower = motorShaftPower / 0.746;
        /// Electric power is same as Field value when load estimation method is POWER
        power = fieldPower;
        return motorShaftPower;
    } else { /// When the load estimation method is Current.
        tempLoadFraction = 0.00;
        double powerE1, powerE2, lf1, lf2, eff1, eff2, current1, current2;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage);
            current = motorCurrent.calculateCurrent(fullLoadAmps);
            if (current > fieldCurrent || tempLoadFraction > 1.5) {
                MotorEfficiency motorEfficiency(lineFrequency, motorRPM, efficiencyClass, motorRatedPower);
                eff = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
                MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                                  motorRatedPower, tempLoadFraction, current, eff, ratedVoltage);
                pf = motorPowerFactor.calculate();
                MotorPower motorPower(ratedVoltage, current, pf);
                power = motorPower.calculate();
                current2 = current;
                powerE2 = power;
                lf2 = tempLoadFraction;
                eff2 = eff;
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
        eff = motorEfficiency.calculate(tempLoadFraction, specifiedEfficiency);
        MotorPowerFactor motorPowerFactor(lineFrequency, motorRPM, efficiencyClass, specifiedEfficiency,
                                          motorRatedPower, tempLoadFraction, current, eff, ratedVoltage);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(ratedVoltage, current, pf);
        power = motorPower.calculate();
        current1 = current;
        powerE1 = power;
        lf1 = tempLoadFraction;
        eff1 = eff;

        /// Adjust pf based on specified FLA
        pf = pf / (fullLoadAmps / estimatedFLA);

        /// Adjust current
        const double adjCurrent1 = ((fieldVoltage / ratedVoltage - 1) * (1 - 2 * lf1) + 1) * current1;
        const double adjCurrent2 = ((fieldVoltage / ratedVoltage - 1) * (1 - 2 * lf2) + 1) * current2;
        const double currentDiff = adjCurrent2 - adjCurrent1;
        const double measuredCurrentDiff = fieldCurrent - adjCurrent1;
        const double fractionalIndex = lf1 + (measuredCurrentDiff / currentDiff) / 100;

        current = fieldCurrent;
        eff = eff1 + 100 * (fractionalIndex - lf1) * (eff2 - eff1);
        power = powerE1 + 100 * (fractionalIndex - lf1) * (powerE2 - powerE1);

        /// Power Factor
        pf = power / (current * fieldVoltage * std::sqrt(3) / 1000);
        /// Output in kW
        motorShaftPower = power * eff;
        /// Output in hP
        motorShaftPower = motorShaftPower / 0.746;
        return motorShaftPower;
    }
}
