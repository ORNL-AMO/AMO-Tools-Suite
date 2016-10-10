#include <iostream>
#include "PSATResult.h"
using namespace std;

int main() {

    std::cout << "Hello, World!" << std::endl;
    Pump pump(Pump::Style::API_DOUBLE_SUCTION, 1780, Pump::Drive::DIRECT_DRIVE, 1.00, 1.000, 1, Pump::Speed::NOT_FIXED_SPEED);
    Motor motor(Motor::LineFrequency::FREQ60, 200, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT, 95, 460, 225.0, 0);
    Financial financial(1.000, 0.05);
    FieldData fieldData(2000, 277, FieldData::LoadEstimationMethod::POWER, 80, 0, 480);
    //FieldData fieldData1(1840, 174.85, FieldData::LoadEstimationMethod::POWER, 80, 125.857, 480);

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

    Pump pump1(Pump::Style::END_SUCTION_ANSI_API,1780,Pump::Drive::DIRECT_DRIVE,
              1,1,1,Pump::Speed::NOT_FIXED_SPEED);
    Motor motor1(Motor::LineFrequency::FREQ60,200,1786,
                Motor::EfficiencyClass::ENERGY_EFFICIENT,0,460,225.8,0);
    Financial fin(1,.05);
    FieldData fd(2000,277,FieldData::LoadEstimationMethod::POWER,
                 80,0,460);

    PSATResult psat(pump1,motor1,fin,fd);
    psat.calculateExisting();
    auto ex = psat.getExisting();

    cout << "msp " << ex.motorShaftPower_ << endl;
}