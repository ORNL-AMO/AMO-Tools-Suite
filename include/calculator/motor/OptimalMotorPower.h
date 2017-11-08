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
        double /*motorMeasuredPower*/,
        int motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        Motor::EfficiencyClass optimalEfficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage,
        double fullLoadAmps,
        double fieldVoltage,
        FieldData::LoadEstimationMethod /*loadEstimationMethod*/,
        double /*fieldCurrent*/,
        double optimalMotorShaftPower
    ) :
        optimalMotorShaftPower_(optimalMotorShaftPower),
        motorRatedPower_(motorRatedPower),
//        fieldPower_(motorMeasuredPower),
        motorRPM_(motorRPM),
        lineFrequency_(lineFrequency),
        ratedVoltage_(ratedVoltage),
        fullLoadAmps_(fullLoadAmps),
        fieldVoltage_(fieldVoltage),
        efficiencyClass_(efficiencyClass),
        optimalEfficiencyClass_(optimalEfficiencyClass),
        specifiedEfficiency_(specifiedEfficiency)
//        fieldCurrent_(fieldCurrent),
//        loadEstimationMethod_(loadEstimationMethod)
    {};

    /**
     * Calculates the optimal motor power
     *
     * @return double, optimal motor power in hp
     */
    double calculate();

    /**
     * Gets the optimal motor shaft power
     *
     * @return double, optimal motor shaft power in hp
     */
    double getOptimalMotorShaftPower_() const {
        return optimalMotorShaftPower_;
    }

    /**
     * Sets the optimal motor shaft power
     *
     * @param optimalMotorShaftPower double, optimal motor shaft power in hp
     *
     */
    void setMotorShaftPower(double optimalMotorShaftPower) {
        optimalMotorShaftPower_ = optimalMotorShaftPower;
    }

    /**
     * Gets the motor efficiency if efficiency class is SPECIFIED
     *
     * @return double, mototr efficiency as %
     */
    double getMotorEfficiency() const {
        return motorEfficiency_;
    }

    /**
     * Sets the motor efficiency if efficiency class is SPECIFIED
     *
     * @param motorEfficiency double, efficiency of motor as %
     *
     */
    void setMotorEfficiency(double motorEfficiency) {
        motorEfficiency_ = motorEfficiency;
    }

    /**
     * Gets the motor current
     *
     * @return double, motor current in A
     */
    double getMotorCurrent(){
        return current;
    }

    /**
     * Gets motor power factor
     *
     * @return double, power factor of motor - unitless
     */
    double getMotorPf(){
        return pf;
    }

    /**
     * Get motor efficiency if efficiency class is not SPECIFIED
     *
     * @return double, motor efficiency as %
     */
    double getMotorEff(){
        return eff;
    }

    /**
     * Gets motor power
     *
     * @return double, motor power in hp
     */
    double getMotorPower(){
        return power;
    }

private:
    double optimalMotorShaftPower_;
    double motorEfficiency_;
    double tempMsp = 0.0, tempMsp1 =0.0, tempMsp2 =0.0;
//    double tempLoadFraction_ = 0.01;
    double power = 0.0, powerE1 = 0.0, powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0, current1 = 0.0, current2 = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;
//    double estimatedFLA;


    double motorRatedPower_ = 0.0;
//    double fieldPower_ = 0.0;
    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    double ratedVoltage_ = 0.0;
    double fullLoadAmps_ = 0.0;
    double fieldVoltage_ = 0.0;
    Motor::EfficiencyClass efficiencyClass_;
    Motor::EfficiencyClass optimalEfficiencyClass_;

    double specifiedEfficiency_;
//    double fieldCurrent_ = 0.0;
//    FieldData::LoadEstimationMethod loadEstimationMethod_;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
