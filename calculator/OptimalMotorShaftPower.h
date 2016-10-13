//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H

#include "../Pump.h"

class OptimalMotorShaftPower {
public:
    OptimalMotorShaftPower(double pumpShaftPower, Pump::Drive drive) : pumpShaftPower_(pumpShaftPower), drive_(drive) {}

    double calculate();

    double getPumpShaftPower() const {
        return pumpShaftPower_;
    }

    void setPumpShaftPower(double pumpShaftPower) {
        pumpShaftPower_ = pumpShaftPower;
    }

    Pump::Drive getDrive() const {
        return drive_;
    }

    void setDrive(Pump::Drive drive) {
        drive_ = drive;
    }

private:
    double pumpShaftPower_;
    Pump::Drive drive_;
    double motorShaftPower_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
