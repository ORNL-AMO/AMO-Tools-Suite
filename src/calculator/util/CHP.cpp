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

std::map<double, size_t>::const_iterator CHP::findNearest(const double val, const size_t index) {
	auto nearest = chpSystemByKey[index].upper_bound(val);
	if (nearest != chpSystemByKey[index].begin()) return std::prev(nearest);
	return nearest;
};

void CHP::calculate() {
	avgPowerDemand = annualElectricityConsumption / annualOperatingHours;
	avgThermalDemand = annualThermalDemand / annualOperatingHours;

	auto nearest = findNearest(avgThermalDemand, 3);
	netCHPpower = std::min(avgPowerDemand, (avgThermalDemand / nearest->first) * chpSystemByIndex[0][nearest->second]);

	if (netCHPpower < findNearest(avgThermalDemand, 0)->first) {
		nearest = chpSystemByKey[1].upper_bound(netCHPpower);
	} else {
		nearest = findNearest(avgThermalDemand, 1);
	}
	chpElectricEfficiency = nearest->first;




	auto blah = 0;
}
