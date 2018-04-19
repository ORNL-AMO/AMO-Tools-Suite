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

#ifndef AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
#define AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H

#include "SteamSystemModelerTool.h"

/**
 * Saturated temperature class
 * Used to calculate the saturated temperature given the saturated pressure.
 */
class SaturatedTemperature {
public:
    /**
     * Constructor for the saturated temperature calculator
     * @param saturatedPressure double, saturated pressure in MPa
     * */
    explicit SaturatedTemperature(double saturatedPressure)
            : saturatedPressure(saturatedPressure) {}
    /**
     * Calculates the saturated temperature
     * @return double, saturated temperature in Kelvin
     */
    double calculate() const;

private:
    const double saturatedPressure;
};


/**
 * Saturated pressure class
 * Used to calculate the saturated pressure given the saturated temperature.
 */
class SaturatedPressure {
public:
    /**
     * Constructor for the saturated pressure calculator
     * @param saturatedTemperature double, saturated temperature in Kelvin
     * */
    explicit SaturatedPressure(double saturatedTemperature) : saturatedTemperature(saturatedTemperature) {}

    /**
     * Calculates the saturated pressure
     * @return double, saturated pressure in MPa
     */
    double calculate() const;

private:
    const double saturatedTemperature;
};



/**
 * Saturated properties class
 * Used to calculate the properties of a saturated substance.
 */
class SaturatedProperties {
public:
    /**
     * Constructor for the saturated properties calculator
     * @param saturatedPressure double, saturated pressure in MPa
     * @param saturatedTemperature double, saturated temperature in Kelvin
     * */
    SaturatedProperties(double saturatedPressure, double saturatedTemperature)
            : saturatedPressure(saturatedPressure),
              saturatedTemperature(saturatedTemperature) {}

    SteamSystemModelerTool::SaturatedPropertiesOutput calculate();

private:
    const double saturatedPressure, saturatedTemperature;
};


#endif //AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
