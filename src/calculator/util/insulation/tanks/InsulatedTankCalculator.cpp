#include "calculator/util/insulation/tanks/InsulatedTankCalculator.h"
#include "calculator/util/insulation/objects/AirProperties.h"
#include <cmath>
#include <vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

InsulatedTankOutput InsulatedTankCalculator::calculate()
{
    InsulatedTankInput input = this->_insulatedTankInput;
    this->validateInput(input);

    // if -1 or 0, then no insulation was provided
    if (this->_insulatedTankInput.getInsulationThickness() == -1 || this->_insulatedTankInput.getInsulationThickness() == 0)
    {
        return InsulatedTankCalculator::calculateNoInsulation(input);
    }
    else
    {
        return InsulatedTankCalculator::calculateInsulation(input);
    }
}

void InsulatedTankCalculator::validateInput(InsulatedTankInput input)
{
    if (input.getTankEmissivity() < 0.0 || input.getTankEmissivity() > 1.0)
    {
        throw "ERROR : Tank - tank emissivity out of acceptable range";
    }
    if (input.getJacketEmissivity() < 0.0 || input.getJacketEmissivity() > 1.0)
    {
        throw "ERROR : Tank - jacket emissivity out of acceptable range";
    }
    if (input.getTankMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Tank - expected exactly 5 tank material coefficients, received " + input.getTankMaterialCoefficients().size();
    }
    if (input.getInsulationMaterialCoefficients().size() != 5)
    {
        throw "ERROR : Tank - expected exactly 5 insulation material coefficients, received " + input.getInsulationMaterialCoefficients().size();
    }
}

InsulatedTankInput InsulatedTankCalculator::calculateInsulation(InsulatedTankInput input)
{
    // double 
    // return InsulatedTankOutput(0, 0);
}