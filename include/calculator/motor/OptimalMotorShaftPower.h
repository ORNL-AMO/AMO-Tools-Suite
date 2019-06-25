/**
 * @brief Header file for OptimalMotorShaftPower class
 *
 * This contains the prototypes of OptimalMotorShaftPower calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H

#include <results/InputData.h>

class OptimalMotorShaftPower {
public:

    struct Output {
        Output(const double motorShaftPower, const double driveEfficiency)
            : motorShaftPower(motorShaftPower), driveEfficiency(driveEfficiency)
        {}

        const double motorShaftPower, driveEfficiency;
    };

    /**
     * Constructor
     * @param pumpShaftPower double, Pump shaft power as defined in hp
     * @param drive Pump::Drive, Type of drive the pump uses from either direct or belt drive.
     */
    OptimalMotorShaftPower(
        double pumpShaftPower,
        Motor::Drive drive,
        double specifiedEfficiency
    ) :
        pumpShaftPower(pumpShaftPower),
        drive(drive),
        specifiedEfficiency(specifiedEfficiency)
    {}

    /**
     * Calculates the optimal motor shaft power
     * @return double, optimal motor shaft power in hp
     */
    Output calculate();

    /**
     * Gets the pump shaft power
     * @return double, pump shaft power in hp
     */
    double getPumpShaftPower() const {
        return pumpShaftPower;
    }

    /**
     * Sets the pump shaft power
     * @param pumpShaftPower double, pump shaft power in hp
     */
    void setPumpShaftPower(double pumpShaftPower) {
        this->pumpShaftPower = pumpShaftPower;
    }

    /**
     * Gets the type of drive the pump uses from either direct or belt drive
     * @return Motor::Drive, type of drive
     */
    Motor::Drive getDrive() const {
        return drive;
    }

    /**
     * Sets the type of drive the pump uses from either direct or belt drive
     * @param drive Motor::Drive, type of drive
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
    double pumpShaftPower;
    Motor::Drive drive;
    // double motorShaftPower;
    // double driveEfficiency;
    double specifiedEfficiency;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
