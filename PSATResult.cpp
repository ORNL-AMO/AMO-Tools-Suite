//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "PSATResult.h"
#include "calculator/MotorShaftPower.h"
#include "calculator/PumpShaftPower.h"
#include "calculator/PumpEfficiency.h"
#include "calculator/AnnualCost.h"
#include "calculator/AnnualEnergy.h"


double PSATResult::calculate() {

    MotorShaftPower motorShaftPower(motor_.getMotorRatedPower(), fieldData_.getMotorPower(), motor_.getMotorRpm(),
                                    motor_.getEfficiencyClass(), motor_.getMotorRatedVoltage(),
                                    fieldData_.getVoltage());
    existing_.motorShaftPower_ = motorShaftPower.calculate();
    existing_.motorCurrent_ = motorShaftPower.calculateCurrent();
    existing_.motorPowerFactor_ = motorShaftPower.calculatePowerFactor();
    existing_.motorEfficiency_= motorShaftPower.calculateEfficiency();
    //existing_.motorPower_ = motorShaftPower.calculateElectricPower();

    // Calculate PumpShaftPower
    PumpShaftPower pumpShaftPower(existing_.motorShaftPower_, pump_.getDrive());
    existing_.pumpShaftPower_ = pumpShaftPower.calculate();

    // Calculate Pump Efficiency
    PumpEfficiency pumpEfficiency(pump_.getSg(), fieldData_.getFlowRate(), fieldData_.getHead(),
                                  existing_.pumpShaftPower_);
    existing_.pumpEfficiency_ = pumpEfficiency.calculate();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(fieldData_.getMotorPower(), financial_.getOperatingFraction());
    existing_.annualEnergy_ = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(existing_.annualEnergy_, financial_.getUnitCost());
    existing_.annualCost_ = annualCost.calculate();

    return 0;
}