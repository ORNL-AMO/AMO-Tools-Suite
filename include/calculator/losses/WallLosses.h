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
#define RAD_CONSTANT 460.0

#include <string>

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
    {
        heatLoss_ = 0.0;
    }

    WallLosses() = default;

    /**
     * Gets the total outside surface area
     *
     * @return double, total outside surface area in ft^2
     */
    double getSurfaceArea() const {
        return surfaceArea_;
    }

    /**
     * Sets the total outside surface area
     *
     * @param surfaceArea double, surface area in ft^2
     *
     * @return nothing
     */
    void setSurfaceArea(double surfaceArea) {
        surfaceArea_ = surfaceArea;
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
     * Gets the average surface temperature (measured)
     *
     * @return double, average surface temperature (measured) in °F
     */
    double getSurfaceTemperature() const {
        return surfaceTemperature_;
    }

    /**
     * Sets the average surface temperature (measured)
     *
     * @param surfaceTemperature double, average surface temperature (measured) in °F
     *
     * @return nothing
     */
    void setSurfaceTemperature(double surfaceTemperature) {
        surfaceTemperature_ = surfaceTemperature;
    }

    /**
     * Gets the wind velocity
     *
     * @return double, wind velocity in miles/hr
     */
    double getWindVelocity() const {
        return windVelocity_;
    }

    /**
     * Sets the wind velocity
     *
     * @param windVelocity double, wind velocity in miles/hr
     *
     * @return nothing
     */
    void setWindVelocity(double windVelocity) {
        windVelocity_ = windVelocity;
    }

    /**
     * Gets the surface emissivity (Typical - 0.9)
     *
     * @return double, surface emissivity - unitless
     */
    double getSurfaceEmissivity() const {
        return surfaceEmissivity_;
    }

    /**
     * Sets the surafce emissivity (Typical - 0.9)
     *
     * @param surfaceEmissivity double, surface emissivity - unitless
     *
     * @return nothing
     */
    void setSurfaceEmissivity(double surfaceEmissivity) {
        surfaceEmissivity_ = surfaceEmissivity;
    }

    /**
     * Gets the condition factor. The condition factor is the surface shape/orientation factor.
     *
     * @return double, condition factor
     */
    double getConditionFactor() const {
        return conditionFactor_;
    }

    /**
     * Sets the condition factor. The condition factor is the surface shape/orientation factor.
     *
     * @param conditionFactor double, condition factor
     *
     * @return nothing
     */
    void setConditionFactor(double conditionFactor) {
        conditionFactor_ = conditionFactor;
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
     * Calculates the wall heat loss
     *
     * @return double, wall heat loss in btu/hr
     */
    double getHeatLoss();

    /**
     * Gets the description of hte surface
     *
     * @return string, description of surface
     */
    std::string getSurface() const {
        return surface_;
    }

    /**
     * Sets the description of surface
     *
     * @param surface string const&, description of surface
     *
     * @return nothing
     */
    void setSurface(std::string const & surface) {
        surface_ = surface;
    }

    /**
     * Gets the ID of surface
     *
     * @return double, ID of surface
     */
    double getID() const {
        return this->id;
    }

    /**
     * Sets the ID of surface
     *
     * @param id const int, ID of surface
     *
     * @return nothing
     */
    void setID(const int id) {
        this->id = id;
    }

    ///bool operator
    bool operator == (const WallLosses& rhs) const
    {
        return conditionFactor_ == rhs.conditionFactor_ &&
               surface_ == rhs.surface_ && id == rhs.id;
    }

    ///bool operator
    bool operator != (const WallLosses& rhs) const
    {
        return !(*this == rhs);
    }

private:
    std::string surface_ = "Unknown";
    double id = 0;

    //in values
    double surfaceArea_;
    double ambientTemperature_;
    double surfaceTemperature_;
    double windVelocity_;
    double surfaceEmissivity_;
    double conditionFactor_;
    double correctionFactor_;

    ///out values
    double heatLoss_;


    friend class SQLite;

    /**
     * Constructor for the surface shape/orientation factor with subset of inputs specified.
     *
     * @param surface string, description of the surface
     * @param conditionFactor double, condition factor
     *
     * */
    WallLosses(
            std::string const & surface,
            double conditionFactor)
            : surface_(surface),
              conditionFactor_(conditionFactor)
    {}

};

#endif //AMO_SUITE_WALLLOSSES_H
