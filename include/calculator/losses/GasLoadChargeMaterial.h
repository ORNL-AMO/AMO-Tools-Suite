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

/**
 * Gas Load Charge Material class
 * Contains all properties of a gas load charge material
 * Used to find the heat required for a gas load charge material to be heated from the inlet temperature to the outlet temperature
 */
class GasLoadChargeMaterial {
public:

    /**
     * Constructor for the gas load/charge material with all inputs specified
     *
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     * @param specificHeatGas Specific Heat of Gas in Btu/(lb*°F)
     * @param feedRate Feed Rate for Gas Mixture in lb/hr
     * @param percentVapor Vapor in Gas Mixture (% of Total)
     * @param initialTemperature Initial Temperature in °F
     * @param dischargeTemperature Discharge Temperature in °F
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb*°F)
     * @param percentReacted Feed Gas Reacted (% of Total)
     * @param reactionHeat Heat of Reaction in Btu/lb
     * @param additionalHeat Additional Heat Required in Btu/hr
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

    /**
     * Gets the classification of thermic reaction type
     *
     * @return LoadChargeMaterial::ThermicReactionType, type of thermic reaction
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    /**
     * Sets the classification of thermic reaction type
     *
     * @param thermicReactionType LoadChargeMaterial::ThermicReactionType, type of thermic reaction
     *
     * @return nothing
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    /**
     * Gets the specific heat of gas
     *
     *
     * @return double, specific heat of gas in btu/(lb*°F)
     */
    double getSpecificHeatGas() const {
        return specificHeatGas_;
    }

    /**
     * Sets the specific heat of gas
     *
     * @param specificHeatGas double, specific heat of gas in btu/(lb*°F)
     *
     * @return nothing
     */
    void setSpecificHeatGas(double specificHeatGas) {
        specificHeatGas_ = specificHeatGas;
    }

    /**
     * Gets the feed rate for gas mixture
     *
     * @return double, feed rate for gas mixture in lb/hr
     */
    double getFeedRate() const {
        return feedRate_;
    }

    /**
     * Sets the feed rate for gas mixture
     *
     * @param feedRate double, feed rate for gas mixture in lb/hr
     *
     * @return nothing
     */
    void setFeedRate(double feedRate) {
        feedRate_ = feedRate;
    }

    /**
     * Gets the initial temperature
     *
     * @return double, initial temperature in °F
     */
    double getInitialTemperature() const {
        return initialTemperature_;
    }

    /**
     * Sets the initial temperature
     *
     * @param initialTemperature double, initial temperature in °F
     *
     * @return nothing
     */
    void setInitialTemperature(double initialTemperature) {
        initialTemperature_ = initialTemperature;
    }

    /**
     * Gets the discharge temperature
     *
     * @return double, discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature_;
    }

    /**
     * Sets the discharge temperature
     *
     * @param dischargeTemperature double, discharge temperature in °F
     *
     * @return nothing
     */
    void setDischargeTemperature(double dischargeTemperature) {
        dischargeTemperature_ = dischargeTemperature;
    }

    /**
     * Gets the specific heat of vapor
     *
     * @return double, specific heat of vapor in btu/(lb*°F)
     */
    double getSpecificHeatVapor() const {
        return specificHeatVapor_;
    }

    /**
     * Sets the specific heat of vapor
     *
     * @param specificHeatVapor double, specific heat of vapor in btu/(lb*°F)
     *
     * @return nothing
     */
    void setSpecificHeatVapor(double specificHeatVapor) {
        specificHeatVapor_ = specificHeatVapor;
    }

    /**
     * Gets the percentage of feed gas reacted
     *
     * @return double, charge gas reacted as % of DRY gas feed
     */
    double getPercentReacted() const {
        return percentReacted_ * 100.0;
    }

    /**
     * Sets the percentage of feed gas reacted
     *
     * @param percentReacted double, charge gas reacted as % of DRY gas feed
     *
     * @return nothing
     */
    void setPercentReacted(double percentReacted) {
        percentReacted_ = percentReacted / 100.0;
    }

    /**
     * Gets the heat of reaction
     *
     * @return double, heat of reaction in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat_;
    }

    /**
     * Sets the heat of reaction
     *
     * @param reactionHeat double, heat of reaction in btu/lb
     *
     * @return nothing
     */
    void setReactionHeat(double reactionHeat) {
        reactionHeat_ = reactionHeat;
    }

    /**
     * Gets the additional heat required
     *
     * @return double, additional heat required in btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat_;
    }

    /**
     * Sets the additional heat required
     *
     * @param additionalHeat double, additional heat required in btu/hr
     *
     * @return nothing
     */
    void setAdditionalHeat(double additionalHeat) {
        additionalHeat_ = additionalHeat;
    }

    /**
     * Gets the percentage of vapor in gas mixture
     *
     * @return double, vapor in gas mixture as %
     */
    double getPercentVapor() const {
        return percentVapor_ * 100.0;
    }

    /**
     * Sets the percentage of vapor in gas mixture
     *
     * @param percentVapor double, vapor in gas mixture as %
     *
     * @return nothing
     */
    void setPercentVapor(double percentVapor) {
        percentVapor_ = percentVapor / 100.0;
    }

    /**
     * Gets the name of substance
     *
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance_;
    }

    /**
     * Sets the name of substance
     *
     * @param substance string const&, name of substance
     *
     * @return nothing
     */
    void setSubstance(std::string substance) {
        substance_ = std::move(substance);
    }

    /**
     * Sets the total heat required
     *
     * @param totalHeat double, total heat required in btu/hr
     *
     * @return nothing
     */
    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    /**
     * Gets the ID of material
     *
     * @return std::size_t, ID of material
     */
    std::size_t getID() const {
        return this->id;
    }

    /**
     * Sets the ID of material
     *
     * @param id const int, ID of material
     *
     * @return nothing
     */
    void setID(const std::size_t id) {
        this->id = id;
    }

    /**
     * Gets the total heat required
     *
     * @return double, total heat required in btu/hr
     */
    double getTotalHeat();

    ///bool operator
    bool operator == (const GasLoadChargeMaterial& rhs) const
    {
        return specificHeatVapor_ == rhs.specificHeatVapor_ &&
               substance_ == rhs.substance_ && id == rhs.id;
    }

    ///bool operator
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
    std::size_t id = 0;
    // Out value
    double totalHeat_ = 0.0;

    friend class SQLite;

    /**
     * Constructor for the gas load/charge material with subset of inputs specified.
     *
     * @param substance Name of substance
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb*°F)
     *
     * */
    GasLoadChargeMaterial(
            std::string substance,
            double specificHeatVapor)
            : specificHeatVapor_(specificHeatVapor),
              substance_(std::move(substance))
    {}
};

#endif //AMO_SUITE_GASLOADCHARGEMATERIAL_H
