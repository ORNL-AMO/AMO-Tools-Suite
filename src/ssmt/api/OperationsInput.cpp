#include <ssmt/api/OperationsInput.h>

OperationsInput::OperationsInput(double sitePowerImport, double makeUpWaterTemperature, double operatingHoursPerYear,
                                 double fuelCosts, double electricityCosts, double makeUpWaterCosts)
        : sitePowerImport(sitePowerImport), makeUpWaterTemperature(makeUpWaterTemperature),
          operatingHoursPerYear(operatingHoursPerYear), fuelCosts(fuelCosts), electricityCosts(electricityCosts),
          makeUpWaterCosts(makeUpWaterCosts) {
}

std::ostream &operator<<(std::ostream &stream, const OperationsInput &oi) {
    return stream << "OperationsInput: "
                  << "sitePowerImport=" << oi.sitePowerImport
                  << ", makeUpWaterTemperature=" << oi.makeUpWaterTemperature
                  << ", operatingHoursPerYear=" << oi.operatingHoursPerYear
                  << ", fuelCosts=" << oi.fuelCosts
                  << ", electricityCosts=" << oi.electricityCosts
                  << ", makeUpWaterCosts=" << oi.makeUpWaterCosts;
}

double OperationsInput::getSitePowerImport() const {
    return sitePowerImport;
}

double OperationsInput::getMakeUpWaterTemperature() const {
    return makeUpWaterTemperature;
}

double OperationsInput::getOperatingHoursPerYear() const {
    return operatingHoursPerYear;
}

double OperationsInput::getFuelCosts() const {
    return fuelCosts;
}

double OperationsInput::getElectricityCosts() const {
    return electricityCosts;
}

double OperationsInput::getMakeUpWaterCosts() const {
    return makeUpWaterCosts;
}
