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
	if (calculationOption == Option::PercentAvgkWhElectricCostAvoided) {
		percentAvgkWhElectricCostAvoided = percentAvgkWhElectricCostAvoidedOrStandbyRate / 100;
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

	auto const chpThermalOutputMMBtuHr = chpThermalOutput * netCHPpower / 1000000;

	nearest = findNearest(avgThermalDemand, 3);
	val = chpSystemByIndex[4][nearest->second];
	if (netCHPpower < val) {
		nearest = findNearest(netCHPpower, 4);
	} else {
		nearest = findNearest(val, 4);
	}
	auto const incrementalOandMcost = nearest->first;

	nearest = findNearest(avgThermalDemand, 3);
	val = chpSystemByIndex[5][nearest->second];
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

	// standby rate is N, percentAvgPerKwhElectricCostAvoided is M

	auto const generatedElectricity = Cases(0, netCHPpower * annualOperatingHours * chpAvailability); // this becomes Y
	auto const purchasedElectricity = Cases(annualElectricityConsumption,
	                                        annualElectricityConsumption - generatedElectricity.chpCase); // this is Z now
	auto const chpThermal = Cases(0, (generatedElectricity.chpCase * chpThermalOutput * thermalUtilization) / 1000000);
	auto const onSiteBoiler = Cases(annualThermalDemand, (annualThermalDemand - chpThermal.chpCase < 0) ? 0 : annualThermalDemand - chpThermal.chpCase); // B'
	auto const boilerHeaterFuel = Cases(annualThermalDemand / displacedThermalEfficiency,
	                                    onSiteBoiler.chpCase / displacedThermalEfficiency); // C' and D' respectively
	auto const chpFuel = Cases(0, (generatedElectricity.chpCase * 3412) / (chpElectricEfficiency * 1000000)); // E'
	auto const totalFuel = Cases(boilerHeaterFuel.baseCase, boilerHeaterFuel.chpCase + chpFuel.chpCase); // F'

	// cost in $ stuff
	auto const cost = (annualElectricityConsumption * avgElectricityCosts) - (generatedElectricity.chpCase * avgElectricityCosts * percentAvgkWhElectricCostAvoided);
	auto const purchasedElectricityDollars = Cases(annualElectricityConsumption * avgElectricityCosts,
	                                               (!standbyRate) ? cost : purchasedElectricity.chpCase * avgElectricityCosts);
	auto const standbyCharges = Cases(0, (!percentAvgkWhElectricCostAvoided) ? 0 : standbyRate * netCHPpower * 12); // H'
	auto const chpFuelDollars = Cases(0, chpFuel.chpCase * chpFuelCosts);
	auto const onSiteBoilerFuelDollars = Cases(boilerHeaterFuel.baseCase * boilerThermalFuelCosts,
	                                    boilerHeaterFuel.chpCase * boilerThermalFuelCostsCHPcase); // J' and K'
	auto const incrementalOandM = Cases(0, incrementalOandMcost * generatedElectricity.chpCase); // L'
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
