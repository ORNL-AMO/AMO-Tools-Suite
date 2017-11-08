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

#include "psat/Pump.h"

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
        pumpShaftPower_(pumpShaftPower),
        drive_(drive)
    {}

    /**
     * Calculates the optimal motor shaft power
     *
     * @return double, optimal motor shaft power in hp
     */
    double calculate();

    /**
     * Gets the pump shaft power
     *
     * @return double, pump shaft power in hp
     */
    double getPumpShaftPower() const {
        return pumpShaftPower_;
    }

    /**
     * Sets the pump shaft power
     *
     * @param pumpShaftPower double, pump shaft power in hp
     *
     */
    void setPumpShaftPower(double pumpShaftPower) {
        pumpShaftPower_ = pumpShaftPower;
    }

    /**
     * Gets the type of drive the pump uses from either direct or belt drive
     *
     * @return Pump::Drive, type of drive
     */
    Pump::Drive getDrive() const {
        return drive_;
    }

    /**
     * Sets the type of drive the pump uses from either direct or belt drive
     *
     * @param drive Pump::Drive, type of drive
     *
     */
    void setDrive(Pump::Drive drive) {
        drive_ = drive;
    }

private:
    double pumpShaftPower_;
    Pump::Drive drive_;
    double motorShaftPower_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSHAFTPOWER_H
