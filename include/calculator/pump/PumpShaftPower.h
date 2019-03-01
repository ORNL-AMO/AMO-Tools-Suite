/**
 * @brief Header file for PumpShaftPower class
 *
 * This contains the prototypes of PumpShaftPower calculator including getters and setters for the important fields.
 *
 * @author Gina Accawi (accawigk)
 * @author Allie Ledbetter (Aeledbetter)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_PUMPSHAFTPOWER_H
#define AMO_LIBRARY_PUMPSHAFTPOWER_H

#include <results/InputData.h>

class PumpShaftPower {
public:
    /**
     * @param driveEfficiency, efficiency of the drive defined as a fraction, unitless
     * 
     * 
     */
    struct Output {
        Output(const double pumpShaftPower, const double driveEfficiency)
            : pumpShaftPower(pumpShaftPower), driveEfficiency(driveEfficiency)
        {}

        const double pumpShaftPower, driveEfficiency;
    };

    /**
     * Constructor
     * @param motorShaftPower double, motor shaft power as defined in hp
     * @param drive Motor::Drive, type of drive the pump uses from either direct or belt drive.
     */
    PumpShaftPower(
        double motorShaftPower,
        Motor::Drive drive,
        double specifiedEfficiency
    ) :
        motorShaftPower(motorShaftPower),
        drive(drive),
        specifiedEfficiency(specifiedEfficiency)
    {}

    /**
     * Calculates the pump shaft power
     * @return double, pump shaft power in hp
     */
    Output calculate();

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

    /**
     * Gets the specified efficiency
     * @return double, specifiedEfficiency
     */
    double getSpecifiedEfficiency() const {
        return specifiedEfficiency;
    }

    /**
     * Sets the specified efficiency
     * @param specifiedEfficiency double
     */
    void setSpecifiedEfficiency(double specifiedEfficiency) {
        this->specifiedEfficiency = specifiedEfficiency;
    }

private:
    double motorShaftPower;
    Motor::Drive drive;
    double specifiedEfficiency;
};

#endif //AMO_LIBRARY_PUMPSHAFTPOWER_H
