/**
 * @file CHP.h
 * @author Preston Shires (pshires) & Allie Ledbetter (aeledbetter)
 * @brief Calculates CHP related operations
 *
 * 
 */
#ifndef AMO_TOOLS_SUITE_CHP_H
#define AMO_TOOLS_SUITE_CHP_H

#include <array>
#include <string>
#include <map>
#include <unordered_map>

class CHP {
public:
	class CostInfoOutput
	{
	public:
	    /**
	     *
	     * @param annualOperationSavings double
	     * @param totalInstalledCostsPayback double
	     * @param simplePayback double
	     * @param fuelCosts double
	     * @param thermalCredit double
	     * @param incrementalOandMDollarsKwH double
	     * @param totalOperatingCostsToGenerate double
	     */
		CostInfoOutput(double annualOperationSavings, double totalInstalledCostsPayback, double simplePayback,
					   double fuelCosts, double thermalCredit, double incrementalOandMDollarsKwH, double totalOperatingCostsToGenerate) :
					   annualOperationSavings(annualOperationSavings), totalInstalledCostsPayback(totalInstalledCostsPayback),
                       simplePayback(simplePayback), fuelCosts(fuelCosts), thermalCredit(thermalCredit),
                       incrementalOandMDollarsKwH(incrementalOandMDollarsKwH), totalOperatingCostsToGenerate(totalOperatingCostsToGenerate){};
		CostInfoOutput() = default;
		double annualOperationSavings;
		double totalInstalledCostsPayback;
		double simplePayback;
		double fuelCosts;
		double thermalCredit;
		double incrementalOandMDollarsKwH;
		double totalOperatingCostsToGenerate;
	};
/**
 * Contructor for the CHP class
 * @param PercentAvgkWhElectricCostAvoided, percent cost saved from CHP electricity, percent
 * @param StandbyRate,  cost of outage, $/kW
 * @param annualOperatingHours, double, Time for which the CHP operates in a year - hours
 * @param annualElectricityConsumption double, kWh
 * @param annualThermalDemand double, MMBtu
 * @param boilerThermalFuelCosts double, $/MMBtu
 * @param avgElectricityCosts double, $/kWh
 * @param option calculationOption, dropdown enum
 * @param boilerThermalFuelCostsCHPcase double, $/MMBtu
 * @param CHPfuelCosts double,  $/MMBtu
 * @param percentAvgkWhElectricCostAvoidedOrStandbyRate double, percent
 * @param displacedThermalEfficiency double, percent
 * @param chpAvailability double, percent
 * @param thermalUtilization double, percent
 */
	enum class Option {
		PercentAvgkWhElectricCostAvoided,
		StandbyRate
	};

	CHP(double annualOperatingHours, double annualElectricityConsumption, double annualThermalDemand,
	    double boilerThermalFuelCosts, double avgElectricityCosts, Option calculationOption,
	    double boilerThermalFuelCostsCHPcase, double CHPfuelCosts,
	    double percentAvgkWhElectricCostAvoidedOrStandbyRate, double displacedThermalEfficiency, double chpAvailability,
		double thermalUtilization);

	CostInfoOutput getCostInfo() const { return costInfo; }
/**
 *  Gets the Annual Operating Hours
 * 
 * @return double const, annual operating hours in hrs/yr
 */
	double getAnnualOperatingHours() const { return annualOperatingHours; }
	/**
	 * Gets the Annual Electricity Consumption
	 * 
	 * @return double const, annual electricity consumption in kWh
	 */
	double getAnnualElectricityConsumption() const { return annualElectricityConsumption; }
	/**
	 * Gets the Annual Thermal Demand 
	 * 
	 * @return double const, annual thermal demand in MMBtu
	 */
	double getAnnualThermalDemand() const { return annualThermalDemand; }
	/**
	 * Gets the Boiler Thermal Fuel Costs
	 * 
	 * @return double const, boiler thermal fuel costs in  $/MMBtu
	 */
	double getBoilerThermalFuelCosts() const { return boilerThermalFuelCosts; }
	/**
	 * Gets the Chp Fuel Costs
	 * 
	 * @return double const, CHP fuel costs  $/MMBtu
	 */
	double getChpFuelCosts() const { return chpFuelCosts; }
	/**
	 * Gets the Avg Electricity Costs
	 * 
	 * @return double const, Average Electricity costs $/kWh
	 */
	double getAvgElectricityCosts() const { return avgElectricityCosts; }
	/**
	 * Gets the Calculation Option
	 * 
	 * @return Option const, Calculation Option, dropdown enum
	 */
	Option getCalculationOption() const { return calculationOption; }
	/**
	 * Gets the Boiler Thermal Fuel Costs CHP case 
	 * 
	 * @return double const, boiler thermal fuel costs CHP case in  $/MMBtu
	 */
	double getBoilerThermalFuelCostsCHPcase() const { return boilerThermalFuelCostsCHPcase; }
	/**
	 * Gets the Percent Avg kWh Electric Cost Avoided
	 * 
	 * @return double const, percent cost saved from CHP electricity, percent
	 */
	double getPercentAvgkWhElectricCostAvoided() const { return percentAvgkWhElectricCostAvoided; }
	/**
	 * Gets the Standby Rate
	 * 
	 * @return double const, cost of outage, $/kW
	 */
	double getStandbyRate() const { return standbyRate; }
	/**
	 * Gets the Displaced Thermal Efficiency
	 * 
	 * @return double const, Displaced Thermal Efficiency as a percent
	 */
	double getDisplacedThermalEfficiency() const { return displacedThermalEfficiency; }
	/**
	 * Gets the Chp Electric Efficiency
	 * 
	 * @return double const, CHP electric efficiency as a percent
	 */
	double getChpElectricEfficiency() const { return chpElectricEfficiency; }
	/**
	 * Get the Chp Thermal Output
	 * 
	 * @return double const, CHP thermal output in  MMBtu
	 */
	double getChpThermalOutput() const { return chpThermalOutput; }
	/**
	 * Gets the Chp Availability 
	 * 
	 * @return double const, CHP availability as a percent
	 */
	double getChpAvailability() const { return chpAvailability; }
	/**
	 * Gets the Thermal Utilization
	 * 
	 * @return double const, Thermal Utilization as a percent
	 */
	double getThermalUtilization() const { return thermalUtilization; }
	/**
	 * Gets the Avg Power Demand
	 * 
	 * @return double const, Average Power Demand in kWh
	 */
	double getAvgPowerDemand() const { return avgPowerDemand; }
	/**
	 * Gets the Avg Thermal Demand 
	 * 
	 * @return double const, Average Thermal Demand in MMBtu
	 */
	double getAvgThermalDemand() const { return avgThermalDemand; }
	/**
	 * Gets the Net CHP power
	 * 
	 * @return double const, Net CHP power in  MMBtu
	 */
	double getNetCHPpower() const { return netCHPpower; }

