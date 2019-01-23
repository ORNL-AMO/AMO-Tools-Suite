#include "catch.hpp"
#include <ssmt/api/SteamModeler.h>

static const BoilerInput makeBoilerInput(const double temperature) {
    return BoilerInput(1, 1, 1, 1, true, true, temperature, 1, 1, 1);
}

static const HeaderInput makeHeaderInput(const double temperature) {
    const HeaderWithHighestPressure &headerWithHighestPressure =
            HeaderWithHighestPressure(1, 1, 1, 1, temperature, true);
    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeader = nullptr;
    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeader = nullptr;
    return HeaderInput(headerWithHighestPressure, mediumPressureHeader, lowPressureHeader);
}

static const OperationsInput makeOperationsInput(const double temperature) {
    return OperationsInput(1, temperature, 1, 1, 1, 1);
}

static const TurbineInput makeTurbineInput() {
    const CondensingTurbine &condensingTurbine =
            CondensingTurbine(1, 1, 1, CondensingTurbineOperation::POWER_GENERATION, 1, true);
    const PressureTurbine &highToLowTurbine =
            PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, true);
    const PressureTurbine &highToMediumTurbine =
            PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, true);
    const PressureTurbine &mediumToLowTurbine =
            PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, true);

    return TurbineInput(condensingTurbine, highToLowTurbine, highToMediumTurbine, mediumToLowTurbine);
}

static const SteamModelerInput makeSteamModelerInput() {
    // Values that work for SteamSystemModelerTool::regionSelect()
    const double temperature = 594.65;

    const bool isBaselineCalc = true;
    const double baselinePowerDemand = 1;
    const BoilerInput &boilerInput = makeBoilerInput(temperature);
    const HeaderInput &headerInput = makeHeaderInput(temperature);
    const OperationsInput &operationsInput = makeOperationsInput(temperature);
    const TurbineInput &turbineInput = makeTurbineInput();

    return SteamModelerInput(isBaselineCalc, baselinePowerDemand, boilerInput, headerInput, operationsInput,
                             turbineInput);
}

TEST_CASE("steamModeler", "[steam modeler]") {
    auto steamModeler = SteamModeler();

    SteamModelerInput steamModelerInput = makeSteamModelerInput();
    SteamModelerOutput actual = steamModeler.model(steamModelerInput);

    //TODO add asserts
}
