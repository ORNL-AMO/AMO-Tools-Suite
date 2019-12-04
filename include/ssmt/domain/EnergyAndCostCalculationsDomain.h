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

    friend std::ostream &operator<<(std::ostream &stream, const EnergyAndCostCalculationsDomain &domain) {
        stream << "EnergyAndCostCalculationsDomain["
               << "powerGenerated=" << domain.powerGenerated
               << ", sitePowerImport=" << domain.sitePowerImport
               << ", powerDemand=" << domain.powerDemand
               << ", powerGenerationCost=" << domain.powerGenerationCost
               << ", boilerFuelCost=" << domain.boilerFuelCost
               << ", makeupWaterCost=" << domain.makeupWaterCost
               << ", totalOperatingCost=" << domain.totalOperatingCost
               << ", boilerFuelUsage=" << domain.boilerFuelUsage
               << "]";
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATIONSDOMAIN_H
