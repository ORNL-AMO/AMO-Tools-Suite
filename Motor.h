//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_MOTOR_H
#define AMO_LIBRARY_MOTOR_H

#include <cmath>

class Motor {
public:
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        SPECIFIED
    };
    enum class LineFrequency {
        FREQ60,
        FREQ50
    };

    Motor(LineFrequency lineFrequency, double motorRatedPower, double motorRpm, EfficiencyClass efficiencyClass,
          double fullLoadEfficiency,
          double motorRatedVoltage, bool flAmps, double fullLoadAmps, double sizeMargin) :
            lineFrequency_(
                    lineFrequency),
            motorRatedPower_(
                    motorRatedPower),
            motorRpm_(motorRpm),
            efficiencyClass_(
                    efficiencyClass),
            fullLoadEfficiency_(
                    fullLoadEfficiency),
            motorRatedVoltage_(
                    motorRatedVoltage),
            flAmps_(flAmps),
            fullLoadAmps_(fullLoadAmps),
            sizeMargin_(sizeMargin) {};


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

    int getMotorRpm() {
        return std::round(motorRpm_);
    }

    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    void setEfficiencyClass(EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }

    double getFullLoadEfficiency() const {
        return fullLoadEfficiency_;
    }

    void setFullLoadEfficiency(double fullLoadEfficiency) {
        fullLoadEfficiency_ = fullLoadEfficiency;
    }

    double getMotorRatedVoltage() const {
        return motorRatedVoltage_;
    }

    void setMotorRatedVoltage(double motorRatedVoltage) {
        motorRatedVoltage_ = motorRatedVoltage;
    }

    bool getFlAmps() {
        return flAmps_;
    }

    void setFlAmps(bool flAmps) {
        flAmps_ = flAmps;
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
    double fullLoadEfficiency_;
    double motorRatedVoltage_;
    bool flAmps_;
    double fullLoadAmps_;
    double sizeMargin_;

};


#endif //AMO_LIBRARY_MOTOR_H
