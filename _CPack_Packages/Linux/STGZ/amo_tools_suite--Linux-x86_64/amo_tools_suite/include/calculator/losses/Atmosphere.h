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

/** Reference Temperature is 60°F */
#define REFERENCE_TEMPERATURE 60.0

/**
 * Atmosphere class
 * Contains all of the properties of the atmosphere of gases within the furnace.
 * Used to calculate how much heat is used by the atmosphere gases.
 * ASSUMPTIONS:
 *  The atmosphere composition does not change.
 *  There is not heat of reaction (endothermic or exothermic) between the atmosphere and materials inside the furnace.
 * WARNINGS:
 *  If the atmosphere reacts with the material being processed, then its composition changes, and it is necessary to use appropriate correction factors based on new and old composition properties.
 */
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
     *
     * */
    Atmosphere(const double inletTemperature, const double outletTemperature, const double flowRate,
               const double correctionFactor, const double specificHeat)
            : inletTemperature(inletTemperature),
              outletTemperature(outletTemperature),
              flowRate(flowRate),
              correctionFactor(correctionFactor),
              specificHeat(specificHeat)
    {
        totalHeat = 0.0;
    }

    Atmosphere() = default;

    /**
     * Getter for the inlet/initial temperature
     * @return double, inlet/initial temperature in °F
     */
    double getInletTemperature() const {
        return inletTemperature;
    }

    /**
     * Sets the inlet/initial temperature
     * @param inletTemperature double, initial temperature in °F
     */
    void setInletTemperature(const double inletTemperature) {
        this->inletTemperature = inletTemperature;
    }

    /**
     * Getter for the outlet/final temperature
     * @return double, outlet/final temperature in °F
     */
    double getOutletTemperature() const {
        return outletTemperature;
    }

    /**
     * Sets the outlet/final temperature
     * @param outletTemperature double, outlet/final temperature in °F
     */
    void setOutletTemperature(const double outletTemperature) {
        this->outletTemperature = outletTemperature;
    }

    /**
     * Getter for the flow rate
     * @return double, flow rate in scfh
     */
    double getFlowRate() const {
        return flowRate;
    }

    /**
     * Sets the flow rate
     * @param flowRate double, flow rate in scfh
     */
    void setFlowRate(const double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Getter for the correction factor
     * @return double, correction factor - unitless
     */
    double getCorrectionFactor() const {
        return correctionFactor;
    }

    /**
     * Sets the correction factor
     * @param correctionFactor double, correction factor - unitless
     */
    void setCorrectionFactor(const double correctionFactor) {
        this->correctionFactor = correctionFactor;
    }

    /**
     * Getter for the specific heat
     * @return double, specific heat in btu/(scf*°F)
     */
    double getSpecificHeat() const {
        return specificHeat;
    }

    /**
     * Sets the specific heat
     * @param specificHeat double, specific heat in btu/(scf*°F)
     */
    void setSpecificHeat(const double specificHeat) {
        this->specificHeat = specificHeat;
    }

    /**
     * Calculates the total heat loss
     * @return double, total heat loss in btu/hr
     */
    double getTotalHeat();

    /**
     * Gets the name of substance
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance;
    }

    /**
     * Sets the name of substance
     * @param substance string, name of substance
     */
    void setSubstance(std::string substance) {
        this->substance = std::move(substance);
    }

    /**
     * Gets the ID of material
     * @return int, ID of material
     */
    int getID() const {
        return this->id;
    }

    /**
     * Sets the ID of material
     * @param id const int, ID of material
     */
    void setID(const int id) {
        this->id = id;
    }

    ///bool operator
    bool operator == (const Atmosphere& rhs) const
    {
        return specificHeat == rhs.specificHeat &&
               substance == rhs.substance && id == rhs.id;
    }

    ///bool operator
    bool operator != (const Atmosphere& rhs) const
    {
        return !(*this == rhs);
    }

private:
    // In values
    double inletTemperature;
    double outletTemperature;
    double flowRate;
    double correctionFactor;
    double specificHeat;

    std::string substance = "Unknown";
    int id = 0;
    // Out value

    /// Total heat loss measured in btu/hr
    double totalHeat;

    friend class SQLite;

    /**
     * Constructor for the specific heat with subset of inputs specified.
     * @param substance Name of substance
     * @param specificHeat Specific Heat of  in Btu/(lb*°F)
     * */
    Atmosphere(
            std::string substance,
            double specificHeat)
            : specificHeat(specificHeat),
              substance(std::move(substance))
    {}
};


#endif //AMO_SUITE_ATMOSPHERE_H
