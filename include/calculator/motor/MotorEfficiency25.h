/**
 * @brief Contains the declaration of MotorEfficiency25 class including the getters and setters as well as the calculators
 *          for motor efficiency.
 *      calculate(): Calculates the motor efficiency givenat 25% intervals of load factor.
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

#ifndef UNTITLED_MOTOREFFICIENCY25_H
#define UNTITLED_MOTOREFFICIENCY25_H

#include <vector>
#include <array>
#include "psat/Motor.h"

class MotorEfficiency25 {
public:
    /**
     * Constructor
     * @param efficiencyClass Motor::EfficiencyClass, Efficiency class of motor
     * @param motorRatedPower double, Rated power of motor in hp
     * @param motorRpm double, Rpm of motor
     * @param lineFrequency Motor::LineFrequency, classification of line frequency in Hz
     */
    MotorEfficiency25(
        const Motor::EfficiencyClass efficiencyClass,
        const double motorRatedPower,
        const double motorRpm,
        const Motor::LineFrequency lineFrequency
    ) :
        efficiencyClass(efficiencyClass),
        motorRatedPower(motorRatedPower),
        motorRpm(motorRpm),
        lineFrequency(lineFrequency)
    {
        if (this->efficiencyClass == Motor::EfficiencyClass::SPECIFIED) {
            throw std::runtime_error("You cannot use SPECIFIED motor efficiency with MotorEfficiency25");
        }
    };

    /**
     * @return std::array<double, 5> containing motor efficiency as %
     */
    std::array<double, 5> calculate();

private:
	const std::array< std::array<double, 4>, 5> determinePartialLoadCoefficients(std::size_t pole) const;

    /**
     * Efficiency class of motor
     */
    const Motor::EfficiencyClass efficiencyClass;
    /**
     * Rated power of motor in hp
     */
    const double motorRatedPower;
    const double motorRpm;
    /**
     * Line Frequency of motor
     */
    const Motor::LineFrequency lineFrequency;
};


#endif //UNTITLED_MOTOREFFICIENCY25_H
