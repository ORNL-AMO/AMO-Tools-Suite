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

class MotorShaftPower {
public:

   /**
    * Constructor
    * @param motorRatedPower Rated Power of motor in hp or Kw.
    * @param motorMeasuredPower Power of the motor.
    * @param motorRPM RPM of motor.
    * @param lineFrequency Line frequency of motor as either 50Hz or 60Hz.
    * @param efficiencyClass Motor::EfficiencyClass, efficiency class of motor
    * @param specifiedEfficiency Specified Efficiency of motor, if efficiency class is SPECIFIED.
    * @param ratedVoltage Rated voltage of motor.
    * @param fullLoadAmps Current at full load in amps.
    * @param fieldVoltage Field voltage.
    * @param loadEstimationMethod Estimated power or current on motor input.
    * @param fieldCurrent Field current as defined in amps.
    * @return nothing
    */
    MotorShaftPower(
		double motorRatedPower,
		double motorMeasuredPower,
		int motorRPM,
		Motor::LineFrequency lineFrequency,
		Motor::EfficiencyClass efficiencyClass,
		double specifiedEfficiency,
		double ratedVoltage,
		double fullLoadAmps,
		double fieldVoltage,
		FieldData::LoadEstimationMethod loadEstimationMethod,
		double fieldCurrent
	) :
		motorRatedPower_(motorRatedPower),
		fieldPower_(motorMeasuredPower),
		motorRPM_(motorRPM),
		lineFrequency_(lineFrequency),
		ratedVoltage_(ratedVoltage),
		fullLoadAmps_(fullLoadAmps),
		fieldVoltage_(fieldVoltage),
		efficiencyClass_(efficiencyClass),
		specifiedEfficiency_(specifiedEfficiency),
		fieldCurrent_(fieldCurrent),
		loadEstimationMethod_(loadEstimationMethod)
	{};

	/**
     * Calculate motor shaft power
     *
     * @return double, motor shaft power in hp
     */
    double calculate();

	/**
     * Calculates the motor shaft current
     *
     * @return double, motor shaft current in A
     */
    double calculateCurrent();

	/**
     * Calculates the motor shaft efficiency
     *
     * @return double, motor shaft efficiency as %
     */
    double calculateEfficiency();

	/**
     * Calculate the power
     *
     * @return double, power in hp or kw
     */
    double calculatePower();

	/**
     * Calculates the power factor
     *
     * @return double, power factor - unitless
     */
    double calculatePowerFactor();

	/**
     * Calculates estimated full load amps
     *
     * @return double, estimated full load amps in A
     */
    double calculateEstimatedFLA();

    ///double, temp load fraction
    double tempLoadFraction_ = 0.01;
	///double, power in hp
    double power = 0.0;
	///double, power in hp
	double powerE1 = 0.0;
	///double, power in hp
	double powerE2 = 0.0;
	///double, line frequency in Hz
    double lf1 = 0.0;
	///double, line frequency in Hz
	double lf2 = 0.0;
	///double efficiency in %
    double eff = 0.0;
	///double efficiency in %
	double eff1 = 0.0;
	///double efficiency in %
	double eff2 = 0.0;
	///double, current in A
    double current = 0.0;
	///double, current in A
	double current1 = 0.0;
	///double, current in A
	double current2 = 0.0;
	///double, power factor - unitless
    double pf = 0.0;
	///double, power factor - unitless
	double pf1 = 0.0;
	///double, power factor - unitless
	double pf2 = 0.0;
	///double, estimated full load amps in A
    double estimatedFLA;

private:
    double motorRatedPower_ = 0.0;
    double fieldPower_ = 0.0;
    int motorRPM_ = 0;
    Motor::LineFrequency lineFrequency_;
    double ratedVoltage_ = 0.0;
    double fullLoadAmps_ = 0.0;
    double fieldVoltage_ = 0.0;
    Motor::EfficiencyClass efficiencyClass_;

    double specifiedEfficiency_;
    double motorShaftPower_ = 0.0;
    double fieldCurrent_ = 0.0;
    FieldData::LoadEstimationMethod loadEstimationMethod_;
};

#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
