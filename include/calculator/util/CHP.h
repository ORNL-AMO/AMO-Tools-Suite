#ifndef AMO_TOOLS_SUITE_CHP_H
#define AMO_TOOLS_SUITE_CHP_H

#include <array>
#include <map>

class CHP {
public:
	enum class Option {
		PercentAvgkWhElectricCostAvoided,
		StandbyRate
	};

	CHP(double annualOperatingHours, double annualElectricityConsumption, double annualThermalDemand,
	    double boilerThermalFuelCosts, double avgElectricityCosts, Option calculationOption,
	    double boilerThermalFuelCostsCHPcase, double CHPfuelCosts,
	    double percentAvgkWhElectricCostAvoidedOrStandbyRate, double displacedThermalEfficiency);

private:
	void calculate();

	std::map<double, size_t>::const_iterator findNearest(double val, size_t index);

	double annualOperatingHours, annualElectricityConsumption, annualThermalDemand;
	double boilerThermalFuelCosts, chpFuelCosts, avgElectricityCosts;
	Option calculationOption;
	double boilerThermalFuelCostsCHPcase, percentAvgkWhElectricCostAvoided = 0, standbyRate = 0;
	double displacedThermalEfficiency, chpElectricEfficiency, chpThermalOutput;

	double avgPowerDemand, avgThermalDemand, netCHPpower;

	const std::array<std::array<double, 8>, 7> chpSystemByIndex = {
			{
					{{50, 600, 1000, 3300, 5000, 10000, 20000, 45000}}, // row 2 - index 0
					{{27.0, 34.5, 36.8, 40.4, 28.9, 27.3, 33.2, 36.0}}, // row 5 - index 1
					{{6700, 4392, 3854, 3233, 4893, 5262, 3821, 3141}}, // row 6 - index 2
					{{0.34, 2.64, 3.85, 10.67, 24.47, 52.62, 76.42, 141.33}}, // row 7 - index 3
					{{0.024, 0.021, 0.019, 0.0126, 0.0123, 0.012, 0.0093, 0.0092}}, // row 11 - index 4
					{{2900, 2737, 2335, 1917, 2080, 1976, 1518, 1248}}, // row 13 - index 5
					{{0, 0, 0, 0, 0, 0, 0, 0}},
			}
	};

	const std::array<std::map<double, size_t>, 7> chpSystemByKey = {
			{
					{{50, 0}, {600, 1}, {1000, 2}, {3300, 3}, {5000, 4}, {10000, 5}, {20000, 6}, {45000, 7}}, // row 2 - index 0
					{{27.0, 0}, {34.5, 1}, {36.8, 2}, {40.4, 3}, {28.9, 4}, {27.3, 5}, {33.2, 6}, {36.0, 7}}, // row 5 - index 1
					{{6700, 0}, {4392, 1}, {3854, 2}, {3233, 3}, {4893, 4}, {5262, 5}, {3821, 6}, {3141, 7}}, // row 6 - index 2
					{{0.34, 0}, {2.64, 1}, {3.85, 2}, {10.67, 3}, {24.47, 4}, {52.62, 5}, {76.42, 6}, {141.33, 7}}, // row 7 - index 3
					{{0.024, 0}, {0.021, 1}, {0.019, 2}, {0.0126, 3}, {0.0123, 4}, {0.012, 5}, {0.0093, 6}, {0.0092, 7}}, // row 11 - index 4
					{{2900, 0}, {2737, 1}, {2335, 2}, {1917, 3}, {2080, 4}, {1976, 5}, {1518, 6}, {1248, 7}}, // row 13 - index 5
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
			}
	};

};

#endif //AMO_TOOLS_SUITE_CHP_H
