#ifndef AMO_TOOLS_SUITE_FANSHAFTPOWER_H
#define AMO_TOOLS_SUITE_FANSHAFTPOWER_H

#include "fsat/Fan.h"

class FanShaftPower {
public:
	FanShaftPower(const bool fanEquippedWithVFD, const bool mainsVoltageDataAvailable, const double ratedHp,
	              const double synchronousSpeed, const double npv, const double fla,
	              const FanRatedInfo::DriveType driveType)
			: fanEquippedWithVFD(fanEquippedWithVFD), mainsVoltageDataAvailable(mainsVoltageDataAvailable),
			  ratedHp(ratedHp), synchronousSpeed(synchronousSpeed), npv(npv), fla(fla), driveType(driveType)
	{}

private:
	const bool fanEquippedWithVFD, mainsVoltageDataAvailable;
	const double ratedHp, synchronousSpeed, npv, fla;
	const FanRatedInfo::DriveType driveType;

};


#endif //AMO_TOOLS_SUITE_FANSHAFTPOWER_H
