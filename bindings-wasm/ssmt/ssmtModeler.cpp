
#include "ssmt/api/SteamModeler.h"
#include "ssmt/api/SteamModelerInput.h"
#include "ssmt/api/SteamModelerOutput.h"
#include "ssmt/api/BoilerInput.h"
#include "ssmt/api/HeaderInput.h"
#include "ssmt/api/OperationsInput.h"
#include "ssmt/api/TurbineInput.h"

#include "ssmt/domain/EnergyAndCostCalculationsDomain.h"
#include "ssmt/domain/HighPressureHeaderCalculationsDomain.h"
#include "ssmt/domain/HighToMediumSteamTurbineCalculationsDomain.h"
#include "ssmt/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h"
#include "ssmt/domain/LowPressureHeaderCalculationsDomain.h"
#include "ssmt/domain/LowPressureVentedSteamCalculationsDomain.h"
#include "ssmt/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h"
#include "ssmt/domain/MakeupWaterVolumeFlowCalculationsDomain.h"
#include "ssmt/domain/MediumPressureHeaderCalculationsDomain.h"
#include "ssmt/domain/PowerBalanceCheckerCalculationsDomain.h"
#include "ssmt/domain/ProcessSteamUsageCalculationsDomain.h"
#include "ssmt/domain/ReturnCondensateCalculationsDomain.h"
#include "ssmt/domain/SteamModelCalculationsDomain.h"

#include <vector>
#include <emscripten/bind.h>
using namespace emscripten;

