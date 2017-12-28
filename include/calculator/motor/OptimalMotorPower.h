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

#include "psat/Motor.h"
#include "psat/FieldData.h"

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
        Motor::EfficiencyClass optimalEfficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage,
        double fullLoadAmps,
        double fieldVoltage,
        double optimalMotorShaftPower
    ) :
        optimalMotorShaftPower(optimalMotorShaftPower),
        motorRatedPower(motorRatedPower),
        motorRPM(motorRPM),
        lineFrequency(lineFrequency),
        ratedVoltage(ratedVoltage),
        fullLoadAmps(fullLoadAmps),
        fieldVoltage(fieldVoltage),
        efficiencyClass(efficiencyClass),
        optimalEfficiencyClass(optimalEfficiencyClass),
        specifiedEfficiency(specifiedEfficiency)
    {};

    /**
     * Calculates the optimal motor power
     * @return double, optimal motor power in hp
     */
    double calculate();

    /**
     * Gets the optimal motor shaft power
     * @return double, optimal motor shaft power in hp
     */
    double getOptimalMotorShaftPower_() const {
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
     * Gets the motor efficiency if efficiency class is SPECIFIED
     * @return double, mototr efficiency as %
     */
    double getMotorEfficiency() const {
        return motorEfficiency;
    }

    /**
     * Sets the motor efficiency if efficiency class is SPECIFIED
     * @param motorEfficiency double, efficiency of motor as %
     *
     */
    void setMotorEfficiency(double motorEfficiency) {
        this->motorEfficiency = motorEfficiency;
    }

    /**
     * Gets the motor current
     * @return double, motor current in A
     */
    double getMotorCurrent(){
        return current;
    }

    /**
     * Gets motor power factor
     * @return double, power factor of motor - unitless
     */
    double getMotorPf(){
        return pf;
    }

    /**
     * Get motor efficiency if efficiency class is not SPECIFIED
     * @return double, motor efficiency as %
     */
    double getMotorEff(){
        return eff;
    }

    /**
     * Gets motor power
     * @return double, motor power in hp
     */
    double getMotorPower(){
        return power;
    }

private:
    double optimalMotorShaftPower;
    double motorEfficiency;
    double tempMsp = 0.0, tempMsp1 =0.0, tempMsp2 =0.0;
    double power = 0.0, powerE1 = 0.0, powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0, current1 = 0.0, current2 = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;

    double motorRatedPower = 0.0;
    double motorRPM = 0;
    Motor::LineFrequency lineFrequency;
    double ratedVoltage = 0.0;
    double fullLoadAmps = 0.0;
    double fieldVoltage = 0.0;
    Motor::EfficiencyClass efficiencyClass;
    Motor::EfficiencyClass optimalEfficiencyClass;

    double specifiedEfficiency;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
