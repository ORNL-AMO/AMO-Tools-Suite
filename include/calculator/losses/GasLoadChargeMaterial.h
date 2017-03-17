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
    {
        totalHeat_ = 0.0;
    }

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

    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    double getPercentVapor() const {
        return percentVapor_ * 100.0;
    }

    void setPercentVapor(double percentVapor) {
        percentVapor_ = percentVapor / 100.0;
    }

    double getTotalHeat();

private:
    LoadChargeMaterial::ThermicReactionType thermicReactionType_;
    double specificHeatGas_;
    double feedRate_;
    double percentVapor_;
    double initialTemperature_;
    double dischargeTemperature_;
    double specificHeatVapor_;
    double percentReacted_;
    double reactionHeat_;
    double additionalHeat_;
    // Out value
    double totalHeat_;
};

#endif //AMO_SUITE_GASLOADCHARGEMATERIAL_H
