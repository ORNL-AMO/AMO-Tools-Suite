/**
 * @file
 * @brief Calculator for heat losses due to water cooling
 *
 * This contains the inputs for calculating a water cooling heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_SUITE_WATERCOOLINGLOSSES_H
#define AMO_SUITE_WATERCOOLINGLOSSES_H

/**
 * Water Cooling Losses class
 * Contains all of the properties of a water cooling system.
 * Used to calculate how much heat loss is caused by the cooling components and their cooling media (water).
 */
class WaterCoolingLosses {
public:

    /**
     * Constructor
     * @param flowRate double, Rate of flow. Units are gpm
     * @param initialTemperature double, Initial temperature in °F.
     * @param outletTemperature double, Outlet temperature in °F.
     * @param correctionFactor double, Correction factor - unitless
     */
    WaterCoolingLosses(double flowRate,
                       double initialTemperature,
                       double outletTemperature,
                       double correctionFactor)
            : flowRate_(flowRate),
              initialTemperature_(initialTemperature),
              outletTemperature_( outletTemperature),
              correctionFactor_(correctionFactor)
    {
        heatLoss_ = 0.0;
    }

    WaterCoolingLosses() = default;

    /**
     * Getter for the cooling water flow rate
     *
     * @return double, cooling water flow rate in GPM
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Sets the cooling water flow rate
     *
     * @param flowRate double, cooling water flow rate in GPM
     *
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
    * Getter for the initial/inlet temperature
    *
    * @return double, initial/inlet temperature in °F
    */
    double getInitialTemperature() const {
        return initialTemperature_;
    }

    /**
    * Sets the initial/inlet temperature
    *
    * @param initialTemperature double, initial/inlet temperature in °F
    *
    */
    void setInitialTemperature(double initialTemperature) {
        initialTemperature_ = initialTemperature;
    }

    /**
    * Getter for the outlet temperature
    *
    * @return double, outlet temperature in °F
    */
    double getOutletTemperature() const {
        return outletTemperature_;
    }

    /**
    * Sets the outlet temperature
     *
     * @param outletTemperature double, outlet temperature in °F
    *
    */
    void setOutletTemperature(double outletTemperature) {
        outletTemperature_ = outletTemperature;
    }

    /**
    * Getter for the heat loss
    *
    * @return double, heat loss in btu/cycle
    */
    double getHeatLoss();

private:
    // In values
    double flowRate_;
    double initialTemperature_;
    double outletTemperature_;
    double correctionFactor_;
    // Out value
    double heatLoss_;
};
#endif //AMO_SUITE_WATERCOOLINGLOSSES_H
