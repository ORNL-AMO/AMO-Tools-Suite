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

class FixtureLosses {
public:
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

    double getSpecificHeat() const {
        return specificHeat_;
    }

    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
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

    double getFinalTemperature() const {
        return finalTemperature_;
    }

    void setFinalTemperature(double finalTemperature) {
        finalTemperature_ = finalTemperature;
    }

    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

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
