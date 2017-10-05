#include <algorithm>
#include "calculator/util/CHP.h"

CHP::CHP(double annualOperatingHours, double annualElectricityConsumption, double annualThermalDemand,
         double boilerThermalFuelCosts, double avgElectricityCosts, Option calculationOption,
         double boilerThermalFuelCostsCHPcase, double CHPfuelCosts,
         double percentAvgkWhElectricCostAvoidedOrStandbyRate, double displacedThermalEfficiency)
		: annualOperatingHours(annualOperatingHours), annualElectricityConsumption(annualElectricityConsumption),
		  annualThermalDemand(annualThermalDemand), boilerThermalFuelCosts(boilerThermalFuelCosts),
		  chpFuelCosts(CHPfuelCosts), avgElectricityCosts(avgElectricityCosts), calculationOption(calculationOption),
		  boilerThermalFuelCostsCHPcase(boilerThermalFuelCostsCHPcase),
		  displacedThermalEfficiency(displacedThermalEfficiency)
{
	if (calculationOption == Option::PercentAvgkWhElectricCostAvoided) {
		percentAvgkWhElectricCostAvoided = percentAvgkWhElectricCostAvoidedOrStandbyRate;
	} else {
		standbyRate = percentAvgkWhElectricCostAvoidedOrStandbyRate;
	}
	calculate();
}

void CHP::calculate() {
	avgPowerDemand = annualElectricityConsumption / annualOperatingHours;
	avgThermalDemand = annualThermalDemand / annualOperatingHours;

	// index 6 is row 7 of the table
	auto lower = chpSystemByKey[6].upper_bound(avgThermalDemand);

	// index 6 is row 7 of the table
	if (lower != chpSystemByKey[6].begin()) lower = std::prev(lower);

	// index 0 is row 1 of the table
	auto const val = chpSystemByIndex[0][lower->second];

	netCHPpower = std::min(avgPowerDemand, (avgThermalDemand / lower->first) * val);

	auto blah = 0;


}
