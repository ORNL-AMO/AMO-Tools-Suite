/**
 * @brief TODO
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_MOTORPERFORMANCE_H
#define AMO_LIBRARY_MOTORPERFORMANCE_H

#include <array>
#include <results/InputData.h>
#include <exception>
#include <stdexcept>

class MotorPerformance {
public:
    struct Output {
	    /**
	     * @param current
	     * @param efficiency
	     * @param powerFactor
	     */
        Output(const double current, const double efficiency, const double powerFactor)
                : current(current), efficiency(efficiency), powerFactor(powerFactor)
        {}

        const double current, efficiency, powerFactor;
    };
    /**
     * Constructor
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
     * @param motorRatedPower double, rated power of motor in hp
     * @param motorRpm double, RPM of motor
     * @param specifiedEfficiency double, Specified efficiency of motor when the efficiency class = SPECIFIED as %
     * @param loadFactor double, load factor - unitless
     * @param ratedVoltage double, Rated voltage of the motor in Volts
     * @param fullLoadAmps double,
    */
    MotorPerformance(
        Motor::LineFrequency lineFrequency,
        double motorRpm,
        Motor::EfficiencyClass efficiencyClass,
        double motorRatedPower,
        double specifiedEfficiency,
        double loadFactor,
        double ratedVoltage,
        double fullLoadAmps
     ) :
        lineFrequency(lineFrequency),
        motorRpm(motorRpm),
        efficiencyClass(efficiencyClass),
        motorRatedPower(motorRatedPower),
        specifiedEfficiency(specifiedEfficiency),
        loadFactor(loadFactor),
        ratedVoltage(ratedVoltage),
        fullLoadAmps(fullLoadAmps)
    {};

    /**
     * Calculates motor performance
     */
    Output calculate();

private:
        Motor::LineFrequency lineFrequency;
        double motorRpm;
        Motor::EfficiencyClass efficiencyClass;
        double motorRatedPower;
        double specifiedEfficiency;
        double loadFactor;
        double ratedVoltage;
        double fullLoadAmps;
};


#endif //AMO_LIBRARY_MOTORPERFORMANCE_H
