#ifndef AMO_LIBRARY_INSULATEDPIPEINPUT_H
#define AMO_LIBRARY_INSULATEDPIPEINPUT_H

#include "calculator/util/insulation/objects/AirProperties.h

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
            naturalGasSystemEfficiency: fraction (0-1.0)
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
        double naturalGasSystemEfficiency,
        double insulationThickness,
        const double pipeMaterialCoefficients[5],
        const double insulationMaterialCoefficients[5],
        AirProperties airProperties,
        double pipeEmissivity = 0,
        double insulationEmissivity = 0,
        double jacketEmissivity = 0,
        double pipeBaseMaterialEmissivity = 0)
        : _operatingHours(operatingHours),
          _length(length),
          _pipeDiameter(pipeDiameter),
          _pipeThickness(pipeThickness),
          _pipeTemperature(pipeTemperature),
          _ambientTemperature(ambientTemperature),
          _windVelocity(windVelocity),
          _naturalGasSystemEfficiency(naturalGasSystemEfficiency),
          _insulationThickness(insulationThickness),
          _pipeMaterialCoefficients(pipeMaterialCoefficients),
          _insulationMaterialCoefficients(insulationMaterialCoefficients),
          _airProperties(airProperties),
          _pipeEmissivity(pipeEmissivity),
          _insulationEmissivity(insulationEmissivity),
          _jacketEmissivity(jacketEmissivity) {}

    int getOperatingHours();
    double getLength();
    double getPipeDiameter();
    double getPipeThickness();
    double getPipeTemperature();
    double getAmbientTemperature();
    double getWindVelocity();
    double getNaturalGasSystemEfficiency();
    double getInsulationThickness();
    double getPipeEmissivity();
    double getInsulationEmissivity();
    double getJacketEmissivity();
    const double[] getPipeMaterialCoefficients();
    const double[] getInsulationMaterialCoefficients();
    AirProperties getAirProperties();

    double lookupAirProperty(int x, int y);
    double lookupPipeProperty(int x, int y);
    double lookupInsulationProperty(int x, int y);

private:
    int _operatingHours;
    double _length;
    double _pipeDiameter;
    double _pipeThickness;
    double _pipeTemperature;
    double _ambientTemperature;
    double _windVelocity;
    double _naturalGasSystemEfficiency;
    double _insulationThickness;
    double _pipeEmissivity;
    double _insulationEmissivity;
    double _jacketEmissivity;
    const double _pipeMaterialCoefficients[5];
    const double _insulationMaterialCoefficients[5];
    AirProperties _airProperties;

    const double _airProperties[5][6];
    // const double _pipeProperties[5][3];
    // const double _insulationProperties[5][8];
};

#endif