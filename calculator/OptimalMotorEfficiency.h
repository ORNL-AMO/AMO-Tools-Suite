//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTOREFFICIENCY_H
#define AMO_LIBRARY_OPTIMALMOTOREFFICIENCY_H


class OptimalMotorEfficiency {
public:
    OptimalMotorEfficiency(double motorRatedPower, double motorShaftPower) : motorRatedPower_(motorRatedPower),
                                                                             motorShaftPower_(motorShaftPower) {}

    double calculate();

    double getMotorRatedPower() const {
        return motorRatedPower_;
    }

    void setMotorRatedPower(double motorRatedPower) {
        motorRatedPower_ = motorRatedPower;
    }

    double getMotorShaftPower() const {
        return motorShaftPower_;
    }

    void setMotorShaftPower(double motorShaftPower) {
        motorShaftPower_ = motorShaftPower;
    }

private:
    double motorRatedPower_;
    double motorShaftPower_;
};


#endif //AMO_LIBRARY_OPTIMALMOTOREFFICIENCY_H
