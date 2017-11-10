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
    if(drive_ == Pump::Drive::DIRECT_DRIVE){
        motorShaftPower_ = pumpShaftPower_;
      } else if(drive_ == Pump::Drive::N_V_BELT_DRIVE){
          //Case of notched Belt Drive - see pumpshaftpower.cpp for more info
          double BLPinPercentage = (0.7489574 * exp((pumpShaftPower_) * (-0.02067997)) +
              4.136368 * exp((pumpShaftPower_) * (-0.226025)) + 4.162707) / 100;
          double BLPinhp = BLPinPercentage * pumpShaftPower_;
          motorShaftPower_ = (pumpShaftPower_ + BLPinhp) * (.93/.95);
      } else if(drive_ == Pump::Drive::S_BELT_DRIVE){
        //Case of Synchronous Belt Drive - see pumpshaftpower.cpp for more info
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower_) * (-0.02067997)) +
            4.136368 * exp((pumpShaftPower_) * (-0.226025)) + 4.162707) / 100;
        double BLPinhp = BLPinPercentage * pumpShaftPower_;
        motorShaftPower_ = (pumpShaftPower_ + BLPinhp) * (.93/.98);
  } else {
        //Case of v- Belt Drive
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower_) * (-0.02067997)) +
            4.136368 * exp((pumpShaftPower_) * (-0.226025)) + 4.162707) / 100;
        double BLPinhp = BLPinPercentage * pumpShaftPower_;
        motorShaftPower_ = pumpShaftPower_ + BLPinhp;
    }
    return motorShaftPower_;
}
