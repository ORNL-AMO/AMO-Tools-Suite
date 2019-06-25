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

/**
 * Liquid Load Charge Material class
 * Contains all properties of a liquid load charge material
 * Used to find the heat required for a liquid load charge material to be heated from the inlet temperature to the outlet temperature
 */
class LiquidLoadChargeMaterial {

public:

    /**
     * Constructor for liquid load/charge material with all inputs specified
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
     * */

    LiquidLoadChargeMaterial(
            const LoadChargeMaterial::ThermicReactionType thermicReactionType,
            const double specificHeatLiquid,
            const double vaporizingTemperature,
            const double latentHeat,
            const double specificHeatVapor,
            const double chargeFeedRate,
            const double initialTemperature,
            const double dischargeTemperature,
            const double percentVaporized,
            const double percentReacted,
            const double reactionHeat,
            const double additionalHeat)
            : thermicReactionType(thermicReactionType),
              specificHeatLiquid(specificHeatLiquid),
              vaporizingTemperature(vaporizingTemperature),
              latentHeat(latentHeat),
              specificHeatVapor(specificHeatVapor),
              chargeFeedRate(chargeFeedRate),
              initialTemperature(initialTemperature),
              dischargeTemperature(dischargeTemperature),
              percentVaporized(percentVaporized / 100.0),
              percentReacted(percentReacted / 100.0),
              reactionHeat(reactionHeat),
              additionalHeat(additionalHeat)
    {}

    LiquidLoadChargeMaterial() = default;

    /**
     * Gets the classification of thermic reaction type
     * @return LoadChargeMaterial::ThermicReactionType, thermic reaction type
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType;
    }

    /**
     * Sets the classification of thermic reaction type
     * @param thermicReactionType LoadChargeMaterial::ThermicaReactionType, thermic reaction type
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        this->thermicReactionType = thermicReactionType;
    }

    /**
     * Gets the specific heat of liquid
     * @return double, specific heat in btu/(lb*°F)
     */
    double getSpecificHeatLiquid() const {
        return specificHeatLiquid;
    }

    /**
     * Sets the specific heat of liquid
     * @param specificHeatLiquid double, specific heat of liquid in btu/(lb*°F)
     */
    void setSpecificHeatLiquid(const double specificHeatLiquid) {
        this->specificHeatLiquid = specificHeatLiquid;
    }

    /**
     * Gets the vaporizing temperature
     * @return double, vaporizing temperature in °F
     */
    double getVaporizingTemperature() const {
        return vaporizingTemperature;
    }

    /**
     * Sets the vaporizing temperature
     * @param vaporizingTemperature double, vaporizing temperature in °F
     */
    void setVaporizingTemperature(const double vaporizingTemperature) {
        this->vaporizingTemperature = vaporizingTemperature;
    }

    /**
     * Gets the latent heat of vaporization
     * @return double, latent heat in btu/lb
     */
    double getLatentHeat() const {
        return latentHeat;
    }

