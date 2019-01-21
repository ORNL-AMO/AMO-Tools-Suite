#include "ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h"

SteamSystemModelerTool::FluidProperties
MakeupWaterAndCondensateHeaderCalculator::calc(const BoilerInput &boilerInput,
                                               const SteamSystemModelerTool::FluidProperties &returnCondensate,
                                               const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput,
                                               const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
                                               const CondensingTurbine &condensingTurbineInput,
                                               const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const {
    const std::shared_ptr<Turbine> &condensingTurbine =
            highPressureHeaderCalculationsDomain.condensingTurbine;

    const double boilerDeaeratorPressure = boilerInput.getDeaeratorPressure();
    const Header &makeupWaterAndCondensateHeader =
            headerFactory.make(boilerDeaeratorPressure, returnCondensate, boilerInput, heatExchangerOutput,
                               makeupWaterAndMassFlow, condensingTurbineInput, condensingTurbine);
    return fluidPropertiesFactory.make(makeupWaterAndCondensateHeader);
}
