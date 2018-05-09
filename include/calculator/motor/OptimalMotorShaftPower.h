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

#include "results/Pump.h"

class OptimalMotorShaftPower {
public:

    /**
     * Constructor
     * @param pumpShaftPower double, Pump shaft power as defined in hp
     * @param drive Pump::Drive, Type of drive the pump uses from either direct or belt drive.
     */
    OptimalMotorShaftPower(
        double pumpShaftPower,
        Pump::Drive drive
    ) :
        pumpShaftPower(pumpShaftPower),
        drive(drive)
    {}

    /**
     * Calculates the optimal motor shaft power
     * @return double, optimal motor shaft power in hp
     */
    double calculate();

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
     * @return Pump::Drive, type of drive
     */
    Pump::Drive getDrive() const {
        return drive;
    }

    /**
     * Sets the type of drive the pump uses from either direct or belt drive
     * @param drive Pump::Drive, type of drive
     */
    void setDrive(Pump::Drive drive) {
        this->drive = drive;
    }

private:
    double pumpShaftPower;
    Pump::Drive drive;
    double motorShaftPower;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
