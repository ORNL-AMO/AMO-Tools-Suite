#ifndef AMO_TOOLS_SUITE_INPUT_DATA_H
#define AMO_TOOLS_SUITE_INPUT_DATA_H

#include <cmath>

struct Motor {
	enum class EfficiencyClass {
		STANDARD,
		ENERGY_EFFICIENT,
		PREMIUM,
		SPECIFIED,
	};

	enum class LineFrequency {
		FREQ60,
		FREQ50
	};

	enum class Drive {
		DIRECT_DRIVE,
		V_BELT_DRIVE,
		N_V_BELT_DRIVE,
		S_BELT_DRIVE
	};

	enum class LoadEstimationMethod {
		POWER,
		CURRENT
	};

	/**
	 * Constructor
	 * @param lineFrequency LineFrequency, main supply frequency at either 50Hz or 60Hz
	 * @param motorRatedPower double, rated power for the motor in hp
	 * @param motorRpm double, motor RPM
	 * @param efficiencyClass EfficiencyClass, classification of motor efficiency
	 * @param specifiedEfficiency double, specified % Efficiency of motor, unused unless efficiency class is SPECIFIED
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

namespace Fan {
	struct Input {
		Input(double const fanSpeed, const Motor::Drive drive, const int stages): fanSpeed(fanSpeed), drive(drive)
//                stages(stages)
		{}

		// TODO FanType enum of fan types
		double fanSpeed;
		Motor::Drive drive;
//        int stages;
	};

	struct FieldData {
		FieldData(const double measuredPower, const double measuredVoltage, const double measuredAmps, const double flowRate,
		          const double inletPressure, const double outletPressure, const double compressibilityFactor,
		          Motor::LoadEstimationMethod loadEstimationMethod, const double airDensity)
				: measuredPower(measuredPower), measuredVoltage(measuredVoltage), measuredAmps(measuredAmps), flowRate(flowRate),
				  inletPressure(inletPressure), outletPressure(outletPressure), compressibilityFactor(compressibilityFactor),
				  airDensity(airDensity), loadEstimationMethod(loadEstimationMethod)
		{}

		double measuredPower, measuredVoltage, measuredAmps;
		double flowRate, inletPressure, outletPressure, compressibilityFactor, airDensity;

		Motor::LoadEstimationMethod loadEstimationMethod;

	};
}

namespace Pump {
	enum class SpecificSpeed {
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

	struct FieldData {
		/**
		 * Constructor
		 * @param flowRate double, rate of flow. Units are gpm
		 * @param head double, pump head measured in feet
		 * @param loadEstimationMethod LoadEstimationMethod, classification of load estimation method
		 * @param motorPower double, power output of the pump's motor in hp.
		 * @param motorAmps double, current measured from the pump's motor in amps
		 * @param voltage double, the measured bus voltage in volts
		 */
		FieldData(const double flowRate, const double head, const Motor::LoadEstimationMethod loadEstimationMethod, const double motorPower,
		          const double motorAmps, const double voltage)
				: loadEstimationMethod(loadEstimationMethod), flowRate(flowRate), head(head), motorPower(motorPower),
				  motorAmps(motorAmps), voltage(voltage)
		{}

		const Motor::LoadEstimationMethod loadEstimationMethod;
		const double flowRate, head, motorPower, motorAmps, voltage;
	};

	struct Input {
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
		Input(const Style style, const double achievableEfficiency, const double rpm, const Motor::Drive drive,
		     const double kviscosity,
		     const double specificGravity, const int stageCount, const SpecificSpeed speed)
				: style(style), drive(drive), speed(speed), achievableEfficiency(achievableEfficiency), rpm(rpm),
				  kviscosity(kviscosity),
				  specificGravity(specificGravity), stageCount(stageCount) {};

		const Style style;
		const Motor::Drive drive;
		const SpecificSpeed speed;
		const double achievableEfficiency, rpm, kviscosity, specificGravity;
		const int stageCount;
	};
};

#endif //AMO_TOOLS_SUITE_INPUT_DATA_H
