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

class Motor {
public:

    ///Classifications of efficiency classes
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        SPECIFIED
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
     * @return nothing
     */
    Motor(
        LineFrequency lineFrequency,
        double motorRatedPower,
        double motorRpm,
        EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double motorRatedVoltage,
        double fullLoadAmps,
        double sizeMargin
    ) :
        lineFrequency_(lineFrequency),
        motorRatedPower_(motorRatedPower),
        motorRpm_(motorRpm),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        motorRatedVoltage_(motorRatedVoltage),
        fullLoadAmps_(fullLoadAmps),
        sizeMargin_(sizeMargin)
    {};

    Motor() = default;

    /**
     * Gets the line frequency at either 50 Hz or 60 Hz
     *
     * @return LineFrequency, classification of line frequency in Hz (either 50Hz or 60Hz)
     */
    LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    /**
     * Sets the line frequency
     *
     * @param lineFrequency LineFrequency, line frequency of either 50Hz or 60Hz
     *
     * @return nothing
     */
    void setLineFrequency(LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    /**
     * Gets the rated motor power
     *
     * @return double, rated motor power in hp
     */
    double getMotorRatedPower() const {
        return motorRatedPower_;
    }

    /**
     * Sets the reated motor power
     *
     * @param motorRatedPower double, rated motor power in hp
     *
     * @return nothing
     */
    void setMotorRatedPower(double motorRatedPower) {
        motorRatedPower_ = motorRatedPower;
    }

    /**
     * Gets the RPM of motor
     *
     * @return int, RPM of motor
     */
    int getMotorRpm();

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
     * Gets the classification of motor efficiency
     *
     * @return EfficiencyClass, efficiency class of motor
     */
    EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    /**
     * Sets the classification of motor efficiency
     *
     * @param efficiencyClass EfficiencyClass, efficiency class of motor
     *
     * @return nothing
     */
    void setEfficiencyClass(EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }

    /**
     * Gets the specified efficiency
     *
     * @return double, specified efficiency as %
     */
    double getSpecifiedEfficiency() const {
        return specifiedEfficiency_;
    }

    /**
     * Sets the specified efficiency
     *
     * @param fullLoadEfficiency double, specified efficiency as %
     *
     * @return nothing
     */
    void setSpecifiedEfficiency(double fullLoadEfficiency) {
        specifiedEfficiency_ = fullLoadEfficiency;
    }

    /**
     * Gets the rated motor voltage
     *
     * @return double, rated motor voltage in V
     */
    double getMotorRatedVoltage() const {
        return motorRatedVoltage_;
    }

    /**
     * Sets the rated motor voltage
     *
     * @param motorRatedVoltage double, rated motor voltage in V
     *
     * @return nothing
     */
    void setMotorRatedVoltage(double motorRatedVoltage) {
        motorRatedVoltage_ = motorRatedVoltage;
    }

    /**
     * Gets the current at full load in amps
     *
     * @return double, current at full load in amps
     */
    double getFullLoadAmps() {
        return fullLoadAmps_;
    }

    /**
     * Sets the current at full load
     *
     * @param fullLoadAmps double, current at full load in amps
     *
     * @return nothing
     */
    void setFullLoadAmps(double fullLoadAmps) {
        fullLoadAmps_ = fullLoadAmps;
    }

    /**
     * Gets the size margin
     *
     * @return double, size margin as %
     */
    double getSizeMargin() {
        return sizeMargin_;
    }

    /**
     * Sets the size margin
     *
     * @param sizeMargin double, size margin as %
     *
     * @return nothing
     */
    void setSizeMargin(double sizeMargin) {
        sizeMargin_ = sizeMargin;
    }

private:
    LineFrequency lineFrequency_;
    double motorRatedPower_;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_;
    double motorRatedVoltage_;
    double fullLoadAmps_;
    double sizeMargin_;

};


#endif //AMO_LIBRARY_MOTOR_H
