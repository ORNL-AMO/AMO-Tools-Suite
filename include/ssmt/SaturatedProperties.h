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
    {
        liquidEnthalpy_ = 0.0;
        evaporationEnthalpy_ = 0.0;
        gasEnthalpy_ = 0.0;
        liquidEntropy_ = 0.0;
        evaporationEntropy_ = 0.0;
        gasEntropy_ = 0.0;
        liquidVolume_ = 0.0;
        evaporationVolume_ = 0.0;
        gasVolume_ = 0.0;
    }


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

    /**
     * Gets the specific enthalpy of the saturated liquid
     *
     * @return double, specific enthalpy of the saturated liquid in btu/lbm
     */
    double getLiquidEnthalpy();

    /**
     * Gets the specific enthalpy of the evaporation
     *
     * @return double, specific enthalpy of the evaporation in btu/lbm
     */
    double getEvaporationEnthalpy();

    /**
     * Gets the specific enthalpy of the saturated gas
     *
     * @return double, specific enthalpy of the saturated gas in btu/lbm
     */
    double getGasEnthalpy();

    /**
     * Gets the specific entropy of the saturated liquid
     *
     * @return double, specific entropy of the saturated liquid in btu/lbm/R
     */
    double getLiquidEntropy();

    /**
     * Gets the specific entropy of the evaporation
     *
     * @return double, specific entropy of the evaporation in btu/lbm/R
     */
    double getEvaporationEntropy();

    /**
     * Gets the specific entropy of the saturated gas
     *
     * @return double, specific entropy of the saturated gas in btu/lbm/R
     */
    double getGasEntropy();

    /**
     * Gets the specific volume of the saturated liquid
     *
     * @return double, specific volume of the saturated liquid in ft^3/lb
     */
    double getLiquidVolume();

    /**
     * Gets the specific volume of the evaporation
     *
     * @return double, specific volume of the evaporation in ft^3/lb
     */
    double getEvaporationVolume();

    /**
     * Gets the specific volume of the saturated gas
     *
     * @return double, specific volume of the saturated gas in ft^3/lb
     */
    double getGasVolume();


private:
    // In values
    double saturatedPressure_ = 0.0;
    double saturatedTemperature_ = 0.0;


    //Out values
    double liquidEnthalpy_;
    double gasEnthalpy_;
    double evaporationEnthalpy_;
    double liquidEntropy_;
    double gasEntropy_;
    double evaporationEntropy_;
    double liquidVolume_;
    double gasVolume_;
    double evaporationVolume_;
};


#endif //AMO_TOOLS_SUITE_SATURATEDPROPERTIES_H
