#include "calculator/util/CHP.h"
#include "calculator/util/CompressedAir.h"
#include <vector>
#include <emscripten/bind.h>
using namespace emscripten;

// CHPcalculator
EMSCRIPTEN_BINDINGS(CHPcalculator)
{
    class_<CHP>("CHP")
        .constructor<double, double, double, double, double, CHP::Option, double, double, double, double, double, double>()
        .function("getCostInfo", &CHP::getCostInfo);

    class_<CHP::CostInfoOutput>("CostInfoOutput")
        .constructor<double, double, double, double, double, double, double>()
        .property("annualOperationSavings", &CHP::CostInfoOutput::annualOperationSavings)
        .property("totalInstalledCostsPayback", &CHP::CostInfoOutput::totalInstalledCostsPayback)
        .property("simplePayback", &CHP::CostInfoOutput::simplePayback)
        .property("fuelCosts", &CHP::CostInfoOutput::fuelCosts)
        .property("thermalCredit", &CHP::CostInfoOutput::thermalCredit)
        .property("incrementalOandM", &CHP::CostInfoOutput::incrementalOandMDollarsKwH)
        .property("totalOperatingCosts", &CHP::CostInfoOutput::totalOperatingCostsToGenerate);
}
// usableAirCapacity
// receiverTank
EMSCRIPTEN_BINDINGS(receiverTank)
{
    class_<ReceiverTank>("ReceiverTank")
        .constructor()
        .constructor<ReceiverTank::Method, double, double, double>()
        .constructor<ReceiverTank::Method, double, double, double, double, double>()
        .constructor<ReceiverTank::Method, double, double, double, double, double, double>()
        .function("calculateSize", &ReceiverTank::calculateSize)
        .function("calculateUsableCapacity", &ReceiverTank::calculateUsableCapacity);
}
// pneumaticAirRequirement
EMSCRIPTEN_BINDINGS(pneumaticAirRequirement)
{
    class_<PneumaticAirRequirement>("PneumaticAirRequirement")
        .constructor()
        .constructor<PneumaticAirRequirement::PistonType, double, double, double, double>()
        .constructor<PneumaticAirRequirement::PistonType, double, double, double, double, double>()
        .function("calculate", &PneumaticAirRequirement::calculate);

    class_<PneumaticAirRequirement::Output>("PneumaticAirRequirementOutput")
        .constructor<double, double, double>()
        .property("volumeAirIntakePiston", &PneumaticAirRequirement::Output::volumeAirIntakePiston)
        .property("compressionRatio", &PneumaticAirRequirement::Output::compressionRatio)
        .property("airRequirementPneumaticCylinder", &PneumaticAirRequirement::Output::airRequirementPneumaticCylinder);
}
// operatingCost
EMSCRIPTEN_BINDINGS(operatingCost)
{
    class_<Compressor::OperatingCost>("OperatingCost")
        .constructor<double, double, double, double, double, double, double>()
        .function("calculate", &Compressor::OperatingCost::calculate);

    class_<Compressor::OperatingCost::Output>("OperatingCostOutput")
        .constructor<double, double, double, double>()
        .property("runTimeUnloaded", &Compressor::OperatingCost::Output::runTimeUnloaded)
        .property("costForLoaded", &Compressor::OperatingCost::Output::costForLoaded)
        .property("costForUnloaded", &Compressor::OperatingCost::Output::costForUnloaded)
        .property("totalAnnualCost", &Compressor::OperatingCost::Output::totalAnnualCost);
}
// airSystemCapacity
EMSCRIPTEN_BINDINGS(airSystemCapacity)
{
    class_<Compressor::PipeData>("PipeData")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("oneHalf", &Compressor::PipeData::oneHalf)
        .property("threeFourths", &Compressor::PipeData::threeFourths)
        .property("one", &Compressor::PipeData::one)
        .property("oneAndOneFourth", &Compressor::PipeData::oneAndOneFourth)
        .property("oneAndOneHalf", &Compressor::PipeData::oneAndOneHalf)
        .property("two", &Compressor::PipeData::two)
        .property("twoAndOneHalf", &Compressor::PipeData::twoAndOneHalf)
        .property("three", &Compressor::PipeData::three)
        .property("threeAndOneHalf", &Compressor::PipeData::threeAndOneHalf)
        .property("four", &Compressor::PipeData::four)
        .property("five", &Compressor::PipeData::five)
        .property("six", &Compressor::PipeData::six);

    class_<Compressor::AirSystemCapacity>("AirSystemCapacity")
        .constructor<Compressor::PipeData, std::vector<double>>()
        .function("calculate", &Compressor::AirSystemCapacity::calculate);

    class_<Compressor::AirSystemCapacity::Output>("AirSystemCapacityOutput")
        .constructor<double, std::vector<double>, double, double, Compressor::PipeData>()
        .property("totalPipeVolume", &Compressor::AirSystemCapacity::Output::totalPipeVolume)
        .property("totalReceiverVolume", &Compressor::AirSystemCapacity::Output::totalReceiverVol)
        .property("totalCapacityOfCompressedAirSystem", &Compressor::AirSystemCapacity::Output::totalCapacityOfCompressedAirSystem)
        .property("receiverCapacities", &Compressor::AirSystemCapacity::Output::receiverCapacities)
        .property("pipeLengths", &Compressor::AirSystemCapacity::Output::pipeLengths);
}
// airVelocity
EMSCRIPTEN_BINDINGS(airVelocity)
{
    class_<Compressor::AirVelocity>("AirVelocity")
        .constructor<double, double, double>()
        .function("calculate", &Compressor::AirVelocity::calculate);
}
// pipeSizing
EMSCRIPTEN_BINDINGS(pipeSizing)
{
    class_<Compressor::PipeSizing>("PipeSizing")
        .constructor<double, double, double, double>()
        .function("calculate", &Compressor::PipeSizing::calculate);

    class_<Compressor::PipeSizing::Output>("PipeSizingOutput")
        .constructor<double, double>()
        .property("crossSectionalArea", &Compressor::PipeSizing::Output::crossSectionalArea)
        .property("pipeDiameter", &Compressor::PipeSizing::Output::pipeDiameter);
}
// pneumaticValve
EMSCRIPTEN_BINDINGS(pneumaticValve)
{
    class_<Compressor::PneumaticValve>("PneumaticValve")
        .constructor<double, double>()
        .constructor<double, double, double>()
        .function("calculate", &Compressor::PneumaticValve::calculate);
}
// bagMethod
EMSCRIPTEN_BINDINGS(bagMethod)
{
    class_<BagMethod>("BagMethod")
        .constructor<double, double, double, double, double>()
        .function("calculate", &BagMethod::calculate);

    class_<BagMethod::Output>("BagMethodOutput")
        .constructor<double, double>()
        .property("flowRate", &BagMethod::Output::flowRate)
        .property("annualConsumption", &BagMethod::Output::annualConsumption);
}