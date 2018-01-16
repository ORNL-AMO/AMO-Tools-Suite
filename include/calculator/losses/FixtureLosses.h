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
 * Fixture Losses class
 * Contains all of the properties of a fixture, tray, conveyor belt, etc.
 * Used to calculate the heat loss caused by fixtures, trays, conveyor belts, etc. that enter the furnace at lower temperatures.
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
     */
    FixtureLosses(const double specificHeat, const double feedRate, const double initialTemperature,
                  const double finalTemperature, const double correctionFactor)
            : specificHeat(specificHeat),
              feedRate(feedRate),
              initialTemperature(initialTemperature),
              finalTemperature(finalTemperature),
              correctionFactor(correctionFactor)
    {
        heatLoss = 0.0;
    }

    FixtureLosses() = default;

    /**
    * Gets the specific heat
    * @return double, specific heat in btu/(lb*°F)
    */
    double getSpecificHeat() const {
        return specificHeat;
    }

    /**
    * Sets the specific heat
    * @param specificHeat double, specific heat in btu/(lb*°F)
    */
    void setSpecificHeat(const double specificHeat) {
		this->specificHeat = specificHeat;
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
    void setFeedRate(const double feedRate) {
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
    void setInitialTemperature(const double initialTemperature) {
		this->initialTemperature = initialTemperature;
    }

    /**
    * Gets the final temperature
    * @return double, final temperature in °F
    */
    double getFinalTemperature() const {
        return finalTemperature;
    }

    /**
    * Sets the final temperature
    * @param finalTemperature double, final temperature in °F
    */
    void setFinalTemperature(const double finalTemperature) {
		this->finalTemperature = finalTemperature;
    }

    /**
    * Gets the correction factor
    * @return double, correction factor - unitless
    */
    double getCorrectionFactor() const {
        return correctionFactor;
    }

    /**
    * Sets the correction factor
    * @param correctionFactor double, correction factor - unitless
    */
    void setCorrectionFactor(const double correctionFactor) {
		this->correctionFactor = correctionFactor;
    }

    /**
    * Gets the total heat loss
    * @return double, total heat loss in btu/hr
    */
    double getHeatLoss();

private:
    // In values
    double specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor;

    // Out values
    double heatLoss;
};

#endif //AMO_SUITE_FIXTURELOSSES_H
