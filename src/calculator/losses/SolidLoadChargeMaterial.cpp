/**
 * @file
 * @brief Contains the implementation of the solid load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/SolidLoadChargeMaterial.h"

double SolidLoadChargeMaterial::getTotalHeat() {

    // Heat required for removal of moisture
    double hmv, hmr;
    if (dischargeTemperature < HEAT_REQUIRED_TEMP) {
        //   (H_mv )=m_st×(%w_i )×〖(t〗_wo-t_si)
        hmv = chargeFeedRate * waterContentCharged * (waterVaporDischargeTemperature - initialTemperature);
    } else {
        // (H_mv )=m_st×(%w_i )×(212-t_si )+m_st×(%w_i-%w_o )  ×[970+0.481×〖(t〗_wo-212)]
        hmv = (chargeFeedRate * waterContentCharged * (HEAT_REQUIRED_TEMP - initialTemperature))
              + chargeFeedRate * (waterContentCharged - waterContentDischarged)
                * (WATER_EVAPORATION + SPECIFIC_HEAT_WATER_VAPOR * (waterVaporDischargeTemperature - HEAT_REQUIRED_TEMP));
    }
    // (H_mr )=m_st×(%w_0 )×〖(t〗_wo-t_si)
    hmr = chargeFeedRate * waterContentDischarged * (waterVaporDischargeTemperature - initialTemperature);

    // Heat required for solid
    double hs = 0.0;
    if (dischargeTemperature < meltingPoint) {
        // (H_s)=m_st×(1-%w_i )×C_ps×(t_so-t_si)
        hs = chargeFeedRate * (1.0 - waterContentCharged) * specificHeatSolid * (dischargeTemperature - initialTemperature);
    } else {
        // (H_s )=m_st×(1-%w_i )×C_ps×(T_sm-t_si )+h_m+C_(pl ×) (t_so-T_sm)
        hs = chargeFeedRate * (1.0 - waterContentCharged)
             * (specificHeatSolid * (meltingPoint - initialTemperature)
                 + (latentHeat * chargeMelted) + specificHeatLiquid * (dischargeTemperature - meltingPoint) * (chargeMelted)
                 + (specificHeatSolid * (1 - chargeMelted) * (dischargeTemperature - meltingPoint)));
    }

    double heatReaction = 0.0;
    if (thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heatReaction = chargeFeedRate * (1.0 - waterContentCharged) * chargeReacted * reactionHeat;
    }

    // H_t=H_mv+H_mr+H_s±H_r
    totalHeat = hmv + hmr + hs + heatReaction + additionalHeat;
    return totalHeat;
}
