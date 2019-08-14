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

#include <results/InputData.h>

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
     */
    MotorCurrent(double motorRatedPower, double motorRPM, Motor::LineFrequency lineFrequency,
                 Motor::EfficiencyClass efficiencyClass, double specifiedEfficiency, double loadFactor,
                 double ratedVoltage) :
            motorRatedPower(motorRatedPower), motorRPM(motorRPM),
            lineFrequency(lineFrequency),
            efficiencyClass(efficiencyClass),
            specifiedEfficiency(specifiedEfficiency),
            loadFactor(loadFactor), ratedVoltage(ratedVoltage)
    {};

    /**
     * calculates the motor current at a given load factor.
     * @param fullLoadAmps double, Current at full load in Amps
     * @return double, motor current in amps
     */
    double calculateCurrent(double fullLoadAmps);

	/**
	 * calculates the optimal motor current
	 * @return double, optimal motor current in amps
	 */
    double calculateOptimalCurrent();

    /**
     * Gets the estimated full load amp
     * @return double, estimated current at full load in Amps
     */
    double getEstimatedFLA() {
        return estimatedFLA;
    }

private:
    double motorRatedPower;
    double motorRPM;
    Motor::LineFrequency lineFrequency;
    Motor::EfficiencyClass efficiencyClass;
    double specifiedEfficiency;
    double loadFactor;
    double ratedVoltage;
    double estimatedFLA = 0.0;
};

#endif //AMO_LIBRARY_MOTORCURRENT_H
