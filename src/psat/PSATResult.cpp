/**
 * @file
 * @brief Contains the two main modules of PSATResult class.
 *
 * Contains 2 important functions:
 *          calculateExisting : calculates the values for the exisiting data.
 *          calculateOptimal : calculates the values for the optimal case.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include "psat/PSATResult.h"
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/pump/PumpShaftPower.h"
#include "calculator/pump/PumpEfficiency.h"
#include "calculator/util/AnnualCost.h"
#include "calculator/util/AnnualEnergy.h"
#include "calculator/pump/OptimalPumpEfficiency.h"
#include "calculator/pump/OptimalPumpShaftPower.h"
#include "calculator/motor/OptimalMotorShaftPower.h"
#include "calculator/motor/OptimalMotorPower.h"
#include "calculator/motor/OptimalMotorSize.h"

double PSATResult::calculateExisting() {
    /**
     * 1a	Calculate motor shaft power from measured power, OR
     * 1b	Calculate motor shaft power from measured current, voltage
     *  This step calculates the following parameters of motor
     *      shaft power,
     *      current,
     *      power factor,
     *      efficiency and
     *      power.
     * 2a	If a belt drive is specified, calculate the pump shaft power
     * 2b	If direct drive, motor shaft power = pump shaft power
     * 3	Calculate fluid power
     * 4	Calculate pump efficiency
     * 5	Calculate annual energy and energy cost
     */
    MotorShaftPower motorShaftPower(motor_.getMotorRatedPower(), fieldData_.getMotorPower(), motor_.getMotorRpm(),
                                    motor_.getLineFrequency(),
                                    motor_.getEfficiencyClass(), motor_.getSpecifiedEfficiency(),
                                    motor_.getMotorRatedVoltage(), motor_.getFullLoadAmps(),
                                    fieldData_.getVoltage(), fieldData_.getLoadEstimationMethod(),
                                    fieldData_.getMotorAmps());
    existing_.motorShaftPower_ = motorShaftPower.calculate();
    existing_.motorCurrent_ = motorShaftPower.calculateCurrent();
    existing_.motorPowerFactor_ = motorShaftPower.calculatePowerFactor();
    existing_.motorEfficiency_ = motorShaftPower.calculateEfficiency();
    existing_.motorRatedPower_ = motor_.getMotorRatedPower();
    existing_.motorPower_ = motorShaftPower.calculatePower();
    existing_.estimatedFLA_ = motorShaftPower.calculateEstimatedFLA();
    // Calculate PumpShaftPower
    PumpShaftPower pumpShaftPower(existing_.motorShaftPower_, pump_.getDrive());
    existing_.pumpShaftPower_ = pumpShaftPower.calculate();

    // Calculate Pump Efficiency
    PumpEfficiency pumpEfficiency(pump_.getSpecificGravity(), fieldData_.getFlowRate(), fieldData_.getHead(),
                                  existing_.pumpShaftPower_);
    existing_.pumpEfficiency_ = pumpEfficiency.calculate();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(existing_.motorPower_, financial_.getOperatingFraction());
    existing_.annualEnergy_ = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(existing_.annualEnergy_, financial_.getUnitCost());
    existing_.annualCost_ = annualCost.calculate();

    return 0;
}

