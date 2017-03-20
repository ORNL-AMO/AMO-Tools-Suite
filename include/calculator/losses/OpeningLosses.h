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
class OpeningLosses {
public:
    enum class OpeningShape {
        CIRCULAR,   ///<
        RECTANGULAR ///<
    };

    /**
	 * Constructor for a rectangular opening
	 * @param emissivity
	 * @param diameterLength
     * @param widthHeight
	 * @param thickness
	 * @param ration
	 * @param ambientTemperature
	 * @param insideTemperature
	 * @param percentTimeOpen
	 * @param viewFactor
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
                  double viewFactor,
                  OpeningShape openingShape)
            : emissivity_(emissivity),
              diameter_(diameterLength),
              width_(widthHeight),
              thickness_(thickness), ratio_(ratio),
              ambientTemperature_(ambientTemperature),
              insideTemperature_(insideTemperature),
              percentTimeOpen_(percentTimeOpen),
              viewFactor_(viewFactor),
              openingShape_(openingShape),
              heatLoss_(0.0)
    {}

   /**
    * Constructor for a circular opening
    * @param emissivity
    * @param diameterLength
    * @param thickness
    * @param ration
    * @param ambientTemperature
    * @param insideTemperature
    * @param percentTimeOpen
    * @param viewFactor
    * @return nothing
    */
    OpeningLosses(double emissivity,
                  double diameterLength,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor,
                  OpeningShape openingShape)
            : emissivity_(emissivity),
              diameter_(diameterLength),
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
	        // TODO error here ? Rectangles must use the rectangle constructor?
        }
    }

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

    double getEmissivity() const {
        return emissivity_;
    }

    void setEmissivity(double emissivity) {
        emissivity_ = emissivity;
    }

    double getDiameter() const {
        return diameter_;
    }

    void setDiameter(double diameter) {
        diameter_ = diameter;
    }

    double getWidth() const {
        return width_;
    }

    void setWidth(double width) {
        width_ = width;
    }

    double getThickness() const {
        return thickness_;
    }

    void setThickness(double thickness) {
        thickness_ = thickness;
    }

    double getRatio() const {
        return ratio_;
    }

    void setRatio(double ratio) {
        ratio_ = ratio;
    }

    double getAmbientTemperature() const {
        return ambientTemperature_;
    }

    void setAmbientTemperature(double ambientTemperature) {
        ambientTemperature_ = ambientTemperature;
    }

    double getInsideTemperature() const {
        return insideTemperature_;
    }

    void setInsideTemperature(double insideTemperature) {
        insideTemperature_ = insideTemperature;
    }

    double getPercentTimeOpen() const {
        return percentTimeOpen_;
    }

    void setPercentTimeOpen(double percentTimeOpen) {
        percentTimeOpen_ = percentTimeOpen;
    }

    double getViewFactor() const {
        return viewFactor_;
    }

    void setViewFactor(double viewFactor) {
        viewFactor_ = viewFactor;
    }

    OpeningShape getOpeningShape() const {
        return openingShape_;
    }

    void setOpeningShape(OpeningShape openingShape) {
        openingShape_ = openingShape;
    }

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
