/**
 * @file
 * @brief Contains the implementation of the solid load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/SolidLoadChargeMaterial.h"

double SolidLoadChargeMaterial::getTotalHeat() {

    // Heat required for removal of moisture
    double hmv = 0.0;
    double hmr = 0.0;
    if (this->dischargeTemperature_ < HEAT_REQUIRED_TEMP) {
        //   (H_mv )=m_st×(%w_i )×〖(t〗_wo-t_si)
        hmv = this->chargeFeedRate_ * this->waterContentCharged_ * (this->waterVaporDischargeTemperature_ - this->initialTemperature_);
    } else {
        // (H_mv )=m_st×(%w_i )×(212-t_si )+m_st×(%w_i-%w_o )  ×[970+0.481×〖(t〗_wo-212)]
        hmv = (this->chargeFeedRate_ * this->waterContentCharged_ * (HEAT_REQUIRED_TEMP - this->initialTemperature_)) + this->chargeFeedRate_ * (this->waterContentCharged_ - this->waterContentDischarged_) * (WATER_EVAPORATION + SPECIFIC_HEAT_WATER_VAPOR * (this->waterVaporDischargeTemperature_ - HEAT_REQUIRED_TEMP));
    }
    // (H_mr )=m_st×(%w_0 )×〖(t〗_wo-t_si)
    hmr = this->chargeFeedRate_ * this->waterContentDischarged_ * (this->waterVaporDischargeTemperature_ - this->initialTemperature_);

    // Heat required for solid
    double hs = 0.0;
    if (this->dischargeTemperature_ < this->meltingPoint_) {
        // (H_s)=m_st×(1-%w_i )×C_ps×(t_so-t_si)
        hs = this->chargeFeedRate_ * (1.0 - this->waterContentCharged_) * this->specificHeatSolid_ * (this->dischargeTemperature_ - this->initialTemperature_);
    } else {
        // (H_s )=m_st×(1-%w_i )×C_ps×(T_sm-t_si )+h_m+C_(pl ×) (t_so-T_sm)
        hs = this->chargeFeedRate_ * (1.0 - this->waterContentCharged_) * this->specificHeatSolid_ * (this->meltingPoint_ - this->initialTemperature_) + this->latentHeat_ + this->specificHeatLiquid_ * (this->dischargeTemperature_ - this->meltingPoint_);
    }

    // Heat of reaction
    double hr = 0.0;
    double percentReacted = this->percentReacted_;
    if (this->thermicReactionType_ == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        percentReacted = this->reactionHeat_;
        hr = this->chargeFeedRate_ * ( 1.0 - this->waterContentCharged_) * (percentReacted) * (this->reactionHeat_);
    }
    // H_r=m_st (1-%w_i )×(%react)×h_react
    // Hr ignored when exothermic
    //hr = this->chargeFeedRate_ * ( 1.0 - this->waterContentCharged_) * (percentReacted) * (this->reactionHeat_);
    // H_t=H_mv+H_mr+H_s±H_r
    totalHeat_ = hmv + hmr + hs + hr + this->additionalHeat_;
    return totalHeat_;

}

