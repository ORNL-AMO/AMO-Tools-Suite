/**
 * @brief Contains the declaration of MotorEfficiency class including the getters and setters as well as the calculators for motor efficiency.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTOREFFICIENCY_H
#define AMO_LIBRARY_MOTOREFFICIENCY_H

#include "../Motor.h"
#include "../FieldData.h"
#include <cmath>
#include "CurveFitVal.h"
#include "MotorEfficiency25.h"

class MotorEfficiency {
public:
    /**
     * Constructor
     * @param lineFrequency
     * @param motorRpm
     * @param efficiencyClass
     * @param specifiedEfficiency
     * @param motorRatedPower
     * @param loadFactor
     * @return
     */
    MotorEfficiency(Motor::LineFrequency lineFrequency,
            double motorRpm, Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double motorRatedPower,
            double loadFactor)
            : lineFrequency_(lineFrequency), motorRpm_(motorRpm),
              efficiencyClass_(efficiencyClass),
              specifiedEfficiency_(specifiedEfficiency),
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

    double getKWloss0() const{
        return kWloss0;
    }

private:
    Motor::LineFrequency lineFrequency_;
    double motorEff_ = 0.0;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_;
    double hp_;
    FieldData::LoadEstimationMethod loadEstimationMethod_;
    double motorKwh_;
    double motorAmps_;
    double kWloss0 = 0.0;
    //double ratedVoltage_;
    double actualEfficiency_;
    double motorRatedPower_;
    double loadFactor_ = 0;
    std::vector<double> motorEfficiency_;
};


#endif //AMO_LIBRARY_MOTOREFFICIENCY_H
