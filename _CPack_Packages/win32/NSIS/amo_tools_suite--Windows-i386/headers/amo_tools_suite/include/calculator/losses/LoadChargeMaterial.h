#ifndef AMO_SUITE_LOADCHARGEMATERIAL_H
#define AMO_SUITE_LOADCHARGEMATERIAL_H

/**
 * Load Charge Material class
 * Used to describe the reaction type (endothermic or exothermic)
 */
namespace LoadChargeMaterial {
    ///Classifications of thermic reaction type
    enum class ThermicReactionType {
        ENDOTHERMIC,
        EXOTHERMIC,
        NONE
    };
}

#endif //AMO_SUITE_LOADCHARGEMATERIAL_H
