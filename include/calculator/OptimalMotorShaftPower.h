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

#include "../Pump.h"

class OptimalMotorShaftPower {
public:

    /**
     * Constructor
     * @param pumpShaftPower Pump shaft power as defined in hp or Kw.
     * @param drive Type of drive the pump uses from either direct or belt drive.
     * @return nothing
     */
    OptimalMotorShaftPower(
        double pumpShaftPower,
        Pump::Drive drive
    ) :
        pumpShaftPower_(pumpShaftPower),
        drive_(drive)
    {}

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
