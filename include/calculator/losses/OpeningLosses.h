/**
 * @file
 * @brief Calculator for opening heat losses
 *
 * This contains the inputs for calculating an opening heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_SUITE_OPENINGLOSSES_H
#define AMO_SUITE_OPENINGLOSSES_H

/**
 * Opening Losses class
 * Contains all the properties of an opening loss.
 * Used to calculate the heat loss caused by heat transfer from the openings on equipment to the surrounding.
 * Only considers thermal radiation losses due to exposure of furnace to the surroundings.
 */
class OpeningLosses {
public:

    ///OpeningShape enum claaa
    enum class OpeningShape {
        CIRCULAR,   ///<
        RECTANGULAR ///<
    };

    /**
	 * Constructor for a rectangular opening
	 * @param emissivity double, emissivity - unitless
	 * @param diameterLength double, length of openings in inches
     * @param widthHeight double, height of openings in inches
	 * @param thickness double, furnace wall thickness in inches
	 * @param ratio double, ratio
	 * @param ambientTemperature double, ambient temperature in °F
	 * @param insideTemperature double, inside temperature in °F
	 * @param percentTimeOpen double, amount of time open as a %
	 * @param viewFactor double, view factor - unitless
	 * @return nothing
	 */
    OpeningLosses(double emissivity,
                  double diameterLength,
                  double widthHeight,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor)
            : emissivity_(emissivity),
              diameter_(diameterLength),
              width_(widthHeight),
              thickness_(thickness), ratio_(ratio),
              ambientTemperature_(ambientTemperature),
              insideTemperature_(insideTemperature),
              percentTimeOpen_(percentTimeOpen),
              viewFactor_(viewFactor),
              openingShape_(OpeningShape::RECTANGULAR),
              heatLoss_(0.0)
    {}

   /**
    * Constructor for a circular opening
    * @param emissivity double, emissivity - unitless
    * @param diameterLength double, length of opening in inches
    * @param thickness double, furnace wall thickness in inches
    * @param ratio double, ratio
    * @param ambientTemperature double, ambient temperature in °F
    * @param insideTemperature double, inside temperature in °F
    * @param percentTimeOpen double, amount of time open as %
    * @param viewFactor double, view factor - unitless
    * @return nothing
    */
    OpeningLosses(double emissivity,
                  double diameterLength,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor)
            : emissivity_(emissivity),
              diameter_(diameterLength),
              thickness_(thickness), ratio_(ratio),
              ambientTemperature_(ambientTemperature),
              insideTemperature_(insideTemperature),
              percentTimeOpen_(percentTimeOpen),
              viewFactor_(viewFactor),
              openingShape_(OpeningShape::CIRCULAR),
              heatLoss_(0.0)
    {   }

    /**
    * Constructor for a circular opening
    * @param diameterLength double, length of opening in inches
    * @param thickness double, furnace wall thickness in inches
    * @param ratio double, ratio
    * @param ambientTemperature double, ambient temperature in °F
    * @param insideTemperature double, inside temperature in °F
    * @param percentTimeOpen double, amount of time open as %
    * @param viewFactor double, view factor - unitless
     * @param openingShape OpeningShape, classification of shape of opening
    * @return nothing
    */
    OpeningLosses(double diameterLength,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor,
                  OpeningShape openingShape)
            : diameter_(diameterLength),
              thickness_(thickness), ratio_(ratio),
              ambientTemperature_(ambientTemperature),
              insideTemperature_(insideTemperature),
              percentTimeOpen_(percentTimeOpen),
              viewFactor_(viewFactor),
              openingShape_(openingShape),
              heatLoss_(0.0)
    {
        if (openingShape == OpeningShape::CIRCULAR) {
            diameter_ = diameterLength;
        } else {
            width_ = diameterLength;
        }
    }

    /**
    * Constructor for a circular opening
    * @param diameterLength double, length of opening in inches
    * @param thickness double, furnace wall thickness in inches
    * @param ambientTemperature double, ambient temperature in °F
    * @param insideTemperature double, inside temperature in °F
    * @param percentTimeOpen double, amount of time open as %
     * @param openingShape OpeningShape, classification of shape of opening
    * @return nothing
    */
    OpeningLosses(double diameterLength,
                  double thickness,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  OpeningShape openingShape)
            : diameter_(diameterLength),
              thickness_(thickness),
              ambientTemperature_(ambientTemperature),
              insideTemperature_(insideTemperature),
              percentTimeOpen_(percentTimeOpen),
              openingShape_(openingShape),
              heatLoss_(0.0)
    {
        if (openingShape == OpeningShape::CIRCULAR) {
            diameter_ = diameterLength;
        } else {
            width_ = diameterLength;
        }
        ratio_ = diameterLength / thickness_;
//        ratio_ = minimumOf(diameterLength, width) / thickness_ ?
    }


