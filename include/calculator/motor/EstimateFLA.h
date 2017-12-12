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

#include "psat/Motor.h"
#include <vector>

class EstimateFLA {
public:
    /**
     * Constructor
     * @param motorRatedPower double, rated power of motor in hp
     * @param motorRPM double, RPM of motor
     * @param lineFrequency Motor::LineFrequency, line frequency of motor in 50Hz or 60Hz
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor
     * @param specifiedEfficiency double, specified efficiency of motor as defined by %
     * @param ratedVoltage double, rated voltage of motor in volts
     */
    EstimateFLA(
        double motorRatedPower,
        double motorRPM,
        Motor::LineFrequency lineFrequency,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double ratedVoltage
    ) :
        motorRatedPower(motorRatedPower),
        motorRPM(motorRPM),
        lineFrequency(lineFrequency),
        efficiencyClass(efficiencyClass),
        specifiedEfficiency(specifiedEfficiency),
        ratedVoltage(ratedVoltage)
    {
        if (efficiencyClass == Motor::EfficiencyClass::SPECIFIED && specifiedEfficiency <= 0) {
            throw std::runtime_error("When using EfficiencyClass::SPECIFIED, you must provide a specified efficiency");
        }
    };

    /**
     * Calculates the 25% interval
     * @return 25% interval values of current.
     */
    std::vector<double> calculate();

    /**
     * Getter for estimated Full load amps
     * @return double, Estimated full load amp
     */
    double getEstimatedFLA() const {
        return estimatedFLA;
    }

private:
    /// Estimated full load amp
    double estimatedFLA;
    /// Rated Power of motor
    double motorRatedPower = 0.0;
    /// Motor RPM
    double motorRPM;
    /// Line Frequency of Motor
    Motor::LineFrequency lineFrequency;
    /// Efficiency class of Motor
    Motor::EfficiencyClass efficiencyClass;
    /// Specified Efficiency of motor, if efficiency class is SPECIFIED
    double specifiedEfficiency;
    /// Rated voltage of motor
    double ratedVoltage;
};


#endif //UNTITLED_ESTIMATEFLA_H
