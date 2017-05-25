/**
 * @file
 * @brief Calculator for total heat of gas load/charge material
 *
 * This contains the inputs for calculating a gas load/charge material's
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_GASLOADCHARGEMATERIAL_H
#define AMO_SUITE_GASLOADCHARGEMATERIAL_H

#include <string>
#include "LoadChargeMaterial.h"

class GasLoadChargeMaterial {
public:

    /**
     * Constructor for the gas load/charge material with all inputs specified
     *
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     * @param specificHeatGas Specific Heat of Gas in Btu/(lb- °F)
     * @param feedRate Feed Rate for Gas Mixture
     * @param percentVapor Vapor in Gas Mixture (% of Total)
     * @param initialTemperature Initial Temperature in °F
     * @param dischargeTemperature Discharge Temperature in °F
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb- °F)
     * @param percentReacted Feed Gas Reacted (% of Total)
     * @param reactionHeat Heat of Reaction in Btu/lb
     * @param additionalHeat Additional Heat Required in Btu/h
     *
     * */
    GasLoadChargeMaterial(
            LoadChargeMaterial::ThermicReactionType thermicReactionType,
            double specificHeatGas,
            double feedRate,
            double percentVapor,
            double initialTemperature,
            double dischargeTemperature,
            double specificHeatVapor,
            double percentReacted,
            double reactionHeat,
            double additionalHeat)
            : thermicReactionType_(thermicReactionType),
              specificHeatGas_(specificHeatGas),
              feedRate_(feedRate),
              percentVapor_(percentVapor / 100.0),
              initialTemperature_(initialTemperature),
              dischargeTemperature_(dischargeTemperature),
              specificHeatVapor_(specificHeatVapor),
              percentReacted_(percentReacted / 100.0),
              reactionHeat_(reactionHeat),
              additionalHeat_(additionalHeat)
    {}

    GasLoadChargeMaterial() = default;

    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    double getSpecificHeatGas() const {
        return specificHeatGas_;
    }

    void setSpecificHeatGas(double specificHeatGas) {
        specificHeatGas_ = specificHeatGas;
    }

    double getFeedRate() const {
        return feedRate_;
    }

    void setFeedRate(double feedRate) {
        feedRate_ = feedRate;
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

    double getSpecificHeatVapor() const {
        return specificHeatVapor_;
    }

    void setSpecificHeatVapor(double specificHeatVapor) {
        specificHeatVapor_ = specificHeatVapor;
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

    double getPercentVapor() const {
        return percentVapor_ * 100.0;
    }

    void setPercentVapor(double percentVapor) {
        percentVapor_ = percentVapor / 100.0;
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

    double getID() {
        return this->id;
    }

    void setID(const int id) {
        this->id = id;
    }

    double getTotalHeat();

    bool operator == (const GasLoadChargeMaterial& rhs) const
    {
        return specificHeatVapor_ == rhs.specificHeatVapor_ &&
               substance_ == rhs.substance_ && id == rhs.id;
    }

    bool operator != (const GasLoadChargeMaterial& rhs) const
    {
        return !(*this == rhs);
    }

private:
    LoadChargeMaterial::ThermicReactionType thermicReactionType_ = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatGas_ = 0.0;
    double feedRate_ = 0.0;
    double percentVapor_ = 0.0;
    double initialTemperature_ = 0.0;
    double dischargeTemperature_ = 0.0;
    double specificHeatVapor_ = 0.0;
    double percentReacted_ = 0.0;
    double reactionHeat_ = 0.0;
    double additionalHeat_ = 0.0;
    std::string substance_ = "Unknown";
    double id = 0;
    // Out value
    double totalHeat_ = 0.0;

    friend class SQLite;

    /**
     * Constructor for the gas load/charge material with subset of inputs specified.
     *
     * @param substance Name of substance
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb- °F)
     *
     * */
    GasLoadChargeMaterial(
            std::string const & substance,
            double specificHeatVapor)
            : specificHeatVapor_(specificHeatVapor),
              substance_(substance)
    {}
};

#endif //AMO_SUITE_GASLOADCHARGEMATERIAL_H
