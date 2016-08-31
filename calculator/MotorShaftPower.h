//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORSHAFTPOWER_H
#define AMO_LIBRARY_MOTORSHAFTPOWER_H


class MotorShaftPower {


public:
    MotorShaftPower(double motorEfficiency, double motorPower) : motorEfficiency_(motorEfficiency),
                                                                 motorPower_(motorPower) { }
    double calculate();
    double getMotorEfficiency() const {
        return motorEfficiency_;
    }

    void setMotorEfficiency(double motorEfficiency) {
        motorEfficiency_ = motorEfficiency;
    }

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

private:
    double motorEfficiency_;
    double motorPower_;

    double motorShaftPower_;
};


#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
