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
    WaterCoolingLosses(
            double flowRate,
            double initialTemperature,
            double outletTemperature)
            : flowRate_(flowRate),
              initialTemperature_(initialTemperature),
              outletTemperature_( outletTemperature)
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
    // Out value
    double heatLoss_;
};
#endif //AMO_SUITE_WATERCOOLINGLOSSES_H
