/**
 * @brief Contains the declaration of MotorEfficiency25 class including the getters and setters as well as the calculators
 *          for motor efficiency.
 *      calculate(): Calculates the motor efficiency givenat 25% intervals of load factor.
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/6/16.
//

#ifndef UNTITLED_MOTOREFFICIENCY25_H
#define UNTITLED_MOTOREFFICIENCY25_H

#include "../Motor.h"
#include <vector>
#include "Poles.h"

class MotorEfficiency25 {
public:
    /**
     * Constructor
     * @param efficiencyClass Efficiency class of motor
     * @param motorRatedPower Rated power of motor
     * @param motorRpm Rpm of motor
     * @param lineFrequency Line Frequency of motor
     * @return nothing
     */
    MotorEfficiency25(Motor::EfficiencyClass efficiencyClass, double motorRatedPower, double motorRpm,
                      Motor::LineFrequency lineFrequency) : efficiencyClass_(efficiencyClass),
                                                            motorRatedPower_(motorRatedPower), motorRpm_(motorRpm),
                                                            lineFrequency_(lineFrequency) {};

    /**
     *
     * @return Vector containing motor efficiency
     */
    std::vector<double> calculate();

private:
    Motor::EfficiencyClass efficiencyClass_;
    double motorRatedPower_;
    double motorRpm_;
    Motor::LineFrequency lineFrequency_;
};


#endif //UNTITLED_MOTOREFFICIENCY25_H
