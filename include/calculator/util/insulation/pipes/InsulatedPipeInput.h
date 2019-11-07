#ifndef AMO_LIBRARY_INSULATEDPIPEINPUT_H
#define AMO_LIBRARY_INSULATEDPIPEINPUT_H

#include "calculator/util/insulation/objects/AirProperties.h"
#include <vector>

class InsulatedPipeInput
{
public:
    /*
        Outline of expected input units: 
            length: meters (m)
            diameter: millimeters (mm)
            pipeTemperature: Kelvin (K)
            ambientTemperature: Kelvin (K)
            windVelocity: meters/second (m/s)
            systemEfficiency: fraction (0-1.0)
            insulationThickness: meters (m)
    */
    InsulatedPipeInput(
        int operatingHours,
        double length,
        double pipeDiameter,
        double pipeThickness,
        double pipeTemperature,
        double ambientTemperature,
        double windVelocity,
        double systemEfficiency,
        double insulationThickness,
        double pipeEmissivity,
        double jacketEmissivity,
        std::vector<double> pipeMaterialCoefficients,
        std::vector<double> insulationMaterialCoefficients)
        : _operatingHours(operatingHours),
          _length(length),
          _pipeDiameter(pipeDiameter),
          _pipeThickness(pipeThickness),
          _pipeTemperature(pipeTemperature),
          _ambientTemperature(ambientTemperature),
          _windVelocity(windVelocity),
          _systemEfficiency(systemEfficiency),
          _insulationThickness(insulationThickness),
          _pipeEmissivity(pipeEmissivity),
          _jacketEmissivity(jacketEmissivity),
          _pipeMaterialCoefficients(pipeMaterialCoefficients),
          _insulationMaterialCoefficients(insulationMaterialCoefficients) {}

    int getOperatingHours();
    double getLength();
    double getPipeDiameter();
    double getPipeThickness();
    double getPipeTemperature();
    double getAmbientTemperature();
    double getWindVelocity();
    double getSystemEfficiency();
    double getInsulationThickness();
    double getPipeEmissivity();
    double getJacketEmissivity();
    std::vector<double> getPipeMaterialCoefficients();
    std::vector<double> getInsulationMaterialCoefficients();

private:
    AirProperties _airProperties;
    int _operatingHours;
    double _length;
    double _pipeDiameter;
    double _pipeThickness;
    double _pipeTemperature;
    double _ambientTemperature;
    double _windVelocity;
    double _systemEfficiency;
    double _insulationThickness;
    double _pipeEmissivity;
    double _jacketEmissivity;
    std::vector<double> _pipeMaterialCoefficients;
    std::vector<double> _insulationMaterialCoefficients;
};

#endif