    /**
     * Sets the latent heat of vaporization
     * @param latentHeat double, latent heat in btu/lb
     */
    void setLatentHeat(const double latentHeat) {
        this->latentHeat = latentHeat;
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
    void setSpecificHeatVapor(const double specificHeatVapor) {
        this->specificHeatVapor = specificHeatVapor;
    }

    /**
     * Gets the charge (liquid)-feed rate
     * @return ndouble, charge (liquid)-feed rate in lb/hr
     */
    double getChargeFeedRate() const {
        return chargeFeedRate;
    }

    /**
     * Sets the charge (liquid)-feed rate
     * @param chargeFeedRate double, charge (liquid)-feed rate in lb/hr
     */
    void setChargeFeedRate(const double chargeFeedRate) {
        this->chargeFeedRate = chargeFeedRate;
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
    void setInitialTemperature(const double initialTemperature) {
        this->initialTemperature = initialTemperature;
    }

    /**
     * Sets the discharge temperature
     * @return double, discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature;
    }

    /**
     * Sets the discharge temperature
     * @param dischargeTemperature double, discharge temperature in °F
     */
    void setDischargeTemperature(const double dischargeTemperature) {
        this->dischargeTemperature = dischargeTemperature;
    }

    /**
     * Gets the percentage of charge vaporized
     * @return double, % of charge vaporized
     */
    double getPercentVaporized() const {
        return percentVaporized * 100.0;
    }

    /**
     * Sets the percentage of charge vaporized
     * @param percentVaporized double, % of charge vaporized
     */
    void setPercentVaporized(const double percentVaporized) {
        this->percentVaporized = percentVaporized / 100.0;
    }

    /**
     * Gets the percentage of charge reacted
     * @return double, % of charge reacted
     */
    double getPercentReacted() const {
        return percentReacted * 100.0;
    }

    /**
     * Sets the percentage of charge reacted
     * @param percentReacted double, % of charge reacted
     */
    void setPercentReacted(const double percentReacted) {
        this->percentReacted = percentReacted / 100.0;
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
    void setReactionHeat(const double reactionHeat) {
        this->reactionHeat = reactionHeat;
    }

    /**
     * Gets the additional heat
     * @return double, additional heat as btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat;
    }

    /**
     * Sets the additional heat
     * @param additionalHeat double, additional heat as btu/hr
     */
    void setAdditionalHeat(const double additionalHeat) {
        this->additionalHeat = additionalHeat;
    }

    /**
     * Gets the name of the substance
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance;
    }

    /**
     * Sets the name of substance
     * @param substance string&, substance name
     */
    void setSubstance(std::string const & substance) {
        this->substance = substance;
    }

    /**
     * Gets the ID of material
     * @return int, ID of material
     */
    int getID() const {
        return id;
    }

    /**
     * Sets the ID of material
     * @param id int const, ID of material
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
    double getTotalHeat() {
        double hliq;
        if (dischargeTemperature < vaporizingTemperature) {
            // H_liq=m_li×C_pl×(t_lo-t_li )
            hliq = chargeFeedRate  * specificHeatLiquid * (dischargeTemperature - initialTemperature);
        } else {
            // H_liq=m_li×C_pl×(t_lv-t_li )+%lv×m_lt×[h_lv+C_pv  (t_lo-T_lv )]+(1-%lv)×C_pl (t_lo-t_lv)
            hliq = chargeFeedRate *
                   (specificHeatLiquid * (vaporizingTemperature - initialTemperature)
                    + percentVaporized * (latentHeat + specificHeatVapor * (dischargeTemperature - vaporizingTemperature))
                    + (1 - percentVaporized) * specificHeatLiquid * (dischargeTemperature - vaporizingTemperature));
        }

        double heatReacted = 0.0;
        if (thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
            heatReacted = chargeFeedRate * percentReacted * reactionHeat;
        }
        totalHeat = hliq + heatReacted + additionalHeat;
        return totalHeat;
    }

    /**
     *bool operator
     */
    bool operator == (const LiquidLoadChargeMaterial& rhs) const
    {
        return specificHeatLiquid == rhs.specificHeatLiquid &&
               latentHeat == rhs.latentHeat &&
               specificHeatVapor == rhs.specificHeatVapor &&
               vaporizingTemperature == rhs.vaporizingTemperature &&
               substance == rhs.substance && id == rhs.id;
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
    LoadChargeMaterial::ThermicReactionType thermicReactionType = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatLiquid = 0.0;
    double vaporizingTemperature = 0.0;
    double latentHeat = 0.0;
    double specificHeatVapor = 0.0;
    double chargeFeedRate = 0.0;
    double initialTemperature = 0.0;
    double dischargeTemperature = 0.0;
    double percentVaporized = 0.0;
    double percentReacted = 0.0;
    double reactionHeat = 0.0;
    double additionalHeat = 0.0;
    std::string substance = "Unknown";
    int id = 0;
    // Out value
    double totalHeat = 0.0;

    friend class SQLite;

    /**
     * Constructor for liquid load/charge material with subset of inputs specified.
     * @param substance Name of substance
     * @param specificHeatLiquid Specific Heat of Liquid in Btu/(lb*°F)
     * @param vaporizingTemperature Vaporizing Temperature in °F
     * @param latentHeat Latent Heat of Vaporization in Btu/lb
     * */
    LiquidLoadChargeMaterial(
            std::string substance,
            double specificHeatLiquid,
            double latentHeat,
            double specificHeatVapor,
            double vaporizingTemperature
    )
            : specificHeatLiquid(specificHeatLiquid),
              vaporizingTemperature(vaporizingTemperature),
              latentHeat(latentHeat),
              specificHeatVapor(specificHeatVapor),
              substance(std::move(substance))
    {}
};
#endif //AMO_SUITE_LIQUIDLOADCHARGEMATERIAL_H
