/**
 * @file
 * @brief Calculator for saturated properties for steam systems
 *
 * This contains the inputs for calculating saturated properties for steam systems
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include <unordered_map>
#include <string>

#ifndef AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
#define AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H

/**
 * Saturated temperature class
 * Used to calculate the saturated temperature given the saturated pressure.
 */
class SaturatedTemperature {
public:
    /**
     *
     * Constructor for the saturated temperature calculator
     *
     * @param saturatedPressure double, saturated pressure in MPa
     *
     * @return nothing
     *
     * */
    SaturatedTemperature(
            double saturatedPressure)
            : saturatedPressure_(saturatedPressure)
    {
        saturatedTemperature_ = 0.0;
    }


    /**
     * Gets the saturated pressure
     *
     * @return double, saturated pressure in MPa
     */
    double getSaturatedPressure() const {
        return saturatedPressure_;
    }

    /**
     * Sets the saturated pressure
     *
     * @param saturatedPressure double, saturated pressure in MPa
     *
     * @return nothing
     */
    void setSaturatedPressure(double saturatedPressure) {
        saturatedPressure_ = saturatedPressure;
    }

    /**
     * Calculates the saturated temperature
     *
     * @return double, saturated temperature in Kelvin
     */
    double calculate();

private:
    // In values
    double saturatedPressure_ = 0.0;


    //Out values
    double saturatedTemperature_;
};


/**
 * Saturated pressure class
 * Used to calculate the saturated pressure given the saturated temperature.
 */
class SaturatedPressure {
public:
    /**
     * Constructor for the saturated pressure calculator
     *
     * @param saturatedTemperature double, saturated temperature in Kelvin
     *
     * @return nothing
     *
     * */
    SaturatedPressure(
            double saturatedTemperature)
            : saturatedTemperature_(saturatedTemperature)
    {
        saturatedPressure_ = 0.0;
    }


    /**
     * Gets the saturated temperature
     *
     * @return double, saturated temperature in Kelvin
     */
    double getSaturatedTemperature() const {
        return saturatedTemperature_;
    }

    /**
     * Sets the saturated temperature
     *
     * @param saturatedTemperature double, saturated temperature in Kelvin
     *
     * @return nothing
     */
    void setSaturatedTemperature(double saturatedTemperature) {
        saturatedTemperature_ = saturatedTemperature;
    }

    /**
     * Calculates the saturated pressure
     *
     * @return double, saturated pressure in MPa
     */
    double calculate();

private:
    // In values
    double saturatedTemperature_ = 0.0;


    //Out values
    double saturatedPressure_;
};



/**
 * Saturated properties class
 * Used to calculate the properties of a saturated substance.
 */
class SaturatedProperties {
public:
    /**
     *
     * Constructor for the saturated properties calculator
     *
     * @param saturatedPressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in Kelvin
     *
     * @return nothing
     *
     * */
    SaturatedProperties(
            double saturatedPressure,
            double saturatedTemperature)
            : saturatedPressure_(saturatedPressure),
              saturatedTemperature_(saturatedTemperature)
    {}


    /**
     * Gets the saturated pressure
     *
     * @return double, saturated pressure in psig
     */
    double getSaturatedPressure() const {
        return saturatedPressure_;
    }

    /**
     * Sets the saturated pressure
     *
     * @param saturatedPressure double, saturated pressure in psig
     *
     * @return nothing
     */
    void setSaturatedPressure(double saturatedPressure) {
        saturatedPressure_ = saturatedPressure;
    }

    /**
     * Gets the saturated temperature
     *
     * @return double, saturated temperature in °F
     */
    double getSaturatedTemperature() const {
        return saturatedTemperature_;
    }

    /**
     * Sets the saturated temperature
     *
     * @param saturatedTemperature double, saturated temperature in °F
     *
     * @return nothing
     */
    void setSaturatedTemperature(double saturatedTemperature) {
        saturatedTemperature_ = saturatedTemperature;
    }

    std::unordered_map<std::string, double> calculate();


private:
    // In values
    double saturatedPressure_ = 0.0;
    double saturatedTemperature_ = 0.0;


    //Out values
    std::unordered_map<std::string, double> saturatedProperties;
};


#endif //AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
