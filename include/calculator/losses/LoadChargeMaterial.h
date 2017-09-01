//
// Created by Accawi, Gina K. on 12/13/16.
//

#ifndef AMO_SUITE_LOADCHARGEMATERIAL_H
#define AMO_SUITE_LOADCHARGEMATERIAL_H

#define SPECIFIC_HEAT_WATER_VAPOR 0.481

/**
 * Load Charge Material class
 * Used to describe the reaction type (endothermic or exothermic)
 */
class LoadChargeMaterial {
public:

    ///Classifications of thermic reaction type
    enum class ThermicReactionType {
        ENDOTHERMIC,
        EXOTHERMIC,
        NONE
    };
};

#endif //AMO_SUITE_LOADCHARGEMATERIAL_H
