/**
 * @brief Contains the declaration of MotorCurrent class including the getters and setters as well as the calculators for motor current.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORCURRENT_H
#define AMO_LIBRARY_MOTORCURRENT_H


#include <cmath>
#include<iostream>
#include "../motor.h"
#include "CurveFitVal.h"
#include "EstimateFLA.h"
#include <vector>

class MotorCurrent {
public:
    /**
     * Constructor
     * @param motorRatedPower Rated power of motor
     * @param motorRPM RPM of motor
     * @param lineFrequency line Frequency of motor
     * @param efficiencyClass Efficiency class of motor
     * @param specifiedEfficiency Specified efficiency of motor when the efficiency class = SPECIFIED
     * @param loadFactor
     * @param ratedVoltage
     * @param fullLoadAmps
     * @return
     */
    MotorCurrent(double motorRatedPower, int motorRPM, Motor::LineFrequency lineFrequency,
                 Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double loadFactor,
                 double ratedVoltage, double fullLoadAmps) :
            motorRatedPower_(motorRatedPower), motorRPM_(motorRPM),
            lineFrequency_(lineFrequency),
            efficiencyClass_(efficiencyClass),
            specifiedEfficiency_(specifiedEfficiency),
            loadFactor_(loadFactor), ratedVoltage_(ratedVoltage),
            fullLoadAmps_(fullLoadAmps) {};

    double calculate();

    double getEstimatedFLA() {
        return estimatedFLA_;
    }


private:
    double motorRatedPower_ = 0.0;
    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_ = 0.0;
    double loadFactor_ = 0.0;
    double motorCurrent_ = 0.0;
    double ratedVoltage_ = 0.0;
    double estimatedFLA_ = 0.0;
    double fullLoadAmps_ = 0.0;
};


#endif //AMO_LIBRARY_MOTORCURRENT_H
