//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORPOWERFACTOR_H
#define AMO_LIBRARY_MOTORPOWERFACTOR_H

#include "../Motor.h"
#include "../FieldData.h"
#include <cmath>

class MotorPowerFactor {
public:
    MotorPowerFactor(double motorRatedPower, double loadFactor, double motorCurrent, double motorEfficiency,
                     double ratedVoltage) :

            motorRatedPower_(motorRatedPower), loadFactor_(loadFactor), motorCurrent_(motorCurrent),
            motorEfficiency_(motorEfficiency), ratedVoltage_(ratedVoltage) {}

    // Use this constructor when the loadFraction is 0.

    MotorPowerFactor(Motor::LineFrequency lineFrequency,
                     double motorRpm, Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency,
                     double motorRatedPower, double loadFactor, double motorCurrent, double motorEfficiency,
                     double ratedVoltage)
            : lineFrequency_(lineFrequency), motorRpm_(motorRpm),
              efficiencyClass_(efficiencyClass), specifiedEfficiency_(specifiedEfficiency),
              motorRatedPower_(motorRatedPower), loadFactor_(loadFactor), motorCurrent_(motorCurrent),
              motorEfficiency_(motorEfficiency), ratedVoltage_(ratedVoltage) {};

    double calculate();


    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    void setLineFrequency(Motor::LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    double getMotorRpm() const {
        return motorRpm_;
    }

    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    Motor::EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    void setEfficiencyClass(Motor::EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }


private:
    Motor::LineFrequency lineFrequency_;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_;
    double motorKwInput =0.0;
    double motorkVA = 0.0;

/*
 * 9/9/16: Added new variables for a changed constructor
 */
    double motorRatedPower_;
    double loadFactor_;
    double motorCurrent_;
    double motorEfficiency_;
    double ratedVoltage_;

};


#endif //AMO_LIBRARY_MOTORPOWERFACTOR_H
