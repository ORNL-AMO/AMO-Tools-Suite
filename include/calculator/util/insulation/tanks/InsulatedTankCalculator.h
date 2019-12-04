#ifndef AMO_LIBRARY_INSULATEDTANKCALCULATOR_H
#define AMO_LIBRARY_INSULATEDTANKCALCULATOR_H

#include "calculator/util/insulation/tanks/InsulatedTankInput.h"
#include "calculator/util/insulation/tanks/InsulatedTankOutput.h"
#include <vector>

//Insulated Tank Calculator class responsible for handling calculation - main driver
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

private:
    void validateInput(InsulatedTankInput input);
    double propertyFit(std::vector<double> coefficients, double temp);

    InsulatedTankInput _insulatedTankInput;
    const double _airPropertiesArray[4][5] = {
        {-1.82109557e-14, 5.27958269e-11, -3.22287031e-8, 8.06185737e-6, 2.38303755e-1},  // specificHeat
        {5.53240532e-12, -2.97098117e-8, 5.96315645e-5, -5.57665211e-2, 2.43046430e1},     // density
        {-6.67800412e-13, 2.42855319e-9, 7.21312269e-8, 3.56111381e-3, -5.82727939e-1},      // kinViscosity
        {-1.63898601e-15, 7.98394765e-12, -1.80852621e-8, 3.85957991e-5, -1.49489778e-3}, // thermCond
    };
};

#endif