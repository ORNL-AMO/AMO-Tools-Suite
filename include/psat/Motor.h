/**
 * @file
 * @brief Function prototypes for the Financial fields
 *
 * This contains the prototypes for the Motor structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting data dealing with
 * motor information.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_LIBRARY_MOTOR_H
#define AMO_LIBRARY_MOTOR_H

#include <cmath>

/**
 * Motor class
 * Contains all of the properties of a motor.
 */
class Motor {
public:

    ///Classifications of efficiency classes
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        SPECIFIED,
        PREMIUM
    };

    ///Classifications of line frequency
    enum class LineFrequency{
        FREQ60,
        FREQ50
    };

    /**
     * Constructor
     * @param lineFrequency LineFrequency, main supply frequency at either 50Hz or 60Hz
     * @param motorRatedPower double, rated power for the motor in hp
     * @param motorRpm double, motor RPM
     * @param efficiencyClass EfficiencyClass, classification of motor efficiency
     * @param specifiedEfficiency double, specified % Efficiency of motor, if efficiency class is SPECIFIED
     * @param motorRatedVoltage double, motor nameplate design voltage in volts
     * @param fullLoadAmps double, current at full load in amps
     * @param sizeMargin double, size margin as defined in %
     */
    Motor(
        LineFrequency lineFrequency,
        double motorRatedPower,
        double motorRpm,
        EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double motorRatedVoltage,
        double fullLoadAmps,
        double sizeMargin = 1
    ) :
        lineFrequency(lineFrequency),
        motorRatedPower(motorRatedPower),
        motorRpm(motorRpm),
        efficiencyClass(efficiencyClass),
        specifiedEfficiency(specifiedEfficiency),
        motorRatedVoltage(motorRatedVoltage),
        fullLoadAmps(fullLoadAmps),
        sizeMargin(sizeMargin)
    {};

    Motor() = default;

    /**
     * Gets the line frequency at either 50 Hz or 60 Hz
     * @return LineFrequency, classification of line frequency in Hz (either 50Hz or 60Hz)
     */
    LineFrequency getLineFrequency() const {
        return lineFrequency;
    }

    /**
     * Sets the line frequency
     * @param lineFrequency LineFrequency, line frequency of either 50Hz or 60Hz
     */
    void setLineFrequency(LineFrequency lineFrequency) {
        this->lineFrequency = lineFrequency;
    }

    /**
     * Gets the rated motor power
     * @return double, rated motor power in hp
     */
    double getMotorRatedPower() const {
        return motorRatedPower;
    }

    /**
     * Sets the rated motor power
     * @param motorRatedPower double, rated motor power in hp
     */
    void setMotorRatedPower(double motorRatedPower) {
        this->motorRatedPower = motorRatedPower;
    }

    /**
     * Gets the RPM of motor
     * @return int, RPM of motor
     */
    int getMotorRpm() {
        return static_cast<int>(std::round(motorRpm));
    };

    /**
     * Sets the RPM of motor
     * @param motorRpm double, RPM of motor
     */
    void setMotorRpm(double motorRpm) {
        this->motorRpm = motorRpm;
    }

    /**
     * Gets the classification of motor efficiency
     * @return EfficiencyClass, efficiency class of motor
     */
    EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass;
    }

    /**
     * Sets the classification of motor efficiency
     * @param efficiencyClass EfficiencyClass, efficiency class of motor
     */
    void setEfficiencyClass(EfficiencyClass efficiencyClass) {
        this->efficiencyClass = efficiencyClass;
    }

    /**
     * Gets the specified efficiency
     * @return double, specified efficiency as %
     */
    double getSpecifiedEfficiency() const {
        return specifiedEfficiency;
    }

    /**
     * Sets the specified efficiency
     * @param fullLoadEfficiency double, specified efficiency as %
     */
    void setSpecifiedEfficiency(double fullLoadEfficiency) {
        this->specifiedEfficiency = fullLoadEfficiency;
    }

    /**
     * Gets the rated motor voltage
     * @return double, rated motor voltage in V
     */
    double getMotorRatedVoltage() const {
        return motorRatedVoltage;
    }

    /**
     * Sets the rated motor voltage
     * @param motorRatedVoltage double, rated motor voltage in V
     */
    void setMotorRatedVoltage(double motorRatedVoltage) {
        this->motorRatedVoltage = motorRatedVoltage;
    }

    /**
     * Gets the current at full load in amps
     * @return double, current at full load in amps
     */
    double getFullLoadAmps() {
        return fullLoadAmps;
    }

    /**
     * Sets the current at full load
     * @param fullLoadAmps double, current at full load in amps
     */
    void setFullLoadAmps(double fullLoadAmps) {
        this->fullLoadAmps = fullLoadAmps;
    }

    /**
     * Gets the size margin
     * @return double, size margin as %
     */
    double getSizeMargin() {
        return sizeMargin;
    }

    /**
     * Sets the size margin
     * @param sizeMargin double, size margin as %
     */
    void setSizeMargin(double sizeMargin) {
        this->sizeMargin = sizeMargin;
    }

private:
    LineFrequency lineFrequency;
    double motorRatedPower;
    double motorRpm;
    Motor::EfficiencyClass efficiencyClass;
    double specifiedEfficiency;
    double motorRatedVoltage;
    double fullLoadAmps;
    double sizeMargin;

};


#endif //AMO_LIBRARY_MOTOR_H
