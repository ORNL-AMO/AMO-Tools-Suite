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
    /**
     * Constructor
     * @param draftPressure double, furnace draft pressure in inch W.C.
     * @param openingArea double, opening area in ft^2
     * @param leakageGasTemperature double, temperature of gases leaking from furnace in °F
     * @param ambientTemperature double. ambient temperature in °F
     * @param coefficient double, coefficient - unitless
     * @param specificGravity double, specific gravity - unitless
     * @param correctionFactor double, correction factor - unitless
     * @return nothing
     */
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
    {
        exfiltratedGasesHeatContent_ = 0.0;
    }

    LeakageLosses() = default;

    /**
     * Gets the furnace draft pressure
     *
     * @return double, draft pressure in inch W.C.
     */
    double getDraftPressure() const {
        return draftPressure_;
    }

    /**
     * Sets the furnace draft pressure
     *
     * @param draftPressure double, draft pressure in inch W.C.
     *
     * @return nothing
     */
    void setDraftPressure(double draftPressure) {
        draftPressure_ = draftPressure;
    }

    /**
     * Gets the opening area
     *
     * @return double, opening area in ft^2
     */
    double getOpeningArea() const {
        return openingArea_;
    }

    /**
     * Sets the opening area
     *
     * @param openingArea double, opening area in ft^2
     *
     * @return nothing
     */
    void setOpeningArea(double openingArea) {
        openingArea_ = openingArea;
    }

    /**
     * Gets the temperature of gases leaking from furnace
     *
     * @return double, leakeage gas temperature in °F
     */
    double getLeakageGasTemperature() const {
        return leakageGasTemperature_;
    }

    /**
     * Sets the temperature of gases leaking from furnace
     *
     * @param leakageGasTemperature double, leakage gas temperature in °F
     *
     * @return nothing
     */
    void setLeakageGasTemperature(double leakageGasTemperature) {
        leakageGasTemperature_ = leakageGasTemperature;
    }

    /**
     * Gets the ambient temperature
     *
     * @return double, ambient temperature in °F
     */
    double getAmbientTemperature() const {
        return ambientTemperature_;
    }

    /**
     * Sets the ambient temperature
     *
     * @param ambientTemperature double, ambient temperature in °F
     *
     * @return nothing
     */
    void setAmbientTemperature(double ambientTemperature) {
        ambientTemperature_ = ambientTemperature;
    }

    /**
     * Gets the coefficient
     *
     * @return double, coefficient - unitless
     */
    double getCoefficient() const {
        return coefficient_;
    }

    /**
     * Sets the coefficient
     *
     * @param coefficient double, coefficient - unitless
     *
     * @return nothing
     */
    void setCoefficient(double coefficient) {
        coefficient_ = coefficient;
    }

    /**
     * Gets teh specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity_;
    }

    /**
     * Sets the specific gravity
     *
     * @param specificGravity double, specific gravity - unitless
     *
     * @return nothing
     */
    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    /**
     * Gets the correction factor
     *
     * @return double, correction factor - unitless
     */
    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    /**
     * Sets the correction factor
     *
     * @param correctionFactor double, correction factor - unitless
     *
     * @return nothing
     */
    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    /**
     * Gets the exfiltrated gases heat content
     *
     * @return double, exfiltrated gases heat content in btu/hr
     */
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
