#include <iostream>
#include <iomanip>
#include "PSATResult.h"
#include "calculator/MotorPowerFactor.h"
#include "calculator/MotorEfficiency.h"

int main() {

    std::cout << "Hello, World!" << std::endl;
    std::cout << std::setprecision(16);
    Pump pump(Pump::Style::END_SUCTION_ANSI_API, 90, 1780, Pump::Drive::DIRECT_DRIVE, 1.00, 1.000, 2, Pump::Speed::NOT_FIXED_SPEED);
    Motor motor(Motor::LineFrequency::FREQ60, 200, 1780, Motor::EfficiencyClass::SPECIFIED, 95, 460, 225.0, 0);
    Financial financial(1.000, 0.05);
    FieldData fieldData(1840, 174.85, FieldData::LoadEstimationMethod::POWER, 80, 125.857, 480);

    PSATResult psatResult(pump,motor,financial,fieldData);
    psatResult.calculateExisting();
    psatResult.calculateOptimal();

    std::cout << "Pump Efficiency: " << psatResult.getExisting().pumpEfficiency_ << std::endl;
    std::cout << "Motor Rated power: " << psatResult.getExisting().motorRatedPower_ << std::endl;
    std::cout << "Motor Shaft power: " << psatResult.getExisting().motorShaftPower_ << std::endl;
    std::cout << "Pump Shaft power: " << psatResult.getExisting().pumpShaftPower_ << std::endl;
    std::cout << "Motor Efficiency: " << psatResult.getExisting().motorEfficiency_ << std::endl;
    std::cout << "Motor power factor: " << psatResult.getExisting().motorPowerFactor_ << std::endl;
    std::cout << "Motor current: " << psatResult.getExisting().motorCurrent_ << std::endl;
    std::cout << "Motor power: " << psatResult.getExisting().motorPower_ << std::endl;
    std::cout << "Annual Energy: " << psatResult.getExisting().annualEnergy_ << std::endl;
    std::cout << "Annual Cost: " << psatResult.getExisting().annualCost_ << std::endl;
    std::cout << "Estimated FLA: " << psatResult.getExisting().estimatedFLA_ << std::endl;

    std::cout << "Optimal **********************************" << std::endl;
    std::cout << "Pump Efficiency: " << psatResult.getOptimal().pumpEfficiency_ << std::endl;
    std::cout << "Motor Rated power: " << psatResult.getOptimal().motorRatedPower_ << std::endl;
    std::cout << "Motor Shaft power: " << psatResult.getOptimal().motorShaftPower_ << std::endl;
    std::cout << "Pump Shaft power: " << psatResult.getOptimal().pumpShaftPower_ << std::endl;
    std::cout << "Motor Efficiency: " << psatResult.getOptimal().motorEfficiency_ << std::endl;
    std::cout << "Motor power factor: " << psatResult.getOptimal().motorPowerFactor_ << std::endl;
    std::cout << "Motor current: " << psatResult.getOptimal().motorCurrent_ << std::endl;
    std::cout << "Motor power: " << psatResult.getOptimal().motorPower_ << std::endl;
    std::cout << "Annual Energy: " << psatResult.getOptimal().annualEnergy_ << std::endl;
    std::cout << "Annual Cost: " << psatResult.getOptimal().annualCost_ << std::endl;

    std::cout << "getAnnualSavingsPotential: " << psatResult.getAnnualSavingsPotential() << std::endl;
    std::cout << "getOptimizationRating: " << psatResult.getOptimizationRating() << std::endl;

}

