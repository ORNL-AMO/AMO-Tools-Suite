/**
 * @brief Contains the definition of functions of OptimalMotorShaftPower class.
 *      calculate(): Calculates the Optimal Motor ShaftPower
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/motor/OptimalMotorShaftPower.h"

double OptimalMotorShaftPower::calculate() {
    if(drive == Motor::Drive::DIRECT_DRIVE) {
        motorShaftPower = pumpShaftPower;
    } else if (drive == Motor::Drive::N_V_BELT_DRIVE) {
        //Case of notched Belt Drive - see pumpshaftpower.cpp for more info
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower) * -0.02067997) +
                                  4.136368 * exp((pumpShaftPower) * -0.226025) + 4.162707) / 100;
        double BLPinhp = BLPinPercentage * pumpShaftPower;
        motorShaftPower = pumpShaftPower + (BLPinhp * 0.05 / 0.07);
    } else if (drive == Motor::Drive::S_BELT_DRIVE) {
        //Case of Synchronous Belt Drive - see pumpshaftpower.cpp for more info
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower) * -0.02067997) +
                                  4.136368 * exp((pumpShaftPower) * -0.226025) + 4.162707) / 100;
        double BLPinhp = BLPinPercentage * pumpShaftPower;
        motorShaftPower = pumpShaftPower + (BLPinhp * 0.02 / 0.07);
    } else if (drive == Motor::Drive::SPECIFIED) {
        //Case of SPECIFIED DRIVE
        motorShaftPower = pumpShaftPower / specifiedEfficiency;
    } else {
        //Case of v- Belt Drive
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower) * -0.02067997) +
                                  4.136368 * exp((pumpShaftPower) * -0.226025) + 4.162707) / 100;
        double BLPinhp = BLPinPercentage * pumpShaftPower;
        motorShaftPower = pumpShaftPower + BLPinhp;
    }
    return motorShaftPower;
}
