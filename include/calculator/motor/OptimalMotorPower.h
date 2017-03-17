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
     * @param motorRatedPower Rated Power of motor
     * @param motorRPM RPM of motor
     * @param lineFrequency Line frequency of motor
     * @param efficiencyClass Efficiency class of motor
     * @param specifiedEfficiency Specified Efficiency of motor, if efficiency class is SPECIFIED
     * @param ratedVoltage Rated voltage of the motor
     * @param fullLoadAmps Current at full load.
     * @param fieldVoltage Field voltage.
     * @param optimalMotorShaftPower Optimal shaft power as defined in hp or Kw.
     * @return nothing
     */
    OptimalMotorPower(
        double motorRatedPower,
        double /*motorMeasuredPower*/,
        int motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
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
        specifiedEfficiency_(specifiedEfficiency)
//        fieldCurrent_(fieldCurrent),
//        loadEstimationMethod_(loadEstimationMethod)
    {};

    double calculate();

    double getOptimalMotorShaftPower_() const {
        return optimalMotorShaftPower_;
    }

    void setMotorShaftPower(double optimalMotorShaftPower) {
        optimalMotorShaftPower_ = optimalMotorShaftPower;
    }

    double getMotorEfficiency() const {
        return motorEfficiency_;
    }

    void setMotorEfficiency(double motorEfficiency) {
        motorEfficiency_ = motorEfficiency;
    }

    double getMotorCurrent(){
        return current;
    }
    double getMotorPf(){
        return pf;
    }
    double getMotorEff(){
        return eff;
    }
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

    double specifiedEfficiency_;
//    double fieldCurrent_ = 0.0;
//    FieldData::LoadEstimationMethod loadEstimationMethod_;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
