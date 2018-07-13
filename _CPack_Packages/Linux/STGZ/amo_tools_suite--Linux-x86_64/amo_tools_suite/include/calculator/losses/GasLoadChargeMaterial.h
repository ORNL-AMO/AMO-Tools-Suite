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
     * */
    GasLoadChargeMaterial(
            const LoadChargeMaterial::ThermicReactionType thermicReactionType,
            const double specificHeatGas,
            const double feedRate,
            const double percentVapor,
            const double initialTemperature,
            const double dischargeTemperature,
            const double specificHeatVapor,
            const double percentReacted,
            const double reactionHeat,
            const double additionalHeat)
            : thermicReactionType(thermicReactionType),
              specificHeatGas(specificHeatGas),
              feedRate(feedRate),
              percentVapor(percentVapor / 100.0),
              initialTemperature(initialTemperature),
              dischargeTemperature(dischargeTemperature),
              specificHeatVapor(specificHeatVapor),
              percentReacted(percentReacted / 100.0),
              reactionHeat(reactionHeat),
              additionalHeat(additionalHeat)
    {}

    GasLoadChargeMaterial() = default;

    /**
     * Gets the classification of thermic reaction type
     * @return LoadChargeMaterial::ThermicReactionType, type of thermic reaction
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType;
    }

    /**
     * Sets the classification of thermic reaction type
     * @param thermicReactionType LoadChargeMaterial::ThermicReactionType, type of thermic reaction
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        this->thermicReactionType = thermicReactionType;
    }

    /**
     * Gets the specific heat of gas
     * @return double, specific heat of gas in btu/(lb*°F)
     */
    double getSpecificHeatGas() const {
        return specificHeatGas;
    }

    /**
     * Sets the specific heat of gas
     * @param specificHeatGas double, specific heat of gas in btu/(lb*°F)
     */
    void setSpecificHeatGas(double specificHeatGas) {
        this->specificHeatGas = specificHeatGas;
    }

    /**
     * Gets the feed rate for gas mixture
     * @return double, feed rate for gas mixture in lb/hr
     */
    double getFeedRate() const {
        return feedRate;
    }

    /**
     * Sets the feed rate for gas mixture
     * @param feedRate double, feed rate for gas mixture in lb/hr
     */
    void setFeedRate(double feedRate) {
        this->feedRate = feedRate;
    }

    /**
     * Gets the initial temperature
     * @return double, initial temperature in °F
     */
    double getInitialTemperature() const {
        return initialTemperature;
    }

    /**
     * Sets the initial temperature
     * @param initialTemperature double, initial temperature in °F
     */
    void setInitialTemperature(double initialTemperature) {
        this->initialTemperature = initialTemperature;
    }

    /**
     * Gets the discharge temperature
     * @return double, discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature;
    }

    /**
     * Sets the discharge temperature
     * @param dischargeTemperature double, discharge temperature in °F
     */
    void setDischargeTemperature(double dischargeTemperature) {
        this->dischargeTemperature = dischargeTemperature;
    }

    /**
     * Gets the specific heat of vapor
     * @return double, specific heat of vapor in btu/(lb*°F)
     */
    double getSpecificHeatVapor() const {
        return specificHeatVapor;
    }

    /**
     * Sets the specific heat of vapor
     * @param specificHeatVapor double, specific heat of vapor in btu/(lb*°F)
     */
    void setSpecificHeatVapor(double specificHeatVapor) {
        this->specificHeatVapor = specificHeatVapor;
    }

    /**
     * Gets the percentage of feed gas reacted
     * @return double, charge gas reacted as % of DRY gas feed
     */
    double getPercentReacted() const {
        return percentReacted * 100.0;
    }

    /**
     * Sets the percentage of feed gas reacted
     * @param percentReacted double, charge gas reacted as % of DRY gas feed
     */
    void setPercentReacted(double percentReacted) {
        percentReacted = percentReacted / 100.0;
    }

    /**
     * Gets the heat of reaction
     * @return double, heat of reaction in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat;
    }

    /**
     * Sets the heat of reaction
     * @param reactionHeat double, heat of reaction in btu/lb
     */
    void setReactionHeat(double reactionHeat) {
        this->reactionHeat = reactionHeat;
    }

    /**
     * Gets the additional heat required
     * @return double, additional heat required in btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat;
    }

    /**
     * Sets the additional heat required
     * @param additionalHeat double, additional heat required in btu/hr
     */
    void setAdditionalHeat(double additionalHeat) {
        this->additionalHeat = additionalHeat;
    }

    /**
     * Gets the percentage of vapor in gas mixture
     * @return double, vapor in gas mixture as %
     */
    double getPercentVapor() const {
        return percentVapor * 100.0;
    }

    /**
     * Sets the percentage of vapor in gas mixture
     * @param percentVapor double, vapor in gas mixture as %
     */
    void setPercentVapor(double percentVapor) {
        percentVapor = percentVapor / 100.0;
    }

    /**
     * Gets the name of substance
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance;
    }

    /**
     * Sets the name of substance
     * @param substance string , name of substance
     */
    void setSubstance(std::string substance) {
        this->substance = std::move(substance);
    }

    /**
     * Gets the ID of material
     * @return int, ID of material
     */
    int getID() const {
        return this->id;
    }

    /**
     * Sets the ID of material
     * @param id const int, ID of material
     */
    void setID(const int id) {
        this->id = id;
    }

    /**
     * Gets the total heat required
     * @return double, total heat required in btu/hr
     */
    double getTotalHeat() {
        const double tempDiff = dischargeTemperature - initialTemperature;
        const double hgas = (1.0 - percentVapor) * feedRate * specificHeatGas * tempDiff;
        const double hvapor = percentVapor * feedRate * specificHeatVapor * tempDiff;

        // heatReact ignored when exothermic
        double heatReact = 0.0;
        if (thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
            heatReact =feedRate * percentReacted * reactionHeat;
        }

        totalHeat =  hgas + hvapor + heatReact + additionalHeat;
        return totalHeat;
    }

    ///bool operator
    bool operator == (const GasLoadChargeMaterial& rhs) const
    {
        return specificHeatVapor == rhs.specificHeatVapor &&
               substance == rhs.substance && id == rhs.id;
    }

    ///bool operator
    bool operator != (const GasLoadChargeMaterial& rhs) const
    {
        return !(*this == rhs);
    }

private:
    LoadChargeMaterial::ThermicReactionType thermicReactionType = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatGas = 0.0;
    double feedRate = 0.0;
    double percentVapor = 0.0;
    double initialTemperature = 0.0;
    double dischargeTemperature = 0.0;
    double specificHeatVapor = 0.0;
    double percentReacted = 0.0;
    double reactionHeat = 0.0;
    double additionalHeat = 0.0;
    std::string substance = "Unknown";
    int id = 0;
    // Out value
    double totalHeat = 0.0;

    friend class SQLite;

    /**
     * Constructor for the gas load/charge material with subset of inputs specified.
     * @param substance Name of substance
     * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb*°F)
     * */
    GasLoadChargeMaterial(
            std::string substance,
            double specificHeatVapor)
            : specificHeatVapor(specificHeatVapor),
              substance(std::move(substance))
    {}
};

#endif //AMO_SUITE_GASLOADCHARGEMATERIAL_H
