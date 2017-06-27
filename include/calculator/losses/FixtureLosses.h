/**
 * @file
 * @brief Calculator for heat loss due to fixtures, trays, conveyors
 *
 * This contains the inputs for calculating heat loss due to fixtures, trays, conveyors.
 *
 * Assumes there is no melting or phase change of the fixture material involved.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_FIXTURELOSSES_H
#define AMO_SUITE_FIXTURELOSSES_H

/**
 * @class FixtureLosses FixtureLosses.h
 */
class FixtureLosses {
public:
    /**
     * Constructor
     * @param specificHeat double, Specific heat in btu/(lb*°F).
     * @param feedRate double, Feed Rate for Gas Mixture in lb/hr
     * @param initialTemperature double, Initial temperature in °F.
     * @param finalTemperature double, Final temperature in °F.
     * @param correctionFactor double, correction factor - unitless
     * @return nothing
     */
    FixtureLosses(
            double specificHeat,
            double feedRate,
            double initialTemperature,
            double finalTemperature,
            double correctionFactor)
            : specificHeat_(specificHeat),
              feedRate_(feedRate),
              initialTemperature_(initialTemperature),
              finalTemperature_(finalTemperature),
              correctionFactor_(correctionFactor)
    {
        heatLoss_ = 0.0;
    }

    FixtureLosses() = default;

    /**
    * Gets the specific heat
    *
    * @return double, specific heat in btu/(lb*°F)
    */
    double getSpecificHeat() const {
        return specificHeat_;
    }

    /**
    * Sets the specific heat
    *
    * @param specificHeat double, specific heat in btu/(lb*°F)
    *
    * @return nothing
    */
    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
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
    * Gets the final temperature
    *
    * @return double, final temperature in °F
    */
    double getFinalTemperature() const {
        return finalTemperature_;
    }

    /**
    * Sets the final temperature
    *
    * @param finalTemperature double, final temperature in °F
    *
    * @return nothing
    */
    void setFinalTemperature(double finalTemperature) {
        finalTemperature_ = finalTemperature;
    }

    /**
    * Gets the correction factor
    *
    * @return double, correction factor - unitless
    */
    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    /**
    * Sets the correction factor
    *
    * @param correctionFactor double, correction factor - unitless
    *
    * @return nothing
    */
    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    /**
    * Gets the total heat loss
    *
    * @return double, total heat loss in btu/hr
    */
    double getHeatLoss();

private:
    // In values
    double specificHeat_;
    double feedRate_;
    double initialTemperature_;
    double finalTemperature_;
    double correctionFactor_;

    // Out values
    double heatLoss_;
};

#endif //AMO_SUITE_FIXTURELOSSES_H
