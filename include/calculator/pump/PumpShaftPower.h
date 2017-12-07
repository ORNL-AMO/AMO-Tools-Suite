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

#include "psat/Pump.h"

class PumpShaftPower {
public:
    /**
     * Constructor
     * @param motorShaftPower double, motor shaft power as defined in hp
     * @param drive Pump::Motor, type of drive the pump uses from either direct or belt drive.
     */
    PumpShaftPower(
        double motorShaftPower,
        Pump::Drive drive
    ) :
        motorShaftPower_(motorShaftPower),
        drive_(drive)
    {}

    PumpShaftPower() = default;

    /**
     * Calculates the pump shaft power
     * @return double, pump shaft power in hp
     */
    double calculate();

    /**
     * Gets the motor shaft power
     * @return double, motor shaft power in hp
     */
    double getMotorShaftPower() const {
        return motorShaftPower_;
    }

    /**
     * Sets the motor shaft power
     * @param motorShaftPower double, in hp
     */
    void setMotorShaftPower(double motorShaftPower) {
        motorShaftPower_ = motorShaftPower;
    }

    /**
     * Gets the type of drive the pump uses from either direct or belt drive
     * @return Pump:Drive, type of drive
     */
    Pump::Drive getDrive() const {
        return drive_;
    }

    /**
     * Set the type of drive the pump uses from either direct or belt drive
     * @param drive Pump:Drive, type of drive
     */
    void setDrive(Pump::Drive drive) {
        drive_ = drive;
    }

private:
    double motorShaftPower_ = 0.0;
    Pump::Drive drive_ = Pump::Drive::DIRECT_DRIVE;
    double pumpShaftPower_ = 0.0;
};

#endif //AMO_LIBRARY_PUMPSHAFTPOWER_H
