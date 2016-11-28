/**
 * @brief Contains the definition of functions of OptimalMotorShaftPower class.
 *      calculate(): Calculates the Optimal Motor ShaftPower
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
//
// Created by Accawi, Gina K. on 8/19/16.
//

#include "OptimalMotorShaftPower.h"

double OptimalMotorShaftPower::calculate() {
    if(drive_ == Pump::Drive::DIRECT_DRIVE){
        motorShaftPower_ = pumpShaftPower_;
    }
    else{
        //Case of Belt Drive
        double BLPinPercentage = (0.7489574 * exp((pumpShaftPower_)*(-0.02067997))+4.136368*exp((pumpShaftPower_)*(-0.226025))+4.162707)/100;
        double BLPinhp = BLPinPercentage * pumpShaftPower_;
        motorShaftPower_ = pumpShaftPower_ + BLPinhp;
    }
    return motorShaftPower_;
}
