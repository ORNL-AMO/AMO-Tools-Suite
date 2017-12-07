/**
 * @brief Contains the declaration of MotorPowerFactor class including the getters and setters as well as the calculators.
 *          for motor efficiency.
 *      calculate(): Calculates the motor power factor
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_MOTORPOWERFACTOR_H
#define AMO_LIBRARY_MOTORPOWERFACTOR_H

#include "psat/Motor.h"
#include "psat/FieldData.h"

class MotorPowerFactor {
public:
    /**
     * Constructor
     * @param motorRatedPower double, Rated Power of motor in hp
     * @param loadFactor double, load factor - unitless
     * @param motorCurrent double, current of motor in A
     * @param motorEfficiency double, motor efficiency as %
     * @param ratedVoltage double, rated voltage as V
     */
    MotorPowerFactor(
        double motorRatedPower,
        double loadFactor,
        double motorCurrent,
        double motorEfficiency,
        double ratedVoltage
    ) :
        motorRatedPower_(motorRatedPower),
        loadFactor_(loadFactor),
        motorCurrent_(motorCurrent),
        motorEfficiency_(motorEfficiency),
        ratedVoltage_(ratedVoltage)
    {}

    /**
     * Constructor when the load factor is 0.
     * When the load factor is zero, you need to calculate the efficiency 0.25 load factor, hence the extra parameters.
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     * @param motorRpm double, RPM of motor
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     * @param specifiedEfficiency double, specified efficiency as %
     * @param motorRatedPower Rated Power of motor in hp
     * @param loadFactor double, load factor - unitless
     * @param motorCurrent double, motor current in A
     * @param motorEfficiency double, motor efficiency as %
     * @param ratedVoltage double, rated voltage in V
     */

    MotorPowerFactor(
        Motor::LineFrequency lineFrequency,
        double motorRpm,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double motorRatedPower,
        double loadFactor,
        double motorCurrent,
        double motorEfficiency,
        double ratedVoltage
    ) :
        lineFrequency_(lineFrequency),
        motorRpm_(motorRpm),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        motorRatedPower_(motorRatedPower),
        loadFactor_(loadFactor),
        motorCurrent_(motorCurrent),
        motorEfficiency_(motorEfficiency),
        ratedVoltage_(ratedVoltage)
    {};

    /**
     * Calculates the motor power factor
     *
     * @return double, power factor - unitless
     */
    double calculate();

    /**
     * Gets the line frequency
     *
     * @return Motor::LineFrequency, classification of line frequency in Hz
     */
    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    /**
     * Sets the line frequency
     *
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     *
     */
    void setLineFrequency(Motor::LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    /**
     * Gets the motor RPM
     *
     * @return double, motor RPM
     */
    double getMotorRpm() const {
        return motorRpm_;
    }

    /**
     * Sets the motor RPM
     *
     * @param motorRpm double, RPM of motor
     *
     */
    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    /**
     * Gets the efficiency class
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
     */
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

    double motorRatedPower_;
    double loadFactor_;
    double motorCurrent_;
    double motorEfficiency_;
    double ratedVoltage_;

};


#endif //AMO_LIBRARY_MOTORPOWERFACTOR_H
