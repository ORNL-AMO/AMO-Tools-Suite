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

#include <array>
#include <results/InputData.h>
#include <exception>
#include <stdexcept>

class MotorEfficiency {
public:
    /**
     * Constructor
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     * @param motorRpm double, RPM of motor
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     * @param motorRatedPower double, rated power of motor in hp
     */
    MotorEfficiency(
        Motor::LineFrequency lineFrequency,
        double motorRpm,
        Motor::EfficiencyClass efficiencyClass,
        double motorRatedPower
    ) :
        lineFrequency(lineFrequency),
        motorRpm(motorRpm),
        efficiencyClass(efficiencyClass),
        motorRatedPower(motorRatedPower)
    {};

    /**
     * Calculates the motor efficiency
     * @param loadFactor double, load factor - unitless ratio
     * @param specifiedEfficiency, efficiency of SPECIFIED efficiency class motor (optional)
     * @return double, motor efficiency as %
     */
    double calculate(double loadFactor, double specifiedEfficiency = -1);

    /**
     * calculate25intervals(): Calculates the motor efficiency given at 25% intervals of load factor.
     * @return std::array<double, 5> containing motor efficiency at 25% intervals of load factor
     */
	std::array<double, 5> calculate25intervals();

    /**
     * Gets the line frequency
     * @return Motor::LineFrequency, classification of line frequency in Hz
     */
    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency;
    }

    /**
     * Sets the line frequency
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     */
    void setLineFrequency(Motor::LineFrequency lineFrequency) {
        this->lineFrequency = lineFrequency;
    }

    /**
     * Gets the RPM of motor
     * @return double, RPM of motor
     */
    double getMotorRpm() const {
        return motorRpm;
    }

    /**
     * Sets the RPM of motor
     * @param motorRpm double, RPM of motor
     */
    void setMotorRpm(double motorRpm) {
        this->motorRpm = motorRpm;
    }

    /**
     * Gets the efficiency class of motor
     * @return Motor::EfficiencyClass, efficiency class of motor
     */
    Motor::EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass;
    }

    /**
     * Sets the efficiency class of motor
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     */
    void setEfficiencyClass(Motor::EfficiencyClass efficiencyClass) {
        this->efficiencyClass = efficiencyClass;
    }

    /**
     * Gets the horsepower of motor
     * @return double, horsepower of motor
     */
    double getHp() const {
        return hp;
    }

    /**
     * Sets the horsepower of motor
     * @param hp double, horsepower of motor
     */
    void setHp(double hp) {
        this->hp = hp;
    }

    /**
     * Gets the motor power in kWh
     * @return double, motor power in kWh
     */
    double getMotorKwh() const {
        return motorKwh;
    }

    /**
     * Sets the motor power in kWh
     * @param motorKwh double, motor power in kWh
     */
    void setMotorKwh(double motorKwh) {
        this->motorKwh = motorKwh;
    }

    /**
     * Gets the motor amps
     * @return double, motor amps in A
     */
    double getMotorAmps() const {
        return motorAmps;
    }

    /**
     * Sets the motor amps
     * @param motorAmps double, motor amps in A
     */
    void setMotorAmps(double motorAmps) {
        this->motorAmps = motorAmps;
    }

    /**
     * Gets the actual efficiency of motor
     * @return double, actual efficiency of motor as %
     */
    double getActualEfficiency() const {
        return actualEfficiency;
    }

    /**
     * Sets the actual efficiency of motor
     * @param actualEfficiency double, actual efficiency of motor as %
     */
    void setActualEfficiency(double actualEfficiency) {
        this->actualEfficiency = actualEfficiency;
    }

    /**
     * Gets the loss of power in kW
     * @return double, power loss in kW
     */
    double getKWloss0() const {
        return kWloss0;
    }

private:
    const std::array< std::array<double, 4>, 5> determinePartialLoadCoefficients(std::size_t pole) const;

    Motor::LineFrequency lineFrequency;
    double motorEff = 0.0;
    double motorRpm;
    Motor::EfficiencyClass efficiencyClass;
    double hp;
    double motorKwh;
    double motorAmps;
    double kWloss0 = 0.0;
    double actualEfficiency;
    double motorRatedPower;
};


#endif //AMO_LIBRARY_MOTOREFFICIENCY_H
