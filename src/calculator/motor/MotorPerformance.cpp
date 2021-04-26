/**
 * @brief 
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "calculator/motor/MotorPerformance.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"


MotorPerformance::Output MotorPerformance::calculate() {
    double current = 0;
    double efficiency = 0;
    double powerFactor = 0;
    
    MotorEfficiency motorEfficiency(lineFrequency, motorRpm, efficiencyClass, motorRatedPower);
    double calculatedEfficiency = motorEfficiency.calculate(loadFactor, specifiedEfficiency);
    //Motor Current
    MotorCurrent motorCurrent(motorRatedPower, motorRpm, lineFrequency, efficiencyClass, specifiedEfficiency, loadFactor, ratedVoltage);
    double calculatedCurrent = motorCurrent.calculateCurrent(fullLoadAmps);
    //Motor Power Factor
    MotorPowerFactor motorPowerFactor(motorRatedPower, loadFactor, calculatedCurrent, calculatedEfficiency, ratedVoltage);
    powerFactor = motorPowerFactor.calculate() * 100; 
    efficiency = calculatedEfficiency * 100;
    current = calculatedCurrent / fullLoadAmps * 100;
    return {current, efficiency, powerFactor};
}