	void setAnnualOperatingHours(double annualOperatingHours);
	void setAnnualElectricityConsumption(double annualElectricityConsumption);
	void setAnnualThermalDemand(double annualThermalDemand);
	void setBoilerThermalFuelCosts(double boilerThermalFuelCosts);
	void setChpFuelCosts(double chpFuelCosts);
	void setAvgElectricityCosts(double avgElectricityCosts);
	void setCalculationOption(Option calculationOption, double percentAvgkWhElectricCostAvoidedOrStandbyRate);
	void setBoilerThermalFuelCostsCHPcase(double boilerThermalFuelCostsCHPcase);
	void setPercentAvgkWhElectricCostAvoided(double percentAvgkWhElectricCostAvoided);
	void setStandbyRate(double standbyRate);
	void setDisplacedThermalEfficiency(double displacedThermalEfficiency);
	void setChpElectricEfficiency(double chpElectricEfficiency);
	void setChpThermalOutput(double chpThermalOutput);
	void setChpAvailability(double chpAvailability);
	void setThermalUtilization(double thermalUtilization);
	void setAvgPowerDemand(double avgPowerDemand);
	void setAvgThermalDemand(double avgThermalDemand);
	void setNetCHPpower(double netCHPpower);

private:
	void calculate();

	std::map<double, std::size_t>::const_iterator findNearest(double val, std::size_t index) const;

	double annualOperatingHours, annualElectricityConsumption, annualThermalDemand;
	double boilerThermalFuelCosts, chpFuelCosts, avgElectricityCosts;
	Option calculationOption;
	double boilerThermalFuelCostsCHPcase, percentAvgkWhElectricCostAvoided = 0, standbyRate = 0;
	double displacedThermalEfficiency, chpElectricEfficiency, chpThermalOutput, chpAvailability, thermalUtilization;

	double avgPowerDemand, avgThermalDemand, netCHPpower;

	CostInfoOutput costInfo;

	const std::array<std::array<double, 8>, 3> chpSystemByIndex = {
			{
					{{50, 600, 1000, 3300, 5000, 10000, 20000, 45000}}, // row 2 - index 0
//					{{27.0, 34.5, 36.8, 40.4, 28.9, 27.3, 33.2, 36.0}}, // row 5 - index .
//					{{6700, 4392, 3854, 3233, 4893, 5262, 3821, 3141}}, // row 6 - index .
//					{{0.34, 2.64, 3.85, 10.67, 24.47, 52.62, 76.42, 141.33}}, // row 7 - index .
					{{0.024, 0.021, 0.019, 0.0126, 0.0123, 0.012, 0.0093, 0.0092}}, // row 11 - index 1
					{{2900, 2737, 2335, 1917, 2080, 1976, 1518, 1248}} // row 13 - index 2
			}
	};

	const std::array<std::map<double, std::size_t>, 6> chpSystemByKey = {
			{
					{{50, 0}, {600, 1}, {1000, 2}, {3300, 3}, {5000, 4}, {10000, 5}, {20000, 6}, {45000, 7}}, // row 2 - index 0
					{{27.0, 0}, {34.5, 1}, {36.8, 2}, {40.4, 3}, {28.9, 4}, {27.3, 5}, {33.2, 6}, {36.0, 7}}, // row 5 - index 1
					{{6700, 0}, {4392, 1}, {3854, 2}, {3233, 3}, {4893, 4}, {5262, 5}, {3821, 6}, {3141, 7}}, // row 6 - index 2
					{{0.34, 0}, {2.64, 1}, {3.85, 2}, {10.67, 3}, {24.47, 4}, {52.62, 5}, {76.42, 6}, {141.33, 7}}, // row 7 - index 3
					{{0.024, 0}, {0.021, 1}, {0.019, 2}, {0.0126, 3}, {0.0123, 4}, {0.012, 5}, {0.0093, 6}, {0.0092, 7}}, // row 11 - index 4
					{{2900, 0}, {2737, 1}, {2335, 2}, {1917, 3}, {2080, 4}, {1976, 5}, {1518, 6}, {1248, 7}} // row 13 - index 5
			}
	};

};

#endif //AMO_TOOLS_SUITE_CHP_H
