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
    GasCoolingLosses(
            double flowRate,
            double initialTemperature,
            double finalTemperature,
            double specificHeat)
            : flowRate_(flowRate),
              initialTemperature_(initialTemperature),
              finalTemperature_(finalTemperature),
              specificHeat_(specificHeat)
    {}

    GasCoolingLosses() = default;

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

    double getFinalTemperature() const {
        return finalTemperature_;
    }

    void setFinalTemperature(double finalTemperature) {
        finalTemperature_ = finalTemperature;
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
    double initialTemperature_;
    double finalTemperature_;
    double specificHeat_;
    double heatLoss_;
};
#endif //AMO_SUITE_GASCOOLINGLOSSES_H
