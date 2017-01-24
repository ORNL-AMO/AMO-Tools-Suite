/**
 * @file
 * @brief Calculator for wall heat losses
 *
 * This contains the inputs for calculating a wall heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_WALLLOSSES_H
#define AMO_SUITE_WALLLOSSES_H

class WallLosses {
public:

    /**
     * Constructor
     * @param surfaceArea
     * @param ambientTemperature
     * @param surfaceTemperature
     * @param windVelocity
     * @param surfaceEmissivity
     * @param conditionFactor
     * @param correctionFactor
     * @return nothing
     */
    WallLosses(
            double surfaceArea,
            double ambientTemperature,
            double surfaceTemperature,
            double windVelocity,
            double surfaceEmissivity,
            double conditionFactor,
            double correctionFactor)
            : surfaceArea_(surfaceArea),
              ambientTemperature_(ambientTemperature),
              surfaceTemperature_(surfaceTemperature),
              windVelocity_(windVelocity),
              surfaceEmissivity_(surfaceEmissivity),
              conditionFactor_(conditionFactor),
              correctionFactor_(correctionFactor)
    {}

    WallLosses() = default;

    double getSurfaceArea() const {
        return surfaceArea_;
    }

    void setSurfaceArea(double surfaceArea) {
        surfaceArea_ = surfaceArea;
    }

    double getAmbientTemperature() const {
        return ambientTemperature_;
    }

    void setAmbientTemperature(double ambientTemperature) {
        ambientTemperature_ = ambientTemperature;
    }

    double getSurfaceTemperature() const {
        return surfaceTemperature_;
    }

    void setSurfaceTemperature(double surfaceTemperature) {
        surfaceTemperature_ = surfaceTemperature;
    }

    double getWindVelocity() const {
        return windVelocity_;
    }

    void setWindVelocity(double windVelocity) {
        windVelocity_ = windVelocity;
    }

    double getSurfaceEmissivity() const {
        return surfaceEmissivity_;
    }

    void setSurfaceEmissivity(double surfaceEmissivity) {
        surfaceEmissivity_ = surfaceEmissivity;
    }

    double getConditionFactor() const {
        return conditionFactor_;
    }

    void setConditionFactor(double conditionFactor) {
        conditionFactor_ = conditionFactor;
    }

    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    double getHeatLoss();

private:
    double surfaceArea_;
    double ambientTemperature_;
    double surfaceTemperature_;
    double windVelocity_;
    double surfaceEmissivity_;
    double conditionFactor_;
    double correctionFactor_;

    double heatLoss_;
};

#endif //AMO_SUITE_WALLLOSSES_H
