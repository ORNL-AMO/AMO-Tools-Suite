/**
 * @file
 * @brief Calculator for heat losses due to liquid (not water) cooling
 *
 * This contains the inputs for calculating a liquid cooling heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_LIQUIDCOOLINGLOSSES_H
#define AMO_SUITE_LIQUIDCOOLINGLOSSES_H

/**
 * Liquid Cooling Losses class
 * Contains all of the properties of a cooling system and its liquid media.
 * Used to calculate how much heat loss is caused by the cooling components and their cooling media (a liquid).
 */
class LiquidCoolingLosses {
public:
    /**
     * Constructor
     * @param flowRate double, Rate of flow. Units are gpm,
     * @param density double, Density in lb/cu.ft
     * @param initialTemperature double, Initial temperature in °F.
     * @param outletTemperature double, Outlet temperature in °F.
     * @param specificHeat double, Specific heat in btu/(lb*°F)
     * @param correctionFactor double, Correction factor - unitless
     */

    LiquidCoolingLosses(double flowRate,
                        double density,
                        double initialTemperature,
                        double outletTemperature,
                        double specificHeat,
                        double correctionFactor)
            : flowRate(flowRate),
              density(density),
              initialTemperature(initialTemperature),
              outletTemperature(outletTemperature),
              specificHeat(specificHeat),
              correctionFactor(correctionFactor)
    {
        heatLoss = 0.0;
    }

    LiquidCoolingLosses() = default;

    /**
     * Gets the flow rate
     * @return double, flow rate in gpm
     */
    double getFlowRate() const {
        return flowRate;
    }

    /**
     * Sets the flow rate
     * @param flowRate double, flow rate in gpm
     */
    void setFlowRate(double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Gets the density
     * @return double, denisty in lb/cu.ft
     */
    double getDensity() const {
        return density;
    }

    /**
     * Sets the density
     * @param density double, density in lb/cu.ft
     */
    void setDensity(double density) {
        this->density = density;
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
    void setInitialTemperature(double initialTemperature) {
        this->initialTemperature = initialTemperature;
    }

    /**
     * Gets the outlet temperature
     * @return double, outlet temperature in °F
     */
    double getOutletTemperature() const {
        return outletTemperature;
    }

    /**
     * Sets the outlet temperature
     * @param outletTemperature double, outlet temperature in °F
     */
    void setOutletTemperature(double outletTemperature) {
        this->outletTemperature = outletTemperature;
    }

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
     *
     */
    void setSpecificHeat(double specificHeat) {
        this->specificHeat = specificHeat;
    }

    /**
     * Gets the total heat loss for cooling
     * @return double, heat loss for cooling in btu/hr
     */
    double getHeatLoss();

private:
    // In values
    double flowRate;
    double density;
    double initialTemperature;
    double outletTemperature;
    double specificHeat;
    double correctionFactor;
    // Out value
    double heatLoss;
};
#endif //AMO_SUITE_LIQUIDCOOLINGLOSSES_H
