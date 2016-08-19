//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORPOWER_H


class OptimalMotorPower {
public:
    OptimalMotorPower(double motorShaftPower, double motorEfficiency) : motorShaftPower_(motorShaftPower),
                                                                        motorEfficiency_(motorEfficiency) {}

    double calculate();

    double getMotorShaftPower() const {
        return motorShaftPower_;
    }

    void setMotorShaftPower(double motorShaftPower) {
        motorShaftPower_ = motorShaftPower;
    }

    double getMotorEfficiency() const {
        return motorEfficiency_;
    }

    void setMotorEfficiency(double motorEfficiency) {
        motorEfficiency_ = motorEfficiency;
    }


private:
    double motorShaftPower_;
    double motorEfficiency_;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
