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
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        SPECIFIED
    };
    enum class LineFrequency{
        FREQ60,
        FREQ50
    };

    /**
     * Constructor
     * @param lineFrequency Mains supply frequency at either 50Hz or 60Hz.
     * @param motorRatedPower Rated power for the motor in hp or kw.
     * @param motorRpm Motor RPM.
     * @param efficiencyClass Classification of motor efficiency.
     * @param specifiedEfficiency Specified % Efficiency of motor, if efficiency class is SPECIFIED
     * @param motorRatedVoltage Motor nameplate design voltage.
     * @param fullLoadAmps Current at full load in amps.
     * @param sizeMargin The size margin as defined in %.
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

    LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    void setLineFrequency(LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    double getMotorRatedPower() const {
        return motorRatedPower_;
    }

    void setMotorRatedPower(double motorRatedPower) {
        motorRatedPower_ = motorRatedPower;
    }

    int getMotorRpm();

    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    void setEfficiencyClass(EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }

    double getSpecifiedEfficiency() const {
        return specifiedEfficiency_;
    }

    void setSpecifiedEfficiency(double fullLoadEfficiency) {
        specifiedEfficiency_ = fullLoadEfficiency;
    }

    double getMotorRatedVoltage() const {
        return motorRatedVoltage_;
    }

    void setMotorRatedVoltage(double motorRatedVoltage) {
        motorRatedVoltage_ = motorRatedVoltage;
    }

    double getFullLoadAmps() {
        return fullLoadAmps_;
    }

    void setFullLoadAmps(double fullLoadAmps) {
        fullLoadAmps_ = fullLoadAmps;
    }

    double getSizeMargin() {
        return sizeMargin_;
    }

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
