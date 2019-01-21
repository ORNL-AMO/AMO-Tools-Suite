#include "ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h"

MakeupWaterAndCondensateHeaderCalculationsDomain
MakeupWaterAndCondensateHeaderModeler::model(const int headerCountInput,
                                             const HeaderWithHighestPressure &highPressureHeaderInput,
                                             const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                             const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                             const BoilerInput &boilerInput, const OperationsInput &operationsInput,
                                             const CondensingTurbine &condensingTurbineInput, const Boiler &boiler,
                                             const std::shared_ptr<FlashTank> &blowdownFlashTank,
                                             const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                             const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                             const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const {
    const std::string methodName = "MakeupWaterAndCondensateHeaderModeler::model: ";

    std::cout << methodName << "calculating combinedCondensateHeader" << std::endl;

    //5A. Calculate Return Condensate
    const Header &combinedCondensateHeader =
            combinedCondensateCalculator.calc(headerCountInput, highPressureHeaderCalculationsDomain,
                                              mediumPressureHeaderCalculationsDomain,
                                              lowPressureHeaderCalculationsDomain);

    //5B. Calculate return condensate
    std::cout << methodName << "calculating returnCondensate" << std::endl;
    SteamSystemModelerTool::FluidProperties returnCondensate =
            returnCondensateCalculator.calc(highPressureHeaderInput, combinedCondensateHeader);

    //5C. Flash return condensate if selected
    std::cout << methodName << "calculating flash returnCondensate" << std::endl;
    ReturnCondensateCalculationsDomain const &returnCondensateCalculationsDomain =
            returnCondensateCalculator.flash(highPressureHeaderInput, boilerInput, returnCondensate);
    returnCondensate = returnCondensateCalculationsDomain.returnCondensateFlashed;

    //5D. Calculate Makeup Water
    std::cout << methodName << "calculating makeupWaterOnly" << std::endl;
    const SteamSystemModelerTool::SteamPropertiesOutput &makeupWaterOnly = makeupWaterCalculator.calc(operationsInput);

    //5E. Calculate makeup water mass flow
    std::cout << methodName << "calculating makeupWater" << std::endl;
    const SteamSystemModelerTool::FluidProperties &makeupWater =
            makeupWaterMassFlowCalculator.calc(headerCountInput, highPressureHeaderInput, mediumPressureHeaderInput,
                                               lowPressureHeaderInput, condensingTurbineInput, boilerInput, boiler,
                                               returnCondensate, makeupWaterOnly,
                                               highPressureHeaderCalculationsDomain,
                                               mediumPressureHeaderCalculationsDomain,
                                               lowPressureHeaderCalculationsDomain);

    std::cout << methodName << "calculating makeupWaterVolumeFlow" << std::endl;
    const MakeupWaterVolumeFlowCalculationsDomain &makeupWaterVolumeFlowCalculationsDomain =
            makeupWaterVolumeFlowCalculator.calc(makeupWater, operationsInput);

    //5F. Run heat exchange if pre heating makeup water
    std::cout << methodName << "calculating heatExchangerOutput" << std::endl;
    std::shared_ptr<HeatExchanger::Output> heatExchangerOutput =
            heatExchangerCalculator.calc(boilerInput, boiler, makeupWater, blowdownFlashTank);

    //5G. Calculate makeup water and condensate combined
    std::cout << methodName << "calculating makeupWaterAndCondensateHeaderOutput" << std::endl;
    const SteamSystemModelerTool::FluidProperties &makeupWaterAndCondensateHeaderOutput =
            makeupWaterAndCondensateHeaderCalculator.calc(boilerInput, returnCondensate, heatExchangerOutput,
                                                          makeupWater, condensingTurbineInput,
                                                          highPressureHeaderCalculationsDomain);
    return {combinedCondensateHeader, returnCondensate, returnCondensateCalculationsDomain, makeupWater,
            makeupWaterVolumeFlowCalculationsDomain, heatExchangerOutput, makeupWaterAndCondensateHeaderOutput};
}
