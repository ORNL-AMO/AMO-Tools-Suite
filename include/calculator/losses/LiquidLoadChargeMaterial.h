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

#include <string>
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

    std::string getSubstance() const {
        return substance_;
    }

    void setSubstance(std::string const & substance) {
        substance_ = substance;
    }

    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    double getID() const {
        return id;
    }

    void setID(int const id) {
        this->id = id;
    }

    double getTotalHeat();

    bool operator == (const LiquidLoadChargeMaterial& rhs) const
    {
        return specificHeatLiquid_ == rhs.specificHeatLiquid_ &&
               latentHeat_ == rhs.latentHeat_ &&
               specificHeatVapor_ == rhs.specificHeatVapor_ &&
               vaporizingTemperature_ == rhs.vaporizingTemperature_ &&
               substance_ == rhs.substance_ && id == rhs.id;
    }

    bool operator != (const LiquidLoadChargeMaterial& rhs) const
    {
        return !(*this == rhs);
    }

private:
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType_ = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatLiquid_ = 0.0;
    double vaporizingTemperature_ = 0.0;
    double latentHeat_ = 0.0;
    double specificHeatVapor_ = 0.0;
    double chargeFeedRate_ = 0.0;
    double initialTemperature_ = 0.0;
    double dischargeTemperature_ = 0.0;
    double percentVaporized_ = 0.0;
    double percentReacted_ = 0.0;
    double reactionHeat_ = 0.0;
    double additionalHeat_ = 0.0;
    std::string substance_ = "Unknown";
    int id = 0;
    // Out value
    double totalHeat_ = 0.0;

    friend class SQLite;

    /**
     * Constructor for liquid load/charge material with subset of inputs specified.
     *
     * @param substance Name of substance
     * @param specificHeatLiquid Specific Heat of Liquid in Btu/(lb-°F)
     * @param vaporizingTemperature Vaporizing Temperature in °F
     * @param latentHeat Latent Heat of Vaporization in Btu/lb
     *
     * */
    LiquidLoadChargeMaterial(
            std::string const & substance,
            double specificHeatLiquid,
            double vaporizingTemperature,
            double latentHeat,
            double specificHeatVapor)
            : specificHeatLiquid_(specificHeatLiquid),
              vaporizingTemperature_(vaporizingTemperature),
              latentHeat_(latentHeat),
              specificHeatVapor_(specificHeatVapor),
              substance_(substance)
    {}
};
#endif //AMO_SUITE_LIQUIDLOADCHARGEMATERIAL_H
