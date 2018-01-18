#include "fans/FanShaftPower.h"
#include <cmath>

FanRatedInfo::FanRatedInfo(double const fanSpeed, double const motorSpeed, double const fanSpeedCorrected,
                           double const densityCorrected, double const pressureBarometricCorrected)
		: fanSpeed(fanSpeed), motorSpeed(motorSpeed), fanSpeedCorrected(fanSpeedCorrected),
		  densityCorrected(densityCorrected), pressureBarometricCorrected(pressureBarometricCorrected)
{}

FanShaftPower::FanShaftPower(const bool fanEquippedWithVFD, const bool mainsVoltageDataAvailable, const double ratedHp,
                             const double synchronousSpeed, const double npv, const double fla, const double hi,
                             const double efficiencyMotor, const double efficiencyVFD, const double efficiencyBelt,
                             const double sumSEF)
		: fanEquippedWithVFD(fanEquippedWithVFD), mainsVoltageDataAvailable(mainsVoltageDataAvailable),
		  ratedHp(ratedHp), synchronousSpeed(synchronousSpeed), npv(npv), fla(fla), hi(hi),
		  efficiencyMotor(efficiencyMotor), efficiencyVFD(efficiencyVFD), efficiencyBelt(efficiencyBelt),
		  sumSEF(sumSEF)
{
	hMo = (hi * efficiencyMotor * efficiencyVFD) / 0.7457;
	hFi = hMo * efficiencyBelt;
}

FanShaftPower::FanShaftPower(const bool fanEquippedWithVFD, const bool mainsVoltageDataAvailable, const double ratedHp,
                             const double synchronousSpeed, const double npv, const double fla, const double voltage,
                             const double amps, const double powerFactorAtLoad, const double efficiencyMotor,
                             const double efficiencyVFD, const double efficiencyBelt,
                             const double sumSEF)
		: fanEquippedWithVFD(fanEquippedWithVFD), mainsVoltageDataAvailable(mainsVoltageDataAvailable),
		  ratedHp(ratedHp), synchronousSpeed(synchronousSpeed), npv(npv), fla(fla), voltage(voltage),
		  amps(amps), powerFactorAtLoad(powerFactorAtLoad), efficiencyMotor(efficiencyMotor / 100),
		  efficiencyVFD(efficiencyVFD / 100), efficiencyBelt(efficiencyBelt / 100),
		  loadFactor((voltage / npv) * (amps / fla)), sumSEF(sumSEF)
{
	hMo = (voltage * amps * std::sqrt(3) * powerFactorAtLoad * this->efficiencyMotor * this->efficiencyVFD) / 746.0;
	hFi = hMo * this->efficiencyBelt;
}
