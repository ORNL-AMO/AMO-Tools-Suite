/**
 * @file
 * @brief Contains the implementation of the liquid load/charge material total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#include "calculator/LiquidLoadChargeMaterial.h"

double LiquidLoadChargeMaterial::getTotalHeat() {
    double hliq = 0.0;
    if (this->dischargeTemperature_ < this->vaporizingTemperature_) {
        // H_liq=m_li×C_pl×(t_lo-t_li )
        hliq = this->chargeFeedRate_  * this->specificHeatLiquid_ * (this->dischargeTemperature_ - this->initialTemperature_);
    } else {
        // H_liq=m_li×C_pl×(t_lv-t_li )+%lv×m_lt×[h_lv+C_pv  (t_lo-T_lv )]+(1-%lv)×C_pl (t_lo-t_lv)
        hliq = this->chargeFeedRate_ * this->specificHeatLiquid_ * (this->vaporizingTemperature_ - this->initialTemperature_) + percentVaporized_ * this->chargeFeedRate_ * (this->latentHeat_ + this->specificHeatVapor_ * (this->dischargeTemperature_ - this->vaporizingTemperature_)) + (1 - this->percentVaporized_) * this->specificHeatLiquid_ * (this->dischargeTemperature_ - this->vaporizingTemperature_);
    }
    double hr = 0.0;
    // (H_react )=m_li×%react×h_react
    hr = this->chargeFeedRate_ * this->percentReacted_ * this->reactionHeat_;
    double hex = 0.0;
    if (this->thermicReactionType_ == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
        hex = this->additionalHeat_ * - 1.0;
    } else {
        hex = this->additionalHeat_;
    }
    totalHeat_ = hliq + hr + hex;
    // Return the total net heat for the example case
    return totalHeat_;
}