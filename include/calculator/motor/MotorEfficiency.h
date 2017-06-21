/**
 * @brief Contains the declaration of MotorEfficiency class including the getters and setters as well as the
 * calculators for motor efficiency.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_MOTOREFFICIENCY_H
#define AMO_LIBRARY_MOTOREFFICIENCY_H

#include <vector>
#include "psat/Motor.h"
#include "psat/FieldData.h"

class MotorEfficiency {
public:
    /**
     * Constructor
     * @param lineFrequency Motor::LineFrequency, line frequency in Hz
     * @param motorRpm double, RPM of motor
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     * @param specifiedEfficiency double, specified efficiency as %
     * @param motorRatedPower double, rated power of motor in hp of kW
     * @param loadFactor double, load factor - unitless
     * @return
     */
    MotorEfficiency(
        Motor::LineFrequency lineFrequency,
        double motorRpm,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double motorRatedPower,
        double loadFactor
    ) :
        lineFrequency_(lineFrequency),
        motorRpm_(motorRpm),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        motorRatedPower_(motorRatedPower),
        loadFactor_(loadFactor)
    {};

    /**
     * Calculates the motor efficiency
     *
     * @return double, motor efficiency as %
     */
    double calculate();

    /**
     * Gets the line frequency
     *
     * @return Motor::LineFrequency, line frequency in Hz
     */
    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    /**
     * Sets the line frequency
     *
     * @param lineFrequency Motor::LineFrequency, line frequency in Hz
     *
     * @return nothing
     */
    void setLineFrequency(Motor::LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    /**
     * Gets the RPM of motor
     *
     * @return double, RPM of motor
     */
    double getMotorRpm() const {
        return motorRpm_;
    }

    /**
     * Sets the RPM of motor
     *
     * @param motorRpm double, RPM of motor
     *
     * @return nothing
     */
    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    /**
     * Gets the efficiency class of motor
     *
     * @return Motor::EfficiencyClass, efficiency class of motor
     */
    Motor::EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    /**
     * Sets the efficiency class of motor
     *
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     *
     * @return nothing
     */
    void setEfficiencyClass(Motor::EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }

    /**
     * Gets the horsepower of motor
     *
     * @return double, horsepower of motor
     */
    double getHp() const {
        return hp_;
    }

    /**
     * Sets the horsepower of motor
     *
     * @param hp double, horsepower of motor
     *
     * @return nothing
     */
    void setHp(double hp) {
        hp_ = hp;
    }

    /**
     * Gets the load estimation method
     *
     * @return FieldData::LoadEstimationMethod, load estimation method
     */
    FieldData::LoadEstimationMethod getLoadEstimationMethod() const {
        return loadEstimationMethod_;
    }

    /**
     * Sets the load estimation method
     *
     * @param loadEstimationMethod FieldData::LoadEstimationMethod, load estimation method
     *
     * @return nothing
     */
    void setLoadEstimationMethod(FieldData::LoadEstimationMethod loadEstimationMethod) {
        loadEstimationMethod_ = loadEstimationMethod;
    }

    /**
     * Gets the motor power in kWh
     *
     * @return double, motor power in kWh
     */
    double getMotorKwh() const {
        return motorKwh_;
    }

    /**
     * Sets the motor power in kWh
     *
     * @param motorKwh double, motor power in kWh
     *
     * @return nothing
     */
    void setMotorKwh(double motorKwh) {
        motorKwh_ = motorKwh;
    }

    /**
     * Gets the motor amps
     *
     * @return double, motor amps in A
     */
    double getMotorAmps() const {
        return motorAmps_;
    }

    /**
     * Sets the motor amps
     *
     * @param motorAmps double, motor amps in A
     *
     * @return nothing
     */
    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    /**
     * Gets the actual efficiency of motor
     *
     * @return double, actual efficiency of motor as %
     */
    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    /**
     * Sets the actual efficiency of motor
     *
     * @param actualEfficiency double, actual efficiency of motor as %
     *
     * @return nothing
     */
    void setActualEfficiency(double actualEfficiency) {
        actualEfficiency_ = actualEfficiency;
    }

    /**
     * Gets the loss of power in kW
     *
     * @return double, power loss in kW
     */
    double getKWloss0() const {
        return kWloss0;
    }

    /**
     * Gets the load factor
     *
     * @return double, load factor - unitless
     */
    double getLoadFactor() const {
        return loadFactor_;
    }

    /**
     * Sets the load factor
     *
     * @param loadFactor double, load factor - unitless
     *
     * @return nothing
     */
    void setLoadFactor(double loadFactor) {
        loadFactor_ = loadFactor;
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
