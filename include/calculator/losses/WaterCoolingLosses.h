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

class WaterCoolingLosses {
public:

    /**
     * Constructor
     * @param flowRate Rate of flow. Units are gpm, MGD(Million Gallons Per Day), L/s, m^3/hr.
     * @param initialTemperature Initial temperature in °F.
     * @param outletTemperature Outlet temperature in °F.
     * @param correctionFactor Correction factor
     * @return nothing
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

    double getFlowRate() const {
        return flowRate_;
    }

    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
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
