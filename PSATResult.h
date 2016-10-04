//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_RESULTS_H
#define AMO_LIBRARY_RESULTS_H

#include "Motor.h"
#include "Pump.h"
#include "Financial.h"
#include "FieldData.h"

class PSATResult {

public:
    PSATResult() = default;

    PSATResult(Pump &pump, Motor &motor, Financial &financial, FieldData &fieldData) :
            pump_(pump),
            motor_(motor),
            financial_(financial),
            fieldData_(fieldData) {};

    struct result_ {
        double pumpEfficiency_;
        double motorRatedPower_;
        double motorShaftPower_;
        double pumpShaftPower_;
        double motorEfficiency_;
        double motorPowerFactor_;
        double motorCurrent_;
        double motorPower_;
        double annualEnergy_;
        double annualCost_;
    };




    double getAnnualSavingsPotential() const {
        return annualSavingsPotential_;
    }

    double getOptimizationRating() const {
        return optimizationRating_;
    }


    const result_ &getExisting() const {
        return existing_;
    }

    const result_ &getOptimal() const {
        return optimal_;
    }

    double calculate();
private:
    // Out values
    result_ existing_, optimal_;
    double annualSavingsPotential_;
    double optimizationRating_;
    // In values
    Pump pump_;
    Motor motor_;
    Financial financial_;
    FieldData fieldData_;
};


#endif //AMO_LIBRARY_RESULTS_H
