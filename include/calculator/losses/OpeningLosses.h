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

#include <functional>
#include <array>

/**
 * Opening Losses class
 * Contains all the properties of an opening loss.
 * Used to calculate the heat loss caused by heat transfer from the openings on equipment to the surrounding.
 * Only considers thermal radiation losses due to exposure of furnace to the surroundings.
 */
class OpeningLosses {
public:
    enum class OpeningShape {
        CIRCULAR,
        RECTANGULAR
    };

    /**
     * Method to calculate viewFactor for circular openings
     * @return double, viewFactor - unitless
     * */
    double calculateViewFactor(OpeningShape shape, double thickness, double diameter);

    /**
     * Method to calculate viewFactor for rectangular openings
     * @return double, viewFactor - unitless
     */
    double calculateViewFactor(OpeningLosses::OpeningShape shape, double thickness, double length, double height);

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
            : emissivity(emissivity),
              diameter(diameterLength),
              width(widthHeight),
              thickness(thickness), ratio(ratio),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              viewFactor(viewFactor),
              openingShape(OpeningShape::RECTANGULAR)
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
    */
    OpeningLosses(double emissivity,
                  double diameterLength,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor)
            : emissivity(emissivity),
              diameter(diameterLength),
              thickness(thickness), ratio(ratio),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              viewFactor(viewFactor),
              openingShape(OpeningShape::CIRCULAR)
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
    */
    OpeningLosses(double diameterLength,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor,
                  OpeningShape openingShape)
            : diameter(diameterLength),
              thickness(thickness), ratio(ratio),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              viewFactor(viewFactor),
              openingShape(openingShape)
    {
        if (openingShape == OpeningShape::CIRCULAR) {
            diameter = diameterLength;
        } else {
            width = diameterLength;
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
    */
    OpeningLosses(double diameterLength,
                  double thickness,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  OpeningShape openingShape)
            : diameter(diameterLength),
              thickness(thickness),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              openingShape(openingShape)
    {
        if (openingShape == OpeningShape::CIRCULAR) {
            diameter = diameterLength;
        } else {
            width = diameterLength;
        }
        ratio = diameterLength / thickness;
//        ratio = minimumOf(diameterLength, width) / thickness ?
    }


    OpeningLosses() = default;

    /**
     * Gets the emissivity
     * @return double, emissivity - unitless
     */
    double getEmissivity() const {
        return emissivity;
    }


    /**
     * Sets the emissivity
     * @param emissivity double, emissivity - unitless
     */
    void setEmissivity(double emissivity) {
        this->emissivity = emissivity;
    }


    /**
     * Gets the diameter of opening
     * @return double, diameter of opening in inches
     */
    double getDiameter() const {
        return diameter;
    }


    /**
     * Sets the diameter of the opening
     * @param diameter double, diameter of opening in inches
     */
    void setDiameter(double diameter) {
        this->diameter = diameter;
    }

    /**
     * Gets the width of the opening
     * @return double, width of opening in inches
     */
    double getWidth() const {
        return width;
    }

    /**
     * Sets the width of opening
     * @param width double, width of opening in inches
     */
    void setWidth(double width) {
        this->width = width;
    }

    /**
     * Gets the furnace wall thickness
     * @return double, furnace wall thickness in inches
     */
    double getThickness() const {
        return thickness;
    }

    /**
     * Sets the furnace wall thickness
     * @param thickness double, furnace wall thickness in inches
     */
    void setThickness(double thickness) {
        this->thickness = thickness;
    }

    /**
     * Gets the ratio
     * @return double, ratio - unitless
     */
    double getRatio() const {
        return ratio;
    }

    /**
     * Sets the ratio
     * @param ratio double, ratio - unitless
     *
     */
    void setRatio(double ratio) {
        this->ratio = ratio;
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
     * Gets the inside temperature
     * @return double, inside temperature in °F
     */
    double getInsideTemperature() const {
        return insideTemperature;
    }

    /**
     * Sets the inside temperature
     * @param insideTemperature double, inside temperature in °F
     */
    void setInsideTemperature(double insideTemperature) {
        this->insideTemperature = insideTemperature;
    }

    /**
     * Gets the percentage of time open
     * @return double, amount of time open as %
     */
    double getPercentTimeOpen() const {
        return percentTimeOpen;
    }

    /**
     * Sets the percentage of time open
     * @param percentTimeOpen double, amount of time open as a %
     */
    void setPercentTimeOpen(double percentTimeOpen) {
        this->percentTimeOpen = percentTimeOpen;
    }

    /**
     * Gets the view factor
     * @return double, view factor - unitless
     */
    double getViewFactor() const {
        return viewFactor;
    }

    /**
     * Sets the view factor
     * @param viewFactor double, view factor - unitless
     */
    void setViewFactor(double viewFactor) {
        this->viewFactor = viewFactor;
    }

    /**
     * Gets the opening shape
     * @return OpeningShape, classification of shape of opening
     */
    OpeningShape getOpeningShape() const {
        return openingShape;
    }

    /**
     * Sets the opening shape
     * @param openingShape OpeningShape, classification of shape of opening
     */
    void setOpeningShape(OpeningShape openingShape) {
        this->openingShape = openingShape;
    }

    /**
     * Gets the heat loss
     * @return double, heat loss in btu/cycle
     */
    double getHeatLoss();

private:
    double emissivity = 0.95;
    double diameter;
    double width;
    double thickness;
    double ratio;
    double ambientTemperature;
    double insideTemperature;
    double percentTimeOpen;
    double viewFactor;
    OpeningShape openingShape;

    double heatLoss = 0;

    const std::array<const std::function< double ( const double thicknessRatio ) >, 8> viewFactorEquations = {
            [](const double tr) { return 1.10000000001829 + 92.8571428570049 * tr - 57.5892857139671 * std::pow(tr, 2) + 15.6249999998005 * std::pow(tr, 3); }, // case 1
            [](const double tr) { return 29.4999999989821 + 26.8416666684161 * tr - 4.35416666785322 * std::pow(tr, 2) - 8.33333330461522E-02 * std::pow(tr, 3) + 0.104166666655532 * std::pow(tr, 4) - 8.33333333686747E-03 * std::pow(tr, 5); }, // case 2
            [](const double tr) { return 3.50000000001719 + 89.5833333332039 * tr - 49.9999999997023 * std::pow(tr, 2) + 10.4166666664804 * std::pow(tr, 3); }, // case 3
            [](const double tr) { return 23.9999999965639 + 39.3916666718743 * tr - 11.6041666697487 * std::pow(tr, 2) + 1.85416666706894 * std::pow(tr, 3) - 0.145833333217932 * std::pow(tr, 4) + 4.16666663902102E-03 * std::pow(tr, 5); }, // case 4
            [](const double tr) { return 2.70000000002409 + 112.678571428391 * tr - 70.9821428567315 * std::pow(tr, 2) + 15.6249999997447 * std::pow(tr, 3); }, // case 5
            [](const double tr) { return 35.4999999992976 + 29.4583333347815 * tr - 4.52083333446976 * std::pow(tr, 2) - 0.687499999606652 * std::pow(tr, 3) + 0.270833333273064 * std::pow(tr, 4) - 2.08333333303721E-02 * std::pow(tr, 5); }, // case 6
            [](const double tr) { return 13.0000000000278 + 123.74999999979 * tr - 99.9999999995182 * std::pow(tr, 2) + 31.249999999699 * std::pow(tr, 3); }, // case 7
            [](const double tr) { return 26.9999999903567 + 64.5666666806646 * tr - 29.9166666745008 * std::pow(tr, 2) + 7.14583333396145 * std::pow(tr, 3) - 0.833333332874441 * std::pow(tr, 4) + 3.74999999085373E-02 * std::pow(tr, 5); }, // case 8
    };
};
#endif //AMO_SUITE_OPENINGLOSSES_H
