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

class HumidityRatio {
public:
    /**
     *
     * Constructor for the humidity ratio calculator
     *
     * @param atmosphericPressure double, pressure of the atmosphere in atm
     * @param dryBulbTemp double, temperature of the inputted air in °F
     * @param relativeHumidity double, relative humidity as %
     * @param wetBulbTemp double, wet bulb temperature in °F
     *
     *
     * */
    HumidityRatio(
            double atmosphericPressure,
            double dryBulbTemp,
            double relativeHumidity,
            double wetBulbTemp)
            : atmosphericPressure_(atmosphericPressure),
              dryBulbTemp_(dryBulbTemp),
              relativeHumidity_(relativeHumidity),
              wetBulbTemp_(wetBulbTemp)

    {
        saturationPressure_ = 0.0;
        humidityRatioUsingRH_ = 0.0;
        humidityRatioUsingWBT_ = 0.0;

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
     */
    void setAtmosphericPressure(double atmosphericPressure) {
        atmosphericPressure_ = atmosphericPressure;
    }

    /**
     * Gets the dry bulb temperature
     *
     * @return double, dry bulb temperature in °F
     */
    double getDryBulbTemp() const {
        return dryBulbTemp_;
    }

    /**
     * Sets the dry bulb temperature
     *
     * @param dryBulbTemp double, dry bulb temperature
     *
     */
    void setDryBulbTemp(double dryBulbTemp) {
        dryBulbTemp_ = dryBulbTemp;
    }

    /**
     * Gets the relative humidity
     *
     * @return double, relative humidity as %
     */
    double getRelativeHumidity() const {
        return relativeHumidity_;
    }

    /**
     * Sets the relative humidity
     *
     * @param relativeHumidity double, relative humidity as %
     *
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
     * Gets the saturation pressure
     *
     * @return double, saturation pressure in atm
     */
    double getSaturationPressure(double temperature);

    /**
     * Sets the wet bulb temperature
     *
     * @param wetBulbTemp double, wet bulb temperature in °F
     *
     */
    void setWetBulbTemp(double wetBulbTemp) {
        wetBulbTemp_ = wetBulbTemp;
    }

    /**
     * Gets the humidity ratio using the relative humidity (instead of wet bulb temperature)
     *
     * @return double, humidity ratio - unitless
     */
    double getHumidityRatioUsingRH();

    /**
     * Gets the humidity ratio using the wet bulb temperature (instead of relative humidity)
     *
     * @return double, humidity ratio - unitless
     */
    double getHumidityRatioUsingWBT();



private:
    // In values
    double atmosphericPressure_ = 0.0;
    double dryBulbTemp_ = 0.0;
    double relativeHumidity_ = 0.0;
    double wetBulbTemp_ = 0.0;

    //In-Out Values
    double saturationPressure_;

    // Out values
    double humidityRatioUsingRH_;
    double humidityRatioUsingWBT_;
};
#endif //AMO_TOOLS_SUITE_HUMIDITYRATIO_H
