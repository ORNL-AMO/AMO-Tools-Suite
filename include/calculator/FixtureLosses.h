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
            double specificHeat_,
            double feedRate_,
            double initialTemperature_,
            double finalTemperature_,
            double correctionFactor_)
            : specificHeat_(specificHeat_),
              feedRate_(feedRate_),
              initialTemperature_(initialTemperature_),
              finalTemperature_(finalTemperature_),
              correctionFactor_(correctionFactor_)
    {}


private:
public:
    double getSpecificHeat_() const {
        return specificHeat_;
    }

    void setSpecificHeat_(double specificHeat_) {
        FixtureLosses::specificHeat_ = specificHeat_;
    }

    double getFeedRate_() const {
        return feedRate_;
    }

    void setFeedRate_(double feedRate_) {
        FixtureLosses::feedRate_ = feedRate_;
    }

    double getInitialTemperature_() const {
        return initialTemperature_;
    }

    void setInitialTemperature_(double initialTemperature_) {
        FixtureLosses::initialTemperature_ = initialTemperature_;
    }

    double getFinalTemperature_() const {
        return finalTemperature_;
    }

    void setFinalTemperature_(double finalTemperature_) {
        FixtureLosses::finalTemperature_ = finalTemperature_;
    }

    double getCorrectionFactor_() const {
        return correctionFactor_;
    }

    void setCorrectionFactor_(double correctionFactor_) {
        FixtureLosses::correctionFactor_ = correctionFactor_;
    }

    void setTotalHeat(double totalHeat) {
        FixtureLosses::totalHeat_ = totalHeat;
    }

    double getTotalHeat();

private:
    // In values
    double specificHeat_;
    double feedRate_;
    double initialTemperature_;
    double finalTemperature_;
    double correctionFactor_;

    // Out values
    double totalHeat_;
};

#endif //AMO_SUITE_FIXTURELOSSES_H
