/**
 * @brief Header file for PumpShaftPower class
 *
 * This contains the prototypes of PumpShaftPower calculator including getters and setters for the important fields.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_PUMPSHAFTPOWER_H
#define AMO_LIBRARY_PUMPSHAFTPOWER_H

#include "../Pump.h"

class PumpShaftPower {
public:
    /**
     * Constructor
     * @param motorShaftPower Motor shaft power as defined in hp or Kw.
     * @param drive Type of drive the pump uses from either direct or belt drive.
     * @return nothing
     */
    PumpShaftPower(
        double motorShaftPower,
        Pump::Drive drive
    ) :
        motorShaftPower_(motorShaftPower),
        drive_(drive)
    {}

    PumpShaftPower() = default;

    double calculate();

    double getMotorShaftPower() const {
        return motorShaftPower_;
    }

    void setMotorShaftPower(double motorShaftPower) {
        motorShaftPower_ = motorShaftPower;
    }

    Pump::Drive getDrive() const {
        return drive_;
    }

    void setDrive(Pump::Drive drive) {
        drive_ = drive;
    }

private:
    double motorShaftPower_ = 0.0;
    Pump::Drive drive_ = Pump::Drive::DIRECT_DRIVE;
    double pumpShaftPower_ = 0.0;
};

#endif //AMO_LIBRARY_PUMPSHAFTPOWER_H
