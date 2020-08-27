#include "calculator/losses/LoadChargeMaterial.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(phast_enums)
{
    enum_<LoadChargeMaterial::ThermicReactionType>("ThermicReactionType")
        .value("ENDOTHERMIC", LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC)
        .value("EXOTHERMIC", LoadChargeMaterial::ThermicReactionType::EXOTHERMIC)
        .value("NONE", LoadChargeMaterial::ThermicReactionType::NONE);
}