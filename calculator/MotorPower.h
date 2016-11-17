/**
 * @brief Contains the declaration of MotorPower class including the getters and setters as well as the calculators.
 *          for motor efficiency.
 *      calculate(): Calculates the motor power
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORPOWER_H
#define AMO_LIBRARY_MOTORPOWER_H

#include <cmath>

class MotorPower {
public:
    /**
     * Constrructor
     * @param ratedVoltage Rated voltage of motor
     * @param motorCurrent Motor current
     * @param powerFactor Power factor of motor
     * @return nothing
     */
    MotorPower(double ratedVoltage, double motorCurrent, double powerFactor) :
            ratedVoltage_(ratedVoltage), motorCurrent_(motorCurrent), powerFactor_(powerFactor) {};

    /**
     * Calculates the motor power
     * @return motor power
     */
    double calculate();

private:
    /**
     * Rated voltage of motor
     */
    double ratedVoltage_;
    /**
     * Motor current
     */
    double motorCurrent_;
    /**
     * Power factor of motor
     */
    double powerFactor_;
};


#endif //AMO_LIBRARY_MOTORPOWER_H
