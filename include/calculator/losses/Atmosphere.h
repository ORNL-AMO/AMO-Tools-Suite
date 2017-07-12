/**
 * @file
 * @brief Calculator for heat required for atmosphere
 *
 * This contains the inputs for calculating the heat loss for atmosphere
 * total heat.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <string>

#ifndef AMO_SUITE_ATMOSPHERE_H
#define AMO_SUITE_ATMOSPHERE_H

#define REFERENCE_TEMPERATURE 60.0


class Atmosphere {
public:
    /**
     *
     * Constructor for the atmospheric heat loss with all inputs specified
     *
     * @param inletTemperature double, inlet temperature of gasses in °F
     * @param outletTemperature double, outlet temperature of gasses in °F
     * @param flowRate double, flow rate of gasses in scfh
     * @param correctionFactor double, correction factor - unitless
     * @param specificHeat double, specific heat of gasses at average air temperature in Btu/(scf*°F)
     *
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

    /**
     * Getter for the inlet/initial temperature
     *
     * @return double, inlet/initial temperature in °F
     */
    double getInletTemperature() const {
        return inletTemperature_;
    }

    /**
     * Sets the inlet/initial temperature
     *
     * @param inletTemperature double, initial temperature in °F
     *
     * @return nothing
     */
    void setInletTemperature(double inletTemperature) {
        inletTemperature_ = inletTemperature;
    }

    /**
     * Getter for the outlet/final temperature
     *
     * @return double, outlet/final temperature in °F
     */
    double getOutletTemperature() const {
        return outletTemperature_;
    }

    /**
     * Sets the outlet/final temperature
     *
     * @param outletTemperature double, outlet/final temperature in °F
     *
     * @return nothing
     */
    void setOutletTemperature(double outletTemperature) {
        outletTemperature_ = outletTemperature;
    }

    /**
     * Getter for the flow rate
     *
     * @return double, flow rate in scfh
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Sets the flow rate
     *
     * @param flowRate double, flow rate in scfh
     *
     * @return nothing
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
     * Getter for the correction factor
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
     * Getter for the specific heat
     *
     * @return double, specific heat in btu/(scf*°F)
     */
    double getSpecificHeat() const {
        return specificHeat_;
    }

    /**
     * Sets the specific heat
     *
     * @param specificHeat double, specific heat in btu/(scf*°F)
     *
     * @return nothing
     */
    void setSpecificHeat(double specificHeat) {
        specificHeat_ = specificHeat;
    }

    /**
     * Sets the total heat loss
     *
     * @param totalHeat double, total heat loss in btu/hr
     *
     * @return nothing
     */
    void setTotalHeat(double totalHeat) {
        totalHeat_ = totalHeat;
    }

    /**
     * Calculates the total heat loss
     *
     * @return double, total heat loss in btu/hr
     */
    double getTotalHeat();

    /**
     * Gets the name of substance
     *
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance_;
    }

    /**
     * Sets the name of substance
     *
     * @param substance string const&, name of substance
     *
     * @return nothing
     */
    void setSubstance(std::string const & substance) {
        substance_ = substance;
    }

    /**
     * Gets the ID of material
     *
     * @return double, ID of material
     */
    double getID() const {
        return this->id;
    }

    /**
     * Sets the ID of material
     *
     * @param id const int, ID of material
     *
     * @return nothing
     */
    void setID(const int id) {
        this->id = id;
    }

    ///bool operator
    bool operator == (const Atmosphere& rhs) const
    {
        return specificHeat_ == rhs.specificHeat_ &&
               substance_ == rhs.substance_ && id == rhs.id;
    }

    ///bool operator
    bool operator != (const Atmosphere& rhs) const
    {
        return !(*this == rhs);
    }

private:
    // In values
    double inletTemperature_;
    double outletTemperature_;
    double flowRate_;
    double correctionFactor_;
    double specificHeat_;

    std::string substance_ = "Unknown";
    double id = 0;
    // Out value

    /// Total heat loss measured in btu/hr
    double totalHeat_;

    friend class SQLite;

    /**
     * Constructor for the specific heat with subset of inputs specified.
     *
     * @param substance Name of substance
     * @param specificHeat Specific Heat of  in Btu/(lb*°F)
     *
     * */
    Atmosphere(
            std::string const & substance,
            double specificHeat)
            : specificHeat_(specificHeat),
              substance_(substance)
    {}
};


#endif //AMO_SUITE_ATMOSPHERE_H
