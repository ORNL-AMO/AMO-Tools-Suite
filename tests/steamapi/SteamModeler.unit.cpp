#include "catch.hpp"
#include <ssmt/api/SteamModeler.h>

static const BoilerInput makeBoilerInput() {
    return {1, 1, 85, 2, true, true, 514.2, .1, 0.204747, 10};
}

static const HeaderInput makeHeaderInput() {
    const HeaderWithHighestPressure &headerWithHighestPressure =
            HeaderWithHighestPressure(1.136, 22680, 50, 0.1, 338.7, true);
    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeader = nullptr;
    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeader = nullptr;
    return {headerWithHighestPressure, mediumPressureHeader, lowPressureHeader};
}

static const OperationsInput makeOperationsInput() {
    return {18000000, 283.15, 8000, 0.000005478, 1.39E-05, 0.66};
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

    return {condensingTurbine, highToLowTurbine, highToMediumTurbine, mediumToLowTurbine};
}

static const SteamModelerInput makeSteamModelerInput() {
    const bool isBaselineCalc = true;
    const double baselinePowerDemand = 1;
    const BoilerInput &boilerInput = makeBoilerInput();
    const HeaderInput &headerInput = makeHeaderInput();
    const OperationsInput &operationsInput = makeOperationsInput();
    const TurbineInput &turbineInput = makeTurbineInput();

    return {isBaselineCalc, baselinePowerDemand, boilerInput, headerInput, operationsInput, turbineInput};
}

TEST_CASE("steamModeler", "[steam modeler]") {
    auto steamModeler = SteamModeler();

    SteamModelerInput steamModelerInput = makeSteamModelerInput();
    SteamModelerOutput actual = steamModeler.model(steamModelerInput);

    //TODO add asserts
}
