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

#include <results/InputData.h>

/**
 * Motor Shaft Power class
 * Contains all of the properties of a motor shaft.
 * Used to calculate the power supplied by the motor to the pump shaft.
 */
class MotorShaftPower {
public:

	struct Output {
		/**
		 * Constructor for MotorShaftPower::Output
		 * @param shaftPower double, hp
		 * @param current double, amps
		 * @param powerFactor double, unitless
		 * @param efficiency double, % motor shaft efficiency
		 * @param power double
		 * @param estimatedFLA double
		 *
		 */
		Output(const double shaftPower, const double current, const double powerFactor, const double efficiency,
		       const double power, const double estimatedFLA, const double loadFactor)
				: shaftPower(shaftPower), current(current), powerFactor(powerFactor), efficiency(efficiency),
				  power(power), estimatedFLA(estimatedFLA), loadFactor(loadFactor)
		{}

		const double shaftPower, current, powerFactor, efficiency, power, estimatedFLA, loadFactor;
	};

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
		const Motor::LoadEstimationMethod loadEstimationMethod,
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
     * @return MotorShaftPower::Output, class containing all the results of the MotorShaftPower calculations, see Output class for more details
     */
    Output calculate();

private:
    double motorRatedPower, fieldPower, motorRPM;
    Motor::LineFrequency lineFrequency;
    double ratedVoltage, fullLoadAmps, fieldVoltage;
    Motor::EfficiencyClass efficiencyClass;

    double specifiedEfficiency, fieldCurrent;
    Motor::LoadEstimationMethod loadEstimationMethod;
};

#endif //AMO_LIBRARY_MOTORSHAFTPOWER_H
