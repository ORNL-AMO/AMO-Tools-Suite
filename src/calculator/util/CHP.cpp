#include <algorithm>
#include "calculator/util/CHP.h"

CHP::CHP(double annualOperatingHours, double annualElectricityConsumption, double annualThermalDemand,
         double boilerThermalFuelCosts, double avgElectricityCosts, Option calculationOption,
         double boilerThermalFuelCostsCHPcase, double CHPfuelCosts,
         double percentAvgkWhElectricCostAvoidedOrStandbyRate, double displacedThermalEfficiency,
         double chpAvailability, double thermalUtilization)
		: annualOperatingHours(annualOperatingHours), annualElectricityConsumption(annualElectricityConsumption),
		  annualThermalDemand(annualThermalDemand), boilerThermalFuelCosts(boilerThermalFuelCosts),
		  chpFuelCosts(CHPfuelCosts), avgElectricityCosts(avgElectricityCosts), calculationOption(calculationOption),
		  boilerThermalFuelCostsCHPcase(boilerThermalFuelCostsCHPcase),
		  displacedThermalEfficiency(displacedThermalEfficiency / 100), chpAvailability(chpAvailability / 100),
		  thermalUtilization(thermalUtilization / 100)
{
	setCalculationOption(calculationOption, percentAvgkWhElectricCostAvoidedOrStandbyRate);
	calculate();
}

std::map<double, std::size_t>::const_iterator CHP::findNearest(const double val, const std::size_t index) const {
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
		nearest = findNearest(netCHPpower, 1);
	} else {
		nearest = findNearest(avgThermalDemand, 1);
	}
	chpElectricEfficiency = nearest->first/ 100.0;

	nearest = findNearest(avgThermalDemand, 3);
	auto val = chpSystemByIndex[0][nearest->second];
	if (netCHPpower < val) {
		nearest = findNearest(netCHPpower, 2);
	} else {
		nearest = findNearest(val, 2);
	}
	chpThermalOutput = nearest->first;

//	auto const chpThermalOutputMMBtuHr = chpThermalOutput * netCHPpower / 1000000;

	nearest = findNearest(avgThermalDemand, 3);
	val = chpSystemByIndex[1][nearest->second];
	if (netCHPpower < val) {
		nearest = findNearest(netCHPpower, 4);
	} else {
		nearest = findNearest(val, 4);
	}
	auto const incrementalOandMcost = nearest->first;

	nearest = findNearest(avgThermalDemand, 3);
	val = chpSystemByIndex[2][nearest->second];
	if (netCHPpower < val) {
		nearest = findNearest(netCHPpower, 5);
	} else {
		nearest = findNearest(val, 5);
	}
	auto const totalInstalledCosts = nearest->first;

	class Cases {
	public:
		Cases(const double base, const double chp) : baseCase(base), chpCase(chp) {}
		const double baseCase, chpCase;
	};

	auto const generatedElectricity = Cases(0, netCHPpower * annualOperatingHours * chpAvailability);
	auto const purchasedElectricity = Cases(annualElectricityConsumption, annualElectricityConsumption - generatedElectricity.chpCase);
	auto const chpThermal = Cases(0, (generatedElectricity.chpCase * chpThermalOutput * thermalUtilization) / 1000000);
	auto const onSiteBoiler = Cases(annualThermalDemand, (annualThermalDemand - chpThermal.chpCase < 0) ? 0 : annualThermalDemand - chpThermal.chpCase);
	auto const boilerHeaterFuel = Cases(annualThermalDemand / displacedThermalEfficiency, onSiteBoiler.chpCase / displacedThermalEfficiency);
	auto const chpFuel = Cases(0, (generatedElectricity.chpCase * 3412) / (chpElectricEfficiency * 1000000));
