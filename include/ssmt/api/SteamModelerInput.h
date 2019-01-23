#ifndef AMO_TOOLS_SUITE_STEAMMODELERINPUT_H
#define AMO_TOOLS_SUITE_STEAMMODELERINPUT_H

#include "BoilerInput.h"
#include "HeaderInput.h"
#include "OperationsInput.h"
#include "TurbineInput.h"

class SteamModelerInput {
public:
    SteamModelerInput(const bool isBaselineCalc, const double baselinePowerDemand, const BoilerInput &boilerInput,
                      const HeaderInput &headerInput, const OperationsInput &operationsInput,
                      const TurbineInput &turbineInput);

    bool isBaselineCalc() const;

    double getBaselinePowerDemand() const;

    BoilerInput getBoilerInput() const;

    HeaderInput getHeaderInput() const;

    OperationsInput getOperationsInput() const;

    TurbineInput getTurbineInput() const;

private:
    bool baselineCalc;
    double baselinePowerDemand;
    BoilerInput boilerInput;
    HeaderInput headerInput;
    OperationsInput operationsInput;
    TurbineInput turbineInput;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELERINPUT_H
