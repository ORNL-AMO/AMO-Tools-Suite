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

#include "psat/Motor.h"

class Poles {
public:
    /**
     * Constructor
     * @param motorRpm RPM of motor.
     * @param lineFreq Line frequency of motor as either 50Hz or 60Hz.
     * @return nothing
     */
    Poles(
        int motorRpm,
        Motor::LineFrequency lineFreq
    ) :
        motorRpm_(motorRpm),
        lineFreq_(lineFreq)
    {};

    int calculate();

private:
    int motorRpm_;
    Motor::LineFrequency lineFreq_;
    int poles_;
};

#endif //UNTITLED_POLECALCULATE_H
