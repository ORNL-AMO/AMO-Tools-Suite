#ifndef AMO_TOOLS_SUITE_FANSHAFTPOWER_H
#define AMO_TOOLS_SUITE_FANSHAFTPOWER_H

#include <cmath>

class FanRatedInfo {
public:
	FanRatedInfo(double const fanSpeed, double const motorSpeed, double const fanSpeedCorrected,
				 double const densityCorrected, double const pressureBarometricCorrected)
			: fanSpeed(fanSpeed), motorSpeed(motorSpeed), fanSpeedCorrected(fanSpeedCorrected),
			  densityCorrected(densityCorrected), pressureBarometricCorrected(pressureBarometricCorrected)
	{}

private:
	double const fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected;
	friend class Fan203;
};

class FanShaftPower {
public:
	FanShaftPower(const double motorShaftPower, const double efficiencyMotor, const double efficiencyVFD,
				  const double efficiencyBelt, const double sumSEF)
			: efficiencyMotor(efficiencyMotor / 100), efficiencyVFD(efficiencyVFD / 100), efficiencyBelt(efficiencyBelt / 100),
			  sumSEF(sumSEF)
	{
		motorPowerOutput = motorShaftPower * this->efficiencyMotor * this->efficiencyVFD;
		fanPowerInput = motorPowerOutput * this->efficiencyBelt;
	}

	/**
	 * Calculates and returns motorShaftPower - used to construct a FanShaftPower object
	 * @param voltage const double
	 * @param amps const double
	 * @param powerFactorAtLoad const double
	 * @return MotorShaftPower, const double
	 */
	static double calculateMotorShaftPower(const double voltage, const double amps, const double powerFactorAtLoad) {
		return voltage * amps * powerFactorAtLoad * std::sqrt(3);
	}

	double getFanPowerInput() const { return fanPowerInput; }

	double getSEF() const { return sumSEF; }

private:
	const double efficiencyMotor, efficiencyVFD, efficiencyBelt;
	const double sumSEF;

	double motorPowerOutput, fanPowerInput;
};


#endif //AMO_TOOLS_SUITE_FANSHAFTPOWER_H
