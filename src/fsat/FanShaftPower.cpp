#include "fsat/FanShaftPower.h"
#include <cmath>

FanRatedInfo::FanRatedInfo(double const fanDamperPosition, double const fanSpeed, double const motorSpeed,
                           double const nc, double const pc, double const pbc, DriveType const driveType)
		: fanDamperPosition(fanDamperPosition / 100.0), fanSpeed(fanSpeed), motorSpeed(motorSpeed),
		  nc(nc), pc(pc), pbc(pbc), driveType(driveType)
{}

FanShaftPower::FanShaftPower(const bool fanEquippedWithVFD, const bool mainsVoltageDataAvailable, const double ratedHp,
                             const double synchronousSpeed, const double npv, const double fla, const double hi,
                             const double efficiencyMotor, const double efficiencyVFD, const double efficiencyBelt,
                             const FanRatedInfo::DriveType driveType)
		: fanEquippedWithVFD(fanEquippedWithVFD), mainsVoltageDataAvailable(mainsVoltageDataAvailable),
		  ratedHp(ratedHp), synchronousSpeed(synchronousSpeed), npv(npv), fla(fla), hi(hi),
		  efficiencyMotor(efficiencyMotor), efficiencyVFD(efficiencyVFD), efficiencyBelt(efficiencyBelt),
		  driveType(driveType)
{
	hMo = (hi * efficiencyMotor * efficiencyVFD) / 0.7457;
	hFi = hMo * efficiencyBelt;
}

FanShaftPower::FanShaftPower(const bool fanEquippedWithVFD, const bool mainsVoltageDataAvailable, const double ratedHp,
                             const double synchronousSpeed, const double npv, const double fla, const double voltage,
                             const double amps, const double powerFactorAtLoad, const double efficiencyMotor,
                             const double efficiencyVFD, const double efficiencyBelt,
                             const FanRatedInfo::DriveType driveType)
		: fanEquippedWithVFD(fanEquippedWithVFD), mainsVoltageDataAvailable(mainsVoltageDataAvailable),
		  ratedHp(ratedHp), synchronousSpeed(synchronousSpeed), npv(npv), fla(fla), voltage(voltage), amps(amps),
		  powerFactorAtLoad(powerFactorAtLoad), efficiencyMotor(efficiencyMotor / 100), efficiencyVFD(efficiencyVFD / 100),
		  efficiencyBelt(efficiencyBelt / 100), powerFactor((voltage / npv) * (amps / fla)), driveType(driveType)
{
	hMo = (voltage * amps * std::sqrt(3) * powerFactorAtLoad * this->efficiencyMotor * this->efficiencyVFD) / 746.0;
	hFi = hMo * this->efficiencyBelt;
}
