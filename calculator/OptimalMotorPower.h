//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORPOWER_H
#define AMO_LIBRARY_OPTIMALMOTORPOWER_H

#include "MotorShaftPower.h"
#include "MotorEfficiency.h"
#include "MotorPower.h"
#include "MotorCurrent.h"
#include "MotorPowerFactor.h"

class OptimalMotorPower {
public:

//    OptimalMotorPower(double motorShaftPower, double motorEfficiency) : motorShaftPower_(motorShaftPower),
//                                                                        motorEfficiency_(motorEfficiency) {}

    OptimalMotorPower(double motorRatedPower, double motorMeasuredPower, int motorRPM,
                        Motor::LineFrequency lineFrequency,
                        Motor::EfficiencyClass efficiencyClass,
                        double specifiedEfficiency,
                        double ratedVoltage, double fullLoadAmps, double fieldVoltage,
                        FieldData::LoadEstimationMethod loadEstimationMethod, double fieldCurrent, double optimalMotorShaftPower)
            :
            fieldPower_(motorMeasuredPower),
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM), lineFrequency_(lineFrequency),
            efficiencyClass_(efficiencyClass), specifiedEfficiency_(specifiedEfficiency),
            ratedVoltage_(ratedVoltage), fullLoadAmps_(fullLoadAmps), fieldVoltage_(fieldVoltage),
            loadEstimationMethod_(loadEstimationMethod), fieldCurrent_(fieldCurrent), optimalMotorShaftPower_(optimalMotorShaftPower) {};

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
    double tempLoadFraction_ = 0.01;
    double power = 0.0, powerE1 = 0.0, powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0, current1 = 0.0, current2 = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;
    double estimatedFLA;


    double motorRatedPower_ = 0.0;
    double fieldPower_ = 0.0;
    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    double ratedVoltage_ = 0.0;
    double fullLoadAmps_ = 0.0;
    double fieldVoltage_ = 0.0;
    Motor::EfficiencyClass efficiencyClass_;

    double specifiedEfficiency_;
    double fieldCurrent_ = 0.0;
    FieldData::LoadEstimationMethod loadEstimationMethod_;

};


#endif //AMO_LIBRARY_OPTIMALMOTORPOWER_H
