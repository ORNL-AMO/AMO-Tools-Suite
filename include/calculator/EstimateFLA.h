/**
 * @brief EstimateFLA class.
 *  This contains the prototypes for the Estimate FLA calculator and 25% interval value calculator.
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef UNTITLED_ESTIMATEFLA_H
#define UNTITLED_ESTIMATEFLA_H

#include "Motor.h"
#include <vector>

class EstimateFLA {
public:
    /**
     * Constructor
     * @param motorRatedPower Rated Power of motor in hp or kW.
     * @param motorRPM RPM of motor.
     * @param lineFrequency Line frequency of motor in 50Hz or 60Hz.
     * @param efficiencyClass Efficiency class of motor.
     * @param specifiedEfficiency Specified Efficiency of motor as defined by %.
     * @param ratedVoltage Rated voltage of motor.
     * @return nothing
     */
    EstimateFLA(
        double motorRatedPower,
        int motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage
    ) :
        motorRatedPower_(motorRatedPower),
        motorRPM_(motorRPM),
        lineFrequency_(lineFrequency),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        ratedVoltage_(ratedVoltage)
    {};

    /**
     * Calculates the 25% interval
     * @return 25% interval values of current.
     */
    std::vector<double> calculate();

    /**
     * Getter for estimated Full load amps
     * @return Estimated full load amp
     */
    double getEstimatedFLA() {
        return estimatedFLA_;
    }

private:
    /// Estimated full load amp
    double estimatedFLA_;
    /// Rated Power of motor
    double motorRatedPower_ = 0.0;
    /// Motor RPM
    int motorRPM_ = 0;
    /// Line Frequency of Motor
    Motor::LineFrequency lineFrequency_;
    /// Efficiency class of Motor
    Motor::EfficiencyClass efficiencyClass_;
    /// Specified Efficiency of motor, if efficiency class is SPECIFIED
    double specifiedEfficiency_ =0.0;
    /// Rated voltage of motor
    double ratedVoltage_ =0.0;
};


#endif //UNTITLED_ESTIMATEFLA_H
