#ifndef AMO_LIBRARY_INSULATEDPIPECALCULATOR_H
#define AMO_LIBRARY_INSULATEDPIPECALCULATOR_H

#include "InsulatedPipeInput.h"
#include "InsulatedPipeOutput.h"
#include "../services/ConvectiveHeatTransferCoefficient.h"
#include "../services/NusseltNumber.h"
#include "../services/RadiativeHeatTransferCoefficient.h"
#include "../services/RayleighNumber.h"
#include "../services/ReynoldsNumber.h"
#include "../services/ThermalResistance.h"

class InsulatedPipeCalculator
{
public:
    InsulatedPipeCalculator();
    InsulatedPipeCalculator(InsulatedPipeInput insulatedPipeInput) : _insulatedPipeInput(insulatedPipeInput) {}

    InsulatedPipeOutput calculate();

private:
    InsulatedPipeInput _insulatedPipeInput;
};

#endif