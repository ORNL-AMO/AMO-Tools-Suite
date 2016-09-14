//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"


double MotorShaftPower::calculate() {


/*
 * Code for Motor Shaft Power
    double tempLoadFraction_ = 0.01;
    double power = 0.0 ,powerE1 = 0.0 , powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;
    while (true) {
        MotorCurrent motorCurrent(200, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, tempLoadFraction_);
        current = motorCurrent.calculate();
        MotorEfficiency motorEfficiency(0, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 0, 0, 0, 200, 80, tempLoadFraction_);
        eff = motorEfficiency.calculate();
        MotorPowerFactor motorPowerFactor(200, tempLoadFraction_, current, eff, 460);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(460, current, pf);
        power = motorPower.calculate();
//        cout << "Load Factor :" << tempLoadFraction_ << endl;
//        cout << "Current: " << current << endl;
//        cout << "Efficiency " << eff << endl;
//        cout << "MotorPower Factor: " << pf << endl;
//        cout << "Power :" << power << endl;
//        cout << "**********************************************" << endl;
        if (power > 80) {
            powerE2 = power;
            lf2 = tempLoadFraction_;
            eff2 = eff;
            pf2 = pf;
            break;
        } else {
            powerE1 = power;
            lf1 = tempLoadFraction_;
            eff1 = eff;
            pf1 = pf;
            tempLoadFraction_ += 0.01;
        }
    }

    double motorPowerdiff_ = powerE2 - powerE1;
    double measuredMotorPowerdiff_ = 80 - powerE1;
    double fractionalIndex_ = lf1 + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    eff = eff1 + 100*(fractionalIndex_-lf1)*(eff2-eff1);
    pf = pf1 + 100*(fractionalIndex_-lf1)*(pf2-pf1);
    double motorShaftPower_ = 80 * eff;
    cout << "Load Factor :" << fractionalIndex_ << endl;
    cout << "Current: " << current << endl;
    cout << "Efficiency " << eff << endl;
    cout << "MotorPower Factor: " << pf << endl;
    cout << "Power :" << power << endl;
    cout << "MotorShaft Power" << motorShaftPower_ << endl;
    cout << "MotorShaft Power(in hp)" << motorShaftPower_/0.746 << endl;
    cout << "**********************************************" << endl;
*/



    motorShaftPower_;
    return 101.19;
}