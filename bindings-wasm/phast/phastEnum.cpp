#include "calculator/losses/LoadChargeMaterial.h"
#include "calculator/furnace/EnergyEquivalency.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(phast_enums)
{
    enum_<LoadChargeMaterial::ThermicReactionType>("ThermicReactionType")
        .value("ENDOTHERMIC", LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC)
        .value("EXOTHERMIC", LoadChargeMaterial::ThermicReactionType::EXOTHERMIC)
        .value("NONE", LoadChargeMaterial::ThermicReactionType::NONE);

    enum_<FlowCalculationsEnergyUse::Gas>("Gas")
        .value("AIR", FlowCalculationsEnergyUse::Gas::AIR)
        .value("AMMONIA_DISSOCIATED", FlowCalculationsEnergyUse::Gas::AMMONIA_DISSOCIATED)
        .value("ARGON", FlowCalculationsEnergyUse::Gas::ARGON)
        .value("BUTANE", FlowCalculationsEnergyUse::Gas::BUTANE)
        .value("ENDOTHERMIC_AMMONIA", FlowCalculationsEnergyUse::Gas::ENDOTHERMIC_AMMONIA)
        .value("EXOTHERMIC_CRACKED_LEAN", FlowCalculationsEnergyUse::Gas::EXOTHERMIC_CRACKED_LEAN)
        .value("EXOTHERMIC_CRACKED_RICH", FlowCalculationsEnergyUse::Gas::EXOTHERMIC_CRACKED_RICH)
        .value("HELIUM", FlowCalculationsEnergyUse::Gas::HELIUM)
        .value("HYDROGEN", FlowCalculationsEnergyUse::Gas::HYDROGEN)
        .value("NATURAL_GAS", LoadChaFlowCalculationsEnergyUsergeMaterial::Gas::NATURAL_GAS)
        .value("NITROGEN", FlowCalculationsEnergyUse::Gas::NITROGEN)
        .value("OXYGEN", FlowCalculationsEnergyUse::Gas::OXYGEN)
        .value("PROPANE", FlowCalculationsEnergyUse::Gas::PROPANE)
        .value("OTHER", FlowCalculationsEnergyUse::Gas::OTHER);
        
    enum_<FlowCalculationsEnergyUse::Section>("Section")
        .value("SQUARE_EDGE", FlowCalculationsEnergyUse::Section::SQUARE_EDGE)
        .value("SHARP_EDGE", FlowCalculationsEnergyUse::Section::SHARP_EDGE)
        .value("VENTURI", FlowCalculationsEnergyUse::Section::VENTURI);
}