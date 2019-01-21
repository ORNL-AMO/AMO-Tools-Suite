#ifndef AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATIONSDOMAIN_H

class EnergyAndCostCalculationsDomain {
public:
    const double powerGenerated;
    const double sitePowerImport;
    const double powerDemand;
    const double powerGenerationCost;
    const double boilerFuelCost;
    const double makeupWaterCost;
    const double totalOperatingCost;
    const double boilerFuelUsage;
};

#endif //AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATIONSDOMAIN_H
