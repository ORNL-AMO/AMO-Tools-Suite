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

    enum class LoadEsimationMethod {

    };

    Motor();

    Motor(EfficiencyClass efficiencyClass, double lineFrequency, double motorRatedPower, double fullLoadEfficiency,
          double motor_rated_voltage, double sizeMargin);

// Setters
    void setEfficiencyClass(Motor::EfficiencyClass efficiencyClass);
    void setLineFrequency(double lineFrequency);
    void setMotorRatedPower(double motorRatedPower);
    void setFullLoadEfficiency(double fullLoadEfficiency);
    void setMotorRatedVoltage(double motorRatedVoltage);
    void setSizeMargin(double sizeMargin);
// Getters
    Motor::EfficiencyClass getEfficiencyClass(void);
    double getLineFrequency(void);
    double getMotorRatedPower(void);
    double getFullLoadEfficiency(void);
    double getMotorRatedVoltage(void);
    double getSizeMargin(void);

private:
    Motor::EfficiencyClass efficiencyClass_;
    double lineFrequency_;
    double motorRatedPower_;
    double fullLoadEfficiency_;
    double motorRatedVoltage_;
    double sizeMargin_;


};


#endif //AMO_LIBRARY_MOTOR_H
