/**
 * @brief Contains the declaration of MotorCurrent class including the getters and setters as well as the calculators for motor current.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_MOTORCURRENT_H
#define AMO_LIBRARY_MOTORCURRENT_H

#include "psat/Motor.h"

class MotorCurrent {
public:
    /**
     * Constructor
     * @param motorRatedPower Rated power of motor in hp or kW
     * @param motorRPM RPM of motor.
     * @param lineFrequency line Frequency of motor in Hz
     * @param efficiencyClass Efficiency class of motor.
     * @param specifiedEfficiency Specified efficiency of motor when the efficiency class = SPECIFIED as %
     * @param loadFactor load factor - unitless
     * @param ratedVoltage Rated voltage of the motor in V
     * @param fullLoadAmps Current at full load in A
     * @return nothing
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

    /**
     * calculates the motor current at a given load factor.
     * @return motor current
     */
    double calculate();

    /**
     * Gets the estimated full load amp
     *
     * @return double, estimated current at full load in A
     */
    double getEstimatedFLA() {
        return estimatedFLA_;
    }


private:
    /**
     * Rated power of motor
     */
    double motorRatedPower_ = 0.0;
    /**
     * RPM of motor
     */
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
