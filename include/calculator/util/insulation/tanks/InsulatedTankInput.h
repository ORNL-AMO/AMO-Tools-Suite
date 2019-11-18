#ifndef AMO_LIBRARY_INSULATEDTANKINPUT_H
#define AMO_LIBRARY_INSULATEDTANKINPUT_H

#include "calculator/util/insulation/objects/AirProperties.h"
#include <vector>

class InsulatedTankInput
{
    public:
    InsulatedTankInput(
        int operatingHours,
        double tankHeight,
        double tankDiameter,
        double tankThickness,
        double ambientTemperature,
        double systemEfficiency,
        double insulationThickness,
        double tankEmissivity,
        double jacketEmissivity,
        std::vector<double> tankMaterialCoefficients,
        std::vector<double> insulationMaterialCoefficients)
        : _operatingHours(operatingHours),
          _tankHeight(tankHeight),
          _tankDiameter(tankDiameter),
          _tankThickness(tankThickness),
          _ambientTemperature(ambientTemperature),
          _systemEfficiency(systemEfficiency),
          _insulationThickness(insulationThickness),
          _tankEmissivity(tankEmissivity),
          _jacketEmissivity(jacketEmissivity),
          _tankMaterialCoefficients(tankMaterialCoefficients),
          _insulationMaterialCoefficients(insulationMaterialCoefficients) {}

    int getOperatingHours();
    double getTankHeight();
    double getTankDiameter();
    double getTankThickness();
    double getAmbientTemperature();
    double getSystemEfficiency();
    double getInsulationThickness();
    double getTankEmissivity();
    double getJacketEmissivity();
    std::vector<double> getTankMaterialCoefficients();
    std::vector<double> getInsulationMaterialCoefficients();

private:
    // AirProperties _airProperties;
    int _operatingHours;
    double _tankHeight;
    double _tankDiameter;
    double _tankThickness;
    double _ambientTemperature;
    double _systemEfficiency;
    double _insulationThickness;
    double _tankEmissivity;
    double _jacketEmissivity;
    std::vector<double> _tankMaterialCoefficients;
    std::vector<double> _insulationMaterialCoefficients;
};


#endif