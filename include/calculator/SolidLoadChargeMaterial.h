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

#include "LoadChargeMaterial.h"

#ifndef AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
#define AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H

class SolidLoadChargeMaterial {
public:

    /**
 * Constructor for the solid load/charge material with all inputs specified.
 *
 * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid Average specific heat of the solid material (dry) in Btu/(lb-°F)
 * @param latentHeat Latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid Specific heat of liquid from molten material in Btu/(lb-°F)
 * @param meltingPoint The melting point of the material in °F
 * @param chargeFeedRate Charge (wet)-feed rate in lb/h
 * @param waterContentCharged Water content as charged (%) in %
 * @param waterContentDischarged Water content as discharged (%) in %
 * @param initialTemperature Initial temperature in °F
 * @param dischargeTemperature Charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature Water vapor discharge temperature in °F
 * @param chargeMelted Charge melted (% of dry charge) in %
 * @param chargedReacted Charge Reacted (% of dry charge) in %
 * @param reactionHeat Heat of reaction in Btu/lb
 * @param additionalHeat Additional heat required in Btu/h
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
        waterContentCharged_(waterContentCharged),
        waterContentDischarged_(waterContentDischarged),
        initialTemperature_(initialTemperature),
        dischargeTemperature_(dischargeTemperature),
        waterVaporDischargeTemperature_(waterVaporDischargeTemperature),
        percentMelted_(chargeMelted),
        percentReacted_(chargedReacted),
        reactionHeat_(reactionHeat),
        additionalHeat_(additionalHeat)
    {}

    SolidLoadChargeMaterial() = default;

    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType_;
    }

    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType  thermicReactionType) {
        thermicReactionType_ = thermicReactionType;
    }

    double getSpecificHeatSolid() const {
        return specificHeatSolid_;
    }

    void setSpecificHeatSolid(double specificHeatSolid) {
        specificHeatSolid_ = specificHeatSolid;
    }

    double getLatentHeat() const {
        return latentHeat_;
    }

    void setLatentHeat(double latentHeat) {
        latentHeat_ = latentHeat;
    }

    double getSpecificHeatLiquid() const {
        return specificHeatLiquid_;
    }

    void setSpecificHeatLiquid(double specificHeatLiquid) {
        specificHeatLiquid_ = specificHeatLiquid;
    }

    double getMeltingPoint() const {
        return meltingPoint_;
    }

    void setMeltingPoint(double meltingPoint) {
        meltingPoint_ = meltingPoint;
    }

    double getChargeFeedRate() const {
        return chargeFeedRate_;
    }

    void setChargeFeedRate(double chargeFeedRate) {
        chargeFeedRate_ = chargeFeedRate;
    }

    double getWaterContentCharged() const {
        return waterContentCharged_;
    }

    void setWaterContentCharged(double waterContentCharged) {
        waterContentCharged_ = waterContentCharged;
    }

    double getWaterContentDischarged() const {
        return waterContentDischarged_;
    }

    void setWaterContentDischarged(double waterContentDischarged) {
        waterContentDischarged_ = waterContentDischarged;
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

    double getWaterVaporDischargeTemperature() const {
        return waterVaporDischargeTemperature_;
    }

    void setWaterVaporDischargeTemperature(double waterVaporDischargeTemperature) {
        waterVaporDischargeTemperature_ = waterVaporDischargeTemperature;
    }

    double getChargeMelted() const {
        return percentMelted_;
    }

    void setChargeMelted(double chargeMelted) {
        percentMelted_ = chargeMelted;
    }

    double getChargedReacted() const {
        return percentReacted_;
    }

    void setChargedReacted(double chargedReacted) {
        percentReacted_ = chargedReacted;
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

    /**
     * Obtain the total head for the solid charge material in Btu/h
     * */
    double getTotalHeat();

private:
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType_;
    double specificHeatSolid_;
    double latentHeat_;
    double specificHeatLiquid_;
    double meltingPoint_;
    double chargeFeedRate_;
    double waterContentCharged_;
    double waterContentDischarged_;
    double initialTemperature_;
    double dischargeTemperature_;
    double waterVaporDischargeTemperature_;
    double percentMelted_;
    double percentReacted_;
    double reactionHeat_;
    double additionalHeat_;
    // Out value
    double totalHeat_;

};

#endif //AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
