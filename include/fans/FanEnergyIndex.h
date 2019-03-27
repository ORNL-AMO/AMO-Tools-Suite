#ifndef AMO_TOOLS_SUITE_FANENERGYINDEX_H
#define AMO_TOOLS_SUITE_FANENERGYINDEX_H
/**
 * @file FanEnergyIndex.h
 * @author Preston Shires (pshires) & Allie Ledbetter (aeledbetter)
 * @brief Contains the calculator for the Fan Energy calculations
 * @bug No known bugs.
 * 
 */
#include <cmath>
/**
 * Constructor for Fan Energy Index
 * Calculates Fan Energy Index
 * 
 */
class FanEnergyIndex {
public:
	/**
	 * @param flowRate, double, flow rate in cfm
	 * @param inletPressure, double, pressure of inlet in inch ws
	 * @param outletPressure, double, pressure of outlet in inch ws
	 * @param airDensity, double, density of air in lbm/ft
	 * @param motorPower, double power of motor in kW
	 */
	FanEnergyIndex(const double flowRate, const double inletPressure, const double outletPressure, const double airDensity,
	               const double motorPower)
			: flowRate(flowRate), inletPressure(inletPressure), outletPressure(outletPressure), airDensity(airDensity),
			  motorPower(motorPower)
	{}

	/**
	 * @param pressure, double, pressure in inch wc
	 * @param outletPressure, double, pressure of outlet in inch ws
	 * @param inletPressure, double, pressure in inlet in inch ws
	 * @param referencepower, double in hp
	 * @param kWreferencepower, double in kW
	 * @param efficiency1, double, as a fraction
	 * @param efficiency2, double, as a fraction
	 * @param motorPower, double, power of motor in kW
	 * @return fan energy index, double
	 */
	double calculateEnergyIndex() {
		const double pressure = outletPressure - inletPressure;
		const double referencePower = (flowRate + 250) * (pressure + 0.4 * (airDensity / 0.075)) / (6343 * 0.66);
		const double kWreferencePower = referencePower * 0.7457;
		const double efficiency1 = 0.96 * std::pow(referencePower / (referencePower + 2.2), 0.05);
		double efficiency2 = 0.962;
		if (kWreferencePower < 185) {
			efficiency2 = -0.003812 * std::pow(std::log10(kWreferencePower), 4) +
			              0.025834 * std::pow(std::log10(kWreferencePower), 3) +
			              -0.072577 * std::pow(std::log10(kWreferencePower), 2) +
			              0.125559 * std::log10(kWreferencePower) + 0.850274;
		}

		return (kWreferencePower * (1 / efficiency1) * (1 / efficiency2)) / motorPower;
	}

private:
	/**
	 *
	 * @param flowRate, double, flow rate in cfm
	 * @param inletPressure, double, pressure of inlet in inch ws
	 * @param outletPressure, double, pressure of outlet in inch ws
	 * @param airDensity, double, density of air in lbm/ft
	 * @param motorPower, double, power of motor in kW
	 */
	const double flowRate, inletPressure, outletPressure, airDensity, motorPower;
};

#endif //AMO_TOOLS_SUITE_FANENERGYINDEX_H
