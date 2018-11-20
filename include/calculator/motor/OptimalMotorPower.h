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

    struct Output {
	    /**
	     * @param power - kW
	     * @param efficiency - unitless
	     * @param current in amps
	     * @param powerFactor  unitless
	     */
        Output(const double power, const double efficiency, const double current, const double powerFactor, const double loadFactor)
                : power(power), efficiency(efficiency), current(current), powerFactor(powerFactor), loadFactor(loadFactor)
        {}

        const double power, efficiency, current, powerFactor, loadFactor;
    };

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
     */
    Output calculate();

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

private:
    double optimalMotorShaftPower, motorRatedPower, motorRPM;
    Motor::LineFrequency lineFrequency;
    double ratedVoltage, fieldVoltage;
    Motor::EfficiencyClass efficiencyClass;
    double specifiedEfficiency;
};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
