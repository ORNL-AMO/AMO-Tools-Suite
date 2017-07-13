/**
 * @file
 * @brief Calculator for the humidity ratio
 *
 * This contains the inputs for calculating the humidity ratio.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_HUMIDITYRATIO_H
#define AMO_TOOLS_SUITE_HUMIDITYRATIO_H

class O2Enrichment {
public:
    /**
     *
     * Constructor for the humidity ratio calculator
     *
     * @param atmosphericPressure double, pressure of the atmosphere in atm
     * @param inputAirTemp double, temperature of the inputted air in °F
     * @param relativeHumidity double, relative humidity - unitless
     * @param wetBulbTemp double, wet bulb temperature in °F
     *
     * @return nothing
     *
     * */
    HumidityRatio(
            double atmosphericPressure,
            double inputAirTemp,
            double relativeHumidity,
            double wetBulbTemp)
            : atmosphericPressure_(atmosphericPressure),
              inputAirTemp_(inputAirTemp),
              relativeHumidity_(relativeHumidity),
              wetBulbTemp_(wetBulbTemp)

    {
        saturationPressure_ = 0.0;
        humidityRatioUsingRelativeHumidity_ = 0.0;
        humidityRatioUsingWetBulbTemp_ = 0.0;

    }

    HumidityRatio() = default;

    /**
     * Gets the pressure of the atmosphere
     *
     * @return double, atmospheric pressure in atm
     */
    double getAtmosphericPressure() const {
        return atmosphericPressure_;
    }

    /**
     * Sets the pressure of the atmosphere
     *
     * @param atmosphericPressure double atmospheric pressure in atm
     *
     * @return nothing
     */
    void setAtmosphericPressure(double atmosphericPressure) {
        atmosphericPressure_ = atmosphericPressure;
    }

    /**
     * Gets the input air temperature/dry bulb temperature
     *
     * @return double, input air temperature/dry bulb temperature in °F
     */
    double getInputAirTemp() const {
        return inputAirTemp_;
    }

    /**
     * Sets the input air temperature/dry bulb temperature
     *
     * @param inputAirTemp double, input air temperature/dry bulb temperature
     *
     * @return nothing
     */
    void setInputAirTemp(double inputAirTemp) {
        inputAirTemp_ = inputAirTemp;
    }

    /**
     * Gets the relative humidity
     *
     * @return double, relative humidity - unitless
     */
    double getRelativeHumidity() const {
        return relativeHumidity_;
    }

    /**
     * Sets the relative humidity
     *
     * @param relativeHumidity double, realtive humidity - unitless
     *
     * @return nothing
     */
    void setRelativeHumidity(double relativeHumidity) {
        relativeHumidity_ = relativeHumidity;
    }

    /**
     * Gets the wet bulb temperature
     *
     * @return double, wet bulb temperature in °F
     */
    double getWetBulbTemp() const {
        return wetBulbTemp_;
    }

    /**
     * Sets the wet bulb temperature
     *
     * @param wetBulbTemp double, wet bulb temperature in °F
     *
     * @return nothing
     */
    void setWetBulbTemp(double wetBulbTemp) {
        wetBulbTemp_ = wetBulbTemp;
    }

    /**
     * Gets the humidity ratio using the relative humidity (instead of wet bulb temperature)
     *
     * @return double, humidity ratio - unitless
     */
    double getHumidityRatioUsingRelativeHumidity();

    /**
     * Gets the humidity ratio using the wet bulb temperature (instead of relative humidity)
     *
     * @return double, humidity ratio - unitless
     */
    double getHumidityRatioUsingRelativeHumidity();


private:
    // In values
    double atmosphericPressure_ = 0.0;
    double inputAirTemp_ = 0.0;
    double relativeHumidity_ = 0.0;
    double wetBulbTemp_ = 0.0;


    // Out values
    double saturationPressure_;
    double humidityRatioUsingRelativeHumidity_;
    double humidityRatioUsingWetBulbTemp_;_
};
#endif //AMO_TOOLS_SUITE_HUMIDITYRATIO_H
