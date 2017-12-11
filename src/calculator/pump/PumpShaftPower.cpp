#include <cmath>
#include "calculator/pump/PumpShaftPower.h"

//     2a	If a belt drive is specified, calculate the pump shaft power
//        2a-1 - V-Belt, calculated from AMCA 203-90 Appendix L
//        2a-2 & 2a-3, calculated, relative to V-Belt, based on AMO Belt Drive Tip Sheet
//     2b	If direct drive, motor shaft power = pump shaft power
double PumpShaftPower::calculate() {
    if (drive_ == Pump::Drive::DIRECT_DRIVE) {
        pumpShaftPower_ = motorShaftPower_;
    } else if (drive_ == Pump::Drive::N_V_BELT_DRIVE) {
        const double BLM = motorShaftPower_ * ((0.68759 * std::exp(motorShaftPower_ * -0.019791) +
                                                3.7558 * std::exp((motorShaftPower_) * -0.21507) + 3.9963) / 100);
        // According to AMO Tip sheet for belt drives, a v-belt drive is on average 93% efficient and a notched v-belt drive is 95% efficient
        pumpShaftPower_ = motorShaftPower_ - (BLM * 0.05 / 0.07);
    } else if (drive_ == Pump::Drive::S_BELT_DRIVE) {
        const double BLM = motorShaftPower_ * ((0.68759 * std::exp(motorShaftPower_ * -0.019791) +
                                                3.7558 * std::exp(motorShaftPower_ * -0.21507) + 3.9963) / 100);
        // According to AMO Tip sheet for belt drives, a v-belt drive is on average 93% efficient and a Synchronous-belt drive is 98% efficient
        pumpShaftPower_ = motorShaftPower_ - (BLM * 0.02 / 0.07);
    } else {
        const double BLM = motorShaftPower_ * ((0.68759 * std::exp(motorShaftPower_ * -0.019791) +
                                                3.7558 * std::exp(motorShaftPower_ * -0.21507) + 3.9963) / 100);
        pumpShaftPower_ = motorShaftPower_ - BLM;
    }
    return pumpShaftPower_;
}
