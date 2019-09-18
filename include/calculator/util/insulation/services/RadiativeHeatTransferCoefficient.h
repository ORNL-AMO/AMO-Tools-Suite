#ifndef AMO_LIBRARY_RADIATIVEHEATTRANSFERCOEFFICIENT_H
#define AMO_LIBRARY_RADIATIVEHEATTRANSFERCOEFFICIENT_H

class RadiativeHeatTransferCoefficient
{
public:
    RadiativeHeatTransferCoefficient(double emissivity, double surfaceTemperature, double ambientTemperature)
        : _emissivity(emissivity), _surfaceTemperature(surfaceTemperature),
          _ambientTemperature(ambientTemperature) {}

    double calculate();

private:
    double _emissivity;
    double _surfaceTemperature;
    double _ambientTemperature;
}

#endif //AMO_LIBRARY_RADIATIVEHEATTRANSFERCOEFFICIENT_H