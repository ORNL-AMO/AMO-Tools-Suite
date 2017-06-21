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


class SlagOtherMaterialLosses {
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
    SlagOtherMaterialLosses(double weight,
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

    SlagOtherMaterialLosses() = default;

    /**
     * Gets the weight discharged
     *
     * @return double, weight discharged in lb/cycle
     */
    double getWeight() const {
        return weight_;
    }

    /**
     * Sets the weight discharged
     *
     * @param weight double, weight discharged in lb/cycle
     *
     * @return nothing
     */
    void setWeight(double weight) {
        weight_ = weight;
    }

    /**
     * Gets inlet temperature
     *
     * @return double, inlet temperature in °F
     */
    double getInletTemperature() const {
        return inletTemperature_;
    }

    /**
     * Sets the inlet temperature
     *
     * @param inletTemperature double, inlet temperature in °F
     *
     * @return nothing
     */
    void setInletTemperature(double inletTemperature) {
        inletTemperature_ = inletTemperature;
    }

    /**
     * Gets the outlet temperature
     *
     * @return double, outlet temperature in °F
     */
    double getOutletTemperature() const {
        return outletTemperature_;
    }

    /**
     * Sets outlet temperature
     *
     * @param outletTemperature double, outlet temperature in °F
     *
     * @return nothing
     */
    void setOutletTemperature(double outletTemperature) {
        outletTemperature_ = outletTemperature;
    }


    /**
     * Gets the correction factor
     *
     * @return double, correction factor
     */
    double getCorrectionFactor() const {
        return correctionFactor_;
    }

    /**
     * Sets correction factor
     *
     * @param correctionFactor double, correction factor
     *
     * @return nothing
     */
    void setCorrectionFactor(double correctionFactor) {
        correctionFactor_ = correctionFactor;
    }

    /**
     * Gets the specific heat of material
     *
     * @return double, specific heat i btu/(lb-°F)
     */
    double getSpecificHeat() const {
        return specificHeat_;
    }

    /**
     * Sets the specific heat of material
     *
     * @param specificHeat double, specific heat of material in btu/(lb-°F)
     *
     * @return nothing
     */
    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
    }

    /**
     * Sets the heat loss
     *
     * @return double, heat loss in kwh/cycle
     */
    void setHeatLoss(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    /**
     * Gets the heat loss
     *
     * @return ndouble, heat loss in kwh/cycle
     */
    double getHeatLoss();


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
