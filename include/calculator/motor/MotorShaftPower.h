/**
 * @file
 * @brief MotorShaftPower class
 *  This contains the prototypes for the MotorShaftPower.
 *
 * calculate(): Calculates the motor power factor
 * calculateCurrent():
 * calculateEfficiency():
 * calculateEfficiency():
 * calculatePower(): Returns the motor shaft power in kWe
 * calculateEstimatedFLA()
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_MOTORSHAFTPOWER_H
#define AMO_LIBRARY_MOTORSHAFTPOWER_H

#include "psat/Motor.h"
#include "psat/FieldData.h"

/**
 * Motor Shaft Power class
 * Contains all of the properties of a motor shaft.
 * Used to calculate the power supplied by the motor to the pump shaft.
 */
class MotorShaftPower {
public:

   /**
    * Constructor for Motor Shaft Power class
    *
    * @param motorRatedPower double, Rated Power of motor in hp
    * @param motorMeasuredPower double, Power of the motor in hp
    * @param motorRPM double, RPM of motor.
    * @param lineFrequency Motor::LineFrequency, Line frequency of motor as either 50Hz or 60Hz.
    * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
    * @param specifiedEfficiency double, Specified Efficiency of motor, if efficiency class is SPECIFIED.
    * @param ratedVoltage double, Rated voltage of motor in volts
    * @param fullLoadAmps double, Current at full load in amps
    * @param fieldVoltage double, Field voltage in volts
    * @param loadEstimationMethod FieldData::LoadEstimationMethod, estimated power or current on motor input in hp
    * @param fieldCurrent double, field current as defined in amps.
    *
    */
    MotorShaftPower(
		const double motorRatedPower,
		const double motorMeasuredPower,
		const double motorRPM,
		const Motor::LineFrequency lineFrequency,
		const Motor::EfficiencyClass efficiencyClass,
		const double specifiedEfficiency,
		const double ratedVoltage,
		const double fullLoadAmps,
		const double fieldVoltage,
		const FieldData::LoadEstimationMethod loadEstimationMethod,
		const double fieldCurrent
	) :
		motorRatedPower(motorRatedPower),
		fieldPower(motorMeasuredPower),
		motorRPM(motorRPM),
		lineFrequency(lineFrequency),
		ratedVoltage(ratedVoltage),
		fullLoadAmps(fullLoadAmps),
		fieldVoltage(fieldVoltage),
		efficiencyClass(efficiencyClass),
		specifiedEfficiency(specifiedEfficiency),
		fieldCurrent(fieldCurrent),
		loadEstimationMethod(loadEstimationMethod)
	{};

	/**
     * Calculate motor shaft power
     * @return double, motor shaft power in hp
     */
    double calculate();

	/**
     * Calculates the motor shaft current
     * @return double, motor shaft current in A
     */
    double getCurrent() {
		return current;
	};

	/**
     * Calculates the motor shaft efficiency
     * @return double, motor shaft efficiency as %
     */
    double getEfficiency() {
		return eff;
	};

	/**
     * Calculate the power
     * @return double, power in hp
     */
    double getPower() {
		return power;
	};

	/**
     * Calculates the power factor
     * @return double, power factor - unitless
     */
    double getPowerFactor() {
		return pf;
	};

	/**
     * Calculates estimated full load amps
     * @return double, estimated full load amps in A
     */
    double getEstimatedFLA() {
		return estimatedFLA;
	};

    ///double, temp load fraction
    double tempLoadFraction = 0.01;
	///double, power in hp
    double power = 0.0;
	///double efficiency in %
    double eff = 0.0;
	///double, current in A
    double current = 0.0;
	///double, power factor - unitless
    double pf = 0.0;
	///double, estimated full load amps in A
    double estimatedFLA = 0;

private:
    double motorRatedPower, fieldPower, motorRPM;
    Motor::LineFrequency lineFrequency;
    double ratedVoltage, fullLoadAmps, fieldVoltage;
    Motor::EfficiencyClass efficiencyClass;

    double specifiedEfficiency, motorShaftPower = 0.0, fieldCurrent;
    FieldData::LoadEstimationMethod loadEstimationMethod;
};

#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