//	auto const totalFuel = Cases(boilerHeaterFuel.baseCase, boilerHeaterFuel.chpCase + chpFuel.chpCase); // unused

	// cost in $ stuff
	auto const cost = (annualElectricityConsumption * avgElectricityCosts) - (generatedElectricity.chpCase
	                                                                          * avgElectricityCosts
	                                                                          * percentAvgkWhElectricCostAvoided);
	auto const purchasedElectricityDollars = Cases(annualElectricityConsumption * avgElectricityCosts,
	                                               (!standbyRate) ? cost : purchasedElectricity.chpCase * avgElectricityCosts);
	auto const standbyCharges = Cases(0, (percentAvgkWhElectricCostAvoided) ? 0 : standbyRate * netCHPpower * 12);
	auto const chpFuelDollars = Cases(0, chpFuel.chpCase * chpFuelCosts);
	auto const onSiteBoilerFuelDollars = Cases(boilerHeaterFuel.baseCase * boilerThermalFuelCosts,
	                                    boilerHeaterFuel.chpCase * boilerThermalFuelCostsCHPcase);
	auto const incrementalOandM = Cases(0, incrementalOandMcost * generatedElectricity.chpCase);
	auto const totalOperatingCosts = Cases(purchasedElectricityDollars.baseCase + onSiteBoilerFuelDollars.baseCase,
	                                       purchasedElectricityDollars.chpCase + standbyCharges.chpCase +
			                                       chpFuelDollars.chpCase +
			                                       onSiteBoilerFuelDollars.chpCase + incrementalOandM.chpCase);

	// simple payback
	auto const annualOperationSavings = totalOperatingCosts.baseCase - totalOperatingCosts.chpCase;
	auto const totalInstalledCostsPayback = totalInstalledCosts * netCHPpower;
	auto const simplePayback = (totalInstalledCostsPayback - 200000) / annualOperationSavings;

	// operating costs to generate
	auto const fuelCosts = chpFuelDollars.chpCase / generatedElectricity.chpCase;
	auto const thermalCredit = -(onSiteBoilerFuelDollars.baseCase - onSiteBoilerFuelDollars.chpCase) / generatedElectricity.chpCase;
	auto const incrementalOandMDollarsKwH = incrementalOandM.chpCase / generatedElectricity.chpCase;
	auto const totalOperatingCostsToGenerate = fuelCosts + thermalCredit + incrementalOandMDollarsKwH;

	costInfo = {
			{"annualOperationSavings", annualOperationSavings},
			{"totalInstalledCostsPayback", totalInstalledCostsPayback},
			{"simplePayback", simplePayback},
			{"fuelCosts", fuelCosts},
			{"thermalCredit", thermalCredit},
			{"incrementalOandM", incrementalOandMDollarsKwH},
			{"totalOperatingCosts", totalOperatingCostsToGenerate}
	};
}

void CHP::setAnnualOperatingHours(const double annualOperatingHours) {
	this->annualOperatingHours = annualOperatingHours;
	calculate();
}

void CHP::setAnnualElectricityConsumption(const double annualElectricityConsumption) {
	this->annualElectricityConsumption = annualElectricityConsumption;
	calculate();
}

void CHP::setAnnualThermalDemand(const double annualThermalDemand) {
	this->annualThermalDemand = annualThermalDemand;
	calculate();
}

void CHP::setBoilerThermalFuelCosts(const double boilerThermalFuelCosts) {
	this->boilerThermalFuelCosts = boilerThermalFuelCosts;
	calculate();
}

void CHP::setChpFuelCosts(const double chpFuelCosts) {
	this->chpFuelCosts = chpFuelCosts;
	calculate();
}

void CHP::setAvgElectricityCosts(const double avgElectricityCosts) {
	this->avgElectricityCosts = avgElectricityCosts;
	calculate();
}

void CHP::setCalculationOption(const CHP::Option calculationOption,
                               const double percentAvgkWhElectricCostAvoidedOrStandbyRate) {
	this->calculationOption = calculationOption;
	if (calculationOption == Option::PercentAvgkWhElectricCostAvoided) {
		percentAvgkWhElectricCostAvoided = percentAvgkWhElectricCostAvoidedOrStandbyRate / 100;
	} else {
		standbyRate = percentAvgkWhElectricCostAvoidedOrStandbyRate;
	}
	calculate();
}

void CHP::setBoilerThermalFuelCostsCHPcase(const double boilerThermalFuelCostsCHPcase) {
	this->boilerThermalFuelCostsCHPcase = boilerThermalFuelCostsCHPcase;
}


void CHP::setPercentAvgkWhElectricCostAvoided(const double percentAvgkWhElectricCostAvoided) {
	this->percentAvgkWhElectricCostAvoided = percentAvgkWhElectricCostAvoided;
}

void CHP::setStandbyRate(const double standbyRate) {
	this->standbyRate = standbyRate;
}

void CHP::setDisplacedThermalEfficiency(const double displacedThermalEfficiency) {
	this->displacedThermalEfficiency = displacedThermalEfficiency;
}

void CHP::setChpElectricEfficiency(const double chpElectricEfficiency) {
	this->chpElectricEfficiency = chpElectricEfficiency;
}

void CHP::setChpThermalOutput(const double chpThermalOutput) {
	this->chpThermalOutput = chpThermalOutput;
}

void CHP::setChpAvailability(const double chpAvailability) {
	this->chpAvailability = chpAvailability;
}

void CHP::setThermalUtilization(const double thermalUtilization) {
	this->thermalUtilization = thermalUtilization;
}

void CHP::setAvgPowerDemand(const double avgPowerDemand) {
	this->avgPowerDemand = avgPowerDemand;
}

void CHP::setAvgThermalDemand(const double avgThermalDemand) {
	this->avgThermalDemand = avgThermalDemand;
}

void CHP::setNetCHPpower(const double netCHPpower) {
	this->netCHPpower = netCHPpower;
}
