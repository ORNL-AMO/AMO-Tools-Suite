#ifndef AMO_TOOLS_SUITE_FANSHAFTPOWER_H
#define AMO_TOOLS_SUITE_FANSHAFTPOWER_H

class FanRatedInfo {
public:
	enum class DriveType {
		DIRECT,
		BELT
	};

	// this currently does not take the field SystemDamperPosition, as it is used "only for reference purposes" as per
	// page 8 in the algorithm document
	FanRatedInfo(double fanDamperPosition, double fanSpeed, double motorSpeed, double nc,
	             double pc, double pbc, DriveType driveType);

private:
	double const fanDamperPosition, fanSpeed, motorSpeed, nc, pc, pbc;
	DriveType const driveType;
	friend class Fan;
};

class FanShaftPower {
public:
	// method 1
	FanShaftPower(bool fanEquippedWithVFD, bool mainsVoltageDataAvailable, double ratedHp,
	              double synchronousSpeed, double npv, double fla, double hi,
	              double efficiencyMotor, double efficiencyVFD, double efficiencyBelt,
	              FanRatedInfo::DriveType driveType, double sumSEF);

	// method 2
	FanShaftPower(bool fanEquippedWithVFD, bool mainsVoltageDataAvailable, double ratedHp,
	              double synchronousSpeed, double npv, double fla, double voltage,
	              double amps, double powerFactorAtLoad, double efficiencyMotor,
	              double efficiencyVFD, double efficiencyBelt, FanRatedInfo::DriveType driveType, double sumSEF);

	double getFanShaftPower() const { return hFi; }

	double getSEF() const { return sumSEF; }

private:
	const bool fanEquippedWithVFD, mainsVoltageDataAvailable;
	const double ratedHp, synchronousSpeed, npv, fla;
	const double voltage = 0, amps = 0, powerFactorAtLoad = 0;
	const double hi = 0;
	const double efficiencyMotor, efficiencyVFD, efficiencyBelt, powerFactor = 0;
	const FanRatedInfo::DriveType driveType;
	const double sumSEF;

	double hMo, hFi;
};


#endif //AMO_TOOLS_SUITE_FANSHAFTPOWER_H
