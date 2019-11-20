#ifndef AMO_LIBRARY_INSULATEDTANKCALCULATOR_H
#define AMO_LIBRARY_INSULATEDTANKCALCULATOR_H

#include "calculator/util/insulation/tanks/InsulatedTankInput.h"
#include "calculator/util/insulation/tanks/InsulatedTankOutput.h"

class InsulatedTankCalculator
{
public:
    InsulatedTankCalculator();
    InsulatedTankCalculator(InsulatedTankInput insulatedTankInput) : _insulatedTankInput(insulatedTankInput) {}

    InsulatedTankOutput calculate();
    InsulatedTankOutput calculateNoInsulation(InsulatedTankInput input);
    InsulatedTankOutput calculateInsulation(InsulatedTankInput input);
    AirProperties calculateAirProperties(double temp);
    double insulationRecursive();
    double noInsulationRecursive();
    double calculateAirProperty(int property, double temp);
    double lookupAirPropertyCoefficient(int property, int n);
    const double *lookupAirProperty(int property);

private:
    void validateInput(InsulatedTankInput input);
    double propertyFit(std::vector<double> coefficients, double temp);

    InsulatedTankInput _insulatedTankInput;
    const double _airPropertiesArray[4][5] = {
        {-1.82110e-14, 1.93117e-11, 1.74898e-8, 4.82437e-6, 2.39515e-1},  // specificHeat
        {5.53241e-12, -1.95375e-8, 2.56753e-5, -1.76282e-2, 8.63177},     // density
        {-6.67800e-13, 1.20068e-9, 2.57451e-6, 4.90742e-3, 1.27551},      // kinViscosity
        {-1.63899e-15, 4.97038e-12, -9.15319e-9, 2.63935e-5, 1.31274e-2}, // thermCond
    };
};

#endif