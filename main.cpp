#include <iostream>
#include "PSATResult.h"
#include "./calculator/MotorPowerFactor.h"
#include "./calculator/MotorEfficiency.h"
#include <iomanip>
using namespace std;

int main() {

    std::cout << "Hello, World!" << std::endl;
    cout <<  setprecision(16);
    Pump pump(Pump::Style::END_SUCTION_ANSI_API, 90, 1780, Pump::Drive::DIRECT_DRIVE, 1.00, 1.000, 2, Pump::Speed::NOT_FIXED_SPEED);
    Motor motor(Motor::LineFrequency::FREQ60, 200, 1780, Motor::EfficiencyClass::SPECIFIED, 95, 460, 225.0, 0);
    Financial financial(1.000, 0.05);
    FieldData fieldData(1840, 174.85, FieldData::LoadEstimationMethod::POWER, 80, 125.857, 480);

    PSATResult psatResult(pump,motor,financial,fieldData);
    psatResult.calculateExisting();
    psatResult.calculateOptimal();

    cout << "Pump Efficiency: " << psatResult.getExisting().pumpEfficiency_ << endl;
    cout << "Motor Rated power: " << psatResult.getExisting().motorRatedPower_ << endl;
    cout << "Motor Shaft power: " << psatResult.getExisting().motorShaftPower_ << endl;
    cout << "Pump Shaft power: " << psatResult.getExisting().pumpShaftPower_ << endl;
    cout << "Motor Efficiency: " << psatResult.getExisting().motorEfficiency_ << endl;
    cout << "Motor power factor: " << psatResult.getExisting().motorPowerFactor_ << endl;
    cout << "Motor current: " << psatResult.getExisting().motorCurrent_ << endl;
    cout << "Motor power: " << psatResult.getExisting().motorPower_ << endl;
    cout << "Annual Energy: " << psatResult.getExisting().annualEnergy_ << endl;
    cout << "Annual Cost: " << psatResult.getExisting().annualCost_ << endl;
    cout << "Estimated FLA: " << psatResult.getExisting().estimatedFLA_ << endl;

    cout << "Optimal **********************************" << endl;
    cout << "Pump Efficiency: " << psatResult.getOptimal().pumpEfficiency_ << endl;
    cout << "Motor Rated power: " << psatResult.getOptimal().motorRatedPower_ << endl;
    cout << "Motor Shaft power: " << psatResult.getOptimal().motorShaftPower_ << endl;
    cout << "Pump Shaft power: " << psatResult.getOptimal().pumpShaftPower_ << endl;
    cout << "Motor Efficiency: " << psatResult.getOptimal().motorEfficiency_ << endl;
    cout << "Motor power factor: " << psatResult.getOptimal().motorPowerFactor_ << endl;
    cout << "Motor current: " << psatResult.getOptimal().motorCurrent_ << endl;
    cout << "Motor power: " << psatResult.getOptimal().motorPower_ << endl;
    cout << "Annual Energy: " << psatResult.getOptimal().annualEnergy_ << endl;
    cout << "Annual Cost: " << psatResult.getOptimal().annualCost_ << endl;

    cout << "getAnnualSavingsPotential: " << psatResult.getAnnualSavingsPotential() << endl;
    cout << "getOptimizationRating: " << psatResult.getOptimizationRating() << endl;

//    MotorEfficiency mef(Motor::LineFrequency::FREQ60,0,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,0,0);
//    cout << mef.calculate();
//
}

