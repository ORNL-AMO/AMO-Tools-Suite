/**
 * @file
 * @brief Calculator for heat required for atmosphere
 *
 * This contains the inputs for calculating a the heat loss for atmosphere
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_ATMOSPHERE_H
#define AMO_SUITE_ATMOSPHERE_H

#define REFERENCE_TEMPERATURE 60.0

class Atmosphere {
public:
    /**
     * Constructor for the atmospheric heat loss with all inputs specified
     *
     * @param inletTemperature Inlet temperature of gasses in °F
     * @param outletTemperature Outlet temperature of gasses in °F
     * @param flowRate Flow rate of gasses in scfh
     * @param correctionFactor Correction factor
     * @param specificHeat Specific heat of gasses at average air temperature in Btu/(scf - °F)
     * @return nothing
     *
     * */
    Atmosphere(double inletTemperature,
               double outletTemperature,
               double flowRate,
               double correctionFactor,
               double specificHeat)
            : inletTemperature_(inletTemperature),
              outletTemperature_(outletTemperature),
              flowRate_(flowRate),
              correctionFactor_(correctionFactor),
              specificHeat_(specificHeat)
    {
        totalHeat_ = 0.0;
    }

    Atmosphere() = default;

    double getInletTemperature() const {
        return inletTemperature_;
    }

    void setInletTemperature(double inletTemperature) {
        inletTemperature_ = inletTemperature;
    }

    double getOutletTemperature() const {
        return outletTemperature_;
    }

    void setOutletTemperature(double outletTemperature) {
        outletTemperature_ = outletTemperature;
    }

    double getFlowRate() const {
        return flowRate_;
    }

    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    double getSpecificHeat() const {
        return specificHeat_;
    }

    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
    }

    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    double getTotalHeat();

private:
    // In values
    double inletTemperature_;
    double outletTemperature_;
    double flowRate_;
    double correctionFactor_;
    double specificHeat_;
    // Out value
    double totalHeat_;
};


#endif //AMO_SUITE_ATMOSPHERE_H
