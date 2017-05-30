#ifndef AMO_TOOLS_SUITE_AUXILIARYPOWER_H
#define AMO_TOOLS_SUITE_AUXILIARYPOWER_H

#include <cmath>

class AuxiliaryPower {
public:
	/**
	 * Constructor
	 * @param motorPhase current motor phase - this option is greyed out in PHAST 3.0
	 * @param supplyVoltage Volts
	 * @param avgCurrent average current in Amperes
	 * @param powerFactor average power factor value
	 * @param operatingTime percent operating time
	 * @return nothing
	 */
	AuxiliaryPower(const double motorPhase, const double supplyVoltage, const double avgCurrent,
	               const double powerFactor, const double operatingTime) :
			motorPhase(motorPhase),
			supplyVoltage(supplyVoltage),
	        avgCurrent(avgCurrent),
	        powerFactor(powerFactor),
	        operatingTime(operatingTime / 100.0)
			{}

	double getPowerUsed() const;


private:
	const double motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime;
};

#endif //AMO_TOOLS_SUITE_AUXILIARYPOWER_H
