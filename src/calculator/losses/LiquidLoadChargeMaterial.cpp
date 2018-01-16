/**
 * @file
 * @brief Contains the implementation of the liquid load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/LiquidLoadChargeMaterial.h"

double LiquidLoadChargeMaterial::getTotalHeat() {
    double hliq = 0.0;
    if (dischargeTemperature < vaporizingTemperature) {
        // H_liq=m_li×C_pl×(t_lo-t_li )
        hliq = chargeFeedRate  * specificHeatLiquid * (dischargeTemperature - initialTemperature);
    } else {
        // H_liq=m_li×C_pl×(t_lv-t_li )+%lv×m_lt×[h_lv+C_pv  (t_lo-T_lv )]+(1-%lv)×C_pl (t_lo-t_lv)
        hliq = chargeFeedRate *
               (specificHeatLiquid * (vaporizingTemperature - initialTemperature)
                + percentVaporized * (latentHeat + specificHeatVapor * (dischargeTemperature - vaporizingTemperature))
                + (1 - percentVaporized) * specificHeatLiquid * (dischargeTemperature - vaporizingTemperature));
    }

    double heatReacted = 0.0;
    if (thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heatReacted = chargeFeedRate * percentReacted * reactionHeat;
    }
    totalHeat = hliq + heatReacted + additionalHeat;

    // Return the total net heat for the example case
    return totalHeat;
}