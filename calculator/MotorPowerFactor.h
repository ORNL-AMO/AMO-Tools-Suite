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

/*
    double getLineFrequency() const {
        return lineFrequency_;
    }

    void setLineFrequency(double lineFrequency) {
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

    double getHp() const {
        return hp_;
    }

    void setHp(double hp) {
        hp_ = hp;
    }

    FieldData::LoadEstimationMethod getLoadEstimationMethod() const {
        return loadEstimationMethod_;
    }

    void setLoadEstimationMethod(FieldData::LoadEstimationMethod loadEstimationMethod) {
        loadEstimationMethod_ = loadEstimationMethod;
    }

    double getMotorKwh() const {
        return motorKwh_;
    }

    void setMotorKwh(double motorKwh) {
        motorKwh_ = motorKwh;
    }

    double getMotorAmps() const {
        return motorAmps_;
    }

    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    void setActualEfficiency(double actualEfficiency) {
        actualEfficiency_ = actualEfficiency;
    }
*/

private:
    Motor::LineFrequency lineFrequency_;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double hp_;
    FieldData::LoadEstimationMethod loadEstimationMethod_;
    double specifiedEfficiency_;

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
