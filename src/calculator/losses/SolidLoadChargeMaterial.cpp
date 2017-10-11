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
    if (dischargeTemperature_ < HEAT_REQUIRED_TEMP) {
        //   (H_mv )=m_st×(%w_i )×〖(t〗_wo-t_si)
        hmv = chargeFeedRate_ * waterContentCharged_ * (waterVaporDischargeTemperature_ - initialTemperature_);
    } else {
        // (H_mv )=m_st×(%w_i )×(212-t_si )+m_st×(%w_i-%w_o )  ×[970+0.481×〖(t〗_wo-212)]
        hmv = (chargeFeedRate_ * waterContentCharged_ * (HEAT_REQUIRED_TEMP - initialTemperature_))
              + chargeFeedRate_ * (waterContentCharged_ - waterContentDischarged_)
                * (WATER_EVAPORATION + SPECIFIC_HEAT_WATER_VAPOR * (waterVaporDischargeTemperature_ - HEAT_REQUIRED_TEMP));
    }
    // (H_mr )=m_st×(%w_0 )×〖(t〗_wo-t_si)
    hmr = chargeFeedRate_ * waterContentDischarged_ * (waterVaporDischargeTemperature_ - initialTemperature_);

    // Heat required for solid
    double hs = 0.0;
    if (dischargeTemperature_ < meltingPoint_) {
        // (H_s)=m_st×(1-%w_i )×C_ps×(t_so-t_si)
        hs = chargeFeedRate_ * (1.0 - waterContentCharged_) * specificHeatSolid_ * (dischargeTemperature_ - initialTemperature_);
    } else {
        // (H_s )=m_st×(1-%w_i )×C_ps×(T_sm-t_si )+h_m+C_(pl ×) (t_so-T_sm)
        hs = chargeFeedRate_ * (1.0 - waterContentCharged_) * specificHeatSolid_ * (meltingPoint_ - initialTemperature_) + latentHeat_ + specificHeatLiquid_ * (dischargeTemperature_ - meltingPoint_);
    }

    double heatReaction = 0.0;
    if (thermicReactionType_ == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        heatReaction = chargeFeedRate_ * (1.0 - waterContentCharged_) * percentReacted_ * reactionHeat_;
    }

    // H_t=H_mv+H_mr+H_s±H_r
    totalHeat_ = hmv + hmr + hs + heatReaction + additionalHeat_;
    return totalHeat_;
}
