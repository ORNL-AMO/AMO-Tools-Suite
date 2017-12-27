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
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage, fullLoadAmps);
            current = motorCurrent.calculate();
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
                current2 = current;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                powerE1 = power;
                lf1 = tempLoadFraction;
                eff1 = eff;
                pf1 = pf;
                current1 = current;
                tempLoadFraction += 0.01;
            }
        }

        double motorPowerdiff_ = powerE2 - powerE1;
        double measuredMotorPowerdiff_ = fieldPower - powerE1;
        double fractionalIndex_ = lf1 + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
        eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
        double adjpf1 = pf1 / (((((fieldVoltage / ratedVoltage) - 1) * (((-2) * lf1) + 1)) + 1) *
                               (fieldVoltage / ratedVoltage));
        double adjpf2 = pf2 / (((((fieldVoltage / ratedVoltage) - 1) * (((-2) * lf2) + 1)) + 1) *
                               (fieldVoltage / ratedVoltage));
        pf = adjpf1 + 100 * (fractionalIndex_ - lf1) * (adjpf2 - adjpf1);\

        /**
         * Adjust pf based on specified FLA
         * This does not happen in the Excel sheet during the final calculations.
         * pf = pf / (fullLoadAmps_/estimatedFLA);
        */
        /// Output current
        current = fieldPower / (fieldVoltage * sqrt(3) * pf / 1000);
        /// Output in kW
        motorShaftPower = fieldPower * eff;
        /// Output in hP
        motorShaftPower = motorShaftPower / 0.746;
        /// Electric power is same as Field value when load estimation method is POWER
        power = fieldPower;
        return motorShaftPower;
    } else { /// When the load estimation method is Current.
        tempLoadFraction = 0.00;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass,
                                      specifiedEfficiency, tempLoadFraction, ratedVoltage, fullLoadAmps);
            current = motorCurrent.calculate();
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
                pf2 = pf;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                tempLoadFraction += 0.01;
            }
        }
        /// Dropping load fraction by 0.01
        tempLoadFraction -= 0.01;
        MotorCurrent motorCurrent1(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency,
                                   tempLoadFraction, ratedVoltage, fullLoadAmps);
        current = motorCurrent1.calculate();
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
        pf1 = pf;

        /// Adjust pf based on specified FLA
        pf = pf / (fullLoadAmps / estimatedFLA);

        /// Adjust current
        double adjCurrent1 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf1)) + 1) * current1;
        double adjCurrent2 = (((fieldVoltage / ratedVoltage) - 1) * (1 - (2 * lf2)) + 1) * current2;
        double currentDiff = adjCurrent2 - adjCurrent1;
        double measuredCurrentDiff = fieldCurrent - adjCurrent1;
        double fractionalIndex_ = lf1 + ((measuredCurrentDiff / currentDiff) / 100);

        current = fieldCurrent;
        eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
        power = powerE1 + 100 * (fractionalIndex_ - lf1) * (powerE2 - powerE1);

        /// Power Factor
        pf = power / (current * fieldVoltage * sqrt(3) / 1000);
        /// Output in kW
        motorShaftPower = power * eff;
        /// Output in hP
        motorShaftPower = motorShaftPower / 0.746;
        /// Return motor Shaft power
        return motorShaftPower;
    }
}
