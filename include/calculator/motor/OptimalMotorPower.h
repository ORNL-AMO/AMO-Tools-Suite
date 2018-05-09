/**
 * @brief Header file for OptimalMotorPower class
 *
 * This contains the prototypes of OptimalMotorPower calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_LIBRARY_OPTIMALMOTORPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORPOWER_H

#include "results/Results.h"

class OptimalMotorPower {
public:

    /**
     * Constructor
     * @param motorRatedPower double, Rated Power of motor in hp
     * @param motorRPM double, RPM of motor
     * @param lineFrequency Motor::LineFrequency, classification of Line frequency of motor in Hz
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor as %
     * @param specifiedEfficiency double, Specified Efficiency of motor, if efficiency class is SPECIFIED
     * @param ratedVoltage double, Rated voltage of the motor in V
     * @param fullLoadAmps double, Current at full load in A
     * @param fieldVoltage double, Field voltage in V
     * @param optimalMotorShaftPower double, Optimal shaft power as defined in hp
     */
    OptimalMotorPower(
        double motorRatedPower,
        double motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage,
        double fieldVoltage,
        double optimalMotorShaftPower
    ) :
        optimalMotorShaftPower(optimalMotorShaftPower),
        motorRatedPower(motorRatedPower),
        motorRPM(motorRPM),
        lineFrequency(lineFrequency),
        ratedVoltage(ratedVoltage),
        fieldVoltage(fieldVoltage),
        efficiencyClass(efficiencyClass),
        specifiedEfficiency(specifiedEfficiency)
    {};

    /**
     * Calculates the optimal motor power
     * @param isPsatOptimal bool, defaults to true so that calculate will use energy efficient or premium depending on motor pole number
     */
    void calculate(bool isPsatOptimal = true);

    /**
     * Gets the optimal motor shaft power
     * @return double, optimal motor shaft power in hp
     */
    double getOptimalMotorShaftPower() const {
        return optimalMotorShaftPower;
    }

    /**
     * Sets the optimal motor shaft power
     * @param optimalMotorShaftPower double, optimal motor shaft power in hp
     */
    void setMotorShaftPower(double optimalMotorShaftPower) {
        this->optimalMotorShaftPower = optimalMotorShaftPower;
    }

    /**
     * Gets the motor current
     * @return double, motor current in A
     */
    double getMotorCurrent() {
        return current;
    }

    /**
     * Gets motor power factor
     * @return double, power factor of motor - unitless
     */
    double getMotorPf() {
        return pf;
    }

    /**
     * Get motor efficiency if efficiency class is not SPECIFIED
     * @return double, motor efficiency as %
     */
    double getMotorEff() {
        return eff;
    }

    /**
     * Gets motor power
     * @return double, motor power in hp
     */
    double getMotorPower() {
        return power;
    }

private:
    double optimalMotorShaftPower, motorRatedPower, motorRPM;
    Motor::LineFrequency lineFrequency;
    double ratedVoltage, fieldVoltage;
    Motor::EfficiencyClass efficiencyClass;
    double specifiedEfficiency;

    // values set in calculate()
    double power = 0, eff = 0, current = 0, pf = 0;
};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
