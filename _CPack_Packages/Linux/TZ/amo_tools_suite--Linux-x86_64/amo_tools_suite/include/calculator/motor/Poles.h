/**
 * @brief Header file for Poles class
 *
 * This contains the prototypes of Poles calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

#ifndef UNTITLED_POLECALCULATE_H
#define UNTITLED_POLECALCULATE_H

#include <results/InputData.h>

class Poles {
public:
    /**
     * Constructor
     * @param motorRpm double, RPM of motor.
     * @param lineFreq Motor::LineFrequency, Line frequency of motor as either 50Hz or 60Hz.
     */
    Poles(double motorRpm, Motor::LineFrequency lineFreq)
            : motorRpm(motorRpm), 
              lineFreq(lineFreq) 
    {};

    /**
     * Calculates the number of poles
     * @return int, number of poles
     */
    int calculate();

private:
    double motorRpm;
    Motor::LineFrequency lineFreq;
};

#endif //UNTITLED_POLECALCULATE_H
