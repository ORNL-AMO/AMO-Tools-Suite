#include "ssmt/api/SteamModelerInput.h"

SteamModelerInput::SteamModelerInput(const bool isBaselineCalc, const double baselinePowerDemand,
                                     const BoilerInput &boilerInput, const HeaderInput &headerInput,
                                     const OperationsInput &operationsInput, const TurbineInput &turbineInput)
        : baselineCalc(isBaselineCalc),
          baselinePowerDemand(baselinePowerDemand),
          boilerInput(boilerInput),
          headerInput(headerInput),
          operationsInput(operationsInput),
          turbineInput(turbineInput) {
}

bool SteamModelerInput::isBaselineCalc() const {
    return baselineCalc;
}

double SteamModelerInput::getBaselinePowerDemand() const {
    return baselinePowerDemand;
}

BoilerInput SteamModelerInput::getBoilerInput() const {
    return boilerInput;
}

HeaderInput SteamModelerInput::getHeaderInput() const {
    return headerInput;
}

OperationsInput SteamModelerInput::getOperationsInput() const {
    return operationsInput;
}

TurbineInput SteamModelerInput::getTurbineInput() const {
    return turbineInput;
}
