//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_ANNUALENERGY_H
#define AMO_LIBRARY_ANNUALENERGY_H


class AnnualEnergy {
public:

    AnnualEnergy(double motorPower, double operatingFraction) : motorPower_(motorPower),
                                                                operatingFraction_(operatingFraction) {}

    double calculate();

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    double getOperatingFraction() const {
        return operatingFraction_;
    }

    void setOperatingFraction(double operatingFraction) {
        operatingFraction_ = operatingFraction;
    }

private:
    double motorPower_;
    double operatingFraction_;
};


#endif //AMO_LIBRARY_ANNUALENERGY_H
