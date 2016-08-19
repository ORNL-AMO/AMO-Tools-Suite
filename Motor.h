//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_MOTOR_H
#define AMO_LIBRARY_MOTOR_H


class Motor {
public:
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        AVERAGE,
        SPECIFIED
    };

    Motor(EfficiencyClass efficiencyClass, double lineFrequency, double motorRatedPower, double fullLoadEfficiency,
          double motorRatedVoltage, double sizeMargin) : efficiencyClass_(efficiencyClass),
                                                         lineFrequency_(lineFrequency),
                                                         motorRatedPower_(motorRatedPower),
                                                         fullLoadEfficiency_(fullLoadEfficiency),
                                                         motorRatedVoltage_(motorRatedVoltage),
                                                         sizeMargin_(sizeMargin) {}

    Motor() = default;

    EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    void setEfficiencyClass(EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }

    double getLineFrequency() const {
        return lineFrequency_;
    }

    void setLineFrequency(double lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    double getMotorRatedPower() const {
        return motorRatedPower_;
    }

    void setMotorRatedPower(double motorRatedPower) {
        motorRatedPower_ = motorRatedPower;
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

    double getSizeMargin() const {
        return sizeMargin_;
    }

    void setSizeMargin(double sizeMargin) {
        sizeMargin_ = sizeMargin;
    }

private:
    Motor::EfficiencyClass efficiencyClass_;
    double lineFrequency_;
    double motorRatedPower_;
    double fullLoadEfficiency_;
    double motorRatedVoltage_;
    double sizeMargin_;


};


#endif //AMO_LIBRARY_MOTOR_H
