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

#include "../Motor.h"
#include "../FieldData.h"

class MotorShaftPower {
public:

   /**
    * Constructor
    * @param motorRatedPower Rated Power of motor in hp or Kw.
    * @param motorMeasuredPower Power of the motor.
    * @param motorRPM RPM of motor.
    * @param lineFrequency Line frequency of motor as either 50Hz or 60Hz.
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

    double calculate();

    double calculateCurrent();

    double calculateEfficiency();

    double calculateEfficiency();;

    double calculatePower();

    double calculateEstimatedFLA();

    double tempLoadFraction_ = 0.01;
    double power = 0.0, powerE1 = 0.0, powerE2 = 0.0;
    double lf1 = 0.0, lf2 = 0.0;
    double eff = 0.0, eff1 = 0.0, eff2 = 0.0;
    double current = 0.0, current1 = 0.0, current2 = 0.0;
    double pf = 0.0, pf1 = 0.0, pf2 = 0.0;
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
