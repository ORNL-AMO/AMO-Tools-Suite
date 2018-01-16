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

/**
 * Leakage Losses class
 * Contains all of the properties of a hot gas leakage.
 * Used to calculate the heat loss caused by gases leaving the furnace via openings other then the flue.
 * This calculator should only be used if the furnace is operating at a positive pressure.
 */
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
     */
    LeakageLosses(
            double draftPressure,
            double openingArea,
            double leakageGasTemperature,
            double ambientTemperature,
            double coefficient,
            double specificGravity,
            double correctionFactor)
            : draftPressure(draftPressure),
              openingArea(openingArea),
              leakageGasTemperature(leakageGasTemperature),
              ambientTemperature(ambientTemperature),
              coefficient(coefficient),
              specificGravity(specificGravity),
              correctionFactor(correctionFactor)
    {
        exfiltratedGasesHeatContent = 0.0;
    }

    LeakageLosses() = default;

    /**
     * Gets the furnace draft pressure
     * @return double, draft pressure in inch W.C.
     */
    double getDraftPressure() const {
        return draftPressure;
    }

    /**
     * Sets the furnace draft pressure
     * @param draftPressure double, draft pressure in inch W.C.
     */
    void setDraftPressure(double draftPressure) {
        this->draftPressure = draftPressure;
    }

    /**
     * Gets the opening area
     * @return double, opening area in ft^2
     */
    double getOpeningArea() const {
        return openingArea;
    }

    /**
     * Sets the opening area
     * @param openingArea double, opening area in ft^2
     */
    void setOpeningArea(double openingArea) {
        this->openingArea = openingArea;
    }

    /**
     * Gets the temperature of gases leaking from furnace
     * @return double, leakeage gas temperature in °F
     */
    double getLeakageGasTemperature() const {
        return leakageGasTemperature;
    }

    /**
     * Sets the temperature of gases leaking from furnace
     * @param leakageGasTemperature double, leakage gas temperature in °F
     */
    void setLeakageGasTemperature(double leakageGasTemperature) {
        this->leakageGasTemperature = leakageGasTemperature;
    }

    /**
     * Gets the ambient temperature
     * @return double, ambient temperature in °F
     */
    double getAmbientTemperature() const {
        return ambientTemperature;
    }

    /**
     * Sets the ambient temperature
     * @param ambientTemperature double, ambient temperature in °F
     */
    void setAmbientTemperature(double ambientTemperature) {
        this->ambientTemperature = ambientTemperature;
    }

    /**
     * Gets the coefficient
     * @return double, coefficient - unitless
     */
    double getCoefficient() const {
        return coefficient;
    }

    /**
     * Sets the coefficient
     * @param coefficient double, coefficient - unitless
     */
    void setCoefficient(double coefficient) {
        this->coefficient = coefficient;
    }

    /**
     * Gets the specific gravity
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity;
    }

    /**
     * Sets the specific gravity
     * @param specificGravity double, specific gravity - unitless
     */
    void setSpecificGravity(double specificGravity) {
        this->specificGravity = specificGravity;
    }

    /**
     * Gets the correction factor
     * @return double, correction factor - unitless
     */
    double getCorrectionFactor() const {
        return correctionFactor;
    }

    /**
     * Sets the correction factor
     * @param correctionFactor double, correction factor - unitless
     */
    void setCorrectionFactor(double correctionFactor) {
        this->correctionFactor = correctionFactor;
    }

    /**
     * Gets the exfiltrated gases heat content
     * @return double, exfiltrated gases heat content in btu/hr
     */
    double getExfiltratedGasesHeatContent();

private:
    // In values
    double draftPressure;
    double openingArea;
    double leakageGasTemperature;
    double ambientTemperature;
    double coefficient;
    double specificGravity;
    double correctionFactor;
    // Out value
    double exfiltratedGasesHeatContent;
};
#endif //AMO_SUITE_LEAKAGELOSSES_H
