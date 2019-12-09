#ifndef AMO_TOOLS_SUITE_OPERATIONSINPUT_H
#define AMO_TOOLS_SUITE_OPERATIONSINPUT_H

#include <iostream>

/**
 * Steam Modeler operations input data.
 */
class OperationsInput {
public:
    OperationsInput(double sitePowerImport, double makeUpWaterTemperature, double operatingHoursPerYear,
                    double fuelCosts, double electricityCosts, double makeUpWaterCosts);

    friend std::ostream &operator<<(std::ostream &stream, const OperationsInput &oi);

    double getSitePowerImport() const;

    double getMakeUpWaterTemperature() const;

    double getOperatingHoursPerYear() const;

    double getFuelCosts() const;

    double getElectricityCosts() const;

    double getMakeUpWaterCosts() const;

private:
    double sitePowerImport;
    double makeUpWaterTemperature;
    double operatingHoursPerYear;
    double fuelCosts;
    double electricityCosts;
    double makeUpWaterCosts;
};

#endif //AMO_TOOLS_SUITE_OPERATIONSINPUT_H
