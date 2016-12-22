/**
 * @file
 * @brief Calculator for total energy loss for gas leakages
 *
 * This contains the inputs for calculating energy loss due to gas
 * leakage.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_SUITE_LEAKAGELOSSES_H
#define AMO_SUITE_LEAKAGELOSSES_H
class LeakageLosses {
public:
    LeakageLosses(
            double draftPressure,
            double openingArea,
            double leakageGasTemperature,
            double ambientTemperature,
            double coefficient,
            double specificGravity,
            double correctionFactor)
            : draftPressure_(draftPressure),
              openingArea_(openingArea),
              leakageGasTemperature_(leakageGasTemperature),
              ambientTemperature_(ambientTemperature),
              coefficient_(coefficient),
              specificGravity_(specificGravity),
              correctionFactor_(correctionFactor)
    {}

    LeakageLosses() = default;

    double getDraftPressure() const {
        return draftPressure_;
    }

    void setDraftPressure(double draftPressure) {
        draftPressure_ = draftPressure;
    }

    double getOpeningArea() const {
        return openingArea_;
    }

    void setOpeningArea(double openingArea) {
        openingArea_ = openingArea;
    }

    double getLeakageGasTemperature() const {
        return leakageGasTemperature_;
    }

    void setLeakageGasTemperature(double leakageGasTemperature) {
        leakageGasTemperature_ = leakageGasTemperature;
    }

    double getAmbientTemperature() const {
        return ambientTemperature_;
    }

    void setAmbientTemperature(double ambientTemperature) {
        ambientTemperature_ = ambientTemperature;
    }

    double getCoefficient() const {
        return coefficient_;
    }

    void setCoefficient(double coefficient) {
        coefficient_ = coefficient;
    }

    double getSpecificGravity() const {
        return specificGravity_;
    }

    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    double getExfiltratedGasesHeatContent();

private:
    // In values
    double draftPressure_;
    double openingArea_;
    double leakageGasTemperature_;
    double ambientTemperature_;
    double coefficient_;
    double specificGravity_;
    double correctionFactor_;
    // Out value
    double exfiltratedGasesHeatContent_;
};
#endif //AMO_SUITE_LEAKAGELOSSES_H