double PSATResult::calculateOptimal() {
    /**
     * Steps for calculating the optimal values:
     *  1. Calculate optimal pump efficiency, fluid power and pump shaft power
     *  2. Calculate Motor shaft power
     *      a. If a belt drive is specified, calculate the motor shaft power
     *      b. If direct drive, motor shaft power = pump shaft power
     *  3. Select motor size based on required motor shaft power
     *  4. Develop 25% interval motor performance data for EE motor of the selected size
     *  5. Do curve fitting of current from 25% to 1% intervals
     *  6. Do curve fitting of efficiency in 1% intervals
     *  7. Using current and efficiency 1% interval data, calculate balance of motor data in 1% intervals
     *  8. Calculate required power, motor eff., current, pf from shaft power
     *  9. Calculate annual energy and energy cost
     *  10.Calculate annual savings potential and optimization rating
     */

    OptimalPumpEfficiency optimalPumpEfficiency(pump_.getStyle(), pump_.getAchievableEfficiency(), pump_.getRpm(),
                                                pump_.getKviscosity(), pump_.getStageCount(), fieldData_.getFlowRate(),
                                                fieldData_.getHead());
    optimal_.pumpEfficiency_ = optimalPumpEfficiency.calculate();
    OptimalPumpShaftPower optimalPumpShaftPower(fieldData_.getFlowRate(), fieldData_.getHead(), pump_.getSpecificGravity(),
                                                optimal_.pumpEfficiency_);
    optimal_.pumpShaftPower_ = optimalPumpShaftPower.calculate();
    OptimalMotorShaftPower optimalMotorShaftPower(optimal_.pumpShaftPower_, pump_.getDrive());
    optimal_.motorShaftPower_ = optimalMotorShaftPower.calculate();
    OptimalMotorSize optimalMotorSize(optimal_.motorShaftPower_, motor_.getSizeMargin());
    optimal_.motorRatedPower_ = optimalMotorSize.calculate();
    OptimalMotorPower optimalMotorPower(optimal_.motorRatedPower_, fieldData_.getMotorPower(), motor_.getMotorRpm(),
                                        motor_.getLineFrequency(),
                                        motor_.getEfficiencyClass(), Motor::EfficiencyClass::ENERGY_EFFICIENT, motor_.getSpecifiedEfficiency(),
                                        motor_.getMotorRatedVoltage(), motor_.getFullLoadAmps(),
                                        fieldData_.getVoltage(), fieldData_.getLoadEstimationMethod(),
                                        fieldData_.getMotorAmps(), optimal_.motorShaftPower_);
    optimalMotorPower.calculate();
    optimal_.motorCurrent_ = optimalMotorPower.getMotorCurrent();
    optimal_.motorEfficiency_ = optimalMotorPower.getMotorEff();
    optimal_.motorPower_ = optimalMotorPower.getMotorPower();
    optimal_.motorPowerFactor_ = optimalMotorPower.getMotorPf();
    // Calculate Annual Energy
    AnnualEnergy annualEnergy(optimal_.motorPower_, financial_.getOperatingFraction());
    optimal_.annualEnergy_ = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(optimal_.annualEnergy_, financial_.getUnitCost());
    optimal_.annualCost_ = annualCost.calculate();

    // Annual Savings potential
//    annualSavingsPotential_ = existing_.annualCost_ - optimal_.annualCost_;
    // Optimization Rating
//    optimizationRating_ = optimal_.motorPower / existing_.motorPower;
    return 0;
}
double PSATResult::calculateModified() {
    /**
         * Steps for calculating the modified values:
     *  1. Calculate fluid power and pump shaft power
     *  2. Calculate Motor shaft power
     *      a. If a belt drive is specified, calculate the motor shaft power
     *      b. If direct drive, motor shaft power = pump shaft power
     *  4. Develop 25% interval motor performance data for specified efficiency rating motor of the selected size
     *  5. Do curve fitting of current from 25% to 1% intervals
     *  6. Do curve fitting of efficiency in 1% intervals
     *  7. Using current and efficiency 1% interval data, calculate balance of motor data in 1% intervals
     *  8. Calculate required power, motor eff., current, pf from shaft power
     *  9. Calculate annual energy and energy cost
     *  10.Calculate annual savings potential and optimization rating

     */

    if (pump_.getStyle() == Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY) {
        modified_.pumpEfficiency_ = pump_.getAchievableEfficiency();
    } else {
        modified_.pumpEfficiency_ = baselinePumpEfficiency_;
    }

    OptimalPumpShaftPower modifiedPumpShaftPower(fieldData_.getFlowRate(), fieldData_.getHead(), pump_.getSpecificGravity(),
                                                modified_.pumpEfficiency_);
    modified_.pumpShaftPower_ = modifiedPumpShaftPower.calculate();

    OptimalMotorShaftPower modifiedMotorShaftPower(modified_.pumpShaftPower_, pump_.getDrive());
    modified_.motorShaftPower_ = modifiedMotorShaftPower.calculate();

    modified_.motorRatedPower_ = motor_.getMotorRatedPower();
    OptimalMotorPower modifiedMotorPower(modified_.motorRatedPower_, fieldData_.getMotorPower(), motor_.getMotorRpm(),
                                        motor_.getLineFrequency(),
                                        motor_.getEfficiencyClass(), motor_.getEfficiencyClass(), motor_.getSpecifiedEfficiency(),
                                        motor_.getMotorRatedVoltage(), motor_.getFullLoadAmps(),
                                        fieldData_.getVoltage(), fieldData_.getLoadEstimationMethod(),
                                        fieldData_.getMotorAmps(), modified_.motorShaftPower_);
    modifiedMotorPower.calculate();
    modified_.motorCurrent_ = modifiedMotorPower.getMotorCurrent();
    modified_.motorEfficiency_ = modifiedMotorPower.getMotorEff();
    modified_.motorPower_ = modifiedMotorPower.getMotorPower();
    modified_.motorPowerFactor_ = modifiedMotorPower.getMotorPf();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(modified_.motorPower_, financial_.getOperatingFraction());
    modified_.annualEnergy_ = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(modified_.annualEnergy_, financial_.getUnitCost());
    modified_.annualCost_ = annualCost.calculate();

    // Annual Savings potential
    //annualSavingsPotential_ = existing_.annualCost_ - modified_.annualCost_;
    annualSavingsPotential_ = 0.0;
    // Optimization Rating
    //optimizationRating_ = modified_.motorPower / existing_.motorPower;
    optimizationRating_ = 0.0;
    return 0;
}
