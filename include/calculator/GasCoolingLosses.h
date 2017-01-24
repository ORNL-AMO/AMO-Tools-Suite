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
<<<<<<< HEAD

    /**
     * Constructor
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @param initialTemperature Initial temperature in °F.
     * @param finalTemperature Final temperature in °F.
     * @param specificHeat Specific heat in °F.
     * @return nothing
     */
    GasCoolingLosses(
            double flowRate,
            double initialTemperature,
            double finalTemperature,
            double specificHeat)
=======
    /**
     * Constructor for the gas cooling losses (including air) with all inputs specified
     *
     * @param flowRate Air or gas volumetric flow rate in SCFM (ft³/min)
     * @param initialTemperature Inlet temperature of air or gas in °F
     * @param finalTemperature Outlet temperature of air or gas in °F
     * @param specificHeat Specific heat of gas or air at average air temperature in Btu/(scf F)
     * @param correctionFactor Correction factor
     *
     * */


    GasCoolingLosses(double flowRate,
                     double initialTemperature,
                     double finalTemperature,
                     double specificHeat,
                     double correctionFactor)
>>>>>>> develop
            : flowRate_(flowRate),
              initialTemperature_(initialTemperature),
              finalTemperature_(finalTemperature),
              specificHeat_(specificHeat),
              correctionFactor_(correctionFactor)
    {
        heatLoss_ = 0.0;
    }

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

    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

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
