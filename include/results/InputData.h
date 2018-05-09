#ifndef AMO_TOOLS_SUITE_RESULTSINPUT_H
#define AMO_TOOLS_SUITE_RESULTSINPUT_H

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

	enum class Drive {
		DIRECT_DRIVE,
		V_BELT_DRIVE,
		N_V_BELT_DRIVE,
		S_BELT_DRIVE
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

struct Pump {
	enum class Speed {
		FIXED_SPEED,
		NOT_FIXED_SPEED
	};

	enum class Style {
		END_SUCTION_SLURRY,
		END_SUCTION_SEWAGE,
		END_SUCTION_STOCK,
		END_SUCTION_SUBMERSIBLE_SEWAGE,
		API_DOUBLE_SUCTION,
		MULTISTAGE_BOILER_FEED,
		END_SUCTION_ANSI_API,
		AXIAL_FLOW,
		DOUBLE_SUCTION,
		VERTICAL_TURBINE,
		LARGE_END_SUCTION,
		SPECIFIED_OPTIMAL_EFFICIENCY
	};

	/**
	 * Constructor
	 * @param style Style, classification of style of pump being used.
	 * @param achievableEfficiency double, pump % efficiency at the specified operating conditions
	 * @param rpm double, pump RPM to define its operating speed
	 * @param drive Drive, type of drive the pump uses from either direct or belt drive.
	 * @param kviscosity double, kinematic viscosity of the fluid being pumped in centistokes.
	 * @param specificGravity double, specific gravity- unitless
	 * @param stageCount int, the number of pump stages
	 * @param speed Speed, type of pump speed from either fixed or not fixed.
	 */
	Pump(const Style style, const double achievableEfficiency, const double rpm, const Motor::Drive drive, const double kviscosity,
	     const double specificGravity, const int stageCount, const Pump::Speed speed)
			: style(style), drive(drive), speed(speed), achievableEfficiency(achievableEfficiency), rpm(rpm), kviscosity(kviscosity),
			  specificGravity(specificGravity), stageCount(stageCount)
	{};

	const Style style;
	const Motor::Drive drive;
	const Pump::Speed speed;
	const double achievableEfficiency, rpm, kviscosity, specificGravity;
	const int stageCount;
};


#endif //AMO_TOOLS_SUITE_RESULTSINPUT_H
