/**
 * @file
 * @brief Calculator for total heat of liquid load/charge material
 *
 * This contains the inputs for calculating a liquid load/charge material's
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_LIQUIDLOADCHARGEMATERIAL_H
#define AMO_SUITE_LIQUIDLOADCHARGEMATERIAL_H

#include "LoadChargeMaterial.h"
#define MOISTURE_BOILING_POINT 210.0

class LiquidLoadChargeMaterial {

public:

    /**
     * Constructor for liquid load/charge material with all inputs specified
     *
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     * @param specificHeatLiquid Specific Heat of Liquid in Btu/(lb-°F)
     * @param vaporizingTemperature Vaporizing Temperature in °F
     * @param latentHeat Latent Heat of Vaporization in Btu/lb
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb-°F)
     * @param chargeFeedRate Charge (Liquid)-Feed Rate in lb/h
     * @param initialTemperature Initial Temperature in °F
     * @param dischargeTemperature Discharge Temperature in °F
     * @param percentVaporized Charge Liquid Vaporized  (% of Charge)
     * @param percentReacted Charge Liquid Reacted (% of Charge)
     * @param reactionHeat Heat of Reaction in Btu/lb
     * @param additionalHeat Additional Heat Required in %
     *
     * */

    LiquidLoadChargeMaterial(
            LoadChargeMaterial::ThermicReactionType thermicReactionType,
            double specificHeatLiquid,
            double vaporizingTemperature,
            double latentHeat,
            double specificHeatVapor,
            double chargeFeedRate,
            double initialTemperature,
            double dischargeTemperature,
            double percentVaporized,
            double percentReacted,
            double reactionHeat,
            double additionalHeat)
            : thermicReactionType_(thermicReactionType),
              specificHeatLiquid_(specificHeatLiquid),
              vaporizingTemperature_(vaporizingTemperature),
              latentHeat_(latentHeat),
              specificHeatVapor_(specificHeatVapor),
              chargeFeedRate_(chargeFeedRate),
              initialTemperature_(initialTemperature),
              dischargeTemperature_(dischargeTemperature),
              percentVaporized_(percentVaporized / 100.0),
              percentReacted_(percentReacted / 100.0),
              reactionHeat_(reactionHeat),
              additionalHeat_(additionalHeat)
    {}

    LiquidLoadChargeMaterial() = default;

    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    double getSpecificHeatLiquid() const {
        return specificHeatLiquid_;
    }

    void setSpecificHeatLiquid(double specificHeatLiquid) {
        specificHeatLiquid_ = specificHeatLiquid;
    }

    double getVaporizingTemperature() const {
        return vaporizingTemperature_;
    }

    void setVaporizingTemperature(double vaporizingTemperature) {
        vaporizingTemperature_ = vaporizingTemperature;
    }

    double getLatentHeat() const {
        return latentHeat_;
    }

    void setLatentHeat(double latentHeat) {
        latentHeat_ = latentHeat;
    }

    double getSpecificHeatVapor() const {
        return specificHeatVapor_;
    }

    void setSpecificHeatVapor(double specificHeatVapor) {
        specificHeatVapor_ = specificHeatVapor;
    }

    double getChargeFeedRate() const {
        return chargeFeedRate_;
    }

    void setChargeFeedRate(double chargeFeedRate) {
        chargeFeedRate_ = chargeFeedRate;
    }

    double getInitialTemperature() const {
        return initialTemperature_;
    }

    void setInitialTemperature(double initialTemperature) {
        initialTemperature_ = initialTemperature;
    }

    double getDischargeTemperature() const {
        return dischargeTemperature_;
    }

    void setDischargeTemperature(double dischargeTemperature) {
        dischargeTemperature_ = dischargeTemperature;
    }

    double getPercentVaporized() const {
        return percentVaporized_ * 100.0;
    }

    void setPercentVaporized(double percentVaporized) {
        percentVaporized_ = percentVaporized / 100.0;
    }

    double getPercentReacted() const {
        return percentReacted_ * 100.0;
    }

    void setPercentReacted(double percentReacted) {
        percentReacted_ = percentReacted / 100.0;
    }

    double getReactionHeat() const {
        return reactionHeat_;
    }

    void setReactionHeat(double reactionHeat) {
        reactionHeat_ = reactionHeat;
    }

    double getAdditionalHeat() const {
        return additionalHeat_;
    }

    void setAdditionalHeat(double additionalHeat) {
        additionalHeat_ = additionalHeat;
    }

    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }
    double getTotalHeat();

private:
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType_;
    double specificHeatLiquid_;
    double vaporizingTemperature_;
    double latentHeat_;
    double specificHeatVapor_;
    double chargeFeedRate_;
    double initialTemperature_;
    double dischargeTemperature_;
    double percentVaporized_;
    double percentReacted_;
    double reactionHeat_;
    double additionalHeat_;
    // Out value
    double totalHeat_;
};
#endif //AMO_SUITE_LIQUIDLOADCHARGEMATERIAL_H
