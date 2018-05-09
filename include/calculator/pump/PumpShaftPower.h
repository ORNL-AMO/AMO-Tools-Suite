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

#include <results/InputData.h>

class PumpShaftPower {
public:
    /**
     * Constructor
     * @param motorShaftPower double, motor shaft power as defined in hp
     * @param drive Pump::Motor, type of drive the pump uses from either direct or belt drive.
     */
    PumpShaftPower(
        double motorShaftPower,
        Motor::Drive drive
    ) :
        motorShaftPower(motorShaftPower),
        drive(drive)
    {}

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
        return motorShaftPower;
    }

    /**
     * Sets the motor shaft power
     * @param motorShaftPower double, in hp
     */
    void setMotorShaftPower(double motorShaftPower) {
        this->motorShaftPower = motorShaftPower;
    }

    /**
     * Gets the type of drive the pump uses from either direct or belt drive
     * @return Pump:Drive, type of drive
     */
    Motor::Drive getDrive() const {
        return drive;
    }

    /**
     * Set the type of drive the pump uses from either direct or belt drive
     * @param drive Motor:Drive, type of drive
     */
    void setDrive(Motor::Drive drive) {
        this->drive = drive;
    }

private:
    double motorShaftPower;
    Motor::Drive drive;
};

#endif //AMO_LIBRARY_PUMPSHAFTPOWER_H
