//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORRATEDPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORRATEDPOWER_H


class OptimalMotorRatedPower {
public:
    OptimalMotorRatedPower(double motorShaftPower, double sizeMargin) : motorShaftPower_(motorShaftPower),
                                                                        sizeMargin_(sizeMargin) {}

    double calculate();

    double getMotorShaftPower() const {
        return motorShaftPower_;
    }

    void setMotorShaftPower(double motorShaftPower) {
        motorShaftPower_ = motorShaftPower;
    }

    double getSizeMargin() const {
        return sizeMargin_;
    }

    void setSizeMargin(double sizeMargin) {
        sizeMargin_ = sizeMargin;
    }

private:
    double motorShaftPower_;
    double sizeMargin_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORRATEDPOWER_H
