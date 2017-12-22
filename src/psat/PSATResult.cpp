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
    MotorShaftPower motorShaftPower(motor.getMotorRatedPower(), fieldData.getMotorPower(), motor.getMotorRpm(),
                                    motor.getLineFrequency(),
                                    motor.getEfficiencyClass(), motor.getSpecifiedEfficiency(),
                                    motor.getMotorRatedVoltage(), motor.getFullLoadAmps(),
                                    fieldData.getVoltage(), fieldData.getLoadEstimationMethod(),
                                    fieldData.getMotorAmps());
    existing.motorShaftPower = motorShaftPower.calculate();
    existing.motorCurrent = motorShaftPower.getCurrent();
    existing.motorPowerFactor = motorShaftPower.getPowerFactor();
    existing.motorEfficiency = motorShaftPower.getEfficiency();
    existing.motorRatedPower = motor.getMotorRatedPower();
    existing.motorPower = motorShaftPower.getPower();
    existing.estimatedFLA = motorShaftPower.getEstimatedFLA();
    // Calculate PumpShaftPower
    PumpShaftPower pumpShaftPower(existing.motorShaftPower, pump.getDrive());
    existing.pumpShaftPower = pumpShaftPower.calculate();

    // Calculate Pump Efficiency
    PumpEfficiency pumpEfficiency(pump.getSpecificGravity(), fieldData.getFlowRate(), fieldData.getHead(),
                                  existing.pumpShaftPower);
    existing.pumpEfficiency = pumpEfficiency.calculate();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(existing.motorPower, financial.getOperatingFraction());
    existing.annualEnergy = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(existing.annualEnergy, financial.getUnitCost());
    existing.annualCost = annualCost.calculate();

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

    OptimalPumpEfficiency optimalPumpEfficiency(pump.getStyle(), pump.getAchievableEfficiency(), pump.getRpm(),
                                                pump.getKviscosity(), pump.getStageCount(), fieldData.getFlowRate(),
                                                fieldData.getHead());
    optimal.pumpEfficiency = optimalPumpEfficiency.calculate();
    OptimalPumpShaftPower optimalPumpShaftPower(fieldData.getFlowRate(), fieldData.getHead(), pump.getSpecificGravity(),
                                                optimal.pumpEfficiency);
    optimal.pumpShaftPower = optimalPumpShaftPower.calculate();
    OptimalMotorShaftPower optimalMotorShaftPower(optimal.pumpShaftPower, pump.getDrive());
    optimal.motorShaftPower = optimalMotorShaftPower.calculate();
    OptimalMotorSize optimalMotorSize(optimal.motorShaftPower, motor.getSizeMargin());
    optimal.motorRatedPower = optimalMotorSize.calculate();
    OptimalMotorPower optimalMotorPower(optimal.motorRatedPower, fieldData.getMotorPower(), motor.getMotorRpm(),
                                        motor.getLineFrequency(),
                                        motor.getEfficiencyClass(), Motor::EfficiencyClass::ENERGY_EFFICIENT, motor.getSpecifiedEfficiency(),
                                        motor.getMotorRatedVoltage(), motor.getFullLoadAmps(),
                                        fieldData.getVoltage(), fieldData.getLoadEstimationMethod(),
                                        fieldData.getMotorAmps(), optimal.motorShaftPower);
    optimalMotorPower.calculate();
    optimal.motorCurrent = optimalMotorPower.getMotorCurrent();
    optimal.motorEfficiency = optimalMotorPower.getMotorEff();
    optimal.motorPower = optimalMotorPower.getMotorPower();
    optimal.motorPowerFactor = optimalMotorPower.getMotorPf();
    // Calculate Annual Energy
    AnnualEnergy annualEnergy(optimal.motorPower, financial.getOperatingFraction());
    optimal.annualEnergy = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(optimal.annualEnergy, financial.getUnitCost());
    optimal.annualCost = annualCost.calculate();

    // Annual Savings potential
//    annualSavingsPotential = existing.annualCost - optimal.annualCost;
    // Optimization Rating
//    optimizationRating = optimal.motorPower / existing.motorPower;
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

    if (pump.getStyle() == Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY) {
        modified.pumpEfficiency = pump.getAchievableEfficiency();
    } else {
        modified.pumpEfficiency = baselinePumpEfficiency;
    }

    OptimalPumpShaftPower modifiedPumpShaftPower(fieldData.getFlowRate(), fieldData.getHead(), pump.getSpecificGravity(),
                                                modified.pumpEfficiency);
    modified.pumpShaftPower = modifiedPumpShaftPower.calculate();

    OptimalMotorShaftPower modifiedMotorShaftPower(modified.pumpShaftPower, pump.getDrive());
    modified.motorShaftPower = modifiedMotorShaftPower.calculate();

    modified.motorRatedPower = motor.getMotorRatedPower();
    OptimalMotorPower modifiedMotorPower(modified.motorRatedPower, fieldData.getMotorPower(), motor.getMotorRpm(),
                                        motor.getLineFrequency(),
                                        motor.getEfficiencyClass(), Motor::EfficiencyClass::PREMIUM, motor.getSpecifiedEfficiency(),
                                        motor.getMotorRatedVoltage(), motor.getFullLoadAmps(),
                                        fieldData.getVoltage(), fieldData.getLoadEstimationMethod(),
                                        fieldData.getMotorAmps(), modified.motorShaftPower);
    modifiedMotorPower.calculate();
    modified.motorCurrent = modifiedMotorPower.getMotorCurrent();
    modified.motorEfficiency = modifiedMotorPower.getMotorEff();
    modified.motorPower = modifiedMotorPower.getMotorPower();
    modified.motorPowerFactor = modifiedMotorPower.getMotorPf();

    // Calculate Annual Energy
    AnnualEnergy annualEnergy(modified.motorPower, financial.getOperatingFraction());
    modified.annualEnergy = annualEnergy.calculate();

    // Calculate Annual Cost
    AnnualCost annualCost(modified.annualEnergy, financial.getUnitCost());
    modified.annualCost = annualCost.calculate();

    // Annual Savings potential
    //annualSavingsPotential = existing.annualCost - modified.annualCost;
    annualSavingsPotential = 0.0;
    // Optimization Rating
    //optimizationRating = modified.motorPower / existing.motorPower;
    optimizationRating = 0.0;
    return 0;
}
