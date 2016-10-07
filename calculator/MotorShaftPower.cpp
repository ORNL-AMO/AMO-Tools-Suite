//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"
#include "MotorEfficiency.h"
#include "MotorPower.h"
#include "MotorCurrent.h"
#include "MotorPowerFactor.h"

double MotorShaftPower::calculate() {
    if (loadEstimationMethod_ == FieldData::LoadEstimationMethod::POWER) {
        tempLoadFraction_ = 0.01;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower_, motorRPM_, efficiencyClass_, specifiedEfficiency_, tempLoadFraction_, ratedVoltage_, fullLoadAmps_ );
            current = motorCurrent.calculate();
            MotorEfficiency motorEfficiency(motorRPM_, efficiencyClass_, specifiedEfficiency_,  motorRatedPower_, tempLoadFraction_);
            eff = motorEfficiency.calculate();
            MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);

            pf = motorPowerFactor.calculate();
            MotorPower motorPower(ratedVoltage_, current, pf);
            power = motorPower.calculate();
            if (power > fieldPower_ || tempLoadFraction_ > 1.5) {
                powerE2 = power;
                lf2 = tempLoadFraction_;
                eff2 = eff;
                pf2 = pf;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                powerE1 = power;
                lf1 = tempLoadFraction_;
                eff1 = eff;
                pf1 = pf;
                tempLoadFraction_ += 0.01;
            }
        }

        double motorPowerdiff_ = powerE2 - powerE1;
        double measuredMotorPowerdiff_ = fieldPower_ - powerE1;
        double fractionalIndex_ = lf1 + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
        eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
        double adjpf1 = pf1 / (((((fieldVoltage_ / ratedVoltage_) - 1) * (((-2) * lf1) + 1)) + 1) *
                               (fieldVoltage_ / ratedVoltage_));
        double adjpf2 = pf2 / (((((fieldVoltage_ / ratedVoltage_) - 1) * (((-2) * lf2) + 1)) + 1) *
                               (fieldVoltage_ / ratedVoltage_));
        pf = adjpf1 + 100 * (fractionalIndex_ - lf1) * (adjpf2 - adjpf1);

        // Adjust pf based on specified FLA
        pf = pf / (fullLoadAmps_/estimatedFLA);

        //Current output
        current = fieldPower_ / (fieldVoltage_ * sqrt(3) * pf / 1000);
        // Output in kW
        motorShaftPower_ = fieldPower_ * eff;
        // Output in hP
        motorShaftPower_ = motorShaftPower_ / 0.746;
        // Electric power is same as Field value when load estimation method is POWER
        power = fieldPower_;
        return motorShaftPower_;
    } else {
        // Load estimation method is current.
        tempLoadFraction_ = 0.01;
        while (true) {
            MotorCurrent motorCurrent(motorRatedPower_, motorRPM_, efficiencyClass_, specifiedEfficiency_, tempLoadFraction_, ratedVoltage_, fullLoadAmps_);
            current = motorCurrent.calculate();
            if (current > fieldCurrent_ || tempLoadFraction_ > 1.5) {
                MotorEfficiency motorEfficiency(motorRPM_, efficiencyClass_,  specifiedEfficiency_, motorRatedPower_, tempLoadFraction_);
                eff = motorEfficiency.calculate();
                MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);
                pf = motorPowerFactor.calculate();
                MotorPower motorPower(ratedVoltage_, current, pf);
                power = motorPower.calculate();
                current2 = current;
                powerE2 = power;
                lf2 = tempLoadFraction_;
                eff2 = eff;
                pf2 = pf;
                estimatedFLA = motorCurrent.getEstimatedFLA();
                break;
            } else {
                tempLoadFraction_ += 0.01;
            }
        }
        //Dropping load fraction by 0.01
        tempLoadFraction_ -= 0.01;
        MotorCurrent motorCurrent1(motorRatedPower_, motorRPM_, efficiencyClass_, specifiedEfficiency_, tempLoadFraction_, ratedVoltage_, fullLoadAmps_);
        current = motorCurrent1.calculate();
        MotorEfficiency motorEfficiency(motorRPM_, efficiencyClass_, specifiedEfficiency_, motorRatedPower_, tempLoadFraction_);
        eff = motorEfficiency.calculate();
        MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(ratedVoltage_, current, pf);
        power = motorPower.calculate();
        current1 = current;
        powerE1 = power;
        lf1 = tempLoadFraction_;
        eff1 = eff;
        pf1 = pf;

        // Adjust pf based on specified FLA
        pf = pf / (fullLoadAmps_/estimatedFLA);


        // Very similar to the Power case above. May be convert to a function?

        // Adjust current
        double adjCurrent1 = (((fieldVoltage_ / ratedVoltage_) - 1) * (1 - (2 * lf1)) + 1) * current1;
        double adjCurrent2 = (((fieldVoltage_ / ratedVoltage_) - 1) * (1 - (2 * lf2)) + 1) * current2;
        double currentDiff = adjCurrent2 - adjCurrent1;
        double measuredCurrentDiff = fieldCurrent_ - adjCurrent1;
        double fractionalIndex_ = lf1 + ((measuredCurrentDiff / currentDiff) / 100);

        current = fieldCurrent_;
        eff = eff1 + 100 * (fractionalIndex_ - lf1) * (eff2 - eff1);
        power = powerE1 + 100 * (fractionalIndex_ - lf1) * (powerE2 - powerE1);
        // Below is not giving correct answer.
        //pf = power / (current * fieldPower_ * sqrt(3) / 1000);
        //std::cout << "PF: " << pf << std::endl;
        // Output in kW
        motorShaftPower_ = fieldPower_ * eff;
        // Output in hP
        motorShaftPower_ = motorShaftPower_ / 0.746;
        return motorShaftPower_;
    }
}

double MotorShaftPower::calculateCurrent() {
    return current;
}

double MotorShaftPower::calculateEfficiency() {
    return eff;
}

double MotorShaftPower::calculatePowerFactor() {
    // Adjusted Pf
    return pf;
}

double MotorShaftPower::calculatePower(){
    //Returns motor power in kWe
    return power;
}

double MotorShaftPower::calculateEstimatedFLA(){
    return estimatedFLA;
}
