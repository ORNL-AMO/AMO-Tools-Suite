#include "catch.hpp"
#include "ssmt/api/TurbineInput.h"

TEST_CASE("turbineInputConstructor", "[turbine input constructor]") {
    CondensingTurbine condensingTurbine =
            CondensingTurbine(1, 1, 1, CondensingTurbineOperation::POWER_GENERATION, 1, 1);
    PressureTurbine highToLowTurbine = PressureTurbine(1, 1, PressureTurbineOperation::POWER_GENERATION, 1, 1, true);
    PressureTurbine highToMediumTurbine = PressureTurbine(2, 2, PressureTurbineOperation::POWER_GENERATION, 2, 2, true);
    PressureTurbine mediumToLowTurbine = PressureTurbine(3, 3, PressureTurbineOperation::POWER_GENERATION, 3, 3, true);

    auto actual = TurbineInput(condensingTurbine, highToLowTurbine, highToMediumTurbine, mediumToLowTurbine);
    CHECK(actual.getCondensingTurbine().getCondenserPressure() == condensingTurbine.getCondenserPressure());
    CHECK(actual.getHighToLowTurbine().getGenerationEfficiency() == highToLowTurbine.getGenerationEfficiency());
    CHECK(actual.getHighToMediumTurbine().getGenerationEfficiency() == highToMediumTurbine.getGenerationEfficiency());
    CHECK(actual.getMediumToLowTurbine().getGenerationEfficiency() == mediumToLowTurbine.getGenerationEfficiency());
}