// steamModeler
EMSCRIPTEN_BINDINGS(steamModeler)
{
    //SteamModelerOutput
    class_<SteamModelerOutput>("SteamModelerOutput")
        .property("boiler", &SteamModelerOutput::boiler)
        .property("blowdownFlashTank", &SteamModelerOutput::blowdownFlashTank)
        .property("highPressureHeaderCalculationsDomain", &SteamModelerOutput::highPressureHeaderCalculationsDomain)
        .property("mediumPressureHeaderCalculationsDomain", &SteamModelerOutput::mediumPressureHeaderCalculationsDomain)
        .property("lowPressureHeaderCalculationsDomain", &SteamModelerOutput::lowPressureHeaderCalculationsDomain)
        .property("makeupWaterAndCondensateHeaderCalculationsDomain", &SteamModelerOutput::makeupWaterAndCondensateHeaderCalculationsDomain)
        .property("deaerator", &SteamModelerOutput::deaerator)
        .property("powerBalanceCheckerCalculationsDomain", &SteamModelerOutput::powerBalanceCheckerCalculationsDomain)
        .property("processSteamUsageCalculationsDomain", &SteamModelerOutput::processSteamUsageCalculationsDomain)
        .property("energyAndCostCalculationsDomain", &SteamModelerOutput::energyAndCostCalculationsDomain);

    class_<HighPressureHeaderCalculationsDomain>("HighPressureHeaderCalculationsDomain")
        .property("highPressureHeaderOutput", &HighPressureHeaderCalculationsDomain::highPressureHeaderOutput)
        .property("highPressureHeaderHeatLoss", &HighPressureHeaderCalculationsDomain::highPressureHeaderHeatLoss)
        .property("highPressureCondensate", &HighPressureHeaderCalculationsDomain::highPressureCondensate)
        .property("highPressureCondensateFlashTank", &HighPressureHeaderCalculationsDomain::highPressureCondensateFlashTank)
        .property("condensingTurbine", &HighPressureHeaderCalculationsDomain::condensingTurbine)
        .property("condensingTurbineIdeal", &HighPressureHeaderCalculationsDomain::condensingTurbineIdeal)
        .property("highToMediumPressureTurbine", &HighPressureHeaderCalculationsDomain::highToMediumPressureTurbine)
        .property("highToMediumPressureTurbineIdeal", &HighPressureHeaderCalculationsDomain::highToMediumPressureTurbineIdeal)
        .property("highToLowPressureTurbine", &HighPressureHeaderCalculationsDomain::highToLowPressureTurbine)
        .property("highToLowPressureTurbineIdeal", &HighPressureHeaderCalculationsDomain::highToLowPressureTurbineIdeal);

    class_<MediumPressureHeaderCalculationsDomain>("MediumPressureHeaderCalculationsDomain")
        .property("highToMediumPressurePrv", &MediumPressureHeaderCalculationsDomain::highToMediumPressurePrv)
        .property("highPressureCondensateFlashTank", &MediumPressureHeaderCalculationsDomain::highPressureCondensateFlashTank)
        .property("mediumPressureHeaderHeatLoss", &MediumPressureHeaderCalculationsDomain::mediumPressureHeaderHeatLoss)
        .property("mediumPressureHeaderOutput", &MediumPressureHeaderCalculationsDomain::mediumPressureHeaderOutput)
        .property("mediumPressureCondensate", &MediumPressureHeaderCalculationsDomain::mediumPressureCondensate)
        .property("mediumToLowPressureTurbine", &MediumPressureHeaderCalculationsDomain::mediumToLowPressureTurbine)
        .property("mediumToLowPressureTurbineIdeal", &MediumPressureHeaderCalculationsDomain::mediumToLowPressureTurbineIdeal)
        .property("highToLowPressureTurbineUpdated", &MediumPressureHeaderCalculationsDomain::highToLowPressureTurbineUpdated)
        .property("highToLowPressureTurbineIdealUpdated", &MediumPressureHeaderCalculationsDomain::highToLowPressureTurbineIdealUpdated);

    class_<LowPressureHeaderCalculationsDomain>("LowPressureHeaderCalculationsDomain")
        .property("lowPressurePrv", &LowPressureHeaderCalculationsDomain::lowPressurePrv)
        .property("lowPressureHeaderOutput", &LowPressureHeaderCalculationsDomain::lowPressureHeaderOutput)
        .property("lowPressureHeaderHeatLoss", &LowPressureHeaderCalculationsDomain::lowPressureHeaderHeatLoss)
        .property("lowPressureCondensate", &LowPressureHeaderCalculationsDomain::lowPressureCondensate)
        .property("lowPressureFlashedSteamIntoHeaderCalculatorDomain", &LowPressureHeaderCalculationsDomain::lowPressureFlashedSteamIntoHeaderCalculatorDomain);

    class_<MakeupWaterAndCondensateHeaderCalculationsDomain>("MakeupWaterAndCondensateHeaderCalculationsDomain")
        .property("combinedCondensate", &MakeupWaterAndCondensateHeaderCalculationsDomain::combinedCondensate)
        .property("returnCondensate", &MakeupWaterAndCondensateHeaderCalculationsDomain::returnCondensate)
        // .property("returnCondensateCalculationsDomain", &MakeupWaterAndCondensateHeaderCalculationsDomain::returnCondensateCalculationsDomain)
        .property("makeupWater", &MakeupWaterAndCondensateHeaderCalculationsDomain::makeupWater)
        .property("makeupWaterVolumeFlowCalculationsDomain", &MakeupWaterAndCondensateHeaderCalculationsDomain::makeupWaterVolumeFlowCalculationsDomain)
        .property("heatExchangerOutput", &MakeupWaterAndCondensateHeaderCalculationsDomain::heatExchangerOutput)
        .property("makeupWaterAndCondensateHeaderOutput", &MakeupWaterAndCondensateHeaderCalculationsDomain::makeupWaterAndCondensateHeaderOutput);

    class_<PowerBalanceCheckerCalculationsDomain>("PowerBalanceCheckerCalculationsDomain")
        .property("steamBalance", &PowerBalanceCheckerCalculationsDomain::steamBalance)
        .property("lowPressureVentedSteamCalculationsDomain", &PowerBalanceCheckerCalculationsDomain::lowPressureVentedSteamCalculationsDomain)
        .property("lowPressureVentedSteam", &PowerBalanceCheckerCalculationsDomain::lowPressureVentedSteam);

    class_<ProcessSteamUsageCalculationsDomain>("ProcessSteamUsageCalculationsDomain")
        .property("highPressureProcessSteamUsage", &ProcessSteamUsageCalculationsDomain::highPressureProcessSteamUsage)
        .property("lowPressureProcessUsagePtr", &ProcessSteamUsageCalculationsDomain::lowPressureProcessUsagePtr)
        .property("mediumPressureProcessUsagePtr", &ProcessSteamUsageCalculationsDomain::mediumPressureProcessUsagePtr);

    class_<EnergyAndCostCalculationsDomain>("EnergyAndCostCalculationsDomain")
        .property("powerGenerated", &EnergyAndCostCalculationsDomain::powerGenerated)
        .property("sitePowerImport", &EnergyAndCostCalculationsDomain::sitePowerImport)
        .property("powerDemand", &EnergyAndCostCalculationsDomain::powerDemand)
        .property("powerGenerationCost", &EnergyAndCostCalculationsDomain::powerGenerationCost)
        .property("boilerFuelCost", &EnergyAndCostCalculationsDomain::boilerFuelCost)
        .property("makeupWaterCost", &EnergyAndCostCalculationsDomain::makeupWaterCost)
        .property("totalOperatingCost", &EnergyAndCostCalculationsDomain::totalOperatingCost)
        .property("boilerFuelUsage", &EnergyAndCostCalculationsDomain::boilerFuelUsage);

    class_<LowPressureFlashedSteamIntoHeaderCalculatorDomain>("LowPressureFlashedSteamIntoHeaderCalculatorDomain")
        .property("mediumPressureCondensateFlashTank", &LowPressureFlashedSteamIntoHeaderCalculatorDomain::mediumPressureCondensateFlashTank)
        .property("highPressureCondensateFlashTank", &LowPressureFlashedSteamIntoHeaderCalculatorDomain::highPressureCondensateFlashTank);

    class_<ReturnCondensateCalculationsDomain>("ReturnCondensateCalculationsDomain")
        .property("condensateFlashTank", &ReturnCondensateCalculationsDomain::condensateFlashTank)
        .property("returnCondensateFlashed", &ReturnCondensateCalculationsDomain::returnCondensateFlashed);

    class_<MakeupWaterVolumeFlowCalculationsDomain>("MakeupWaterVolumeFlowCalculationsDomain")
        .property("makeupWaterVolumeFlow", &MakeupWaterVolumeFlowCalculationsDomain::makeupWaterVolumeFlow)
        .property("makeupWaterVolumeFlowAnnual", &MakeupWaterVolumeFlowCalculationsDomain::makeupWaterVolumeFlowAnnual);

    class_<LowPressureVentedSteamCalculationsDomain>("LowPressureVentedSteamCalculationsDomain")
        .property("lowPressureVentedSteam", &LowPressureVentedSteamCalculationsDomain::lowPressureVentedSteam)
        .property("makeupWater", &LowPressureVentedSteamCalculationsDomain::makeupWater)
        .property("makeupWaterAndCondensateHeaderOutputUpdated", &LowPressureVentedSteamCalculationsDomain::makeupWaterAndCondensateHeaderOutputUpdated)
        .property("makeupWaterVolumeFlowCalculationsDomain", &LowPressureVentedSteamCalculationsDomain::makeupWaterVolumeFlowCalculationsDomain)
        .property("deaerator", &LowPressureVentedSteamCalculationsDomain::deaerator);

    class_<ProcessSteamUsage>("ProcessSteamUsage")
        .property("pressure", &ProcessSteamUsage::pressure)
        .property("temperature", &ProcessSteamUsage::temperature)
        .property("energyFlow", &ProcessSteamUsage::energyFlow)
        .property("massFlow", &ProcessSteamUsage::massFlow)
        .property("processUsage", &ProcessSteamUsage::processUsage);

    //SteamModeler
    class_<SteamModeler>("SteamModeler")
        .constructor<>();

    //steam modeler input
    class_<SteamModelerInput>("SteamModelerInput")
        .constructor<bool, double, BoilerInput, HeaderInput, OperationsInput, TurbineInput>();
    //BoilerInput
    class_<BoilerInput>("BoilerInput")
        .constructor<double, double, double, double, bool, bool, double, double, double, double>();

    //HeaderInput
    class_<HeaderInput>("HeaderInput")
        .constructor<HeaderWithHighestPressure, std::shared_ptr<HeaderNotHighestPressure>, std::shared_ptr<HeaderNotHighestPressure>>()
        .constructor<HeaderWithHighestPressure, std::shared_ptr<HeaderNotHighestPressure>>()
        .constructor<HeaderWithHighestPressure>();

    //register nullptr
    // value_object<nullptr>("nullptr");

    //HeaderWithPressure
    class_<HeaderWithPressure>("HeaderWithPressure")
        .constructor<double, double, double, double, bool>();
    //HeaderWithHighestPressure
    class_<HeaderWithHighestPressure, emscripten::base<HeaderWithPressure>>("HeaderWithHighestPressure")
        .constructor<double, double, double, double, double, bool>();

    //HeaderNotHighestPressure
    class_<HeaderNotHighestPressure, emscripten::base<HeaderWithPressure>>("HeaderNotHighestPressure")
        .constructor<double, double, double, double, bool, bool, double>();

    //OperationsInput
    class_<OperationsInput>("OperationsInput")
        .constructor<double, double, double, double, double, double>();

    //TurbineInput
    class_<TurbineInput>("TurbineInput")
        .constructor<CondensingTurbine, PressureTurbine, PressureTurbine, PressureTurbine>();

    //CondensingTurbine
    class_<CondensingTurbine>("CondensingTurbine")
        .constructor<double, double, double, CondensingTurbineOperation, double, bool>();
    //PressureTurbine
    class_<PressureTurbine>("PressureTurbine")
        .constructor<double, double, PressureTurbineOperation, double, double, bool>();
}