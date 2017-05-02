/**
 * @file
 * @brief Calculator for heat required for slag - other material losses
 *
 * This contains the inputs for calculating a the heat loss for slag - other material.
 * Only electrotechnologies.
 *
 *
 * totalHeat = weight * specificHeat * (finalTemp - initialTemp);
 * totalHeat = totalHeat * correctionFactor;
 *
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_SUITE_SLAGOTHERMATERIAL_H
#define AMO_SUITE_SLAGOTHERMATERIAL_H


class SlagOtherMaterial {
public:
    /**
     * Constructor for the slag - other material heat loss with all inputs specified
     *
     * @param weight Lb/cycle
     * @param inletTemperature Inlet temperature of gasses in °F
     * @param outletTemperature Outlet temperature of gasses in °F
     * @param specificHeat Specific heat of material at average air temperature in Btu/(lb - °F)
     * @param correctionFactor Correction factor
     * @return nothing
     *
     * */
    SlagOtherMaterial(double weight,
               double inletTemperature,
               double outletTemperature,
               double specificHeat,
               double correctionFactor)
            : weight_(weight),
              inletTemperature_(inletTemperature),
              outletTemperature_(outletTemperature),
              specificHeat_(specificHeat),
              correctionFactor_(correctionFactor)
    {
        totalHeat_ = 0.0;
    }

    SlagOtherMaterial() = default;

    double getWeight() const {
        return weight_;
    }

    void setWeight(double weight) {
        weight_ = weight;
    }

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
    double weight_;
    double inletTemperature_;
    double outletTemperature_;
    double specificHeat_;
    double correctionFactor_ = 1.0;
    // Out value
    double totalHeat_;
};


#endif //AMO_SUITE_SLAGOTHERMATERIAL_H
