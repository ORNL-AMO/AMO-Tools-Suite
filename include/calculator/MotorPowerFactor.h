/**
 * @brief Contains the declaration of MotorPowerFactor class including the getters and setters as well as the calculators.
 *          for motor efficiency.
 *      calculate(): Calculates the motor power factor
 *
 * @author Subhankar Mishra (mishras)
 * @bug No known bugs.
 *
 */

//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORPOWERFACTOR_H
#define AMO_LIBRARY_MOTORPOWERFACTOR_H

#include "../Motor.h"
#include "../FieldData.h"

class MotorPowerFactor {
public:
    /**
     * Constructor
     * @param motorRatedPower
     * @param loadFactor
     * @param motorCurrent
     * @param motorEfficiency
     * @param ratedVoltage
     * @return nothing
     */
    MotorPowerFactor(
        double motorRatedPower,
        double loadFactor,
        double motorCurrent,
        double motorEfficiency,
        double ratedVoltage
    ) :
        motorRatedPower_(motorRatedPower),
        loadFactor_(loadFactor),
        motorCurrent_(motorCurrent),
        motorEfficiency_(motorEfficiency),
        ratedVoltage_(ratedVoltage)
    {}

    /**
     * Constructor when the load factor is 0.
     * When the load factor is zero, you need to calculate the efficiency 0.25 load factor, hence the extra parameters.
     * @param lineFrequency
     * @param motorRpm
     * @param efficiencyClass
     * @param specifiedEfficiency
     * @param motorRatedPower
     * @param loadFactor
     * @param motorCurrent
     * @param motorEfficiency
     * @param ratedVoltage
     * @return nothing
     */

    MotorPowerFactor(
        Motor::LineFrequency lineFrequency,
        double motorRpm,
        Motor::EfficiencyClass efficiencyClass,
        double specifiedEfficiency,
        double motorRatedPower,
        double loadFactor,
        double motorCurrent,
        double motorEfficiency,
        double ratedVoltage
    ) :
        lineFrequency_(lineFrequency),
        motorRpm_(motorRpm),
        efficiencyClass_(efficiencyClass),
        specifiedEfficiency_(specifiedEfficiency),
        motorRatedPower_(motorRatedPower),
        loadFactor_(loadFactor),
        motorCurrent_(motorCurrent),
        motorEfficiency_(motorEfficiency),
        ratedVoltage_(ratedVoltage)
    {};

    double calculate();

    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency_;
    }

    void setLineFrequency(Motor::LineFrequency lineFrequency) {
        lineFrequency_ = lineFrequency;
    }

    double getMotorRpm() const {
        return motorRpm_;
    }

    void setMotorRpm(double motorRpm) {
        motorRpm_ = motorRpm;
    }

    Motor::EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass_;
    }

    void setEfficiencyClass(Motor::EfficiencyClass efficiencyClass) {
        efficiencyClass_ = efficiencyClass;
    }


private:
    Motor::LineFrequency lineFrequency_;
    double motorRpm_;
    Motor::EfficiencyClass efficiencyClass_;
    double specifiedEfficiency_;
    double motorKwInput =0.0;
    double motorkVA = 0.0;

    double motorRatedPower_;
    double loadFactor_;
    double motorCurrent_;
    double motorEfficiency_;
    double ratedVoltage_;

};


#endif //AMO_LIBRARY_MOTORPOWERFACTOR_H
