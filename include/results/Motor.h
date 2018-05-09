/**
 * @file
 * @brief Function prototypes for the Motor fields
 *
 * This contains the prototypes for the Motor structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting data dealing with
 * motor information.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_LIBRARY_MOTOR_H
#define AMO_LIBRARY_MOTOR_H

#include <cmath>

struct Motor {
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        PREMIUM,
        SPECIFIED,
    };

    enum class LineFrequency{
        FREQ60,
        FREQ50
    };

    /**
     * Constructor
     * @param lineFrequency LineFrequency, main supply frequency at either 50Hz or 60Hz
     * @param motorRatedPower double, rated power for the motor in hp
     * @param motorRpm double, motor RPM
     * @param efficiencyClass EfficiencyClass, classification of motor efficiency
     * @param specifiedEfficiency double, specified % Efficiency of motor, if efficiency class is SPECIFIED
     * @param motorRatedVoltage double, motor nameplate design voltage in volts
     * @param fullLoadAmps double, current at full load in amps
     * @param sizeMargin double, size margin as defined in %
     */
    Motor(const LineFrequency lineFrequency, const double motorRatedPower, const double motorRpm,
          const EfficiencyClass efficiencyClass, const double specifiedEfficiency, const double motorRatedVoltage,
          const double fullLoadAmps, const double sizeMargin = 1)
            : lineFrequency(lineFrequency), motorRatedPower(motorRatedPower), motorRpm(motorRpm),
              specifiedEfficiency(specifiedEfficiency), motorRatedVoltage(motorRatedVoltage),
              fullLoadAmps(fullLoadAmps), sizeMargin(sizeMargin), efficiencyClass(efficiencyClass)
    {};

    const LineFrequency lineFrequency;
    const double motorRatedPower, motorRpm, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin;
    const Motor::EfficiencyClass efficiencyClass;
};


#endif //AMO_LIBRARY_MOTOR_H
