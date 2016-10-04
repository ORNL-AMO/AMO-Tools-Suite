#include <iostream>
#include "PSATResult.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Pump pump(Pump::Style::API_DOUBLE_SUCTION, 1780, Pump::Drive::DIRECT_DRIVE, 1.00, 1.000, 1, false);
    Motor motor(Motor::LineFrequency::FREQ60, 200, 1780, Motor::EfficiencyClass::ENERGY_EFFICIENT, 95, 460, false,
                225.0, 0);
    Financial financial(1.000, 0.05);
    FieldData fieldData(2000, 277, FieldData::LoadEstimationMethod::POWER, 80, 0, 460);
    PSATResult psatResult(pump, motor, financial, fieldData);
    psatResult.calculate();
    cout << "Motor SHaft power: " << psatResult.getExisting().motorShaftPower_ << endl;
}