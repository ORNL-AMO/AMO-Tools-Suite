//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORCURRENT_H
#define AMO_LIBRARY_MOTORCURRENT_H


class MotorCurrent {
public:
    MotorCurrent(double motorAmps, double motorKw, double voltage) : motorAmps_(motorAmps), motorKw_(motorKw),
                                                                     voltage_(voltage) {}

    double calculate();

    double getMotorAmps() const {
        return motorAmps_;
    }

    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    double getMotorKw() const {
        return motorKw_;
    }

    void setMotorKw(double motorKw) {
        motorKw_ = motorKw;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

private:
    double motorAmps_;
    double motorKw_;
    double voltage_;
};


#endif //AMO_LIBRARY_MOTORCURRENT_H
