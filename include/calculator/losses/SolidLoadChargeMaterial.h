/**
 * @file
 * @brief Calculator for total heat of solid load/charge material
 *
 * This contains the inputs for calculating a solid load/charge material's
 * total heat.
 *
 * @author Mark Adams
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
#define AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H

#include <string>
#include "LoadChargeMaterial.h"

#define WATER_EVAPORATION 970.0
#define HEAT_REQUIRED_TEMP 212.0


class SolidLoadChargeMaterial {
public:

    /**
 * Constructor for the solid load/charge material with all inputs specified.
 *
 * @param thermicReactionType LoadChargeMaterial::ThermicReactionType, Enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
 * @param latentHeat double, Latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
 * @param meltingPoint double, The melting point of the material in °F
 * @param chargeFeedRate double, Charge (wet)-feed rate in lb/hr
 * @param waterContentCharged double, Water content as charged (%)
 * @param waterContentDischarged double, Water content as discharged (%)
 * @param initialTemperature double, Initial temperature in °F
 * @param dischargeTemperature double, Charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature double, Water vapor discharge temperature in °F
 * @param chargeMelted double, Charge melted (% of dry charge)
 * @param chargedReacted double, Charge Reacted (% of dry charge) in %
 * @param reactionHeat double, Heat of reaction in Btu/lb
 * @param additionalHeat double, Additional heat required in Btu/h
 *
 * */
    SolidLoadChargeMaterial(
            LoadChargeMaterial::ThermicReactionType thermicReactionType,
            double specificHeatSolid,
            double latentHeat,
            double specificHeatLiquid,
            double meltingPoint,
            double chargeFeedRate,
            double waterContentCharged,
            double waterContentDischarged,
            double initialTemperature,
            double dischargeTemperature,
            double waterVaporDischargeTemperature,
            double chargeMelted,
            double chargedReacted,
            double reactionHeat,
            double additionalHeat
    ) : thermicReactionType_ (thermicReactionType),
        specificHeatSolid_(specificHeatSolid),
        latentHeat_(latentHeat),
        specificHeatLiquid_(specificHeatLiquid),
        meltingPoint_(meltingPoint),
        chargeFeedRate_(chargeFeedRate),
        waterContentCharged_(waterContentCharged / 100.0),
        waterContentDischarged_(waterContentDischarged / 100.0),
        initialTemperature_(initialTemperature),
        dischargeTemperature_(dischargeTemperature),
        waterVaporDischargeTemperature_(waterVaporDischargeTemperature),
        percentMelted_(chargeMelted / 100.0),
        percentReacted_(chargedReacted / 100.0),
        reactionHeat_(reactionHeat),
        additionalHeat_(additionalHeat)
    {}

    SolidLoadChargeMaterial() = default;

    /**
     * Gets the thermic reaction type
     *
     * @return LoadChargeMaterial::ThermicReactionType classification of thermic reaction type
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    /**
     * Sets the thermic reaction type
     *
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     *
     * @return nothing
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    /**
     * Gets the average specific heat of the solid material(dry)
     *
     * @return double, average specific heat of solid material (dry) in btu/(lb*°F)
     */
    double getSpecificHeatSolid() const {
        return specificHeatSolid_;
    }

    /**
     * Sets the average specific heat of the solid material (dry)
     *
     * @param specificHeatSolid double, average specific heat of the solid material (dry) in btu/(lb*°F)
     *
     * @return nothing
     */
    void setSpecificHeatSolid(double specificHeatSolid) {
        specificHeatSolid_ = specificHeatSolid;
    }

    /**
     * Gets the latent heat of fusion
     *
     * @return double, latent heat of fusion in btu/lb
     */
    double getLatentHeat() const {
        return latentHeat_;
    }

    /**
     * Sets the latent heat of fusion
     *
     * @param latentHeat double, latent heat of fusion in btu/lb
     *
     * @return nothing
     */
    void setLatentHeat(double latentHeat) {
        latentHeat_ = latentHeat;
    }

    /**
     * Gets the specific heat of liquid from molten material
     *
     * @return double, specific heat of liquid from molten material in btu/(lb*°F)
     */
    double getSpecificHeatLiquid() const {
        return specificHeatLiquid_;
    }

    /**
     * Sets the specific heat of liquid from molten material
     *
     * @param specificHeatLiquid double, specific heat of liquid from molten material in btu/(lb*°F)
     *
     * @return nothing
     */
    void setSpecificHeatLiquid(double specificHeatLiquid) {
        specificHeatLiquid_ = specificHeatLiquid;
    }

    /**
     * Gets the melthing point of the material
     *
     * @return double, melting point of material in °F
     */
    double getMeltingPoint() const {
        return meltingPoint_;
    }

    /**
     * Gets the ID of material
     *
     * @return double, ID number of material
     */
    double getID() const {
        return this->id;
    }

    /**
     * Sets the ID of a material
     *
     * @param id int, ID of the material
     *
     * @return nothing
     */
    void setID(const int id) {
        this->id = id;
    }

    /**
     * Sets the melting point of the material
     *
     * @param meltingPoint double, melthing point of material in °F
     *
     * @return nothing
     */
    void setMeltingPoint(double meltingPoint) {
        meltingPoint_ = meltingPoint;
    }

    /**
     * Gets the charge (wet)-feed rate
     *
     * @return double, charge (wet)-feed rate in lb/hr
     */
    double getChargeFeedRate() const {
        return chargeFeedRate_;
    }

    /**
     * Sets the charge (wet)-feed rate
     *
     * @param chargeFeedRate double, charge (wet)-feed rate in lb/hr
     *
     * @return nothing
     */
    void setChargeFeedRate(double chargeFeedRate) {
        chargeFeedRate_ = chargeFeedRate;
    }

    /**
     * Gets the water content as charged (%)
     *
     * @return double, % of water content charged
     */
    double getWaterContentCharged() const {
        return waterContentCharged_ * 100.0;
    }

    /**
     * Sets the water content as charged (%)
     *
     * @param waterContentCharged double, % of water content charged
     *
     * @return nothing
     */
    void setWaterContentCharged(double waterContentCharged) {
        waterContentCharged_ = waterContentCharged / 100.0;
    }

    /**
     * Gets the water content as discharged (%)
     *
     * @return double, % of water content discharged
     */
    double getWaterContentDischarged() const {
        return waterContentDischarged_ * 100.0;
    }

    /**
     * Sets the water content as discharged (%)
     *
     * @param waterContentDischarged double, % of water content discharged
     *
     * @return nothing
     */
    void setWaterContentDischarged(double waterContentDischarged) {
        waterContentDischarged_ = waterContentDischarged / 100.0;
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
     * Gets the charge material discharge temperature
     *
     * @return double, charge material discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature_;
    }

    /**
     * Sets the charge material discharge temperature
     *
     * @param dischargeTemperature double, charge material discharge temperature in °F
     *
     * @return nothing
     */
    void setDischargeTemperature(double dischargeTemperature) {
        dischargeTemperature_ = dischargeTemperature;
    }

    /**
     * Gets the water vapor discharge temperature
     *
     * @return double, water vapor discharge temperature in °F
     */
    double getWaterVaporDischargeTemperature() const {
        return waterVaporDischargeTemperature_;
    }

    /**
     * Sets the water vapor discharge temperature
     *
     * @param waterVaporDischargeTemperature double, water vapor discharge temperature in °F
     *
     * @return nothing
     */
    void setWaterVaporDischargeTemperature(double waterVaporDischargeTemperature) {
        waterVaporDischargeTemperature_ = waterVaporDischargeTemperature;
    }

    /**
     * Gets the charge melted (% of dry charge)
     *
     * @return double, charge melted (% of dry charge)
     */
    double getChargeMelted() const {
        return percentMelted_ * 100.0;
    }

    /**
     * Sets the charge melted (% of dry charge)
     *
     * @param chargeMelted double, charge melted (% of dry charge)
     *
     * @return nothing
     */
    void setChargeMelted(double chargeMelted) {
        percentMelted_ = chargeMelted / 100.0;
    }

    /**
     * Gets the charge reacted
     *
     * @return double, charge reacted (% of dry charge)
     */
    double getChargedReacted() const {
        return percentReacted_ * 100.0;
    }

    /**
     * Sets the charged reacted
     *
     * @param chargedReacted double, charge reacted (% of dry charge)
     *
     * @return nothing
     */
    void setChargedReacted(double chargedReacted) {
        percentReacted_ = chargedReacted / 100.0;
    }

    /**
     * Gets the reaction heat
     *
     * @return double, reaction heat in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat_;
    }

    /**
     * Sets the reaction heat
     *
     * @param reactionHeat double, reaction heat in btu/lb
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
     * Gets the substance
     *
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance_;
    }

    /**
     * Sets the substance
     *
     * @param substance string, name of substance
     *
     * @return nothing
     */
    void setSubstance(std::string const & substance) {
        substance_ = substance;
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
     * bool operator
     */
    bool operator == (const SolidLoadChargeMaterial& rhs) const
    {
        return specificHeatSolid_ == rhs.specificHeatSolid_ &&
                latentHeat_ == rhs.latentHeat_ &&
                specificHeatLiquid_ == rhs.specificHeatLiquid_ &&
                meltingPoint_ == rhs.meltingPoint_ &&
                substance_ == rhs.substance_ && id == rhs.id;
    }

    /**
     * bool operature
     */
    bool operator != (const SolidLoadChargeMaterial& rhs) const
    {
        return !(*this == rhs);
    }

    /**
     * Obtain the total heat for the solid charge material in Btu/hr
     * */
    double getTotalHeat();

private:

    // In/Out values
    std::string substance_ = "Unknown";
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType_ = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatSolid_ = 0.0;
    double latentHeat_ = 0.0;
    double specificHeatLiquid_ = 0.0;
    double meltingPoint_ = 0.0;
    double chargeFeedRate_ = 0.0;
    double waterContentCharged_ = 0.0;
    double waterContentDischarged_ = 0.0;
    double initialTemperature_ = 0.0;
    double dischargeTemperature_ = 0.0;
    double waterVaporDischargeTemperature_ = 0.0;
    double percentMelted_ = 0.0;
    double percentReacted_ = 0.0;
    double reactionHeat_ = 0.0;
    double additionalHeat_ = 0.0;
    int id = 0;
    // Out values
    double totalHeat_ = 0.0;

    friend class SQLite;

    /**
    * Constructor for the solid load/charge material with subset of inputs specified.
    *
    * @param substance string, Name of substance
    * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
    * @param latentHeat double, Latent heat of fusion in Btu/(lb)
    * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
    * @param meltingPoint double, The melting point of the material in °F
    *
    * */
    SolidLoadChargeMaterial(
            const std::string & substance,
            double specificHeatSolid,
            double latentHeat,
            double specificHeatLiquid,
            double meltingPoint
    ) : substance_ (substance),
        specificHeatSolid_ (specificHeatSolid),
        latentHeat_ (latentHeat),
        specificHeatLiquid_ (specificHeatLiquid),
        meltingPoint_ (meltingPoint)
    {}

};

#endif //AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
