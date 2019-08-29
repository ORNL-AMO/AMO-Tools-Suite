#ifndef AMO_LIBRARY_INSULATEDPIPEINPUT_H
#define AMO_LIBRARY_INSULATEDPIPEINPUT_H

class InsulatedPipeInput
{
public:
    InsulatedPipeInput(int operatingHours, double length, double diameter, double ambientTemperature,
                       double windVelocity, double naturalGasSystemEfficiency, int pipeMaterial, int insulationMaterial,
                       double insulationThickness, int jacketMaterial)
        : operatingHours(operatingHours), length(length), diameter(diameter), ambientTemperature(ambientTemperature),
          windVelocity(windVelocity), naturalGasSystemEfficiency(naturalGasSystemEfficiency), pipeMaterial(pipeMaterial),
          insulationMaterial(insulationMaterial), insulationThickness(insulationThickness), jacketMaterial(jacketMaterial) {}

    

private:
    int operatingHours, pipeMaterial, insulationMaterial, jacketMaterial;
    double length, diameter, ambientTemperature, windVelocity, naturalGasSystemEfficiency, insulationThickness;

};