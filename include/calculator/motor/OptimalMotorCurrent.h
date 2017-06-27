/**
 * @brief Header file for OptimalMotorCurrent class
 *
 * This contains the prototypes of OptimalMotorCurrent calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALMOTORCURRENT_H
#define AMO_LIBRARY_OPTIMALMOTORCURRENT_H

#include "psat/Motor.h"

class OptimalMotorCurrent {
public:

   /**
    * Constructor
    * @param motorRatedPower double, Rated Power of motor in hp
    * @param motorRPM double, RPM of motor.
    * @param lineFrequency Motor::LineFrequency, Line frequency of motor in either 60Hz or 50Hz.
    * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor.
    * @param specifiedEfficiency double, Specified Efficiency of motor, if efficiency class is SPECIFIED.
    * @param loadFactor double, Load factor - unitless
    * @param ratedVoltage double, Rated voltage of the motor in volts
    * @return nothing
    */
    OptimalMotorCurrent(
        double motorRatedPower,
        int motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double loadFactor ,
        double ratedVoltage,
        double /*fieldVoltage*/,
        double /*fullLoadAmps*/
    ) :
        motorRatedPower_(motorRatedPower),
        motorRPM_(motorRPM),
        lineFrequency_(lineFrequency),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        loadFactor_(loadFactor),
        ratedVoltage_(ratedVoltage)
//        fullLoadAmps_(fullLoadAmps),
//        fieldVoltage_(fieldVoltage)
    {};

    /**
     * Calculates the optimal motor current
     *
     * @return double, optimal motor current in Amps
     */
    double calculate();

    /**
     * Gets the motor power
     *
     * @return double, motor power in hp
     */
    double getMotorPower() const {
        return motorPower_;
    }

    /**
     * Sets the motor power
     *
     * @param motorPower double, motor power in hp
     *
     * @return nothing
     */
    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    /**
     * Gets the voltage of the motor
     *
     * @return double, voltage in Volts
     */
    double getVoltage() const {
        return voltage_;
    }

    /**
     * Sets the voltage of the motor
     *
     * @param voltage double, voltage of motor in Volts
     *
     * @return nothing
     */
    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

private:
    double motorPower_;
    double voltage_;
    double motorRatedPower_ = 0.0;

    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_ = 0.0;
    double loadFactor_ = 0.0;
    double motorCurrent_ = 0.0;
    double ratedVoltage_ = 0.0;
//    double estimatedFLA_ = 0.0;
//    double fullLoadAmps_ = 0.0;
//    double fieldVoltage_ = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALMOTORCURRENT_H
