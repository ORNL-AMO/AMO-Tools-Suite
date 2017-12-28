/**
 * @brief Header file for OptimalMotorCurrent class
 *
 * This contains the prototypes of OptimalMotorCurrent calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALMOTORCURRENT_H
#define AMO_LIBRARY_OPTIMALMOTORCURRENT_H

#include "psat/Motor.h"

class OptimalMotorCurrent {
public:

   /**
    * Constructor
    * @param motorRatedPower double, Rated Power of motor in hp
    * @param motorRPM double, RPM of motor.
    * @param lineFrequency Motor::LineFrequency, Line frequency of motor in either 60Hz or 50Hz.
    * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor.
    * @param specifiedEfficiency double, Specified Efficiency of motor, if efficiency class is SPECIFIED.
    * @param loadFactor double, Load factor - unitless
    * @param ratedVoltage double, Rated voltage of the motor in volts
    */
    OptimalMotorCurrent(
        const double motorRatedPower,
        const double motorRPM,
        const Motor::LineFrequency lineFrequency,
        const Motor::EfficiencyClass efficiencyClass,
        const double specifiedEfficiency,
        const double loadFactor,
        const double ratedVoltage
    ) :
        motorRatedPower(motorRatedPower),
        motorRPM(motorRPM),
        lineFrequency(lineFrequency),
        efficiencyClass(efficiencyClass),
        specifiedEfficiency(specifiedEfficiency),
        loadFactor(loadFactor),
        ratedVoltage(ratedVoltage)
    {};

    /**
     * Calculates the optimal motor current
     * @return double, optimal motor current in Amps
     */
    double calculate();

private:
    double motorRatedPower, motorRPM;
    Motor::LineFrequency lineFrequency;
    Motor::EfficiencyClass efficiencyClass;
    double specifiedEfficiency, loadFactor, ratedVoltage;
};


#endif //AMO_LIBRARY_OPTIMALMOTORCURRENT_H
