#include <iostream>
#include "PSATResult.h"
using namespace std;

int main() {

    std::cout << "Hello, World!" << std::endl;
    Pump pump(Pump::Style::API_DOUBLE_SUCTION, 1780, Pump::Drive::DIRECT_DRIVE, 1.00, 1.000, 1, Pump::Speed::NOT_FIXED_SPEED);
    Motor motor(Motor::LineFrequency::FREQ60, 200, 1780, Motor::EfficiencyClass::SPECIFIED, 95, 460, 225.0, 0);
    Financial financial(1.000, 0.05);
    FieldData fieldData(1840, 174.85, FieldData::LoadEstimationMethod::POWER, 150, 0, 480);

    PSATResult psatResult(pump,motor,financial,fieldData);
    psatResult.calculateExisting();
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

}