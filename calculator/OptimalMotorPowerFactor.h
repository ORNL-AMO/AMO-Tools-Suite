//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORPOWERFACTOR_H
#define AMO_LIBRARY_OPTIMALMOTORPOWERFACTOR_H


class OptimalMotorPowerFactor {
public:
    OptimalMotorPowerFactor(double motorRatedPower, double motorPower) : motorRatedPower_(motorRatedPower),
                                                                         motorPower_(motorPower) {}

    double calculate();

    double getMotorRatedPower() const {
        return motorRatedPower_;
    }

    void setMotorRatedPower(double motorRatedPower) {
        motorRatedPower_ = motorRatedPower;
    }

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

private:
    double motorRatedPower_;
    double motorPower_;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWERFACTOR_H
