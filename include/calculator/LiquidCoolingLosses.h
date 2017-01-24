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
class LiquidCoolingLosses {
public:
    /**
     * Constructor
     * @param flowRate Rate of flow. Units are gpm, MGD(Million Gallons Per Day), L/s, m^3/hr.
     * @param density Density
     * @param initialTemperature Initial temperature in °F.
     * @param outletTemperature Outlet temperature in °F.
     * @param specificHeat Specific heat in °F.
     * @return nothing
     */
    LiquidCoolingLosses(
            double flowRate,
            double density,
            double initialTemperature,
            double outletTemperature,
            double specificHeat)
            : flowRate_(flowRate),
              density_(density),
              initialTemperature_(initialTemperature),
              outletTemperature_(outletTemperature),
              specificHeat_(specificHeat)
    {}

    LiquidCoolingLosses() = default;

    double getFlowRate() const {
        return flowRate_;
    }

    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    double getDensity() const {
        return density_;
    }

    void setDensity(double density) {
        density_ = density;
    }

    double getInitialTemperature() const {
        return initialTemperature_;
    }

    void setInitialTemperature(double initialTemperature) {
        initialTemperature_ = initialTemperature;
    }

    double getOutletTemperature() const {
        return outletTemperature_;
    }

    void setOutletTemperature(double outletTemperature) {
        outletTemperature_ = outletTemperature;
    }

    double getSpecificHeat() const {
        return specificHeat_;
    }

    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
    }

    double getHeatLoss();

private:
    // In values
    double flowRate_;
    double density_;
    double initialTemperature_;
    double outletTemperature_;
    double specificHeat_;
    // Out value
    double heatLoss_;
};
#endif //AMO_SUITE_LIQUIDCOOLINGLOSSES_H
