//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTOREFFICIENCY_H
#define AMO_LIBRARY_MOTOREFFICIENCY_H

#include "../Motor.h"
#include "../FieldData.h"
#include <cmath>
#include "CurveFitVal.h"

class MotorEfficiency {
public:

    MotorEfficiency(//double lineFrequency,
            double motorRpm, Motor::EfficiencyClass efficiencyClass, double motorRatedPower,
            double loadFactor)
            : motorRpm_(motorRpm),
              efficiencyClass_(efficiencyClass),
              motorRatedPower_(
                      motorRatedPower), loadFactor_(loadFactor) {};

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

    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    void setActualEfficiency(double actualEfficiency) {
        actualEfficiency_ = actualEfficiency;
    }

private:
    Motor::LineFrequency lineFrequency_;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double hp_;
    FieldData::LoadEstimationMethod loadEstimationMethod_;
    double motorKwh_;
    double motorAmps_;
    //double ratedVoltage_;
    double actualEfficiency_;
    double motorRatedPower_;
    double loadFactor_ = 0;
};


#endif //AMO_LIBRARY_MOTOREFFICIENCY_H
