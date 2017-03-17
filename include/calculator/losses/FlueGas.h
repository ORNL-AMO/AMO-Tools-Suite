/**
 * @file
 * @brief Calculator for flue gas heat losses
 *
 * This contains the inputs for calculating flue gas heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_FLUEGAS_H
#define AMO_SUITE_FLUEGAS_H
class FlueGas {
public:
    /**
     * Constructor for the flue gas losses with all inputs specified
     *
     * @param furnaceDraft Furnace daft in inch W.C
     * @param leakageTemperature Leakage temperature of gasses in °F
     * @param openingArea Opening area of flue in ft²
     * @param leakageTemperature Temperature of leakage gasses in °F
     * @param ambientTemperature Ambient temparture of gasses in °F
     * @param flowCoeeficient Coefficient of discharge double
     * @param specificGravity Specific gravity of flue gasses
     * @param correction Factor
     * @return nothing
     *
     * */
    FlueGas(double furnaceDraft,
            double openingArea,
            double leakageTemperature,
            double ambientTemperature,
            double flowCoefficient,
            double specificGravity,
            double correctionFactor) :
            furnaceDraft_(furnaceDraft),
            openingArea_(openingArea),
            leakageTemperature_(leakageTemperature),
            ambientTemperature_(ambientTemperature),
            flowCoefficient_(flowCoefficient),
            specificGravity_(specificGravity),
            correctionFactor_(correctionFactor) {
        heatLoss_ = 0.0;
    }

    double getFurnaceDraft() const {
        return furnaceDraft_;
    }

    void setFurnaceDraft(double furnaceDraft) {
        furnaceDraft_ = furnaceDraft;
    }

    double getOpeningArea() const {
        return openingArea_;
    }

    void setOpeningArea(double openingArea) {
        openingArea_ = openingArea;
    }

    double getLeakageTemperature() const {
        return leakageTemperature_;
    }

    void setLeakageTemperature(double leakageTemperature) {
        leakageTemperature_ = leakageTemperature;
    }

    double getAmbientTemperature() const {
        return ambientTemperature_;
    }

    void setAmbientTemperature(double ambientTemperature) {
        ambientTemperature_ = ambientTemperature;
    }

    double getFlowCoefficient() const {
        return flowCoefficient_;
    }

    void setFlowCoefficient(double flowCoefficient) {
        flowCoefficient_ = flowCoefficient;
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

    double getHeatLoss();
private:
    // In values
    double furnaceDraft_;
    double openingArea_;
    double leakageTemperature_;
    double ambientTemperature_;
    double flowCoefficient_;
    double specificGravity_;
    double correctionFactor_;
    // Out value
    double heatLoss_;
};
#endif //AMO_SUITE_FLUEGAS_H
