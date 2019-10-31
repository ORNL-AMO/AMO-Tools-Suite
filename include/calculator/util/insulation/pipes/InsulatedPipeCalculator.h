#ifndef AMO_LIBRARY_INSULATEDPIPECALCULATOR_H
#define AMO_LIBRARY_INSULATEDPIPECALCULATOR_H

#include "calculator/util/insulation/pipes/InsulatedPipeInput.h"
#include "calculator/util/insulation/pipes/InsulatedPipeOutput.h"
#include "calculator/util/insulation/services/ConvectiveHeatTransferCoefficient.h"
#include "calculator/util/insulation/services/NusseltNumber.h"
#include "calculator/util/insulation/services/RadiativeHeatTransferCoefficient.h"
#include "calculator/util/insulation/services/RayleighNumber.h"
#include "calculator/util/insulation/services/ReynoldsNumber.h"
#include "calculator/util/insulation/services/ThermalResistance.h"

class InsulatedPipeCalculator
{
public:
    InsulatedPipeCalculator();
    InsulatedPipeCalculator(InsulatedPipeInput insulatedPipeInput) : _insulatedPipeInput(insulatedPipeInput) {}

    InsulatedPipeOutput calculate();

private:
    void sanatizeInput(InsulatedPipeInput input);
    InsulatedPipeOutput calculateNoInsulation(InsulatedPipeInput input);
    InsulatedPipeOutput calculateInsulation(InsulatedPipeInput input);

    InsulatedPipeInput _insulatedPipeInput;
    static double _airPropertiesArray[6][5];
};

#endif