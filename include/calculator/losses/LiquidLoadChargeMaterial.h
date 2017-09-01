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

/** Moisture boiling point is 210°F */
#define MOISTURE_BOILING_POINT 210.0

/**
 * Liquid Load Charge Material class
 * Contains all properties of a liquid load charge material
 * Used to find the heat required for a liquid load charge material to be heated from the inlet temperature to the outlet temperature
 */
class LiquidLoadChargeMaterial {

public:

    /**
     * Constructor for liquid load/charge material with all inputs specified
     *
     * @param thermicReactionType LoadChargeMaterial::ThermicREactionType, Enumerated value for either endothermic or exothermic reactions
     * @param specificHeatLiquid double, Specific Heat of Liquid in Btu/(lb*°F)
     * @param vaporizingTemperature double, Vaporizing Temperature in °F
     * @param latentHeat double, Latent Heat of Vaporization in Btu/lb
     * @param specificHeatVapor double, Specific Heat of Vapor in Btu/(lb*°F)
     * @param chargeFeedRate double, Charge (Liquid)-Feed Rate in lb/hr
     * @param initialTemperature double, Initial Temperature in °F
     * @param dischargeTemperature double, Discharge Temperature in °F
     * @param percentVaporized double, Charge Liquid Vaporized  (% of Charge)
     * @param percentReacted double, Charge Liquid Reacted (% of Charge)
     * @param reactionHeat double, Heat of Reaction in Btu/lb
     * @param additionalHeat double, Additional Heat Required in btu/hr
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

    /**
     *
     * Gets the classification of thermic reaction type
     *
     * @return LoadChargeMaterial::ThermicReactionType, thermic reaction type
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    /**
     * Sets the classification of thermic reaction type
     *
     * @param thermicReactionType LoadChargeMaterial::ThermicaReactionType, thermic reaction type
     *
     * @return nothing
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    /**
     * Gets the specific heat of liquid
     *
     * @return double, specific heat in btu/(lb*°F)
     */
    double getSpecificHeatLiquid() const {
        return specificHeatLiquid_;
    }

    /**
     *
     * Sets the specific heat of liquid
     *
     * @param specificHeatLiquid double, specific heat of liquid in btu/(lb*°F)
     *
     * @return nothing
     */
    void setSpecificHeatLiquid(double specificHeatLiquid) {
        specificHeatLiquid_ = specificHeatLiquid;
    }

    /**
     *
     * Gets the vaporizing temperature
     *
     * @return double, vaporizing temperature in °F
     */
    double getVaporizingTemperature() const {
        return vaporizingTemperature_;
    }

    /**
     *
     * Sets the vaporizing temperature
     *
     * @param vaporizingTemperature double, vaporizing temperature in °F
     *
     * @return nothing
     */
    void setVaporizingTemperature(double vaporizingTemperature) {
        vaporizingTemperature_ = vaporizingTemperature;
    }

    /**
     *
     * Gets the latent heat of vaporization
     *
     * @return double, latent heat in btu/lb
     */
    double getLatentHeat() const {
        return latentHeat_;
    }

    /**
     *
     * Sets the latent heat of vaporization
     *
     * @param latentHeat double, latent heat in btu/lb
     *
     * @return nothing
     */
    void setLatentHeat(double latentHeat) {
        latentHeat_ = latentHeat;
    }

    /**
     *
     * Gets the specific heat of vapor
     *
     * @return double, specific heat of vapor in btu/(lb*°F)
     */
    double getSpecificHeatVapor() const {
        return specificHeatVapor_;
    }

    /**
     *
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
     *
     * Gets the charge (liquid)-feed rate
     *
     * @return ndouble, charge (liquid)-feed rate in lb/hr
     */
    double getChargeFeedRate() const {
        return chargeFeedRate_;
    }

    /**
     *
     * Sets the charge (liquid)-feed rate
     *
     * @param chargeFeedRate double, charge (liquid)-feed rate in lb/hr
     *
     * @return nothing
     */
    void setChargeFeedRate(double chargeFeedRate) {
        chargeFeedRate_ = chargeFeedRate;
    }

    /**
     *
     * Gets the initial temperature
     *
     * @return double, initial temperature in °F
     */
    double getInitialTemperature() const {
        return initialTemperature_;
    }

    /**
     *
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
     *
     * Sets the discharge temperature
     *
     * @return double, discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature_;
    }

    /**
     *
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
     *
     * Gets the percentage of charge vaporized
     *
     * @return double, % of charge vaporized
     */
    double getPercentVaporized() const {
        return percentVaporized_ * 100.0;
    }

    /**
     *
     * Sets the percentage of charge vaporized
     *
     * @param percentVaporized double, % of charge vaporized
     *
     * @return nothing
     */
    void setPercentVaporized(double percentVaporized) {
        percentVaporized_ = percentVaporized / 100.0;
    }

    /**
     *
     * Gets the percentage of charge reacted
     *
     * @return double, % of charge reacted
     */
    double getPercentReacted() const {
        return percentReacted_ * 100.0;
    }

    /**
     *
     * Sets the percentage of charge reacted
     *
     * @param percentReacted double, % of charge reacted
     *
     * @return nothing
     */
    void setPercentReacted(double percentReacted) {
        percentReacted_ = percentReacted / 100.0;
    }

    /**
     *
     * Gets the heat of reaction
     *
     * @return double, heat of reaction in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat_;
    }

    /**
     *
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
     *
     * Gets the additional heat
     *
     * @return double, additional heat as btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat_;
    }

    /**
     *
     * Sets the additional heat
     *
     * @param additionalHeat double, additional heat as btu/hr
     *
     * @return nothing
     */
    void setAdditionalHeat(double additionalHeat) {
        additionalHeat_ = additionalHeat;
    }

    /**
     *
     * Gets the name of the substance
     *
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance_;
    }

    /**
     *
     * Sets the naem of substance
     *
     * @param substance string&, substance name
     *
     * @return nothing
     */
    void setSubstance(std::string const & substance) {
        substance_ = substance;
    }

    /**
     *
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
     *
     * Gets the ID of material
     *
     * @return double, ID of material
     */
    double getID() const {
        return id;
    }

    /**
     * Sets the ID of material
     *
     * @param id int const, ID of material
     *
     * @return nothing
     */
    void setID(int const id) {
        this->id = id;
    }

    /**
     *
     * Gets the total heat required
     *
     * @return double, total heat required in btu/hr
     */
    double getTotalHeat();

    /**
     *bool operator
     */
    bool operator == (const LiquidLoadChargeMaterial& rhs) const
    {
        return specificHeatLiquid_ == rhs.specificHeatLiquid_ &&
               latentHeat_ == rhs.latentHeat_ &&
               specificHeatVapor_ == rhs.specificHeatVapor_ &&
               vaporizingTemperature_ == rhs.vaporizingTemperature_ &&
               substance_ == rhs.substance_ && id == rhs.id;
    }

    /**
     *bool operator
     *
     */
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
     * @param specificHeatLiquid Specific Heat of Liquid in Btu/(lb*°F)
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
