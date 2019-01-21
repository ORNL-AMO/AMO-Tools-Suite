#include "ssmt/service/power_balance/LowPressureVentedSteamCalculator.h"

LowPressureVentedSteamCalculationsDomain
LowPressureVentedSteamCalculator::calc(const int headerCountInput,
                                       const HeaderWithHighestPressure &highPressureHeaderInput,
                                       const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                       const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                       const CondensingTurbine &condensingTurbineInput,
                                       const OperationsInput &operationsInput,
                                       const BoilerInput &boilerInput, const Boiler &boiler,
                                       const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                       const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                       const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
                                       const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain,
                                       const double massFlowForLowPressureVentedSteam,
                                       const bool recalcMakeupWaterAndMassFlow) const {
    const std::string methodName = "LowPressureVentedSteamCalculator::calc: ";

    //TODO check requ'd things?? or push to called methods?
    if (lowPressureHeaderCalculationsDomain == nullptr) {
        std::string msg = methodName + "lowPressureHeaderCalculationsDomain is null";
        std::cout << msg << std::endl;
        throw std::invalid_argument(msg);
    }

    const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput =
            lowPressureHeaderCalculationsDomain->lowPressureHeaderOutput;

    double lowPressureVentedSteam =
            calcLowPressureVentedSteam(lowPressureHeaderInput, lowPressureHeaderOutput,
                                       massFlowForLowPressureVentedSteam);

    //5E. Calculate makeup water mass flow
    SteamSystemModelerTool::FluidProperties makeupWaterAndMassFlow =
            makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput;
    const SteamSystemModelerTool::FluidProperties &returnCondensate =
            makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain.returnCondensateFlashed;
    const SteamSystemModelerTool::FluidProperties &makeupWaterAndCondensateHeaderOutput =
            makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput;

    if (recalcMakeupWaterAndMassFlow) {
        std::cout << methodName << "calculating makeupWaterAndMassFlow" << std::endl;
        makeupWaterAndMassFlow =
                makeupWaterMassFlowCalculator.calc(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                                   lowPressureHeaderInput, condensingTurbineInput, boilerInput, boiler,
                                                   returnCondensate, makeupWaterAndCondensateHeaderOutput,
                                                   highPressureHeaderCalculationsDomain,
                                                   mediumPressureHeaderCalculationsDomain,
                                                   lowPressureHeaderCalculationsDomain);
    }

    SteamSystemModelerTool::FluidProperties makeupWaterAndCondensateHeaderOutputUpdated =
            fluidPropertiesFactory.makeWithVentedSteamAmount(makeupWaterAndMassFlow, lowPressureVentedSteam);
    const MakeupWaterVolumeFlowCalculationsDomain &makeupWaterVolumeFlowCalculationsDomain =
            makeupWaterVolumeFlowCalculator.calc(makeupWaterAndCondensateHeaderOutputUpdated, operationsInput);

    //5G. Calculate makeup water and condensate combined
    std::cout << methodName << "calculating makeupWaterAndCondensateHeaderOutput" << std::endl;
    const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput =
            makeupWaterAndCondensateHeaderCalculationsDomain.heatExchangerOutput;

    makeupWaterAndCondensateHeaderOutputUpdated =
            makeupWaterAndCondensateHeaderCalculator.calc(boilerInput, returnCondensate, heatExchangerOutput,
                                                          makeupWaterAndCondensateHeaderOutputUpdated,
                                                          condensingTurbineInput, highPressureHeaderCalculationsDomain);
    //6. Calculate Deaerator
    std::cout << methodName << "running deaeratorModeler" << std::endl;
    const Deaerator &deaerator =
            deaeratorModeler.model(headerCountInput, boilerInput, boiler, highPressureHeaderCalculationsDomain,
                                   mediumPressureHeaderCalculationsDomain, lowPressureHeaderCalculationsDomain,
                                   makeupWaterAndCondensateHeaderCalculationsDomain);

    return {lowPressureVentedSteam, makeupWaterAndMassFlow, makeupWaterAndCondensateHeaderOutputUpdated,
            makeupWaterVolumeFlowCalculationsDomain, deaerator};
}

double
LowPressureVentedSteamCalculator::calcLowPressureVentedSteam(
        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
        const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
        const double massFlow) const {
    const double processSteamUsage = lowPressureHeaderInput->getProcessSteamUsage();
    return lowPressureHeaderOutput.massFlow - (processSteamUsage + massFlow);
}
