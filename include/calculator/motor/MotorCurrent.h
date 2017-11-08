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
     * @param motorRatedPower double, Rated power of motor in hp
     * @param motorRPM double, RPM of motor.
     * @param lineFrequency Motor::LineFrequency, classification of line Frequency of motor in Hz
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor.
     * @param specifiedEfficiency double, Specified efficiency of motor when the efficiency class = SPECIFIED as %
     * @param loadFactor double, load factor - unitless
     * @param ratedVoltage double, Rated voltage of the motor in Volts
     * @param fullLoadAmps double, Current at full load in Amps
     */
    MotorCurrent(double motorRatedPower, double motorRPM, Motor::LineFrequency lineFrequency,
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
     * @return double, motor current in amps
     */
    double calculate();

    /**
     * Gets the estimated full load amp
     *
     * @return double, estimated current at full load in Amps
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
    double motorRPM_ = 0;
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
