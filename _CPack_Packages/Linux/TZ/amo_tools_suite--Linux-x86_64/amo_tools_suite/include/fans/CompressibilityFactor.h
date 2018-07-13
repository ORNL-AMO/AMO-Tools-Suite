#ifndef AMO_TOOLS_SUITE_COMPRESSIBILITYFACTOR_H
#define AMO_TOOLS_SUITE_COMPRESSIBILITYFACTOR_H

#include <cmath>

class CompressibilityFactor {
public:

	/**
	* Constructor
 	* @param moverShaftPower double, in horsepower
 	* @param inletPressure double, in inches of water column, gauge
 	* @param outletPressure double, in inches of water column, gauge
 	* @param barometricPressure double, in Hg
 	* @param flowRate double, in cfm
 	* @param specificHeatRatio double, unitless
 	*/
	CompressibilityFactor(const double moverShaftPower, const double inletPressure, const double outletPressure,
	                      const double barometricPressure, const double flowRate, const double specificHeatRatio)
			: moverShaftPower(moverShaftPower), inletPressure(inletPressure), outletPressure(outletPressure),
			  barometricPressure(barometricPressure), flowRate(flowRate), specificHeatRatio(specificHeatRatio)
	{}

	double calculate() {
		double const p1 = inletPressure + 13.63 * barometricPressure;
		double const x = (outletPressure - inletPressure) / p1;
		double const z = ((6362 * moverShaftPower / flowRate) / p1) * ((specificHeatRatio - 1) / specificHeatRatio);

		return std::log(1 + x) * z / (std::log(1 + z) * x);
	}

private:
	const double moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio;
};


#endif //AMO_TOOLS_SUITE_COMPRESSIBILITYFACTOR_H
