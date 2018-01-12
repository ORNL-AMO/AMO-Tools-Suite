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
	// integrate this into method 1 by also calculating method 2 hi - just have one constructor where we have hi being a parameter, the UI
	// will pop up a modal for "method 2" and will calculate hi based off a static method contained in FanShaftPower.
	// This same modal will also calculate efficiencyMotor for the user based off the same inputs that hi was calculated from
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
	const double efficiencyMotor, efficiencyVFD, efficiencyBelt, loadFactor = 0;
	const FanRatedInfo::DriveType driveType;
	const double sumSEF;

	double hMo, hFi;
};


#endif //AMO_TOOLS_SUITE_FANSHAFTPOWER_H
