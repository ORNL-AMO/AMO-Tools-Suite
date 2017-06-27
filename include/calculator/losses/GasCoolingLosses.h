/**
 * @file
 * @brief Calculator for total energy loss for gas, including air
 *
 * This contains the inputs for calculating energy loss due to air or gas
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_GASCOOLINGLOSSES_H
#define AMO_SUITE_GASCOOLINGLOSSES_H


class GasCoolingLosses {
public:
    /**
     * Constructor for the gas cooling losses (including air) with all inputs specified
     *
     * @param flowRate double, Air or gas volumetric flow rate in SCFM (ft³/min)
     * @param initialTemperature double, Inlet temperature of air or gas in °F
     * @param finalTemperature double, Outlet temperature of air or gas in °F
     * @param specificHeat double, Specific heat of gas or air at average air temperature in Btu/(scf*°F)
     * @param correctionFactor double, Correction factor - unitless
     *
     * */


    GasCoolingLosses(double flowRate,
                     double initialTemperature,
                     double finalTemperature,
                     double specificHeat,
                     double correctionFactor)
            : flowRate_(flowRate),
              initialTemperature_(initialTemperature),
              finalTemperature_(finalTemperature),
              specificHeat_(specificHeat),
              correctionFactor_(correctionFactor)
    {
        heatLoss_ = 0.0;
    }

    GasCoolingLosses() = default;

    /**
     * Gets the air or gas volumetric flow rate
     *
     * @return double, flow rate in scfm
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Sets the air or gas volumetric flow rate
     *
     * @param flowRate double, flow rate in scfm
     *
     * @return nothing
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
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
     * @return double, final temeprature in °F
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
     * Gets the specific heat of air or gas at average air temperature
     *
     * @return double, specific heat of air or gas in btu/(scf*°F)
     */
    double getSpecificHeat() const {
        return specificHeat_;
    }

    /**
     * Sets the specific heat of air or gas at average air temperature
     *
     * @param specificHeat double, specific heat of air or gas in btu/(scf*°F)
     *
     * @return nothing
     */
    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
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
     * @return double, heat loss in btu/hr
     */
    double getHeatLoss();

private:
    // In values
    double flowRate_;
    double initialTemperature_;
    double finalTemperature_;
    double specificHeat_;
    double correctionFactor_;
    double heatLoss_;
};
#endif //AMO_SUITE_GASCOOLINGLOSSES_H
