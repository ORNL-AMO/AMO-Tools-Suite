//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "PSATResult.h"
#include "Motor.h"
#include "./calculator/MotorShaftPower.h"
#include "./calculator/PumpShaftPower.h"
#include "calculator/PumpEfficiency.h"
#include "AnnualEnergy.h"
#include "AnnualCost.h"

int PSATResult::calculate() {
    /*
    //Existing case

    MotorShaftPower motorShaftPower(motorRatedPower_, motorMeasuredPower_, motorRPM_, efficiencyClass_, motorRatedVoltage_);
    existing_.motorShaftPower_ = motorShaftPower.calculate();
    existing_.motorCurrent_ = motorShaftPower.calculateCurrent();
    existing_.motorPowerFactor_ = motorShaftPower.calculatePowerFactor();
    existing_.motorEfficiency_= motorShaftPower.calculateEfficiency();
    existing_.motorPower_ = motorShaftPower.calculateElectricPower();

    // Calculate PumpShaftPower
    PumpShaftPower pumpShaftPower(existing_.motorShaftPower_, Pump::Drive::DIRECT_DRIVE);
    existing_.pumpShaftPower_ = pumpShaftPower.calculate();

    // Calculate Pump Efficiency
    PumpEfficiency pumpEfficiency(specificGravity_, flowRate_, head_, existing_.pumpShaftPower_);
    existing_.pumpEfficiency_ = pumpEfficiency.calculate();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(motormeasuredPower_, operatingFraction);
    existing_.annualEnergy_ = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(existing_.annualEnergy_,kwhRate_);
    existing_.annualCost_ = annualCost.calculate();
     */

    return 0;
}