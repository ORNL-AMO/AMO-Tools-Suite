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

/** Rad constant is 460.0 */
#define RAD_CONSTANT 460.0

#include <string>

/**
 * Wall Losses class
 * Contains all of the properties of a wall loss
 * Used to calculate the heat loss caused by heat being transferred from the outer surface of the wall to the surroundings.
 * ASSUMPTIONS:
 *  Surface emissivity is uniform for the entire surface area.
 *  Wind velocity is uniform over the entire surface area.
 */
class WallLosses {
public:

    /**
     * Constructor
     * @param surfaceArea double, total outside surface area in ft^2
     * @param ambientTemperature double, ambient temperature in °F
     * @param surfaceTemperature double, average surface temperature (measured) in °F
     * @param windVelocity double, wind velocity in miles/hr
     * @param surfaceEmissivity double, surface emissivity - unitless
     * @param conditionFactor double, condition factor - unitless
     * @param correctionFactor double, correction factor - unitless
     */
    WallLosses(const double surfaceArea, const double ambientTemperature, const double surfaceTemperature,
               const double windVelocity, const double surfaceEmissivity, const double conditionFactor,
               const double correctionFactor)
            : surfaceArea(surfaceArea),
              ambientTemperature(ambientTemperature),
              surfaceTemperature(surfaceTemperature),
              windVelocity(windVelocity),
              surfaceEmissivity(surfaceEmissivity),
              conditionFactor(conditionFactor),
              correctionFactor(correctionFactor)
    {
        heatLoss = 0.0;
    }

    WallLosses() = default;

    /**
     * Gets the total outside surface area
     * @return double, total outside surface area in ft^2
     */
    double getSurfaceArea() const {
        return surfaceArea;
    }

    /**
     * Sets the total outside surface area
     * @param surfaceArea double, surface area in ft^2
     */
    void setSurfaceArea(const double surfaceArea) {
        this->surfaceArea = surfaceArea;
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
    void setAmbientTemperature(const double ambientTemperature) {
        this->ambientTemperature = ambientTemperature;
    }

    /**
     * Gets the average surface temperature (measured)
     * @return double, average surface temperature (measured) in °F
     */
    double getSurfaceTemperature() const {
        return surfaceTemperature;
    }

    /**
     * Sets the average surface temperature (measured)
     * @param surfaceTemperature double, average surface temperature (measured) in °F
     */
    void setSurfaceTemperature(const double surfaceTemperature) {
        this->surfaceTemperature = surfaceTemperature;
    }

    /**
     * Gets the wind velocity
     * @return double, wind velocity in miles/hr
     */
    double getWindVelocity() const {
        return windVelocity;
    }

    /**
     * Sets the wind velocity
     * @param windVelocity double, wind velocity in miles/hr
     */
    void setWindVelocity(const double windVelocity) {
        this->windVelocity = windVelocity;
    }

    /**
     * Gets the surface emissivity (Typical - 0.9)
     * @return double, surface emissivity - unitless
     */
    double getSurfaceEmissivity() const {
        return surfaceEmissivity;
    }

    /**
     * Sets the surafce emissivity (Typical - 0.9)
     * @param surfaceEmissivity double, surface emissivity - unitless
     */
    void setSurfaceEmissivity(const double surfaceEmissivity) {
        this->surfaceEmissivity = surfaceEmissivity;
    }

    /**
     * Gets the condition factor. The condition factor is the surface shape/orientation factor.
     * @return double, condition factor
     */
    double getConditionFactor() const {
        return conditionFactor;
    }

    /**
     * Sets the condition factor. The condition factor is the surface shape/orientation factor.
     * @param conditionFactor double, condition factor
     */
    void setConditionFactor(const double conditionFactor) {
        this->conditionFactor = conditionFactor;
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
    void setCorrectionFactor(const double correctionFactor) {
        this->correctionFactor = correctionFactor;
    }

    /**
     * Calculates the wall heat loss
     * @return double, wall heat loss in btu/hr
     */
    double getHeatLoss();

    /**
     * Gets the surface description
     * @return string, surface description
     */
    std::string getSurface() const {
        return surface;
    }

    /**
     * Sets the surface description
     * @param surface string , surface description
     */
    void setSurface(std::string surface) {
        this->surface = std::move(surface);
    }

    /**
     * Gets the ID of surface description
     * @return int, ID of surface description
     */
    int getID() const {
        return this->id;
    }

    /**
     * Sets the ID of surface description
     * @param id const int, ID of surface description
     */
    void setID(const int id) {
        this->id = id;
    }

    ///bool operator
    bool operator == (const WallLosses& rhs) const
    {
        return conditionFactor == rhs.conditionFactor &&
               surface == rhs.surface && id == rhs.id;
    }

    ///bool operator
    bool operator != (const WallLosses& rhs) const
    {
        return !(*this == rhs);
    }

private:
    std::string surface = "Unknown";
    ///in value
    double surfaceArea;
    double ambientTemperature;
    double surfaceTemperature;
    double windVelocity;
    double surfaceEmissivity;
    double conditionFactor;
    double correctionFactor;
///out value
    double heatLoss;

    int id = 0;

    friend class SQLite;

    WallLosses(
            std::string surface,
            double conditionFactor)
            : surface(std::move(surface)),
              conditionFactor(conditionFactor)
    {}
};

#endif //AMO_SUITE_WALLLOSSES_H
