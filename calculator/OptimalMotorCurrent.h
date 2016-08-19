//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORCURRENT_H
#define AMO_LIBRARY_OPTIMALMOTORCURRENT_H


class OptimalMotorCurrent {
public:
    OptimalMotorCurrent(double motorPower, double voltage) : motorPower_(motorPower), voltage_(voltage) {}

    double calculate();

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

private:
    double motorPower_;
    double voltage_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORCURRENT_H
