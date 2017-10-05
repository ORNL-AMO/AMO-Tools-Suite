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

	double annualOperatingHours, annualElectricityConsumption, annualThermalDemand;
	double boilerThermalFuelCosts, chpFuelCosts, avgElectricityCosts;
	Option calculationOption;
	double boilerThermalFuelCostsCHPcase, percentAvgkWhElectricCostAvoided = 0, standbyRate = 0;
	double displacedThermalEfficiency;

	double avgPowerDemand, avgThermalDemand, netCHPpower;

	const std::array<std::array<double, 8>, 7> chpSystemByIndex = {
			{
					{{50, 600, 1000, 3300, 5000, 10000, 20000, 45000}},
					{{0, 0, 0, 0, 0, 0, 0, 0}},
					{{0, 0, 0, 0, 0, 0, 0, 0}},
					{{0, 0, 0, 0, 0, 0, 0, 0}},
					{{0, 0, 0, 0, 0, 0, 0, 0}},
					{{0, 0, 0, 0, 0, 0, 0, 0}},
					{{0.34, 2.64, 3.85, 10.67, 24.47, 52.62, 76.42, 141.33}}
			}
	};

//	const std::array<std::map<double, size_t>, 2> chpSystemByKey = {
//			std::map<double, size_t>({{50, 0}, {600, 1}, {1000, 2}, {3300, 3}, {5000, 4}, {10000, 5}, {20000, 6}, {45000, 7}}),
//			std::map<double, size_t>({{0.34, 0}, {2.64, 1}, {3.85, 2}, {10.67, 3}, {24.47, 4}, {52.62, 5}, {76.42, 6}, {141.33, 7}}),
//	};

	const std::array<std::map<double, size_t>, 7> chpSystemByKey = {
			{
					{{50, 0}, {600, 1}, {1000, 2}, {3300, 3}, {5000, 4}, {10000, 5}, {20000, 6}, {45000, 7}},
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
					{{1.0, 0}, {1.1, 1}, {1.2, 2}, {1.3, 3}, {1.4, 4}, {1.5, 5}, {1.6, 6}, {1.7, 7}},
					{{0.34, 0}, {2.64, 1}, {3.85, 2}, {10.67, 3}, {24.47, 4}, {52.62, 5}, {76.42, 6}, {141.33, 7}},
			}
	};

};

#endif //AMO_TOOLS_SUITE_CHP_H
