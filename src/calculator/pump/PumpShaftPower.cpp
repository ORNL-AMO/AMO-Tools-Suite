#include <cmath>
#include "calculator/pump/PumpShaftPower.h"

//     2a	If a belt drive is specified, calculate the pump shaft power
//        2a-1 - V-Belt, calculated from AMCA 203-90 Appendix L
//        2a-2 & 2a-3, calculated, relative to V-Belt, based on AMO Belt Drive Tip Sheet
//     2b	If direct drive, motor shaft power = pump shaft power
PumpShaftPower::Output PumpShaftPower::calculate() {
    if (drive == Motor::Drive::DIRECT_DRIVE) {
        const double BLM = 0;
        const double driveEfficiency = 1 - BLM;
        return {motorShaftPower, driveEfficiency};
    } else if (drive == Motor::Drive::N_V_BELT_DRIVE) {
        const double BLM = motorShaftPower * ((0.68759 * std::exp(motorShaftPower * -0.019791) +
                                                3.7558 * std::exp((motorShaftPower) * -0.21507) + 3.9963) * (0.05 / 0.07)/ 100);
        const double driveEfficiency = 1 - BLM/motorShaftPower;
        const double pumpShaftPower = motorShaftPower - BLM;
        // According to AMO Tip sheet for belt drives, a v-belt drive is on average 93% efficient and a notched v-belt drive is 95% efficient
        return {pumpShaftPower, driveEfficiency};
    } else if (drive == Motor::Drive::S_BELT_DRIVE) {
        const double BLM = motorShaftPower * ((0.68759 * std::exp(motorShaftPower * -0.019791) +
                                                3.7558 * std::exp(motorShaftPower * -0.21507) + 3.9963) * (0.02 / 0.07) / 100);
        const double driveEfficiency = 1 - BLM/motorShaftPower;
        const double pumpShaftPower = motorShaftPower - BLM;
        // According to AMO Tip sheet for belt drives, a v-belt drive is on average 93% efficient and a Synchronous-belt drive is 98% efficient
        return {pumpShaftPower, driveEfficiency};
    }
    else if (drive == Motor::Drive::SPECIFIED) {
        //Case of SPECIFIED DRIVE
        const double driveEfficiency = specifiedEfficiency;
        const double pumpShaftPower = motorShaftPower * specifiedEfficiency;
        return {pumpShaftPower, driveEfficiency};
    }

    const double BLM = motorShaftPower * ((0.68759 * std::exp(motorShaftPower * -0.019791) +
                                           3.7558 * std::exp(motorShaftPower * -0.21507) + 3.9963) / 100);
    const double driveEfficiency = 1 - BLM/motorShaftPower;
    const double pumpShaftPower = motorShaftPower - BLM;
    return {pumpShaftPower, driveEfficiency};
}