    OpeningLosses() = default;

    /**
     * Gets the emissivity
     *
     * @return double, emissivity - unitless
     */
    double getEmissivity() const {
        return emissivity_;
    }


    /**
     * Sets the emissivity
     *
     * @param emissivity double, emissivity - unitless
     *
     * @return nothing
     */
    void setEmissivity(double emissivity) {
        emissivity_ = emissivity;
    }


    /**
     * Gets the diameter of opening
     *
     * @return double, diameter of opening in inches
     */
    double getDiameter() const {
        return diameter_;
    }


    /**
     * Sets the diameter of the opening
     *
     * @param diameter double, diameter of opening in inches
     *
     * @return nothing
     */
    void setDiameter(double diameter) {
        diameter_ = diameter;
    }

    /**
     * Gets the width of the opening
     *
     * @return double, width of opening in inches
     */
    double getWidth() const {
        return width_;
    }

    /**
     * Sets the width of opening
     *
     * @param width double, width of opening in inches
     *
     * @return nothing
     */
    void setWidth(double width) {
        width_ = width;
    }

    /**
     * Gets the furnace wall thickness
     *
     * @return double, furnace wall thickness in inches
     */
    double getThickness() const {
        return thickness_;
    }

    /**
     * Sets the furnace wall thickness
     *
     * @param thickness double, furnace wall thickness in inches
     *
     * @return nothing
     */
    void setThickness(double thickness) {
        thickness_ = thickness;
    }

    /**
     * Gets the ratio
     *
     * @return double, ratio - unitless
     */
    double getRatio() const {
        return ratio_;
    }

    /**
     * Sets the ratio
     *
     * @param ratio double, ratio - unitless
     *
     * @return nothing
     */
    void setRatio(double ratio) {
        ratio_ = ratio;
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
     * Gets the inside temperature
     *
     * @return double, inside temperature in °F
     */
    double getInsideTemperature() const {
        return insideTemperature_;
    }

    /**
     * Sets the inside temperature
     *
     * @param insideTemperature double, inside temperature in °F
     *
     * @return nothing
     */
    void setInsideTemperature(double insideTemperature) {
        insideTemperature_ = insideTemperature;
    }

    /**
     * Gets the percentage of time open
     *
     * @return double, amount of time open as %
     */
    double getPercentTimeOpen() const {
        return percentTimeOpen_;
    }

    /**
     * Sets the percentage of time open
     *
     * @param percentTimeOpen double, amount of time open as a %
     *
     * @return nothing
     */
    void setPercentTimeOpen(double percentTimeOpen) {
        percentTimeOpen_ = percentTimeOpen;
    }

    /**
     * Gets the view factor
     *
     * @return double, view factor - unitless
     */
    double getViewFactor() const {
        return viewFactor_;
    }

    /**
     * Sets the view factor
     *
     * @param viewFactor double, view factor - unitless
     *
     * @return nothing
     */
    void setViewFactor(double viewFactor) {
        viewFactor_ = viewFactor;
    }

    /**
     * Gets the opening shape
     *
     * @return OpeningShape, classification of shape of opening
     */
    OpeningShape getOpeningShape() const {
        return openingShape_;
    }

    /**
     * Sets the opening shape
     *
     * @param openingShape OpeningShape, classification of shape of opening
     *
     * @return nothing
     */
    void setOpeningShape(OpeningShape openingShape) {
        openingShape_ = openingShape;
    }

    /**
     * Gets the heat loss
     *
     * @return double, heat loss in btu/cycle
     */
    double getHeatLoss();

private:
    double emissivity_ = 0.95;
    double diameter_;
    double width_;
    double thickness_;
    double ratio_;
    double ambientTemperature_;
    double insideTemperature_;
    double percentTimeOpen_;
    double viewFactor_;
    OpeningShape openingShape_;

    double heatLoss_;

};
#endif //AMO_SUITE_OPENINGLOSSES_H
